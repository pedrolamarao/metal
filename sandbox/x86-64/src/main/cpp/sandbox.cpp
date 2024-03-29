// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


//! Play here!

namespace sandbox
{
    void main ()
    {
        // Look for output in QEMU debugcon!

        // The machine is prepared for C++ automatic variables and procedure calls.

        const unsigned short debugcon { 0xE9 };

        // GNU extended inline assembly default syntax is AT&T.

        __asm__ ( "outb %0, %1" : : "a"('P'), "Nd"(debugcon) : );
        __asm__ ( "outb %0, %1" : : "a"('S'), "Nd"(debugcon) : );
        __asm__ ( "outb %0, %1" : : "a"('Y'), "Nd"(debugcon) : );
        __asm__ ( "outb %0, %1" : : "a"('S'), "Nd"(debugcon) : );

        // Microsoft assembly block default syntax is Intel.

        __asm__ {
            push rax
            mov al, 'P'
            out 0xE9, al
            mov al, 'S'
            out 0xE9, al
            mov al, 'Y'
            out 0xE9, al
            mov al, 'S'
            out 0xE9, al
            pop rax
        }
    }
}

