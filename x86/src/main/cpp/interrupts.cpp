// Copyright (C) 2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/idt.h>

namespace x86
{
    // Primitive procedures.

    void sti ()
    {
        __asm__ volatile ( "sti" : : : );
    }

    void cli ()
    {
        __asm__ volatile ( "cli" : : : );
    }
}