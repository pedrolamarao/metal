// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>
#include <x86/port.h>

#include <pc/pic.h>
#include <pc/pit.h>
#include <pc/test.h>


// x86 architecture.

namespace x86
{
    void set_global_descriptor_table_register ();

    unsigned exception_counter {};
    unsigned master_pic_counter {};
    unsigned slave_pic_counter {};
    unsigned interrupt_counter {};

    void set_interrupt_descriptor_table_register ();
}

// Multiboot2 application procedure.

void main ( multiboot2::information_list & mbi )
{
    using namespace x86;

    // set the GDT register and set segment registers

    _test_control = 2;

    set_global_descriptor_table_register();

    // set the IDT register

    _test_control = 3;

    set_interrupt_descriptor_table_register();

    // test: verify interrupt sanity

    _test_control = 4;

    x86::interrupt<0x30>();

    if (interrupt_counter == 0) {
        _test_control = 0;
        return;
    }

    // initialize PIC

    _test_control = 5;

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

    _test_control = 6;

    master.ocw1(0xFE);
    slave.ocw1(0xFF);

    sti();

    // pit

    auto pit = pc::pit<x86::port>(0x40, 0x41, 0x42, 0x43);

    // test: 'configure' command builder

    _test_control = 10;

    auto configure = pc::pit_configure_command(pc::pit_counter::zero, pc::pit_access::low, pc::pit_mode::hardware_retriggerable_one_shot, pc::pit_format::binary);
    if (configure != 0b00010010) {
        _test_control = configure;
        _test_control = 0;
        return;
    }

    // test: 'read back' command builder

    _test_control = 11;

    auto read_back = pc::pit_read_back_command(false, true, pc::pit_counter::zero);
    if (read_back != 0b11010010) {
        _test_control = read_back;
        _test_control = 0;
        return;
    }

    // test: PIT mode 0: configure, read_back
    // assumption: test is faster than counter

    _test_control = 20;

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

    _test_control = 21;

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

    _test_control = 22;

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

    _test_control = 23;

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

    _test_control = 24;

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

    _test_control = 25;

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

//! x86-32 architecture.

namespace x86
{
    // Segments.

    [[gnu::section(".gdt")]]
    constinit
    segment_descriptor global_descriptor_table [5] =
    {
        { },
        { 0, 0xFFFFF, code_segment(true, true, true), 0, true, true, true, true, },
        { 0, 0xFFFFF, data_segment(true, true, true), 0, true, true, true, true, },
        { 0, 0xFFFFF, code_segment(true, true, true), 3, true, true, true, true, },
        { 0, 0xFFFFF, data_segment(true, true, true), 3, true, true, true, true, },
    };

    void set_global_descriptor_table_register ()
    {
        set_global_descriptor_table_register(global_descriptor_table);
        auto const cs = segment_selector(1, false, 0);
        set_code_segment_register(cs);
        auto const ds = segment_selector(2, false, 0);
        set_data_segment_register(ds);
        set_stack_segment_register(ds);
        set_extra_segment_registers(ds);
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
        __asm__
        {
            pushad
            inc master_pic_counter
            mov al, 0x20
            out 0x20, al
            popad
            iretd
        }
    }

    [[gnu::naked]] void slave_pic_handler ()
    {
        __asm__
        {
            pushad
            inc slave_pic_counter
            mov al, 0x20
            out 0xA0, al
            out 0x20, al
            popad
            iretd
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
    interrupt_gate_descriptor interrupt_descriptor_table [256] {};

    void set_interrupt_descriptor_table_register ()
    {
        auto const interrupt_segment = segment_selector(1, false, 0);

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

        set_interrupt_descriptor_table_register(interrupt_descriptor_table);
    }
}