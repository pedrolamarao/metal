// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

namespace x86
{
    // Primitive procedures.

    void halt ()
    {
        __asm__ ( "hlt" : : : );
    }

    void pause ()
    {
        __asm__ ( "pause" : : : );
    }
}