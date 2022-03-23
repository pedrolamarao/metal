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
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;

    _test_control = 10;
    auto short_cr3 = get_short_paging_control_register();

    _test_control = 20;
    auto long_cr3 = get_long_paging_control_register();

    _test_control = -1;
    return;
}