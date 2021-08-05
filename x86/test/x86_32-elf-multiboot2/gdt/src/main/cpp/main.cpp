// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>


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

    [[gnu::aligned(8), gnu::section(".gdt")]]
    constexpr segment_descriptor global_descriptor_table [5] =
    {
        { },
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
    };
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

    x86::set_global_descriptor_table(global_descriptor_table);

    // #XXX: verify

    _test_control = 2;

    x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

    // #XXX: verify

    _test_control = 3;

    auto gdt = x86::get_global_descriptor_table();

    if (((5 * sizeof(segment_descriptor)) - 1) != (gdt & 0xFFFF)) {
        _test_control = 0;
        return;
    }

    _test_control = 4;

    if (ps::size4(& global_descriptor_table) != ((gdt >> 16) & 0xFFFFFFFF)) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
