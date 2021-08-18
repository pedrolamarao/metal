// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Multiboot 2 request

namespace
{
    using namespace multiboot2;

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

//! Test result

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
    [[gnu::used]] unsigned volatile _test_debug {};

    void _test_start () { }
    void _test_finish () { }
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list * response )
{
    _test_control = 1;

    if (magic == 0) {
        _test_control = 0;
        return;
    }

    _test_control = 2;

    if (response == 0) {
        _test_control = 0;
        return;
    }

    _test_control = 3;

    if (magic != multiboot2::information_magic) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}

namespace multiboot2
{
    //! Multiboot2 entry point

    extern "C"
    constinit
    unsigned char __multiboot2_stack [ 0x4000 ] {};

    extern "C"
    [[gnu::naked]]
    void __multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset __multiboot2_stack + 0x4000
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