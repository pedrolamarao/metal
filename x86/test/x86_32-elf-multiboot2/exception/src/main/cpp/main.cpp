// Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>


// x86-32 architecture.

namespace x86
{
    // Segments.

    extern segment_descriptor global_descriptor_table [8];

    void set_segment_registers ( segment_selector code, segment_selector data );

    // Interrupts.

    extern interrupt_gate_descriptor interrupt_descriptor_table [256];

    extern "C" void __raise_DE ();
    unsigned __x86_interrupt_00_counter {};
    void __x86_interrupt_00 ();

    void __raise_BP ();
    unsigned __x86_interrupt_03_counter {};
    void __x86_interrupt_03 ();

    void __raise_OF ();
    unsigned __x86_interrupt_04_counter {};
    void __x86_interrupt_04 ();

    extern "C" void __raise_BR ();
    unsigned __x86_interrupt_05_counter {};
    void __x86_interrupt_05 ();

    extern "C" void __raise_UD ();
    unsigned __x86_interrupt_06_counter {};
    void __x86_interrupt_06 ();

    extern "C" void __raise_NP ();
    unsigned __x86_interrupt_0B_counter {};
    void __x86_interrupt_0B ();

    extern "C" void __raise_GP ();
    unsigned __x86_interrupt_0D_counter {};
    void __x86_interrupt_0D ();

    unsigned __x86_interrupt_FF_counter {};
    void __x86_interrupt_FF ();
}

// Psys test protocol.

namespace
{
    extern "C" [[gnu::used]] unsigned volatile _test_control {};
    extern "C" [[gnu::used]] unsigned volatile _test_debug {};

    extern "C" void _test_start () { }
    extern "C" void _test_finish () { }
}

