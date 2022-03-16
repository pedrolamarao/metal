// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/size.h>
#include <psys/test.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Application.

namespace app
{
    void main ( multiboot2::information_list & response );
}

//! Multiboot2 loader protocol.

namespace
{
    using namespace multiboot2;

    //! Multiboot2 request.

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

    //! Multiboot2 start procedure.

    [[gnu::section(".multiboot2.stack")]]
    constinit
    unsigned char stack [ 0x4000 ] {};

    [[gnu::section(".multiboot2.start")]]
    void main ( ps::size4 magic, multiboot2::information_list & response )
    {
        if (magic != information_magic) return;
        app::main(response);
    }

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
            // mark test start
            call _test_start
            // call C++
            push ebx
            push eax
            call main
            // mark test finish
            call _test_finish
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
            // mark test start
            call _test_start
            // call C++
            push rbx
            push rax
            call main
            // mark test finish
            call _test_finish
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