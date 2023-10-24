// Copyright (C) 2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

import br.dev.pedrolamarao.metal.multiboot2;
import br.dev.pedrolamarao.metal.psys;

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

    //! User supplied main procedure.

    void main ( ps::size4 magic, multiboot2::information_list & response );

    //! x86-32 start procedure.

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
        __asm__
        {
            .code32
            // Call main.
            push ebx
            push eax
            call main
            // Halt.
            cli
          halt:
            hlt
            jmp halt
        }
    }
}