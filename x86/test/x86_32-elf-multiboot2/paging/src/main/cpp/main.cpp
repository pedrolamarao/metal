// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/start.h>
#include <psys/test.h>

#include <x86/gdt.h>
#include <x86/_32/page.h>
#include <x86/_32/segment.h>


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

    // #TODO: appropriately align this object
    constinit
    short_page_table_entry page_table [ 2048 ] {};

    // #TODO: appropriately align this object
    constinit
    short_small_page_directory_entry page_directory [ 2048 ] {};
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;

    // Smoke test paging operators.

    _test_control = 1;
    get_short_paging_control_register();

    _test_control = 2;
    get_long_paging_control_register();

    // Set flat segmentation.

    _test_control = 3;
    set_global_descriptor_table_register(global_descriptor_table);
    set_code_segment_register( segment_selector(2, false, 0) );
    set_code_segment_register( segment_selector(2, false, 0) );
    set_data_segment_register( segment_selector(2, false, 0) );
    set_stack_segment_register( segment_selector(3, false, 0) );
    set_extra_segment_registers( segment_selector(3, false, 0) );

    // Verify we can set the paging control register with zero.

    _test_control = 10;
    set_paging_control_register( short_paging_control { 0, 0, 0 } );

    _test_control = 11;
    auto control = get_short_paging_control_register();

    _test_control = 12;
    if (control.write_through() != 0) {
        _test_control = 0;
        return;
    }

    _test_control = 13;
    if (control.cache() != 0) {
        _test_control = 0;
        return;
    }

    _test_control = 14;
    if (control.address() != 0) {
        _test_control = 0;
        return;
    }

    // Verify we can set the paging control register with non-zero.

    _test_control = 20;
    set_paging_control_register( short_paging_control { 1, 1, 1 } );

    _test_control = 21;
    control = get_short_paging_control_register();

    _test_control = 22;
    if (control.write_through() != 1) {
        _test_control = 0;
        return;
    }

    _test_control = 23;
    if (control.cache() != 1) {
        _test_control = 0;
        return;
    }

    _test_control = 24;
    if (control.address() != 0x1000) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}