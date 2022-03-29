// Copyright (C) 2021, 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/segments.h>


namespace x86
{
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
}