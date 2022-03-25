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

    alignas(0x1000) constinit
    short_large_page_directory_entry page_directory_table [ 0x400 ] {};
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;
    
    size step = 1;

    // Smoke test paging operators.

    _test_control = step++;
    get_short_paging_control_register();

    _test_control = step++;
    get_long_paging_control_register();

    // Set flat segmentation.

    _test_control = step++;
    set_global_descriptor_table_register(global_descriptor_table);
    set_code_segment_register( segment_selector(2, false, 0) );
    set_code_segment_register( segment_selector(2, false, 0) );
    set_data_segment_register( segment_selector(2, false, 0) );
    set_stack_segment_register( segment_selector(3, false, 0) );
    set_extra_segment_registers( segment_selector(3, false, 0) );

    // Verify we can manipulate control registers.

    // Verify we can manipulate page size extensions (CR4.PSE).

    step = 100;

    _test_control = step++;
    disable_large_pages();

    _test_control = step++;
    if (is_large_pages()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    enable_large_pages();

    _test_control = step++;
    if (! is_large_pages()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    disable_large_pages();

    _test_control = step++;
    if (is_large_pages()) {
        _test_control = 0;
        return;
    }

    // Post: page size extensions (CR4.PSE) disabled.

    // Verify we can manipulate page address extensions (CR4.PAE).

    step = 200;

    _test_control = step++;
    disable_long_pages();

    _test_control = step++;
    if (is_long_pages()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    enable_long_pages();

    _test_control = step++;
    if (! is_long_pages()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    disable_long_pages();

    _test_control = step++;
    if (is_long_pages()) {
        _test_control = 0;
        return;
    }

    // Post: page address extensions (CR4.PAE) disabled.

    // Verify we can manipulate the paging control (CR3) register.

    step = 300;

    _test_control = step++;
    get_short_paging_control_register();

    _test_control = step++;
    get_long_paging_control_register();

    _test_control = step++;
    set_paging_control_register( short_paging_control { 0, 0, 0 } );

    _test_control = step++;
    auto control = get_short_paging_control_register();

    _test_control = step++;
    if (control.write_through() != 0) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (control.cache() != 0) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (control.address() != 0) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    set_paging_control_register( short_paging_control { 1, 1, 1 } );

    _test_control = step++;
    control = get_short_paging_control_register();

    _test_control = step++;
    if (control.write_through() != 1) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (control.cache() != 1) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (control.address() != 0x1000) {
        _test_control = 0;
        return;
    }

    // Post: paging control (CR3) register is invalid!

    // Verify that we can manipulate paging.

    step = 400;

    // Multiboot2 x86 requires that paging is disabled at entry time.

    _test_control = step++;
    if (is_paging()) {
        _test_control = 0;
        return;
    }

    // Prepare page directory table for identity paging.

    for (size i = 0; i != 0x400; ++i) {
        page_directory_table[i] = {
            true, true, true, false, false, false, false, false, 0, 0, (0x400000 * i)
        };
    }

    _test_control = step++;
    enable_large_pages();

    _test_control = step++;
    size4 page_directory_table_address { reinterpret_cast<size4>(&page_directory_table[0]) };
    set_paging_control_register( short_paging_control{nullptr,false,false,page_directory_table_address} );

    _test_control = step++;
    enable_paging();

    _test_control = step++;
    if (! is_paging()) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}