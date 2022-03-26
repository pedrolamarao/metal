// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>
#include <psys/start.h>
#include <psys/test.h>

#include <x86/segments.h>


namespace
{
    using namespace x86;
    using namespace x86::_32;

    constexpr unsigned global_descriptor_table_size = 6;

    [[gnu::section(".gdt")]]
    constinit
    segment_descriptor global_descriptor_table [ global_descriptor_table_size ] =
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
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;

    // test: data structures

    auto& segment = global_descriptor_table[4];

    _test_control = 1;
    if (segment.type() != code_segment(true, true, true)) {
        _test_control = 0;
        return;
    }

    _test_control = 2;
    if (segment.privilege() != 3) {
        _test_control = 0;
        return;
    }

    _test_control = 3;
    if (segment.is_system()) {
        _test_control = 0;
        return;
    }

    _test_control = 4;
    if (segment.privilege() != 3) {
        _test_control = 0;
        return;
    }

    _test_control = 5;
    if (! segment.is_present()) {
        _test_control = 0;
        return;
    }

    _test_control = 6;
    if (! segment.is_available()) {
        _test_control = 0;
        return;
    }

    _test_control = 8;
    if (! segment.is_32bit()) {
        _test_control = 0;
        return;
    }

    _test_control = 9;
    if (! segment.is_4kb()) {
        _test_control = 0;
        return;
    }

    _test_control = 10;
    if (segment.base() != 0) {
        _test_debug = segment.base();
        _test_control = 0;
        return;
    }

    _test_control = 11;
    if (segment.limit() != 0x000FFFFF) {
        _test_debug = segment.limit();
        _test_control = 0;
        return;
    }

    // set GDT register

    _test_control = 20;

    set_global_descriptor_table(global_descriptor_table);

    // test: did we successfully update the GDT register?

    _test_control = 21;

    auto expected_size = ((global_descriptor_table_size * sizeof(segment_descriptor)) - 1);
    auto expected_offset = reinterpret_cast<size>(global_descriptor_table);

    auto [actual_size, actual_offset] = get_global_descriptor_table();

    if (actual_size != expected_size || actual_offset != expected_offset) {
        _test_debug = expected_size;
        _test_debug = expected_offset;
        _test_debug = actual_size;
        _test_debug = actual_offset;
        _test_control = 0;
        return;
    }

    // set CS register

    _test_control = 30;

    auto const expected_cs = x86::segment_selector(2, false, 0);

    x86::set_code_segment( expected_cs );

    // test: did we successfully update the CS register?

    _test_control = 31;

    segment_selector actual_cs { get_code_segment() };

    if (expected_cs != actual_cs) {
        _test_debug = size2{expected_cs};
        _test_debug = size2{actual_cs};
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}