// Psys multiboot2 program.

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
    __raise_DE();
    if (__x86_interrupt_00_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 03: breakpoint

    _test_control = 1003;
    __raise_BP();
    if (__x86_interrupt_03_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 04: integer overflow

    _test_control = 1004;
    __raise_OF();
    if (__x86_interrupt_04_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 05: bound range exceeded

    _test_control = 1005;
    __raise_BR();
    if (__x86_interrupt_05_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 06: undefined instruction

    _test_control = 1006;
    __raise_UD();
    if (__x86_interrupt_06_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 0B: segment not present

    _test_control = 1000 + 0x0B;
    __raise_NP();
    if (__x86_interrupt_0B_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 0D: general protection fault

    _test_control = 1000 + 0x0D;
    __raise_GP();
    if (__x86_interrupt_0D_counter == 0) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}

// x86-32 architecture.

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

    [[gnu::section(".idt")]]
    constinit
    interrupt_gate_descriptor interrupt_descriptor_table [256] =
    { };

    // Fault handlers return to the very same location which caused the fault.
    // If the handler can't solve the fault, the program must terminate.
    // If the handler solves the fault, the program must retry the instruction.

    // In these tests, all faults are solved by rewriting the program.
    // Offending instructions are rewritten with NOPs.
    // It is assumed safe to write four NOPs into "bad" locations.

    [[gnu::naked]] void __raise_DE_bad ()
    {
        // divide zero by zero

        __asm__
        {
            div eax, eax
            nop
            nop
            nop
            popad
            ret
        }
    }

    [[gnu::naked]] void __raise_DE ()
    {
        // prepare zero divisor

        __asm__
        {
            pushad
            mov eax, 0
            jmp __raise_DE_bad
        }
    }

    [[gnu::naked]] void __x86_interrupt_00 ()
    {
        __asm__
        {
             // "fix" caller: rewrite with NOPS
             mov __raise_DE_bad, 0x90909090
             // increment interrupt counter
             inc __x86_interrupt_00_counter
             iretd
        }
    }

    void __raise_BP ()
    {
        // `int3` raises BP

        __asm__ volatile ( "int3" : : : );
    }

    [[gnu::naked]] void __x86_interrupt_03 ()
    {
        __asm__
        {
             // increment interrupt counter
             inc __x86_interrupt_03_counter
             iretd
        }
    }

    void __raise_OF ()
    {
        // increment 0x7F overflows, `into` raises OF

        unsigned char value { 0x7F };
        __asm__ volatile ( "incb %0 \n into" : : "r"(value) : );
    }

    [[gnu::naked]] void __x86_interrupt_04 ()
    {
        __asm__
        {
             // increment interrupt counter
             inc __x86_interrupt_04_counter
             iretd
        }
    }

    [[gnu::naked]] void __raise_BR_bad ()
    {
        // `bound` index 4 bounds [0, 1] raises BR

        __asm__
        {
            bound eax, [esp]
            nop
            nop
            nop
            add esp, 8
            popad
            ret
        }
    }

    [[gnu::naked]] void __raise_BR ()
    {
        // prepare bounds [0, 1] and index 4

        __asm__
        {
            pushad
            mov eax, 1
            push eax
            mov eax, 0
            push eax
            mov eax, 4
            jmp __raise_BR_bad
        }
    }

    [[gnu::naked]] void __x86_interrupt_05 ()
    {
        __asm__
        {
             // "fix" caller: rewrite with NOPS
             mov __raise_BR_bad, 0x90909090
             // increment interrupt counter
             inc __x86_interrupt_05_counter
             iretd
        }
    }

    [[gnu::naked]] void __raise_UD_bad ()
    {
        // `ud2` raises UD

        __asm__
        {
            ud2
            nop
            nop
            nop
            popad
            ret
        }
    }

    [[gnu::naked]] void __raise_UD ()
    {
        __asm__
        {
            pushad
            jmp __raise_UD_bad
        }
    }

    [[gnu::naked]] void __x86_interrupt_06 ()
    {
        __asm__
        {
             // "fix" caller: rewrite with NOPS
             mov __raise_UD_bad, 0x90909090
             // increment interrupt counter
             inc __x86_interrupt_06_counter
             iretd
        }
    }

    [[gnu::naked]] void __raise_NP_bad ()
    {
        // storing non-present data segment into GS raises `NP`

        __asm__
        {
            mov gs, bx
            nop
            nop
            nop
            mov gs, ax
            popad
            ret
        }

        // restore GS before leaving
    }

    [[gnu::naked]] void __raise_NP ()
    {
        // prepare segment selector for non-present data segment

        __asm__
        {
            pushad
            mov ax, gs
            mov bx, 0x30
            jmp __raise_NP_bad
        }

        // save GS before leaving
    }

    [[gnu::naked]] void __x86_interrupt_0B ()
    {
        __asm__
        {
             // "fix" caller: rewrite with NOPS
             mov __raise_NP_bad, 0x90909090
             // increment interrupt counter
             inc __x86_interrupt_0B_counter
             // discard error code from stack
             add esp, 4
             iretd
        }
    }

    [[gnu::naked]] void __raise_GP_bad ()
    {
        // storing non-readable code segment into GS raises `GP`

        __asm__
        {
            mov gs, bx
            nop
            nop
            nop
            mov gs, ax
            popad
            ret
        }

        // restore GS before leaving
    }

    [[gnu::naked]] void __raise_GP ()
    {
        // prepare segment selector for non-readable code segment

        __asm__
        {
            pushad
            mov ax, gs
            mov bx, 0x38
            jmp __raise_GP_bad
        }

        // save GS before leaving
    }

    [[gnu::naked]] void __x86_interrupt_0D ()
    {
        __asm__
        {
             // "fix" caller: rewrite with NOPS
             mov __raise_GP_bad, 0x90909090
             // increment interrupt counter
             inc __x86_interrupt_0D_counter
             // discard error code from stack
             add esp, 4
             iretd
        }
    }

    [[gnu::naked]] void __x86_interrupt_FF ()
    {
        __asm__
        {
             // increment interrupt counter
             inc __x86_interrupt_FF_counter
             iretd
        }
    }
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