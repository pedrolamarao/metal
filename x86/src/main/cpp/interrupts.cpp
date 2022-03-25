// Copyright (C) 2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/interrupts.h>


namespace x86
{
    void enable_interrupts ()
    {
        __asm__ volatile ( "sti" : : : );
    }

    void cli ()
    {
        __asm__ volatile ( "cli" : : : );
    }
}