// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/segments.h>

namespace x86::_32
{
    auto get_global_descriptor_table () -> global_descriptor_table_register
    {
        global_descriptor_table_register value;
        __asm__ ( "sgdt %0" : "=m"(value) : : );
        return value;
    }

    void set_global_descriptor_table_register ( global_descriptor_table_register value )
    {
        __asm__ ( "lgdt %0" : : "m"(value) : );
    }
}