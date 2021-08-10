// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>
#include <x86/port.h>

#include <pc/pic.h>


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

    // test: software interrupt increments counter

    _test_control = 2;

    x86::interrupt<48>();

    if (_x86_interrupt_free_counter == 0) {
        _test_control = 0;
        return;
    }

    // pic: initialize

    _test_control = 3;

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

    // pic: unmask IRQ 0

    master.ocw1(0xFE);
    slave.ocw1(0xFF);

    // test: hardware interrupt increments counter
    // assumption: PIT shall interrupt IRQ 0

    asm volatile ("sti");

    _test_control = 4;

    while (_x86_interrupt_master_counter == 0) {
        // wait!
    }

    // test: hardware interrupt increments counter
    // assumption: PIT shall interrupt IRQ 0 again

    asm volatile ("cli");

    _x86_interrupt_master_counter = 0;

    asm volatile ("sti");

    _test_control = 5;

    while (_x86_interrupt_master_counter == 0) {
        // wait!
    }

    _test_control = -1;
    return;
}
