// Copyright (C) 2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/identification.h>

namespace x86
{
    [[gnu::naked]]
    auto find_age () -> size
    {
        __asm__
        {
            // get EFLAGS: eax to play, ecx to keep
            pushfd
            pop eax
            mov ecx, eax

            // detect i386: can we flip EFLAGS AC?
            mov edx, 3
            // flip AC flag
            xor eax, 0x40000
            // set EFLAGS with flipped AC flag
            push eax
            popfd
            // get EFLAGS
            pushfd
            pop eax
            // terminate if AC flag did not change
            xor eax, ecx
            jz _x86_cpu_age_end

            // reset EFLAGS
            push ecx
            popfd
            mov eax, ecx

            // detect i486: can we flip EFLAGS ID?
            mov edx, 4
            // flip ID flag
            xor eax, 0x200000
            // set EFLAGS with flipped ID flag
            push eax
            popfd
            // get EFLAGS
            pushfd
            pop eax
            // terminate if ID flag did not change
            xor eax, ecx
            jz _x86_cpu_age_end

            // detect i586
            mov edx, 5

        _x86_cpu_age_end:

            // reset EFLAGS
            push ecx
            popfd

            // return detected CPU age
            mov eax, edx
            ret
        }
    }
}