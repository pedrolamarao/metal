// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/instructions.h>


// Interface.

namespace x86
{
    //! Discover the "age" of this processor.

    auto find_age () -> size;

    //! Test if this processor supports the processor identification (cpuid) instruction.

    inline
    auto has_cpuid () -> bool
    {
        return find_age() >= 4;
    }

    //! Test if this processor has a local APIC.

    inline
    auto has_local_apic () -> bool
    {
        return (cpuid(1).d & (1 << 11)) != 0;
    }

    //! Test if this processor is capable of long mode.

    inline
    auto has_long_mode () -> bool
    {
        return (cpuid(0x80000001).d & (1 << 29)) != 0;
    }

    //! Test if this processor has model-specific registers.

    inline
    auto has_msr () -> bool
    {
        return (cpuid(1).d & (1 << 4)) != 0;
    }
}