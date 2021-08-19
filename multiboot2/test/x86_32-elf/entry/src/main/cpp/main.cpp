// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Psys test protocol

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
	[[gnu::used]] unsigned volatile _test_debug {};

    void _test_start () { }
    void _test_finish () { }
}

//! Multiboot 2 request

namespace multiboot2
{
    struct request_type
    {
        header_prologue        prologue;
        entry_address_request  address;
        end_request            end;
    };

    // Assumption: the .text section begins with __multiboot2_start at address 0x1000

    [[gnu::used, gnu::section(".multiboot2")]]
    constinit
    request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { tag_type::entry, 0, sizeof(entry_address_request), 0x1000 },
        { },
    };

    //! Multiboot2 entry point with response

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
            call _test_start
            mov _test_control, 1
            mov _test_control, -1
            call _test_finish
            __multiboot2_halt:
            hlt
            jmp __multiboot2_halt
        }
    }
}