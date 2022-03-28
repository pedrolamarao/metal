// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/start.h>
#include <psys/test.h>

#include <x86/cpuid.h>
#include <x86/identification.h>
#include <x86/interrupts.h>
#include <x86/msr.h>
#include <x86/pages.h>
#include <x86/segments.h>


namespace
{
    using namespace x86;
    using namespace x86::_32;

    // segments.

    extern
    segment_descriptor global_descriptor_table [ 8 ];

    // interrupts.

    extern
    interrupt_gate_descriptor interrupt_descriptor_table [ 256 ];

    [[gnu::naked]]
    void interrupt_handler ();

    // pages.

    extern
    long_large_page_directory_entry page_directory_table [ 0x200 ];

    extern
    page_directory_pointer_entry page_directory_pointer_table [ 4 ];
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;

    size step { 1 };

    // is long mode supported?

    _test_control = step++;
    if (! has_cpuid()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;
    if (! has_long_mode()) {
        _test_control = 0;
        return;
    }

    // prepare segments.

    _test_control = step++;
    set_global_descriptor_table(global_descriptor_table);
    set_code_segment( segment_selector{2,false,0} );
    set_data_segments( segment_selector{3,false,0} );

    // prepare interrupts.

    _test_control = step++;
    auto interrupt_segment = segment_selector(2, false, 0);
    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_segment, interrupt_handler, true, true, 0, true };
    }
    set_interrupt_descriptor_table(interrupt_descriptor_table);
    
    // prepare long mode pages.

    _test_control = step++;
    for (size i = 0; i != 0x200; ++i) {
        page_directory_table[i] = {
            {}, true, true, true, false, false, false, false, false, 0, 0, (0x200000 * i), false
        };
    }
    for (size i = 0; i != 4; ++i) {
        page_directory_pointer_table[i] = {
            {}, true, false, false, 0, reinterpret_cast<size8>(page_directory_table)
        };
    }
    // #XXX: prepare level 4 table.
    enable_large_pages();
    enable_long_addresses();
    set_paging( long_paging { {}, false, false, reinterpret_cast<size>(page_directory_pointer_table) } );

    // enable long mode.

    _test_control = step++;
    set_msr(msr::EFER, get_msr(msr::EFER) | (1 << 8));

    // did we succeed?

    _test_control = step++;
    if ((get_msr(msr::EFER) & (1 << 8)) == 0) {
        _test_control = 0;
        return;
    }

    // enable paging, enter long compatibility mode.

    _test_control = step++;
    enable_paging();

    // did we succeed?

    _test_control = step++;
    if ((get_msr(msr::EFER) & (1 << 9)) == 0) {
        _test_control = 0;
        return;
    }

    // jump to a long mode code segment, enter long mode.
    // #TODO: jump!

    _test_control = -1;
    return;
}

namespace
{
    // segments.

    constinit
    segment_descriptor global_descriptor_table [ 8 ] =
    {
        // null descriptor
        { },
        { },
        // protected mode flat system code segment
        { 0, 0xFFFFF, code_segment(true, true, true), 0, true, true, true, true, },
        // protected mode flat system data segment
        { 0, 0xFFFFF, data_segment(true, true, true), 0, true, true, true, true, },
        // long mode flat system code descriptor
        { },
        { 0, 0xFFFFF, code_segment(true, true, true), 0, true, true, true, true, },
        // long mode flat system data descriptor
        { },
        { 0, 0xFFFFF, data_segment(true, true, true), 0, true, true, true, true, },
    };

    // interrupts.

    constinit
    interrupt_gate_descriptor interrupt_descriptor_table [ 256 ]
    { };

    [[gnu::naked]]
    void interrupt_handler ()
    {
        __asm__
        {
            xor eax, eax
            mov _test_debug, eax
            mov eax, 1234
            mov _test_debug, eax
            xor eax, eax
            mov _test_control, eax
            cli
        loop:
            hlt
            jmp loop
        }
    }

    // pages.

    alignas(0x1000) constinit
    long_large_page_directory_entry page_directory_table [ 0x200 ] {};

    alignas(0x1000) constinit
    page_directory_pointer_entry page_directory_pointer_table [ 4 ] {};
}