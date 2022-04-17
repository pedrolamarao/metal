// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>
#include <psys/start.h>
#include <psys/test.h>

#include <x86/segments.h>
#include <x86/identification.h>
#include <x86/interrupts.h>
#include <x86/msr.h>
#include <x86/ports.h>

#include <pc/pic.h>


namespace
{
    void set_global_descriptor_table_register ();

    unsigned exception_counter {};
    unsigned master_pic_counter {};
    unsigned slave_pic_counter {};
    unsigned interrupt_counter {};

    void set_interrupt_descriptor_table ();
}

void psys::main ()
{
    using namespace x86;

    // set the GDT register and set segment registers

    _test_control = 2;

    set_global_descriptor_table_register();

    // set the IDT register

    _test_control = 3;

    set_interrupt_descriptor_table();

    // test: handle software interrupt

    _test_control = 4;

    x86::interrupt<0x30>();

    if (interrupt_counter == 0) {
        _test_control = 0;
        return;
    }

    // initialize PIC

    _test_control = 10;

    auto master = pc::master_pic<x86::port>(0x20, 0x21);
    auto slave  = pc::slave_pic<x86::port>(0xA0, 0xA1);

    master.icw1(true, false, true);
    slave.icw1(true, false, true);
    master.icw2(0x20);
    slave.icw2(0x28);
    master.icw3(4);
    slave.icw3(2);
    master.icw4(true, false, pc::pic_buffering::none, false);
    slave.icw4(true, false, pc::pic_buffering::none, false);

    // unmask PIC IRQ 0 and enable hardware interrupts

    _test_control = 12;

    master.ocw1(0xFE);
    slave.ocw1(0xFF);

    enable_interrupts();

    // test: hardware interrupt increments counter
    // assumption: PIT shall interrupt IRQ 0

    _test_control = 13;

    while (master_pic_counter == 0) {
        // wait!
    }

    // test: hardware interrupt increments counter
    // assumption: PIT shall interrupt IRQ 0 again

    _test_control = 14;

    disable_interrupts();

    master_pic_counter = 0;

    enable_interrupts();

    while (master_pic_counter == 0) {
        // wait!
    }

    _test_control = -1;
    return;
}

namespace
{
    using namespace x86;
    using namespace x86::_32;

    // Segments.

