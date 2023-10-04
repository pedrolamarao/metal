// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <psys/test.h>


//! Test image layout.

namespace
{
    [[gnu::used]]
    void test ( ps::size magic )
    {
        _test_control = 1;
        if (magic != multiboot2::information_magic) _test_control = 0;
        _test_control = -1;
    }

    // Very large object in the text section.

    [[gnu::used]]
    void large_text ()
    {
        __asm__
        {
            .zero 0x8000
        }
    }

    // Very large object in the data section.

    [[gnu::used]]
    constinit
    char large_data [ 0x8000 ] { -1 };
}

namespace multiboot2
{
    struct request_type
    {
        header_prologue        prologue;
        entry_address_request  address;
        end_request            end;
    };

    [[gnu::used, gnu::section(".multiboot2.request")]]
    constinit
    request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { },
    };

    [[gnu::section(".multiboot2.stack")]]
    constinit
    unsigned char stack [ 0x4000 ] {};

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