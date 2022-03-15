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

    // #XXX: Clang cannot assemble cmp with _ExtInt.
    constexpr unsigned _magic = information_magic;

    void start_x86_32 ();

    void start_x86_64 ();

    extern "C"
    [[gnu::naked, gnu::section(".multiboot2.start"), gnu::used]]
    void multiboot2_start ()
    {
        __asm__
        {
#if defined(__i386__)
            jmp start_x86_32
#elif defined(__x86_64__)
            jmp start_x86_64
#else
# error unsupported target
#endif
        }
    }

    [[gnu::naked, gnu::section(".multiboot2.start")]]
    void start_x86_32 ()
    {
        __asm__
        {
            // set stack
            mov esp, offset stack + 0x4000
            // reset eflags
            xor ecx, ecx
            push ecx
            popf
            // validate multiboot2
            cmp eax, _magic
            jne finish
            // mark test start
            call _test_start
            // call application
            push ebx
            call app::main
            // mark test finish
            call _test_finish
            // finish
          finish:
            cli
          halt:
            hlt
            jmp halt
        }
    }

    [[gnu::naked, gnu::section(".multiboot2.start")]]
    void start_x86_64 ()
    {
        __asm__
        {
            mov esp, offset stack + 0x4000
            xor ecx, ecx
            push rcx
            popf
            cmp eax, 0x36D76289 // #XXX: clang assembles _magic into a %rip relative address which doesn't work
            jne finish
            push rbx
            call app::main
          finish:
            cli
          halt:
            hlt
            jmp halt
        }
    }
}