// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Psys test protocol.

extern "C"
{
    extern void _test_start ();
    extern void _test_finish ();
}

//! Multiboot2 loader protocol.

namespace multiboot2
{
    //! Multiboot2 loader request.

    struct request_type
    {
        header_prologue prologue;
        end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constinit
    request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { },
    };
}

//! Multiboot2 application procedure.

extern
void main ( ps::size4 magic, multiboot2::information_list & mbi );

namespace multiboot2
{
    //! Multiboot2 start procedure.

    constinit
    unsigned char stack [ 0x4000 ] {};

    extern "C"
    [[gnu::naked]]
    void multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset stack + 0x4000
            xor ecx, ecx
            push ecx
            popf
            call _test_start
            push ebx
            push eax
            call main
            call _test_finish
            __multiboot2_halt:
            hlt
            jmp __multiboot2_halt
        }
    }
}
