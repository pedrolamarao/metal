// Copyright (C) 2020,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>


// x86-32 architecture.

namespace x86
{
    [[gnu::section(".gdt")]]
    constinit
    segment_descriptor global_descriptor_table [6] =
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
        set_data_segment_register(data);
        set_stack_segment_register(data);
        set_extra_segment_registers(data);
    }

    // Interrupts.

    constexpr unsigned interrupt_descriptor_table_size = 256;

    [[gnu::section(".idt")]]
    constinit
    interrupt_gate_descriptor interrupt_descriptor_table [ interrupt_descriptor_table_size ];

    unsigned interrupted {};

    [[gnu::naked]]
    void interrupt_handler ()
    {
        __asm__
        {
            inc interrupted
            iretd
        }
    }
}

// Psys test protocol.

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
    [[gnu::used]] unsigned volatile _test_debug {};

    void _test_start () { }
    void _test_finish () { }
}

// Psys multiboot2 program.

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

    // test: data structures

    auto interrupt_segment = segment_selector(2, false, 0);

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_segment, interrupt_handler, true, true, 0, true };
    }

    auto& descriptor = interrupt_descriptor_table[0];

    _test_control = 10;
    if (descriptor.type() != 0b1110) {
        _test_debug = descriptor.type();
        _test_control = 0;
        return;
    }

    _test_control = 11;
    if (descriptor.privilege() != 0) {
        _test_debug = descriptor.privilege();
        _test_control = 0;
        return;
    }

    _test_control = 12;
    if (descriptor.is_present() != true) {
        _test_control = 0;
        return;
    }

    _test_control = 13;
    if (descriptor.segment() != interrupt_segment) {
        _test_debug = size2{descriptor.segment()};
        _test_control = 0;
        return;
    }

    _test_control = 14;
    if (descriptor.offset() != reinterpret_cast<size4>(interrupt_handler)) {
        _test_debug = descriptor.offset();
        _test_control = 0;
        return;
    }

    _test_control = 15;
    if (descriptor.is_32bit() != true) {
        _test_control = 0;
        return;
    }

    _test_control = 16;
    if (descriptor.must_cli() != true) {
        _test_control = 0;
        return;
    }

    // set the IDT register

    _test_control = 20;

    set_interrupt_descriptor_table_register(interrupt_descriptor_table);
    
    // test: did we successfully update the IDT register?

    _test_control = 21;

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

    _test_control = 30;

    interrupt<0x30>();

    if (interrupted != 1) {
        _test_control = 0;
        return;
    }

    // test: handle another software interrupt

    _test_control = 31;

    interrupt<0x31>();

    if (interrupted != 2) {
        _test_control = 0;
        return;
    }

    // test: enable hardware interrupts

    _test_control = 40;

    sti();

    _test_control = -1;
    return;
}

// Multiboot2 loader.

namespace multiboot2
{
    extern
    unsigned char stack [ 0x4000 ];

    extern "C"
    [[gnu::naked]]
    void __multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset stack + 0x4000
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