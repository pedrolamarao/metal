// Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>


namespace multiboot2
{
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

namespace x86
{
    inline namespace details
    {
        constexpr auto granularity = segment_granularity(false, true, true);
    }

    [[gnu::section(".gdt")]]
    constexpr segment_descriptor global_descriptor_table [8] =
    {
        // required null segment
        { },
        // atypical null segment!
        { },
        // system flat code segment
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), granularity },
        // system flat data segment
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), granularity },
        // user flat code segment
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), granularity },
        // user flat data segment
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), granularity },
        // test segment: data non-present
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 0, false), granularity },
        // test segment: code execute-only
        { 0, 0xFFFFFFFF, code_segment_access(false, false, 0), granularity },
    };

    void set_segment_registers ( segment_selector code, segment_selector data )
    {
        auto const ds = data.value();
        set_code_segment_register(code);
        asm volatile ("mov %0, %%ds" : : "r"(ds));
        asm volatile ("mov %0, %%ss" : : "r"(ds));
        asm volatile ("mov %0, %%es" : : "r"(ds));
        asm volatile ("mov %0, %%fs" : : "r"(ds));
        asm volatile ("mov %0, %%gs" : : "r"(ds));
    }
}

// IA32 IDT

namespace x86
{
    [[gnu::section(".idt")]]
    interrupt_gate_descriptor interrupt_descriptor_table [256] =
    { };

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_00_counter {};
    extern "C" void __x86_interrupt_00 ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_03_counter {};
    extern "C" void __x86_interrupt_03 ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_04_counter {};
    extern "C" void __x86_interrupt_04 ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_05_counter {};
    extern "C" void __x86_interrupt_05 ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_06_counter {};
    extern "C" void __x86_interrupt_06 ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_0B_counter {};
    extern "C" void __x86_interrupt_0B ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_0D_counter {};
    extern "C" void __x86_interrupt_0D ();

    extern "C" [[gnu::used]] unsigned volatile __x86_interrupt_FF_counter {};
    extern "C" void __x86_interrupt_FF ();
}

//! Psys test protocol

namespace
{
    extern "C" [[gnu::used]] unsigned volatile _test_control {};

    extern "C" [[gnu::used]] unsigned volatile _test_debug {};

    extern "C" void __test_trap_DE ();
    extern "C" void __test_trap_BP ();
    extern "C" void __test_trap_OF ();
    extern "C" void __test_trap_BR ();
    extern "C" void __test_trap_UD ();
    extern "C" void __test_trap_NP ();
    extern "C" void __test_trap_GP ();
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    using namespace multiboot2;
    using namespace ps;
    using namespace x86;

    // verify boot sanity

    _test_control = 1;

    if (magic != multiboot2::information_magic) {
        _test_control = 0;
        return;
    }

    // set the GDT register and set segment registers

    _test_control = 2;

    set_global_descriptor_table_register(global_descriptor_table);

    set_segment_registers(segment_selector(2, false, 0), segment_selector(3, false, 0));

    // set the IDT register

    _test_control = 3;

    auto interrupt_selector = segment_selector(2, false, 0);
    auto interrupt_access = interrupt_gate_access(true, 0);

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_selector, __x86_interrupt_FF, interrupt_access };
    }

    interrupt_descriptor_table[0x00] = { interrupt_selector, __x86_interrupt_00, interrupt_access };
    interrupt_descriptor_table[0x03] = { interrupt_selector, __x86_interrupt_03, interrupt_access };
    interrupt_descriptor_table[0x04] = { interrupt_selector, __x86_interrupt_04, interrupt_access };
    interrupt_descriptor_table[0x05] = { interrupt_selector, __x86_interrupt_05, interrupt_access };
    interrupt_descriptor_table[0x06] = { interrupt_selector, __x86_interrupt_06, interrupt_access };
    interrupt_descriptor_table[0x0B] = { interrupt_selector, __x86_interrupt_0B, interrupt_access };
    interrupt_descriptor_table[0x0D] = { interrupt_selector, __x86_interrupt_0D, interrupt_access };

    set_interrupt_descriptor_table_register(interrupt_descriptor_table);

    // test: exception 00: division error

    _test_control = 1000;
    __test_trap_DE();
    if (__x86_interrupt_00_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 03: breakpoint

    _test_control = 1003;
    __test_trap_BP();
    if (__x86_interrupt_03_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 04: integer overflow

    _test_control = 1004;
    __test_trap_OF();
    if (__x86_interrupt_04_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 05: bound range exceeded

    _test_control = 1005;
    __test_trap_BR();
    if (__x86_interrupt_05_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 06: undefined instruction

    _test_control = 1006;
    __test_trap_UD();
    if (__x86_interrupt_06_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 0B: segment not present

    _test_control = 1000 + 0x0B;
    __test_trap_NP();
    if (__x86_interrupt_0B_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 0D: general protection fault

    _test_control = 1000 + 0x0D;
    __test_trap_GP();
    if (__x86_interrupt_0D_counter == 0) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
