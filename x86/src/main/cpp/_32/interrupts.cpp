// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/interrupts.h>

namespace x86::_32
{
    auto get_interrupt_descriptor_table () -> interrupt_descriptor_table_register
    {
        interrupt_descriptor_table_register value;
        __asm__ ( "sidt %0" : "=m"(value) : : );
        return value;
    }

    void set_interrupt_descriptor_table_register ( interrupt_descriptor_table_register value )
    {
        __asm__ ( "lidt %0" : : "m"(value) : );
    }
}