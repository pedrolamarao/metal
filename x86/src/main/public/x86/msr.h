// Copyright (C) 2012,2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/instructions.h>


//! Interface.

namespace x86
{
    //! Model specific registers.

    enum class msr : size4
    {
        APIC_BASE   = 0x0000001B,
        MISC_ENABLE = 0x000001A0,
        EFER        = 0xC0000080,
    };
}