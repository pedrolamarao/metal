// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/cpuid.h>

namespace x86
{
    [[gnu::naked]]
    auto cpu_age () -> ps::size4
    {
#if defined(__i386__)
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
#elif defined(__x86_64__)
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
#else
# error unsupported target
#endif
    }
}