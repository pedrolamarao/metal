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
            pushfq
            pop rax
            mov rcx, rax

            // detect i386: can we flip EFLAGS AC?
            mov rdx, 3
            // flip AC flag
            xor rax, 0x40000
            // set EFLAGS with flipped AC flag
            push rax
            popfq
            // get EFLAGS
            pushfq
            pop rax
            // terminate if AC flag did not change
            xor rax, rcx
            jz _x86_cpu_age_end

            // reset EFLAGS
            push rcx
            popfq
            mov rax, rcx

            // detect i486: can we flip EFLAGS ID?
            mov rdx, 4
            // flip ID flag
            xor rax, 0x200000
            // set EFLAGS with flipped ID flag
            push rax
            popfq
            // get EFLAGS
            pushfq
            pop rax
            // terminate if ID flag did not change
            xor rax, rcx
            jz _x86_cpu_age_end

            // detect i586
            mov rdx, 5

        _x86_cpu_age_end:

            // reset EFLAGS
            push rcx
            popfq

            // return detected CPU age
            mov rax, rdx
            ret
        }
    }
}