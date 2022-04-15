// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


//! Play here!

namespace psys
{
    void sandbox ()
    {
        // Look for output in QEMU debugcon!

        // The machine is prepared for C++ automatic variables and procedure calls.

        const short port { 0xE9 };

        // GNU extended inline assembly default syntax is AT&T.

        __asm__ ( "outb %0, %1" : : "a"('P'), "Nd"(port) : );
        __asm__ ( "outb %0, %1" : : "a"('S'), "Nd"(port) : );
        __asm__ ( "outb %0, %1" : : "a"('Y'), "Nd"(port) : );
        __asm__ ( "outb %0, %1" : : "a"('S'), "Nd"(port) : );

        // Microsoft assembly block default syntax is Intel.

        __asm__ {
            push eax
            mov al, 'P'
            out 0xE9, al
            mov al, 'S'
            out 0xE9, al
            mov al, 'Y'
            out 0xE9, al
            mov al, 'S'
            out 0xE9, al
            pop eax
        }
    }
}

