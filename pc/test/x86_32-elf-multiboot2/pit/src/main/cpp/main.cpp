// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>
#include <x86/port.h>

#include <pc/pic.h>
#include <pc/pit.h>


//! Multiboot2 minimal request for ELF program

namespace
{
    struct request_type
    {
        multiboot2::header_prologue prologue;
        multiboot2::end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constexpr request_type request =
    {
        { multiboot2::architecture_type::x86, sizeof(request), },
        { },
    };
}

//! x86 protected-mode GDT

namespace
{
    [[gnu::section(".gdt")]]
    constexpr x86::segment_descriptor global_descriptor_table [5] =
    {
        { },
        { 0, 0xFFFFFFFF, x86::code_segment_access(true, false, 0), x86::segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, x86::data_segment_access(true, false, 0), x86::segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, x86::code_segment_access(true, false, 3), x86::segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, x86::data_segment_access(true, false, 3), x86::segment_granularity(false, true, true) },
    };
}

//! x86 protected-mode IDT

namespace
{
    [[gnu::section(".idt")]]
    x86::interrupt_gate_descriptor interrupt_descriptor_table [256] =
    { };

    extern "C" void _x86_exception ();
    extern "C" [[gnu::used]] unsigned volatile _x86_exception_counter {};

    extern "C" void _x86_interrupt_master ();
    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_master_counter {};

    extern "C" void _x86_interrupt_slave ();
    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_slave_counter {};

    extern "C" void _x86_interrupt_free ();
    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_free_counter {};
}

//! Psys test protocol

namespace
{
    extern "C" [[gnu::used]] unsigned volatile _test_control {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    _test_control = 1;

    // gdt

    x86::set_global_descriptor_table(global_descriptor_table);
    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

    // idt

    for (auto i = 0U, j = 32U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, _x86_exception, x86::interrupt_gate_access(true, 0) };
    }
    for (auto i = 32U, j = 40U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, _x86_interrupt_master, x86::interrupt_gate_access(true, 0) };
    }
    for (auto i = 40U, j = 48U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, _x86_interrupt_slave, x86::interrupt_gate_access(true, 0) };
    }
    for (auto i = 48U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, _x86_interrupt_free, x86::interrupt_gate_access(true, 0) };
    }
    x86::set_interrupt_descriptor_table(interrupt_descriptor_table, 256);

    // pic

    auto master = pc::master_pic<x86::port>::create();
    auto slave  = pc::slave_pic<x86::port>::create();

    master.icw1(true, false, true);
    slave.icw1(true, false, true);
    master.icw2(0x20);
    slave.icw2(0x28);
    master.icw3(4);
    slave.icw3(2);
    master.icw4(true, false, pc::pic_buffering::none, false);
    slave.icw4(true, false, pc::pic_buffering::none, false);
    master.ocw1(0xFE);
    slave.ocw1(0xFF);

    // pit

    auto pit = pc::pit<x86::port>::create();

    // test: configure command builder

    _test_control = 2;

    auto configure = pc::pit_configure_command(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::hardware_retriggerable_one_shot, pc::pit_format::binary);
    if (configure != 0b00010010) {
        _test_control = configure;
        _test_control = 0;
        return;
    }

    // test: read_back command builder

    _test_control = 3;

    auto read_back = pc::pit_read_back_command(false, true, pc::pit_counter::zero);
    if (read_back != 0b11010010) {
        _test_control = read_back;
        _test_control = 0;
        return;
    }

    // test: PIT mode 0: configure, read_back
    // assumption: test is faster than counter

    _test_control = 100;

    pit.configure(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::interrupt_on_terminal_count, pc::pit_format::binary);
    pit.counter_0(0);
    pit.read_back(true, false, pc::pit_counter::zero);

    auto actual_100 = pit.counter_0();
    if (actual_100 != 0b00010000) {
        _test_control = 0;
        return;
    }

    // test: PIT mode 1: configure, read_back
    // assumption: test is faster than counter

    _test_control = 101;

    pit.configure(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::hardware_retriggerable_one_shot, pc::pit_format::binary);
    pit.counter_0(0);
    pit.read_back(true, false, pc::pit_counter::zero);

    auto actual_101 = pit.counter_0();
    if (actual_101 != 0b10010010) {
        _test_control = actual_101;
        _test_control = 0;
        return;
    }

    // test: PIT mode 2: configure, read_back
    // assumption: test is faster than counter

    _test_control = 102;

    pit.configure(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::rate_generator, pc::pit_format::binary);
    pit.counter_0(0);
    pit.read_back(true, false, pc::pit_counter::zero);

    auto actual_102 = pit.counter_0();
    if (actual_102 != 0b00010100) { // #TODO: ???
        _test_control = actual_102;
        _test_control = 0;
        return;
    }

    // test: PIT mode 3: configure, read_back
    // assumption: test is faster than counter

    _test_control = 103;

    pit.configure(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::square_wave_generator, pc::pit_format::binary);
    pit.counter_0(0);
    pit.read_back(true, false, pc::pit_counter::zero);

    auto actual_103 = pit.counter_0();
    if (actual_103 != 0b10010110) {
        _test_control = actual_103;
        _test_control = 0;
        return;
    }

    // test: PIT mode 4: configure, read_back
    // assumption: test is faster than counter

    _test_control = 104;

    pit.configure(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::software_triggered_strobe, pc::pit_format::binary);
    pit.counter_0(0);
    pit.read_back(true, false, pc::pit_counter::zero);

    auto actual_104 = pit.counter_0();
    if (actual_104 != 0b00011000) { // #TODO: ???
        _test_control = actual_104;
        _test_control = 0;
        return;
    }

    // test: PIT mode 5: configure, read_back
    // assumption: test is faster than counter

    _test_control = 105;

    pit.configure(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::hardware_triggered_strobe, pc::pit_format::binary);
    pit.counter_0(0);
    pit.read_back(true, false, pc::pit_counter::zero);

    auto actual_105 = pit.counter_0();
    if (actual_105 != 0b00011010) { // #TODO: ???
        _test_control = actual_105;
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
