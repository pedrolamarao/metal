// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/information.h>
#include <multiboot2/start.h>

#include <psys/test.h>


//! Start library test.

namespace multiboot2
{
    // Incorrect entry point.

    [[gnu::used, gnu::section(".multiboot2.start")]]
    void _first ()
    {
        __asm__
        {
            cli
        halt:
            hlt
            jmp halt
        }
    }

    // Incorrect entry point.

    extern "C"
    [[gnu::naked, gnu::section(".multiboot2.start"), gnu::used]]
    void _start ()
    {
        __asm__
        {
            cli
        loop:
            hlt
            jmp loop
        }
    }

    // Test procedure.

    void test ()
    {
    }

    // Correct entry point.

    void main ( ps::size4 magic, multiboot2::information_list & response )
    {
        unsigned step { 1 };
        _test_start();

        // Test if loaded from the expected loader.

        _test_control = step++;
        if (magic != information_magic) {
            _test_control = 0;
            return;
        }

        // Test if we can call a C++ procedure.

        _test_control = step++;
        test();

        _test_control = -1;
        _test_finish();
    }
}