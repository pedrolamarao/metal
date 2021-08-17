// Copyright (C) 2020,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>

// Multiboot2 boot request

namespace multiboot2
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

namespace x86
{
    [[gnu::section(".gdt")]]
    constexpr segment_descriptor global_descriptor_table [6] =
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
    };

    void set_segment_registers ( segment_selector code, segment_selector data )
    {
        set_code_segment_register(code);
        set_data_segment_registers(data);
    }
}

// IA32 IDT

namespace x86
{
    constexpr unsigned interrupt_descriptor_table_size = 256;

    [[gnu::section(".idt")]]
    interrupt_gate_descriptor interrupt_descriptor_table [ interrupt_descriptor_table_size ];

    extern "C"
    [[gnu::used]]
    unsigned volatile interrupted {};

    extern "C"
    void __interrupt_service_routine ();
}

//! Psys test protocol

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};

    [[gnu::used]] unsigned volatile _test_debug {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    using namespace multiboot2;
    using namespace ps;
    using namespace x86;

    // test: boot sanity

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

    _test_control = 10;

    auto interrupt_segment = segment_selector(2, false, 0);
    auto interrupt_access = interrupt_gate_access(true, 0);

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_segment, __interrupt_service_routine, interrupt_access };
    }

    set_interrupt_descriptor_table_register(interrupt_descriptor_table);
    
    // test: did we successfully update the IDT register?

    _test_control = 11;

    auto expected_idtr = system_table_register {
        interrupt_descriptor_table_size * sizeof(interrupt_gate_descriptor),
        reinterpret_cast<size4>(interrupt_descriptor_table)
    };

    auto actual_idtr = get_interrupt_descriptor_table_register();

    if (actual_idtr != expected_idtr) {
        _test_debug = expected_idtr.size;
        _test_debug = expected_idtr.offset;
        _test_debug = actual_idtr.size;
        _test_debug = actual_idtr.offset;
        _test_control = 0;
        return;
    }

    // test: handle one software interrupt

    _test_control = 20;

    interrupt<0x30>();

    if (interrupted != 1) {
        _test_control = 0;
        return;
    }

    // test: handle another software interrupt

    _test_control = 21;

    interrupt<0x31>();

    if (interrupted != 2) {
        _test_control = 0;
        return;
    }

    // test: enable hardware interrupts

    _test_control = 30;

    enable_interrupts();

    _test_control = -1;
    return;
}
