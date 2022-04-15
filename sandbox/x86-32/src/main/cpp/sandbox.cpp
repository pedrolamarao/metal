// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/ports.h>


//! Play here!

namespace psys
{
    void sandbox ()
    {
        // Look for this output in QEMU debugcon!

        auto debug = x86::port<1>(0xE9);
        debug.write('P');
        debug.write('S');
        debug.write('Y');
        debug.write('S');
    }
}

