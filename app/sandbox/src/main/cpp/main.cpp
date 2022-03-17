// Copyright (C) 2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/integer.h>
#include <psys/start.h>

#include <x86/port.h>


namespace psys
{
    void main ()
    {
        // Look for this output in QEMU debugcon!

        auto debug = x86::port<1>(0xE9);
        debug.write('P');
        debug.write('S');
        debug.write('Y');
        debug.write('S');
    }
}