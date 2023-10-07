// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/test.h>

import br.dev.pedrolamarao.metal.multiboot2;
import br.dev.pedrolamarao.metal.psys;

//! Minimal test.

namespace
{
    [[gnu::used]]
    void test ( ps::size magic )
    {
        _test_control = 1;
        if (magic != multiboot2::information_magic) _test_control = 0;
        _test_control = -1;
    }
}

namespace multiboot2
{
    struct request_type
    {
        header_prologue prologue;
        end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2.request")]]
    constinit
    request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { },
    };

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

    [[gnu::section(".multiboot2.stack")]]
    constinit
    unsigned char stack [ 0x4000 ] {};

    extern "C"
    [[gnu::naked, gnu::section(".multiboot2.start")]]
    void multiboot2_start ()
    {
#if defined(__i386__)
        __asm__
        {
            mov esp, offset stack + 0x4000
            xor ecx, ecx
            push ecx
            popf
            call _test_start
            push eax
            call test
            call _test_finish
            cli
        loop:
            hlt
            jmp loop
        }
#elif defined(__x86_64__)
        __asm__
        {
            mov rsp, offset stack + 0x4000
            xor rcx, rcx
            push rcx
            popf
            call _test_start
            push rax
            call test
            call _test_finish
            cli
        loop:
            hlt
            jmp loop
        }
#else
# error unsupported target
#endif
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
}