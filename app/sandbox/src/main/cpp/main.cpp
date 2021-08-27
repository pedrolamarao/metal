// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/port.h>


//! Multiboot2 application procedure.

void main ( multiboot2::information_list & response )
{
    // Look for this output in QEMU debugcon!

    auto debug = x86::port<1>(0xE9);
    debug.write('P');
    debug.write('S');
    debug.write('Y');
    debug.write('S');

    return;
}

//! Multiboot2 loader protocol.

namespace multiboot2
{
    //! Multiboot2 request.

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

    //! Multiboot2 start procedure.

    constinit
    unsigned char stack [ 0x4000 ] {};

    // #XXX: Clang cannot assemble cmp with _ExtInt.
    constexpr unsigned _magic = information_magic;

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
            cmp eax, _magic
            jne halt
            push ebx
            call main
            halt:
            hlt
            jmp halt
        }
    }
}