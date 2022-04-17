// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/start.h>


namespace multiboot2
{
    //! x86-32 start procedure.

    [[gnu::naked, gnu::section(".multiboot2.start")]]
    void start_x86_32 ()
    {
        __asm__
        {
            .code32
            // Call main.
            push ebx
            push eax
            call main
            // Halt.
            cli
          halt:
            hlt
            jmp halt
        }
    }
}
