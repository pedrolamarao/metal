// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/port.h>

#include <pc/pic.h>
#include <pc/uart.h>


//! Multiboot2

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

//! x86

namespace x86
{
    void set_global_descriptor_table_register ();

    extern "C" [[gnu::used]] unsigned __x86_exception_counter {};
    extern "C" [[gnu::used]] unsigned __x86_interrupt_master_counter {};
    extern "C" [[gnu::used]] unsigned __x86_interrupt_slave_counter {};
    extern "C" [[gnu::used]] unsigned __x86_interrupt_counter {};

    void set_interrupt_descriptor_table_register ();
}

//! Psys test protocol

namespace
{
    extern "C" [[gnu::used]] unsigned volatile _test_control {};
    extern "C" [[gnu::used]] unsigned volatile _test_debug {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    using namespace multiboot2;
    using namespace pc::uart;
    using namespace x86;

    // test: verify boot sanity

    _test_control = 1;

    if (magic != multiboot2::information_magic) {
        _test_control = 0;
        return;
    }

    // set the GDT register and set segment registers

    _test_control = 2;

    set_global_descriptor_table_register();

    // set the IDT register

    _test_control = 3;

    set_interrupt_descriptor_table_register();

    // test: verify interrupt sanity

    _test_control = 4;

    x86::interrupt<0x30>();

    if (__x86_interrupt_counter == 0) {
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

    // mask PIC and enable hardware interrupts

    _test_control = 6;

    master.ocw1(0xFF);
    slave.ocw1(0xFF);

    sti();

    // uart: data types

    // test: fcr data type

    _test_control = 120;

    fcr fcr0;
    fcr0.enabled(true);
    fcr0.receiver_reset(true);
    fcr0.transmitter_reset(true);
    fcr0.trigger(3);
    if ( size1{fcr0} != 0xC7 ) {
        _test_debug = size1{fcr0};
        _test_control = 0;
        return;
    }

    // test: lcr data type

    _test_control = 130;

    lcr lcr0;
    lcr0.dlab(true);
    if ( size1{lcr0} != 0x80 ) {
        _test_debug = size1{lcr0};
        _test_control = 0;
        return;
    }

    _test_control = 131;
    if ( size1{lcr{}.dlab(true)} != 0x80 ) {
        _test_control = 0;
        return;
    }

    // test: mcr data type

    _test_control = 140;

    mcr mcr0;
    mcr0.loopback(true);
    if ( size1{mcr0} != 0x10 ) {
        _test_debug = size1{mcr0};
        _test_control = 0;
        return;
    }

    // uart: interface types

    // test: poll mode configuration

    _test_control = 200;

    auto uart = pc::uart::uart<x86::port>( _ExtInt(16){0x03F8} );
    uart.ier( ier{} );
    uart.lcr( lcr{}.dlab(true) );
    uart.dll( 0x03 );
    uart.dlm( 0x00 );
    uart.lcr( lcr{}.word(3) );
    uart.fcr( fcr{}
        .enabled(true)
        .receiver_reset(true)
        .transmitter_reset(true)
        .trigger(3)
    );

    // test: poll mode loopback

    _test_control = 201;

    uart.mcr( mcr{}.loopback(true) );
    uart.thr( 0xFE );
    auto read_201 = uart.rbr();
    if ( read_201 != 0xFE ) {
        _test_debug = read_201;
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}

//! Definitions

namespace x86
{
    // GDT

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

    // IDT

    extern "C" void __x86_exception_00 ();
    extern "C" void __x86_exception_01 ();
    extern "C" void __x86_exception_02 ();
    extern "C" void __x86_exception_03 ();
    extern "C" void __x86_exception_04 ();
    extern "C" void __x86_exception_05 ();
    extern "C" void __x86_exception_06 ();
    extern "C" void __x86_exception_07 ();
    extern "C" void __x86_exception_08 ();
    extern "C" void __x86_exception_09 ();
    extern "C" void __x86_exception_0A ();
    extern "C" void __x86_exception_0B ();
    extern "C" void __x86_exception_0C ();
    extern "C" void __x86_exception_0D ();
    extern "C" void __x86_exception_0E ();
    extern "C" void __x86_exception_0F ();
    extern "C" void __x86_exception_10 ();
    extern "C" void __x86_exception_10 ();
    extern "C" void __x86_exception_11 ();
    extern "C" void __x86_exception_12 ();
    extern "C" void __x86_exception_13 ();
    extern "C" void __x86_exception_14 ();
    extern "C" void __x86_exception_15 ();
    extern "C" void __x86_exception_16 ();
    extern "C" void __x86_exception_17 ();
    extern "C" void __x86_exception_18 ();
    extern "C" void __x86_exception_19 ();
    extern "C" void __x86_exception_1A ();
    extern "C" void __x86_exception_1B ();
    extern "C" void __x86_exception_1C ();
    extern "C" void __x86_exception_1D ();
    extern "C" void __x86_exception_1E ();
    extern "C" void __x86_exception_1F ();
    extern "C" void __x86_interrupt_master ();
    extern "C" void __x86_interrupt_slave ();
    extern "C" void __x86_interrupt ();

    [[gnu::section(".idt")]]
    constinit
    interrupt_gate_descriptor interrupt_descriptor_table [256];

    void set_interrupt_descriptor_table_register ()
    {
        auto const interrupt_segment = segment_selector(1, false, 0);

        interrupt_descriptor_table[0x00] = { interrupt_segment, __x86_exception_00, true, true, 0, true };
        interrupt_descriptor_table[0x01] = { interrupt_segment, __x86_exception_01, true, true, 0, true };
        interrupt_descriptor_table[0x02] = { interrupt_segment, __x86_exception_02, true, true, 0, true };
        interrupt_descriptor_table[0x03] = { interrupt_segment, __x86_exception_03, true, true, 0, true };
        interrupt_descriptor_table[0x04] = { interrupt_segment, __x86_exception_04, true, true, 0, true };
        interrupt_descriptor_table[0x05] = { interrupt_segment, __x86_exception_05, true, true, 0, true };
        interrupt_descriptor_table[0x06] = { interrupt_segment, __x86_exception_06, true, true, 0, true };
        interrupt_descriptor_table[0x07] = { interrupt_segment, __x86_exception_07, true, true, 0, true };
        interrupt_descriptor_table[0x08] = { interrupt_segment, __x86_exception_08, true, true, 0, true };
        interrupt_descriptor_table[0x09] = { interrupt_segment, __x86_exception_09, true, true, 0, true };
        interrupt_descriptor_table[0x0A] = { interrupt_segment, __x86_exception_0A, true, true, 0, true };
        interrupt_descriptor_table[0x0B] = { interrupt_segment, __x86_exception_0B, true, true, 0, true };
        interrupt_descriptor_table[0x0C] = { interrupt_segment, __x86_exception_0C, true, true, 0, true };
        interrupt_descriptor_table[0x0D] = { interrupt_segment, __x86_exception_0D, true, true, 0, true };
        interrupt_descriptor_table[0x0E] = { interrupt_segment, __x86_exception_0E, true, true, 0, true };
        interrupt_descriptor_table[0x0F] = { interrupt_segment, __x86_exception_0F, true, true, 0, true };
        interrupt_descriptor_table[0x10] = { interrupt_segment, __x86_exception_10, true, true, 0, true };
        interrupt_descriptor_table[0x11] = { interrupt_segment, __x86_exception_11, true, true, 0, true };
        interrupt_descriptor_table[0x12] = { interrupt_segment, __x86_exception_12, true, true, 0, true };
        interrupt_descriptor_table[0x13] = { interrupt_segment, __x86_exception_13, true, true, 0, true };
        interrupt_descriptor_table[0x14] = { interrupt_segment, __x86_exception_14, true, true, 0, true };
        interrupt_descriptor_table[0x15] = { interrupt_segment, __x86_exception_15, true, true, 0, true };
        interrupt_descriptor_table[0x16] = { interrupt_segment, __x86_exception_16, true, true, 0, true };
        interrupt_descriptor_table[0x17] = { interrupt_segment, __x86_exception_17, true, true, 0, true };
        interrupt_descriptor_table[0x18] = { interrupt_segment, __x86_exception_18, true, true, 0, true };
        interrupt_descriptor_table[0x19] = { interrupt_segment, __x86_exception_19, true, true, 0, true };
        interrupt_descriptor_table[0x1A] = { interrupt_segment, __x86_exception_1A, true, true, 0, true };
        interrupt_descriptor_table[0x1B] = { interrupt_segment, __x86_exception_1B, true, true, 0, true };
        interrupt_descriptor_table[0x1C] = { interrupt_segment, __x86_exception_1C, true, true, 0, true };
        interrupt_descriptor_table[0x1D] = { interrupt_segment, __x86_exception_1D, true, true, 0, true };
        interrupt_descriptor_table[0x1E] = { interrupt_segment, __x86_exception_1E, true, true, 0, true };
        interrupt_descriptor_table[0x1F] = { interrupt_segment, __x86_exception_1F, true, true, 0, true };

        for (auto i = 32U, j = 40U; i != j; ++i) {
           interrupt_descriptor_table[i] = { interrupt_segment, __x86_interrupt_master, true, true, 0, true };
        }

        for (auto i = 40U, j = 48U; i != j; ++i) {
           interrupt_descriptor_table[i] = { interrupt_segment, __x86_interrupt_slave, true, true, 0, true };
        }

        for (auto i = 48U, j = 256U; i != j; ++i) {
           interrupt_descriptor_table[i] = { interrupt_segment, __x86_interrupt, true, true, 0, true };
        }

        set_interrupt_descriptor_table_register(interrupt_descriptor_table);
    }
}