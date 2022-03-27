// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86
{
    //! Processor identification.

    struct cpuid_type { size a {}; size b {}; size c {}; size d {}; };

    //! Get processor identification.

    auto cpuid2 (size feature, size variant = 0) -> cpuid_type;

    //! Halt processor.

    void halt ();

    //! Pause processor.

    void halt ();
}