// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86
{
    //! If this processor is capable of long mode.

    inline
    auto has_long_mode () -> bool
    {
        unsigned a = 0x80000001, b = 0, c = 0, d = 0;
        __asm__ ( "cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(a), "c"(c) );
        return (d & (1 << 29)) != 0;
    }
}