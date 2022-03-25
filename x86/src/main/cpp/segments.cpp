// Copyright (C) 2021, 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/segments.h>


namespace x86
{
    // Interface types.

    auto get_code_segment () -> segment_selector
    {
        segment_selector value;
        __asm__ ( "movw %%cs, %0" : "=mr"(value) );
        return value;
    }

    void set_code_segment ( segment_selector value )
    {
        unsigned int const _value { size2 { value } };
        __asm__ (
            "push %0   \n"
            "push $%=f \n"
            "lret      \n"
            "%=:        \n"
            :
            : "mr"(_value)
            :
       );
    }

    void set_data_segment ( segment_selector value )
    {
        __asm__ ( "mov %%ds, %0" : : "mr"(value) : );
    }

    void set_stack_segment ( segment_selector value )
    {
        __asm__ ( "mov %%ss, %0" : : "mr"(value) : );
    }

    void set_data_segments ( segment_selector value )
    {
        __asm__ ( "mov %%ds, %0" : : "mr"(value) : );
        __asm__ ( "mov %%es, %0" : : "mr"(value) : );
        __asm__ ( "mov %%fs, %0" : : "mr"(value) : );
        __asm__ ( "mov %%gs, %0" : : "mr"(value) : );
        __asm__ ( "mov %%ss, %0" : : "mr"(value) : );
    }
}