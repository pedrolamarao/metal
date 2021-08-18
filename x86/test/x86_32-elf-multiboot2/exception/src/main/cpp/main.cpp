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
    constinit
    request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { },
    };
}

// IA32 GDT

namespace x86
{
    [[gnu::section(".gdt")]]
    constinit
    segment_descriptor global_descriptor_table [8] =
    {
        // required null descriptor
        { },
        // unexpected null descriptor!
        { },
        // system flat code descriptor
        { 0, 0xFFFFF, code_segment(true, true, true), 0, true, true, true, true, },
        // system flat data descriptor
        { 0, 0xFFFFF, data_segment(true, true, true), 0, true, true, true, true, },
        // user flat code descriptor
        { 0, 0xFFFFF, code_segment(true, true, true), 3, true, true, true, true, },
        // user flat data descriptor
        { 0, 0xFFFFF, data_segment(true, true, true), 3, true, true, true, true, },
        // test segment: data non-present
        { 0, 0xFFFFF, data_segment(true, true, true), 0, false, true, true, true, },
        // test segment: code execute-only
        { 0, 0xFFFFF, code_segment(true, false, true), 0, true, true, true, true, },
    };

    void set_segment_registers ( segment_selector code, segment_selector data )
    {
        set_code_segment_register(code);
        set_data_segment_register(data);
        set_stack_segment_register(data);
        set_extra_segment_registers(data);
    }
}

// IA32 IDT

namespace x86
{
    [[gnu::section(".idt")]]
    constinit
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

    extern "C" void _test_start () { }
    extern "C" void _test_finish () { }

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

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_selector, __x86_interrupt_FF, true, true, 0, true };
    }

    interrupt_descriptor_table[0x00] = { interrupt_selector, __x86_interrupt_00, true, true, 0, true };
    interrupt_descriptor_table[0x03] = { interrupt_selector, __x86_interrupt_03, true, true, 0, true };
    interrupt_descriptor_table[0x04] = { interrupt_selector, __x86_interrupt_04, true, true, 0, true };
    interrupt_descriptor_table[0x05] = { interrupt_selector, __x86_interrupt_05, true, true, 0, true };
    interrupt_descriptor_table[0x06] = { interrupt_selector, __x86_interrupt_06, true, true, 0, true };
    interrupt_descriptor_table[0x0B] = { interrupt_selector, __x86_interrupt_0B, true, true, 0, true };
    interrupt_descriptor_table[0x0D] = { interrupt_selector, __x86_interrupt_0D, true, true, 0, true };

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

namespace multiboot2
{
    //! Multiboot2 entry point

    extern "C"
    constinit
    unsigned char __multiboot2_stack [ 0x4000 ] {};

    extern "C"
    [[gnu::naked]]
    void __multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset __multiboot2_stack + 0x4000
            xor ecx, ecx
            push ecx
            popf
            call _test_start
            push ebx
            push eax
            call main
            call _test_finish
            __multiboot2_halt:
            hlt
            jmp __multiboot2_halt
        }
    }
}