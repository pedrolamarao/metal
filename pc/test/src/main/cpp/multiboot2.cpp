// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <psys/test.h>


//! Multiboot2 loader protocol.

namespace multiboot2
{
    //! Multiboot2 loader request.

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
}

//! Multiboot2 application procedure.

extern
void main ( multiboot2::information_list & mbi );

namespace multiboot2
{
    //! Multiboot2 start procedure.

    [[gnu::section(".multiboot2.stack")]]
    constinit
    unsigned char stack [ 0x4000 ] {};

    // #XXX: Clang is not capable of assembling cmp with _ExtInt
    constexpr unsigned _magic = information_magic;

    extern "C"
    [[gnu::naked, gnu::section(".multiboot2.start")]]
    void multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset stack + 0x4000
            xor ecx, ecx
            push ecx
            popf
            cmp eax, _magic
            jne halt
            call _test_start
            push ebx
            call main
            call _test_finish
            halt:
            hlt
            jmp halt
        }
    }
}
