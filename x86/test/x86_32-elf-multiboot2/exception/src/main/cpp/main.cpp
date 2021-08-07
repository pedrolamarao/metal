// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>


namespace
{
    using namespace multiboot2;

    struct request_type
    {
        header_prologue prologue;
        end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constexpr request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { },
    };
}

// IA32 GDT

namespace
{
    using namespace x86;

    [[gnu::section(".gdt")]]
    constexpr segment_descriptor global_descriptor_table [5] =
    {
        { },
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
    };
}

// IA32 IDT

namespace
{
    using gate_descriptor = x86::interrupt_gate_descriptor;

    [[gnu::section(".idt")]]
    gate_descriptor interrupt_descriptor_table [256] =
    { };

    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_00_counter {};
    extern "C" void _x86_interrupt_00 ();

    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_03_counter {};
    extern "C" void _x86_interrupt_03 ();

    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_04_counter {};
    extern "C" void _x86_interrupt_04 ();

    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_05_counter {};
    extern "C" void _x86_interrupt_05 ();

    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_06_counter {};
    extern "C" void _x86_interrupt_06 ();

    extern "C" [[gnu::used]] unsigned volatile _x86_interrupt_FF_counter {};
    extern "C" void _x86_interrupt_FF ();
}

//! Psys test protocol

namespace
{
    extern "C" [[gnu::used]] unsigned volatile _test_control {};

    extern "C" void _test_trap_DE ();
    extern "C" void _test_trap_BP ();
    extern "C" void _test_trap_OF ();
    extern "C" void _test_trap_BR ();
    extern "C" void _test_trap_UD ();
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    x86::set_global_descriptor_table(global_descriptor_table);

    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, _x86_interrupt_FF, interrupt_gate_access(true, 0) };
    }
    interrupt_descriptor_table[0] = { 0x8, _x86_interrupt_00, interrupt_gate_access(true, 0) };
    interrupt_descriptor_table[3] = { 0x8, _x86_interrupt_03, interrupt_gate_access(true, 0) };
    interrupt_descriptor_table[4] = { 0x8, _x86_interrupt_04, interrupt_gate_access(true, 0) };
    interrupt_descriptor_table[5] = { 0x8, _x86_interrupt_05, interrupt_gate_access(true, 0) };
    interrupt_descriptor_table[6] = { 0x8, _x86_interrupt_06, interrupt_gate_access(true, 0) };

    x86::set_interrupt_descriptor_table(interrupt_descriptor_table, 256);

    // test exception 00 : division error

    _test_control = 1000;
    _test_trap_DE();
    if (_x86_interrupt_00_counter == 0) {
        _test_control = 0;
        return;
    }

    // test exception 03 : breakpoint

    _test_control = 1003;
    _test_trap_BP();
    if (_x86_interrupt_03_counter == 0) {
        _test_control = 0;
        return;
    }

    // test exception 04 : integer overflow

    _test_control = 1004;
    _test_trap_OF();
    if (_x86_interrupt_04_counter == 0) {
        _test_control = 0;
        return;
    }

    // test exception 05 : bound range exceeded

    _test_control = 1005;
    _test_trap_BR();
    if (_x86_interrupt_05_counter == 0) {
        _test_control = 0;
        return;
    }

    // test exception 06 : undefined instruction

    _test_control = 1006;
    _test_trap_UD();
    if (_x86_interrupt_06_counter == 0) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
