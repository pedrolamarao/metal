// Copyright (C) 2020,2021,2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/start.h>
#include <psys/test.h>

#include <x86/segments.h>
#include <x86/interrupts.h>

import br.dev.pedrolamarao.metal.psys;

namespace
{
    using namespace x86;

    // Segments.

    struct
    {
        size8                   null_descriptor   {};
        data_segment_descriptor flat_data_segment { 0, 0xFFFFF, true, true, true, 0, true,  0, true,  true };
        code_segment_descriptor flat_code_segment { 0, 0xFFFFF, true, true, true, 0, true,  0, false, true, true };
        data_segment_descriptor bad_data_segment  { 0, 0xFFFFF, true, true, true, 0, false, 0, true,  true };
        code_segment_descriptor bad_code_segment  { 0, 0xFFFFF, true, true, true, 0, true,  0, false, true, true };
    }
    global_descriptor_table;

    static_assert(sizeof(global_descriptor_table) == 40, "unexpected size of global_descriptor_table");

    void set_segment_registers ( segment_selector code, segment_selector data );

    // Interrupts.

    extern short_interrupt_gate_descriptor interrupt_descriptor_table [256];

    void raise_DE ();
    unsigned interrupt_00_counter {};
    void interrupt_00 ();

    void raise_BP ();
    unsigned interrupt_03_counter {};
    void interrupt_03 ();

    void raise_OF ();
    unsigned interrupt_04_counter {};
    void interrupt_04 ();

    void raise_BR ();
    unsigned interrupt_05_counter {};
    void interrupt_05 ();

    void raise_UD ();
    unsigned interrupt_06_counter {};
    void interrupt_06 ();

    void raise_NP ();
    unsigned interrupt_0B_counter {};
    void interrupt_0B ();

    void raise_GP ();
    unsigned interrupt_0D_counter {};
    void interrupt_0D ();

    unsigned interrupt_FF_counter {};
    void interrupt_FF ();
}

