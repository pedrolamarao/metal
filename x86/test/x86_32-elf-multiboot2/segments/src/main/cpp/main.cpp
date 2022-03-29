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

    struct [[gnu::packed]]
    {
        size8                   null_descriptor   {};
        size8                   null_descriptor_2 {};
        data_segment_descriptor flat_data_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor flat_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
        data_segment_descriptor more_data_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor more_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
    }
    global_descriptor_table;

    static_assert(sizeof(global_descriptor_table) == 48, "unexpected size of global_descriptor_table");
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;

    unsigned step { 1 };

    // Verify we can manipulate the global descriptor table register.

    _test_control = step++;
    auto old_gdtr = gdtr();

    _test_control = step++;
    set_global_descriptor_table(&global_descriptor_table, sizeof(global_descriptor_table));

    _test_control = step++;
    auto new_gdtr = gdtr();

    _test_control = step++;
    if (old_gdtr.size == new_gdtr.size || old_gdtr.offset == new_gdtr.offset) {
        _test_control = 0;
        return;
    }

    // Verify we can manipulate the data segment registers.

    // Verify we can manipulate the DS register.

    step = 10;

    _test_control = step++;
    ds( segment_selector{2,false,0} );

    _test_control = step++;
    auto ds_2 = ds();

    _test_control = step++;
    if (ds_2 != segment_selector{2,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    ds( segment_selector{4,false,0} );

    _test_control = step++;
    auto ds_4 = ds();

    _test_control = step++;
    if (ds_4 != segment_selector{4,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (ds_2 == ds_4) {
        _test_control = 0;
        return;
    }

    // Verify we can manipulate the ES register.

    step = 20;

    _test_control = step++;
    es( segment_selector{2,false,0} );

    _test_control = step++;
    auto es_2 = es();

    _test_control = step++;
    if (es_2 != segment_selector{2,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    es( segment_selector{4,false,0} );

    _test_control = step++;
    auto es_4 = es();

    _test_control = step++;
    if (es_4 != segment_selector{4,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (es_2 == es_4) {
        _test_control = 0;
        return;
    }

    // Verify we can manipulate the FS register.

    step = 30;

    _test_control = step++;
    fs( segment_selector{2,false,0} );

    _test_control = step++;
    auto fs_2 = fs();

    _test_control = step++;
    if (fs_2 != segment_selector{2,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    fs( segment_selector{4,false,0} );

    _test_control = step++;
    auto fs_4 = fs();

    _test_control = step++;
    if (fs_4 != segment_selector{4,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (fs_2 == fs_4) {
        _test_control = 0;
        return;
    }

    // Verify we can manipulate the GS register.

    step = 40;

    _test_control = step++;
    gs( segment_selector{2,false,0} );

    _test_control = step++;
    auto gs_2 = gs();

    _test_control = step++;
    if (gs_2 != segment_selector{2,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    gs( segment_selector{4,false,0} );

    _test_control = step++;
    auto gs_4 = gs();

    _test_control = step++;
    if (gs_4 != segment_selector{4,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (gs_2 == gs_4) {
        _test_control = 0;
        return;
    }

    // Verify we can manipulate the SS register.

    step = 50;

    _test_control = step++;
    ss( segment_selector{2,false,0} );

    _test_control = step++;
    auto ss_2 = ss();

    _test_control = step++;
    if (ss_2 != segment_selector{2,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    ss( segment_selector{4,false,0} );

    _test_control = step++;
    auto ss_4 = ss();

    _test_control = step++;
    if (ss_4 != segment_selector{4,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (ss_2 == ss_4) {
        _test_control = 0;
        return;
    }

    // Verify we can manipulate the code segment register.

    step = 100;

    _test_control = step++;
    set_code_segment( segment_selector{3,false,0} );

    _test_control = step++;
    auto cs_3 = cs();

    _test_control = step++;
    if (cs_3 != segment_selector{3,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    set_code_segment( segment_selector{5,false,0} );

    _test_control = step++;
    auto cs_5 = cs();

    _test_control = step++;
    if (cs_5 != segment_selector{5,false,0}) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (cs_3 == cs_5) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}