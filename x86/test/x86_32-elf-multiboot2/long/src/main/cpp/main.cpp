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

    // segments.

    extern
    _32::segment_descriptor global_descriptor_table [ 4 ];

    // protected mode.

    extern
    _32::interrupt_gate_descriptor interrupt_descriptor_table_32 [ 256 ];

    [[gnu::naked]]
    void interrupt_handler_32 ();

    // long mode.

    extern
    _64::page_table_entry page_table [ 0x200 ];

    extern
    _64::small_page_directory_entry page_directory [ 0x200 ];

    extern
    _64::small_page_directory_pointer_entry page_directory_pointers [ 0x200 ];

    extern
    _64::page_map_entry page_map [ 0x200 ];
}

[[gnu::naked, gnu::used]]
extern "C"
void test_64 ()
{
    __asm__ (
        ".code64          \n"
        "mov $999, %%rax  \n"
        "mov %%eax, %0    \n"
        "lretl            \n"
        :
        : "m"(_test_control)
        : "rax"
    );
}

void psys::main ()
{
    using namespace x86;
    using namespace x86::_32;
    using namespace x86::_64;

    unsigned step { 1 };

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
    set_data_segments(segment_selector{1,false,0});
    auto code_segment_32 = segment_selector{2,false,0};
    set_code_segment(code_segment_32);

    // prepare 32 bit protected mode interrupts.

    _test_control = step++;
    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table_32[i] = { code_segment_32, interrupt_handler_32, true, true, 0, true };
    }
    set_interrupt_descriptor_table(interrupt_descriptor_table_32);
    
    // prepare long mode pages.

    _test_control = step++;
    for (size i = 0; i != 0x200; ++i) {
        page_table[i] = {
            true, true, true, false, false, false, false, 0, false, 0, (0x1000 * i), 0, false
        };
    }
    for (size i = 0; i != 0x200; ++i) {
        page_directory[i] = {
            true, true, true, false, false, false, 0, reinterpret_cast<size8>(page_table), false
        };
    }
    for (size i = 0; i != 0x200; ++i) {
        page_directory_pointers[i] = {
            true, true, true, false, false, false, 0, reinterpret_cast<size8>(page_directory), false
        };
    }
    for (size i = 0; i != 0x200; ++i) {
        page_map[i] = {
            true, true, true, false, false, false, 0, reinterpret_cast<size8>(page_directory_pointers), false
        };
    }
    enable_large_pages();
    enable_long_addresses();
    set_paging( _32::long_paging { {}, false, false, reinterpret_cast<size4>(page_map) } );

    // enable long mode.

    _test_control = step++;
    set_msr(msr::EFER, get_msr(msr::EFER) | (1 << 8));

    // is long mode enabled?

    _test_control = step++;
    if ((get_msr(msr::EFER) & (1 << 8)) == 0) {
        _test_control = 0;
        return;
    }

    // activate long mode.

    _test_control = step++;
    enable_paging();

    // is long mode active?

    _test_control = step++;
    if ((get_msr(msr::EFER) & (1 << 10)) == 0) {
        _test_control = 0;
        return;
    }

    // processor is executing in 32 bit long mode.

    // far call 64 bit code.

    _test_control = step++;
    far_call(segment_selector{3,false,0}, test_64);

   _test_control = -1;
}

namespace
{
    // protected mode segments.

    constinit
    _32::segment_descriptor global_descriptor_table [ 4 ] =
    {
        // null descriptor
        { },
        // data segment
        { 0, 0xFFFFF, data_segment(true, true, true), 0, true, true, true, true, },
        // 32 bit code segment
        { 0, 0xFFFFF, code_segment(true, true, true), 0, true, true, true, true, },
        // 64 bit code segment
        { 0, 0xFFFFF, code_segment(true, true, true), 0, true, true, true, false, true, },
    };

    // protected mode interrupts.

    constinit
    _32::interrupt_gate_descriptor interrupt_descriptor_table_32 [ 256 ]
    { };

    [[gnu::naked]]
    void interrupt_handler_32 ()
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

    // long mode pages.

    alignas(0x1000) constinit
    _64::page_table_entry page_table [ 0x200 ];

    alignas(0x1000) constinit
    _64::small_page_directory_entry page_directory [ 0x200 ];

    alignas(0x1000) constinit
    _64::small_page_directory_pointer_entry page_directory_pointers [ 0x200 ];

    alignas(0x1000) constinit
    _64::page_map_entry page_map [ 0x200 ];
}