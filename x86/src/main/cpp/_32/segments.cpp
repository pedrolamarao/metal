// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/registers.h>
#include <x86/_32/segments.h>

namespace x86::_32
{
    auto get_global_descriptor_table () -> global_descriptor_table_register
    {
        auto [size,offset] = gdtr();
        return { size, offset };
    }

    void set_global_descriptor_table ( global_descriptor_table_register value )
    {
        gdtr( { value.size, value.offset } );
    }
}