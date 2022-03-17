// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <multiboot2/header.h>
#include <multiboot2/start.h>


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

    //! Start procedure.

    extern "C"
    [[gnu::naked, gnu::section(".multiboot2.start"), gnu::used]]
    void multiboot2_start ()
    {
        __asm__
        {
#if defined(__i386__)
        __asm__
        {
            // set stack
            mov esp, offset stack + 0x4000
            // reset eflags
            xor ecx, ecx
            push ecx
            popf
            // call C++
            push ebx
            push eax
            call main
            // finish
            cli
          halt:
            hlt
            jmp halt
        }
#elif defined(__x86_64__)
        __asm__
        {
            // set stack
            mov esp, offset stack + 0x4000
            // reset eflags
            xor ecx, ecx
            push rcx
            popf
            // call C++
            push rbx
            push rax
            call main
            // finish
          finish:
            cli
          halt:
            hlt
            jmp halt
        }
#else
# error unsupported target
#endif
        }
    }
}