void psys::main ()
{
    using namespace ps;
    using namespace x86;

    // set the GDT register and set segment registers

    _test_control = 2;

    set_global_descriptor_table(&global_descriptor_table, sizeof(global_descriptor_table));

    set_segment_registers(segment_selector(2, false, 0), segment_selector(1, false, 0));

    // set the IDT register

    _test_control = 3;

    auto interrupt_selector = segment_selector(2, false, 0);

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_selector, interrupt_FF, true, false, 0, true };
    }

    interrupt_descriptor_table[0x00] = { interrupt_selector, interrupt_00, true, false, 0, true };
    interrupt_descriptor_table[0x03] = { interrupt_selector, interrupt_03, true, false, 0, true };
    interrupt_descriptor_table[0x04] = { interrupt_selector, interrupt_04, true, false, 0, true };
    interrupt_descriptor_table[0x05] = { interrupt_selector, interrupt_05, true, false, 0, true };
    interrupt_descriptor_table[0x06] = { interrupt_selector, interrupt_06, true, false, 0, true };
    interrupt_descriptor_table[0x0B] = { interrupt_selector, interrupt_0B, true, false, 0, true };
    interrupt_descriptor_table[0x0D] = { interrupt_selector, interrupt_0D, true, false, 0, true };

    set_interrupt_descriptor_table(interrupt_descriptor_table);

    // test: exception 00: division error

    _test_control = 1000;
    raise_DE();
    if (interrupt_00_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 03: breakpoint

    _test_control = 1003;
    raise_BP();
    if (interrupt_03_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 04: integer overflow

    _test_control = 1004;
    raise_OF();
    if (interrupt_04_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 05: bound range exceeded

    _test_control = 1005;
    raise_BR();
    if (interrupt_05_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 06: undefined instruction

    _test_control = 1006;
    raise_UD();
    if (interrupt_06_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 0B: segment not present

    _test_control = 1000 + 0x0B;
    raise_NP();
    if (interrupt_0B_counter == 0) {
        _test_control = 0;
        return;
    }

    // test: exception 0D: general protection fault

    _test_control = 1000 + 0x0D;
    raise_GP();
    if (interrupt_0D_counter == 0) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}

namespace
{
    using namespace x86;

    void set_segment_registers ( segment_selector code, segment_selector data )
    {
        set_code_segment(code);
        set_data_segments(data);
    }

    [[gnu::section(".idt")]]
    constinit
    short_interrupt_gate_descriptor interrupt_descriptor_table [256] =
    { };

    // Fault handlers return to the very same location which caused the fault.
    // If the handler can't solve the fault, the program must terminate.
    // If the handler solves the fault, the program must retry the instruction.

    // In these tests, all faults are "solved" by rewriting the program.
    // Offending instructions are rewritten with NOPs.
    // It is assumed safe to write `size` NOPs into "bad" locations.

    [[gnu::naked]] void raise_DE_bad ()
    {
#if defined(__i386__)
        __asm__
        {
            // divide zero by zero
            div eax, eax
            nop
            nop
            nop
            // restore
            pop eax
            ret
        }
#elif defined(__x86_64__)
        __asm__
        {
            // divide zero by zero
            div rax, rax
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            // restore
            pop rax
            ret
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_DE ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            // prepare zero divisor
            mov eax, 0
            jmp raise_DE_bad
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            // prepare zero divisor
            mov rax, 0
            jmp raise_DE_bad
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void interrupt_00 ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            // "fix" caller: rewrite with NOPS
            mov eax, 0x90909090
            mov raise_DE_bad, eax
            // increment interrupt counter
            inc interrupt_00_counter
            // restore
            pop eax
            iretd
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            // "fix" caller: rewrite with NOPS
            mov rax, 0x9090909090909090
            mov raise_DE_bad, rax
            // increment interrupt counter
            inc interrupt_00_counter
            // restore
            pop rax
            iretd
        }
#else
# error unsupported target
#endif
    }

    void raise_BP ()
    {
        // `int3` raises BP

        __asm__ volatile ( "int3" : : : );
    }

    [[gnu::naked]] void interrupt_03 ()
    {
        __asm__
        {
             // increment interrupt counter
             inc interrupt_03_counter
             iretd
        }
    }

    void raise_OF ()
    {
#if defined(__i386__)
        // increment 0x7F overflows, `into` raises OF
        unsigned char value { 0x7F };
        __asm__ volatile ( "incb %0 \n into" : : "r"(value) : );
#elif defined(__x86_64__)
        // #TODO
        __asm__ volatile ( "cli \n hlt" : : : );
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void interrupt_04 ()
    {
        __asm__
        {
             // increment interrupt counter
             inc interrupt_04_counter
             iretd
        }
    }

    [[gnu::naked]] void raise_BR_bad ()
    {
#if defined(__i386__)
        __asm__
        {
            // assert index 4 in bounds [0, 1]
            bound eax, [esp]
            nop
            nop
            nop
            add esp, 8
            // restore
            pop eax
            ret
        }
#elif defined(__x86_64__)
        __asm__
        {
            // #TODO
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            cli
            hlt
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_BR ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            // prepare bounds [0, 1] and index 4
            mov eax, 1
            push eax
            mov eax, 0
            push eax
            mov eax, 4
            jmp raise_BR_bad
        }
#elif defined(__x86_64__)
        __asm__
        {
            // #TODO
            cli
            hlt
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void interrupt_05 ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            // "fix" caller: rewrite with NOPS
            mov eax, 0x90909090
            mov raise_BR_bad, eax
            // increment interrupt counter
            inc interrupt_05_counter
            // restore
            pop eax
            iretd
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            // "fix" caller: rewrite with NOPS
            mov rax, 0x9090909090909090
            mov raise_BR_bad, rax
            // increment interrupt counter
            inc interrupt_05_counter
            // restore
            pop rax
            iretd
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_UD_bad ()
    {
        __asm__
        {
            // `ud2` raises UD
            ud2
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            ret
        }
    }

    [[gnu::naked]] void raise_UD ()
    {
        __asm__
        {
            jmp raise_UD_bad
        }
    }

    [[gnu::naked]] void interrupt_06 ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            // "fix" caller: rewrite with NOPS
            mov eax, 0x90909090
            mov raise_UD_bad, eax
            // increment interrupt counter
            inc interrupt_06_counter
            // restore
            pop eax
            iretd
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            // "fix" caller: rewrite with NOPS
            mov rax, 0x9090909090909090
            mov raise_UD_bad, rax
            // increment interrupt counter
            inc interrupt_06_counter
            // restore
            pop rax
            iretd
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_NP_bad ()
    {
#if defined(__i386__)
        __asm__
        {
            // store non-present data segment into GS
            mov gs, ax
            nop
            nop
            nop
            // restore
            mov _test_debug, 2
            mov _test_debug, gs
            pop gs
            mov _test_debug, 3
            mov _test_debug, gs
            pop eax
            ret
        }
#elif defined(__x86_64__)
        __asm__
        {
            // store non-present data segment into GS
            mov gs, ax
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            // restore
            pop gs
            pop rax
            ret
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_NP ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            push gs
            // prepare segment selector for non-present data segment
            mov _test_debug, 1
            mov _test_debug, gs
            mov ax, 0x18
            jmp raise_NP_bad
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            push gs
            // prepare segment selector for non-present data segment
            mov ax, 0x18
            jmp raise_NP_bad
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void interrupt_0B ()
    {
#if defined(__i386__)
        __asm__
        {
            // "fix" caller: rewrite with NOPS
            push eax
            mov eax, 0x90909090
            mov raise_NP_bad, eax
            pop eax
            // increment interrupt counter
            inc interrupt_0B_counter
            // discard error code from stack
            add esp, 4
            iretd
        }
#elif defined(__x86_64__)
        __asm__
        {
            // "fix" caller: rewrite with NOPS
            push rax
            mov rax, 0x9090909090909090
            mov raise_NP_bad, rax
            pop rax
            // increment interrupt counter
            inc interrupt_0B_counter
            // discard error code from stack
            add rsp, 4
            iretd
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_GP_bad ()
    {
#if defined(__i386__)
        __asm__
        {
            // store non-readable code segment into GS
            mov gs, ax
            nop
            nop
            nop
            // restore
            pop gs
            pop eax
            ret
        }
#elif defined(__x86_64__)
        __asm__
        {
            // store non-readable code segment into GS
            mov gs, ax
            nop
            nop
            nop
            nop
            nop
            nop
            nop
            // restore
            pop gs
            pop rax
            ret
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void raise_GP ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            push gs
            // prepare segment selector for non-readable code segment
            mov ax, 0x38
            jmp raise_GP_bad
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            push gs
            // prepare segment selector for non-readable code segment
            mov ax, 0x38
            jmp raise_GP_bad
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void interrupt_0D ()
    {
#if defined(__i386__)
        __asm__
        {
            // save
            push eax
            // "fix" caller: rewrite with NOPS
            mov eax, 0x90909090
            mov raise_GP_bad, eax
            // increment interrupt counter
            inc interrupt_0D_counter
            // discard error code from stack
            add esp, 4
            // restore
            pop eax
            iretd
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save
            push rax
            // "fix" caller: rewrite with NOPS
            mov rax, 0x9090909090909090
            mov raise_GP_bad, rax
            // increment interrupt counter
            inc interrupt_0D_counter
            // discard error code from stack
            add rsp, 4
            // restore
            pop rax
            iretd
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void interrupt_FF ()
    {
        __asm__
        {
             // increment interrupt counter
             inc interrupt_FF_counter
             iretd
        }
    }
}