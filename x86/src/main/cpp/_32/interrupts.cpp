// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/interrupts.h>
#include <x86/registers.h>

namespace x86::_32
{
    auto get_interrupt_descriptor_table () -> interrupt_descriptor_table_register
    {
        auto [size,offset] = idtr();
        return { size, offset };
    }

    void set_interrupt_descriptor_table ( interrupt_descriptor_table_register value )
    {
        idtr( { value.size, value.offset } );
    }
}