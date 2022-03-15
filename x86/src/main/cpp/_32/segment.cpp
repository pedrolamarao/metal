// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/segment.h>

namespace x86::_32
{
    auto get_global_descriptor_table_register () -> global_descriptor_table_register
    {
        global_descriptor_table_register value;
        __asm__ ( "sgdtl %0" : "=m"(value) : : );
        return value;
    }

    void set_global_descriptor_table_register ( global_descriptor_table_register value )
    {
        __asm__ ( "lgdtl %0" : : "m"(value) : );
    }
}