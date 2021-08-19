// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/port.h>


//! Psys multiboot2 program.

void main ( ps::size4 magic, multiboot2::information_list * response )
{
    if (magic != multiboot2::information_magic) {
        // oops.
        return;
    }

    // Look for this output in QEMU debugcon!

    auto debug = x86::port<1>(0xE9);
    debug.write('P');
    debug.write('S');
    debug.write('Y');
    debug.write('S');

    return;
}

//! Multiboot2 loader.

namespace multiboot2
{
    //! Multiboot2 request

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

    //! Multiboot2 entry point.

    constinit
    unsigned char multiboot2_stack [ 0x4000 ] {};

    extern "C"
    [[gnu::naked]]
    void __multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset multiboot2_stack + 0x4000
            xor ecx, ecx
            push ecx
            popf
            __multiboot2_halt:
            hlt
            jmp __multiboot2_halt
        }
    }
}