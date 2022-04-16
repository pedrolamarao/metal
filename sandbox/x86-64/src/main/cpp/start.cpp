// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/header.h>

#include <x86/pages.h>
#include <x86/segments.h>


// Start code.

namespace sandbox { void main(); }

namespace x86
{
    // x86 segments.

    struct
    {
        size8                   null_descriptor    {};
        size8                   oops_descriptor    {};
        data_segment_descriptor data_segment       { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true };
        code_segment_descriptor short_code_segment { 0, 0xFFFFF, true, true, true, 0, true, 0, false, true, true };
        code_segment_descriptor long_code_segment  { 0, 0xFFFFF, true, true, true, 0, true, 0, true, true, true };
    }
    constexpr global_descriptor_table;

    constexpr auto global_descriptor_table_size = sizeof(global_descriptor_table) - 1;

    constexpr segment_selector data_segment { 2, false, 0 };

    constexpr segment_selector short_code_segment { 3, false, 0 };

    constexpr segment_selector long_code_segment { 4, false, 0 };

    // x86 pages.

    alignas(0x1000) constinit
    long_page_table_entry page_table [ 0x200 ] { };

    alignas(0x1000) constinit
    long_small_page_directory_entry page_directory [ 0x200 ] { };

    alignas(0x1000) constinit
    long_small_page_directory_pointer_entry page_directory_pointers [ 0x200 ] { };

    alignas(0x1000) constinit
    long_page_map_entry page_map [ 0x200 ] { };
}


namespace multiboot2
{
    //! Multiboot2 request.

    struct request_type
    {
        header_prologue prologue;
        end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2.request")]]
    constinit
    request_type request
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
        __asm__ {
            .code32
            // set stack
            mov esp, offset stack + 0x4000
            // reset eflags
            xor eax, eax
            push eax
            popfd
            // TRACE
            mov al, '0'
            out 0xE9, al
            // load global descriptor table register
            mov eax, offset x86::global_descriptor_table
            push eax
            mov ebx, offset x86::global_descriptor_table_size
            mov eax, [ebx]
            push ax
            lgdt [esp]
            add esp, 6
            // TRACE
            mov al, '1'
            out 0xE9, al
            // load data segment selector registers
            mov eax, offset x86::data_segment
            mov dx, [eax]
            mov ds, dx
            mov es, dx
            mov fs, dx
            mov gs, dx
            mov ss, dx
            // TRACE
            mov al, '2'
            out 0xE9, al
        }
        // far return to short code segment
        __asm__ (
            ".code32           \n"
            "push %0           \n"
            "push $%=f         \n"
            "lret              \n"
            "%=:               \n"
            :
            : "r"(x86::short_code_segment)
            :
        );
        __asm__
        {
            // TRACE
            mov al, '3'
            out 0xE9, al
            // finish
          halt:
            hlt
            jmp halt
        }
    }
}
