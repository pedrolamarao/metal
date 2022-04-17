// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <multiboot2/header.h>
#include <multiboot2/start.h>

#include <x86/pages.h>
#include <x86/segments.h>


namespace multiboot2
{
    //! Request.

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

    //! Start procedure stack.

    [[gnu::section(".multiboot2.stack")]]
    constinit
    unsigned char stack [ 0x4000 ] {};

    //! x86_32 start procedure.

    void start_x86_32 ();

    //! x86-64 start procedure.

    void start_x86_64 ();
}

//! Start procedure.

extern "C"
[[gnu::naked, gnu::section(".multiboot2.start"), gnu::used]]
void multiboot2_start ()
{
    __asm__
    {
        .code32
        // set stack
        mov esp, offset multiboot2::stack + 0x4000
        mov ebp, esp
        // reset eflags
        xor ecx, ecx
        push ecx
        popfd
        // #TODO: validate magic number in eax
    }
#if defined(__i386__)
    __asm__
    {
        .code32
        jmp multiboot2::start_x86_32
    }
#elif defined(__x86_64__)
    __asm__
    {
        .code32
        jmp multiboot2::start_x86_64
    }
#else
# error unsupported target
#endif
}