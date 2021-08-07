// Copyright (C) 2020,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


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

    extern "C"
    [[gnu::used]] unsigned volatile interrupted {};

    extern "C"
    void __interrupt_service_routine ();
}

//! Psys test protocol

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    _test_control = 1;

    if (magic != multiboot2::information_magic) {
        _test_control = 0;
        return;
    }

    _test_control = 2;

    x86::set_global_descriptor_table(global_descriptor_table);

    _test_control = 3;

    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

    _test_control = 4;

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { 0x8, __interrupt_service_routine, interrupt_gate_access(true, 0) };
    }

    x86::set_interrupt_descriptor_table(interrupt_descriptor_table, 256);

    _test_control = 5;

    auto idt = x86::get_interrupt_descriptor_table();

    _test_control = 6;

    // #TODO document this assert
    if ((256 * sizeof(interrupt_gate_descriptor)) != (idt & 0xFFFF)) {
        _test_control = 0;
        return;
    }

    _test_control = 7;

    // #TODO document this assert
    if (ps::size4(& interrupt_descriptor_table) != ((idt >> 16) & 0xFFFFFFFF)) {
        _test_control = 0;
        return;
    }

    _test_control = 8;

    x86::interrupt<0>();

    _test_control = -1;
    return;
}
