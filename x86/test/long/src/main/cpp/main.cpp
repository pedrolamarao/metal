// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/start.h>
#include <psys/test.h>

#include <x86/identification.h>
#include <x86/interrupts.h>
#include <x86/msr.h>
#include <x86/pages.h>
#include <x86/segments.h>


namespace
{
    using namespace x86;

    // segments.

    struct
    {
        size8                   null_descriptor    {};
        data_segment_descriptor data_segment       { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor short_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
        code_segment_descriptor long_code_segment  { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true, true };
    }
    global_descriptor_table;

    // protected mode.

    extern
    short_interrupt_gate_descriptor interrupt_descriptor_table_32 [ 256 ];

    [[gnu::naked]]
    void interrupt_handler_32 ();

    // long mode.

    const extern
    long_page_table_entry page_table [ 0x200 ];

    extern
    long_small_page_directory_entry page_directory [ 0x200 ];

    extern
    long_small_page_directory_pointer_entry page_directory_pointers [ 0x200 ];

    extern
    long_page_map_entry page_map [ 0x200 ];
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
    set_global_descriptor_table(&global_descriptor_table,sizeof(global_descriptor_table));
    set_data_segments(segment_selector{1,false,0});
    auto code_segment_32 = segment_selector{2,false,0};
    set_code_segment(code_segment_32);

    // prepare 32 bit protected mode interrupts.

    _test_control = step++;
    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table_32[i] = { code_segment_32, interrupt_handler_32, true, false, 0, true };
    }
    set_interrupt_descriptor_table(interrupt_descriptor_table_32);
    
    // prepare long mode pages.

    _test_control = step++;
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
    set_paging( extended_paging { {}, false, false, reinterpret_cast<size4>(page_map) } );

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
    // protected mode interrupts.

    constinit
    short_interrupt_gate_descriptor interrupt_descriptor_table_32 [ 256 ]
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

    alignas(0x1000) constexpr
    long_page_table_entry page_table [ 0x200 ]
    {
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x000), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x001), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x002), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x003), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x004), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x005), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x006), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x007), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x008), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x009), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x00A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x00B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x00C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x00D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x00E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x00F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x010), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x011), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x012), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x013), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x014), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x015), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x016), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x017), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x018), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x019), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x01A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x01B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x01C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x01D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x01E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x01F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x020), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x021), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x022), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x023), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x024), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x025), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x026), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x027), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x028), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x029), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x02A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x02B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x02C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x02D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x02E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x02F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x030), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x031), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x032), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x033), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x034), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x035), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x036), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x037), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x038), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x039), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x03A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x03B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x03C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x03D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x03E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x03F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x040), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x041), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x042), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x043), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x044), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x045), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x046), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x047), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x048), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x049), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x04A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x04B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x04C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x04D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x04E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x04F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x050), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x051), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x052), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x053), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x054), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x055), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x056), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x057), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x058), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x059), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x05A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x05B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x05C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x05D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x05E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x05F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x060), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x061), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x062), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x063), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x064), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x065), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x066), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x067), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x068), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x069), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x06A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x06B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x06C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x06D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x06E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x06F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x070), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x071), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x072), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x073), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x074), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x075), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x076), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x077), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x078), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x079), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x07A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x07B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x07C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x07D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x07E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x07F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x080), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x081), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x082), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x083), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x084), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x085), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x086), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x087), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x088), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x089), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x08A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x08B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x08C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x08D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x08E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x08F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x090), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x091), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x092), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x093), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x094), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x095), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x096), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x097), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x098), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x099), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x09A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x09B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x09C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x09D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x09E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x09F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0A9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0AA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0AB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0AC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0AD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0AE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0AF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0B9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0BA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0BB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0BC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0BD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0BE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0BF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0C9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0CA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0CB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0CC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0CD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0CE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0CF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0D9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0DA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0DB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0DC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0DD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0DE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0DF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0E9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0EA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0EB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0EC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0ED), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0EE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0EF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0F9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0FA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0FB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0FC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0FD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0FE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x0FF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x100), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x101), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x102), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x103), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x104), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x105), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x106), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x107), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x108), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x109), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x10A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x10B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x10C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x10D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x10E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x10F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x110), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x111), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x112), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x113), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x114), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x115), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x116), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x117), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x118), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x119), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x11A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x11B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x11C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x11D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x11E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x11F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x120), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x121), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x122), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x123), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x124), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x125), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x126), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x127), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x128), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x129), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x12A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x12B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x12C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x12D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x12E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x12F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x130), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x131), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x132), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x133), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x134), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x135), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x136), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x137), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x138), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x139), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x13A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x13B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x13C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x13D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x13E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x13F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x140), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x141), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x142), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x143), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x144), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x145), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x146), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x147), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x148), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x149), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x14A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x14B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x14C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x14D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x14E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x14F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x150), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x151), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x152), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x153), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x154), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x155), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x156), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x157), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x158), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x159), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x15A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x15B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x15C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x15D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x15E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x15F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x160), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x161), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x162), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x163), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x164), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x165), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x166), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x167), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x168), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x169), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x16A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x16B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x16C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x16D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x16E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x16F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x170), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x171), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x172), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x173), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x174), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x175), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x176), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x177), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x178), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x179), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x17A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x17B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x17C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x17D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x17E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x17F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x180), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x181), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x182), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x183), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x184), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x185), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x186), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x187), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x188), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x189), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x18A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x18B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x18C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x18D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x18E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x18F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x190), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x191), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x192), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x193), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x194), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x195), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x196), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x197), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x198), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x199), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x19A), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x19B), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x19C), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x19D), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x19E), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x19F), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1A9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1AA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1AB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1AC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1AD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1AE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1AF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1B9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1BA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1BB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1BC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1BD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1BE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1BF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1C9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1CA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1CB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1CC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1CD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1CE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1CF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1D9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1DA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1DB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1DC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1DD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1DE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1DF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1E9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1EA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1EB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1EC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1ED), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1EE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1EF), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F0), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F1), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F2), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F3), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F4), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F5), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F6), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F7), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F8), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1F9), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1FA), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1FB), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1FC), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1FD), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1FE), 0, false },
        long_page_table_entry { true, true, true, false, false, false, false, 0, false, 0, (0x1000 * 0x1FF), 0, false },
    };

    alignas(0x1000) constinit
    long_small_page_directory_entry page_directory [ 0x200 ];

    alignas(0x1000) constinit
    long_small_page_directory_pointer_entry page_directory_pointers [ 0x200 ];

    alignas(0x1000) constinit
    long_page_map_entry page_map [ 0x200 ];
}