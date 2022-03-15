// Copyright (C) 2021, 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/gdt.h>

namespace x86
{
    // Interface types.

    auto get_code_segment_register () -> segment_selector
    {
        segment_selector value;
        __asm__ ( "movw %%cs, %0" : "=mr"(value) );
        return value;
    }

    void set_code_segment_register ( segment_selector value )
    {
        unsigned int const _value { size2 { value } };
        __asm__ (
            "pushl %0   \n"
            "pushl $%=f \n"
            "lretl      \n"
            "%=:        \n"
            :
            : "mr"(_value)
            :
       );
    }

    void set_data_segment_register ( segment_selector value )
    {
        __asm__ ( "movw %%ds, %0" : : "mr"(value) : );
    }

    void set_stack_segment_register ( segment_selector value )
    {
        __asm__ ( "movw %%ss, %0" : : "mr"(value) : );
    }

    void set_extra_segment_registers ( segment_selector value )
    {
        __asm__ ( "movw %%ds, %0" : : "mr"(value) : );
    }
}