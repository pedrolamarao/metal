// Copyright (C) 2021, 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/segments.h>


namespace x86
{
    void set_code_segment ( segment_selector value )
    {
        __asm__ (
            "push %0   \n"
            "push $%=f \n"
            "lret      \n"
            "%=:       \n"
            :
            : "m"(value)
            :
       );
    }
}