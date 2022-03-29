// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/instructions.h>


// Interface.

namespace x86
{
    //! Test if this processor is capable of long mode.

    inline
    auto has_long_mode () -> bool
    {
        return (cpuid2(0x80000001).d & (1 << 29)) != 0;
    }

    //! Test if this processor has model-specific registers.

    inline
    auto has_msr () -> bool
    {
        return (cpuid2(1).d & (1 << 4)) != 0;
    }
}