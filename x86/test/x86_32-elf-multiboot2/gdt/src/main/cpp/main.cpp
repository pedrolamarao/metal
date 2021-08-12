// Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>


namespace multiboot2
{
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
    constexpr unsigned global_descriptor_table_size = 6;

    [[gnu::section(".gdt")]]
    constexpr segment_descriptor global_descriptor_table [ global_descriptor_table_size ] =
    {
        // required null descriptor
        { },
        // unexpected null descriptor!
        { },
        // system flat code descriptor
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
        // system flat data descriptor
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
        // user flat code descriptor
        { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
        // user flat data descriptor
        { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
    };
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
    // set GDT register

    _test_control = 10;

    const x86::system_table_register expected_gdtr {
        ((x86::global_descriptor_table_size * sizeof(x86::segment_descriptor)) - 1),
        reinterpret_cast<ps::size4>(x86::global_descriptor_table)
    };

    x86::set_global_descriptor_table_register(x86::global_descriptor_table);

    // test: did we successfully update the GDT register?

    _test_control = 11;

    auto const actual_gdtr = x86::get_global_descriptor_table_register();

    if (actual_gdtr != expected_gdtr) {
        _test_debug = expected_gdtr.size;
        _test_debug = expected_gdtr.offset;
        _test_debug = actual_gdtr.size;
        _test_debug = actual_gdtr.offset;
        _test_control = 0;
        return;
    }

    // set CS register

    _test_control = 20;

    auto const expected_cs = x86::segment_selector(2, false, 0);

    x86::set_code_segment_register( expected_cs );

    // test: did we successfully update the CS register?

    _test_control = 21;

    ps::size2 actual_cs {};
    asm("" : "=cs"(actual_cs));

    if (expected_cs.value() != actual_cs) {
        _test_debug = expected_cs.value();
        _test_debug = actual_cs;
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