    struct
    {
        size8                   null_descriptor {};
        data_segment_descriptor data_segment    { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor code_segment    { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
    }
    global_descriptor_table;

    void set_global_descriptor_table_register ()
    {
        set_global_descriptor_table(&global_descriptor_table,sizeof(global_descriptor_table));
        auto const cs = segment_selector(2, false, 0);
        set_code_segment(cs);
        auto const ds = segment_selector(1, false, 0);
        set_data_segments(ds);
    }

    // Interrupts.

    template <unsigned N>
    [[gnu::naked]] void trap_handler ()
    {
        __asm__
        {
            inc exception_counter
            iretd
        }
    }

    template <unsigned N>
    [[gnu::naked]] void fault_handler ()
    {
        __asm__
        {
            inc exception_counter
        loop:
            hlt
            jmp loop
        }
    }

    [[gnu::naked]] void master_pic_handler ()
    {
#if defined(__i386__)
        __asm__
        {
            // save registers
            push eax
            // handle
            inc master_pic_counter
            mov al, 0x20
            out 0x20, al
            // restore registers
            pop eax
            iretd
        }
#elif defined(__x86_64__)
        __asm__
        {
            // save registers
            push rax
            // handle
            inc master_pic_counter
            mov al, 0x20
            out 0x20, al
            // restore registers
            pop rax
            iretd
        }
#else
# error unsupported target
#endif
    }

    [[gnu::naked]] void slave_pic_handler ()
    {
        __asm__
        {
#if defined(__i386__)
            // save registers
            push eax
            // handle
            inc slave_pic_counter
            mov al, 0x20
            out 0xA0, al
            out 0x20, al
            // restore registers
            pop eax
            iretd
#elif defined(__x86_64__)
            // save registers
            push rax
            // handle
            inc slave_pic_counter
            mov al, 0x20
            out 0xA0, al
            out 0x20, al
            // restore registers
            pop rax
            iretd
#else
# error unsupported target
#endif
        }
    }

    [[gnu::naked]] void interrupt_handler ()
    {
        __asm__
        {
            inc interrupt_counter
            iretd
        }
    }

    [[gnu::section(".idt")]]
    constinit
    short_interrupt_gate_descriptor interrupt_descriptor_table [256] {};

    void set_interrupt_descriptor_table ()
    {
        auto const interrupt_segment = segment_selector(2, false, 0);

        interrupt_descriptor_table[0x00] = { interrupt_segment, fault_handler<0x00>, true, true, 0, true };
        interrupt_descriptor_table[0x01] = { interrupt_segment, fault_handler<0x01>, true, true, 0, true };
        interrupt_descriptor_table[0x02] = { interrupt_segment, trap_handler<0x02>,  true, true, 0, true };
        interrupt_descriptor_table[0x03] = { interrupt_segment, trap_handler<0x03>,  true, true, 0, true };
        interrupt_descriptor_table[0x04] = { interrupt_segment, trap_handler<0x04>,  true, true, 0, true };
        interrupt_descriptor_table[0x05] = { interrupt_segment, fault_handler<0x05>, true, true, 0, true };
        interrupt_descriptor_table[0x06] = { interrupt_segment, fault_handler<0x06>, true, true, 0, true };
        interrupt_descriptor_table[0x07] = { interrupt_segment, fault_handler<0x07>, true, true, 0, true };
        interrupt_descriptor_table[0x08] = { interrupt_segment, fault_handler<0x08>, true, true, 0, true };
        interrupt_descriptor_table[0x09] = { interrupt_segment, fault_handler<0x09>, true, true, 0, true };
        interrupt_descriptor_table[0x0A] = { interrupt_segment, fault_handler<0x0A>, true, true, 0, true };
        interrupt_descriptor_table[0x0B] = { interrupt_segment, fault_handler<0x0B>, true, true, 0, true };
        interrupt_descriptor_table[0x0C] = { interrupt_segment, fault_handler<0x0C>, true, true, 0, true };
        interrupt_descriptor_table[0x0D] = { interrupt_segment, fault_handler<0x0D>, true, true, 0, true };
        interrupt_descriptor_table[0x0E] = { interrupt_segment, fault_handler<0x0E>, true, true, 0, true };
        interrupt_descriptor_table[0x0F] = { interrupt_segment, trap_handler<0x0F>,  true, true, 0, true };
        interrupt_descriptor_table[0x10] = { interrupt_segment, fault_handler<0x10>, true, true, 0, true };
        interrupt_descriptor_table[0x11] = { interrupt_segment, fault_handler<0x11>, true, true, 0, true };
        interrupt_descriptor_table[0x12] = { interrupt_segment, fault_handler<0x12>, true, true, 0, true };
        interrupt_descriptor_table[0x13] = { interrupt_segment, fault_handler<0x13>, true, true, 0, true };
        interrupt_descriptor_table[0x14] = { interrupt_segment, fault_handler<0x14>, true, true, 0, true };
        interrupt_descriptor_table[0x15] = { interrupt_segment, fault_handler<0x15>, true, true, 0, true };
        interrupt_descriptor_table[0x16] = { interrupt_segment, trap_handler<0x16>,  true, true, 0, true };
        interrupt_descriptor_table[0x17] = { interrupt_segment, trap_handler<0x17>,  true, true, 0, true };
        interrupt_descriptor_table[0x18] = { interrupt_segment, trap_handler<0x18>,  true, true, 0, true };
        interrupt_descriptor_table[0x19] = { interrupt_segment, trap_handler<0x19>,  true, true, 0, true };
        interrupt_descriptor_table[0x1A] = { interrupt_segment, trap_handler<0x1A>,  true, true, 0, true };
        interrupt_descriptor_table[0x1B] = { interrupt_segment, trap_handler<0x1B>,  true, true, 0, true };
        interrupt_descriptor_table[0x1C] = { interrupt_segment, trap_handler<0x1C>,  true, true, 0, true };
        interrupt_descriptor_table[0x1D] = { interrupt_segment, trap_handler<0x1D>,  true, true, 0, true };
        interrupt_descriptor_table[0x1E] = { interrupt_segment, trap_handler<0x1E>,  true, true, 0, true };
        interrupt_descriptor_table[0x1F] = { interrupt_segment, trap_handler<0x1F>,  true, true, 0, true };

        for (auto i = 32U, j = 40U; i != j; ++i) {
           interrupt_descriptor_table[i] = { interrupt_segment, master_pic_handler, true, true, 0, true };
        }

        for (auto i = 40U, j = 48U; i != j; ++i) {
           interrupt_descriptor_table[i] = { interrupt_segment, slave_pic_handler, true, true, 0, true };
        }

        for (auto i = 48U, j = 256U; i != j; ++i) {
           interrupt_descriptor_table[i] = { interrupt_segment, interrupt_handler, true, true, 0, true };
        }

        set_interrupt_descriptor_table(interrupt_descriptor_table);
    }
}