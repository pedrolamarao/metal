// Copyright (C) 2020,2021,2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/start.h>
#include <psys/test.h>

#include <x86/segments.h>
#include <x86/interrupts.h>

import br.dev.pedrolamarao.metal.psys;

namespace
{
    using namespace x86;

    struct
    {
        size8                   null_descriptor   {};
        data_segment_descriptor flat_data_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor flat_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
    }
    global_descriptor_table;

    static_assert(sizeof(global_descriptor_table) == 24, "unexpected size of global_descriptor_table");

    void set_segment_registers ( segment_selector code, segment_selector data )
    {
        set_code_segment(code);
        set_data_segments(data);
    }

    // Interrupts.

    constexpr unsigned interrupt_descriptor_table_size = 256;

    [[gnu::section(".idt")]]
    constinit
    short_interrupt_gate_descriptor interrupt_descriptor_table [ interrupt_descriptor_table_size ];

    unsigned interrupted {};

    [[gnu::naked]]
    void interrupt_handler ()
    {
        __asm__
        {
            inc interrupted
            iretd
        }
    }
}

void psys::main ()
{
    using namespace ps;
    using namespace x86;

    // set the GDT register and set segment registers

    _test_control = 2;

    set_global_descriptor_table(&global_descriptor_table, sizeof(global_descriptor_table));

    set_segment_registers(segment_selector(2, false, 0), segment_selector(1, false, 0));

    auto interrupt_segment = segment_selector(2, false, 0);

    for (auto i = 0U, j = 256U; i != j; ++i) {
        interrupt_descriptor_table[i] = { interrupt_segment, interrupt_handler, true, false, 0, true };
    }

    // set the IDT register

    _test_control = 20;

    set_interrupt_descriptor_table(interrupt_descriptor_table);
    
    // test: did we successfully update the IDT register?

    _test_control = 21;

    auto expected_size = interrupt_descriptor_table_size * sizeof(short_interrupt_gate_descriptor);
    auto expected_offset = halt_cast<size4>(interrupt_descriptor_table);

    auto [actual_size, actual_offset] = idtr();

    if (actual_size != expected_size || actual_offset != expected_offset) {
        _test_debug = expected_size;
        _test_debug = expected_offset;
        _test_debug = actual_size;
        _test_debug = actual_offset;
        _test_control = 0;
        return;
    }

    // test: handle one software interrupt

    _test_control = 30;

    interrupt<0x30>();

    if (interrupted != 1) {
        _test_control = 0;
        return;
    }

    // test: handle another software interrupt

    _test_control = 31;

    interrupt<0x31>();

    if (interrupted != 2) {
        _test_control = 0;
        return;
    }

    // test: enable hardware interrupts

    _test_control = 40;

    enable_interrupts();

    _test_control = -1;
    return;
}