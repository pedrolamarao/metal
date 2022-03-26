// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/registers.h>

// NOTE: inline assembler in `att` syntax.

namespace x86
{
    // #XXX: LLVM 13 doesn't know how to do extended asm with _ExtInt
    struct carrier4 { size4 value; };

    static_assert(sizeof(carrier4) == 4, "unexpected size of carrier4");

    // Control registers.

    auto cr0 () -> size4
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr0, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr0 (size4 value)
    {
        carrier4 carrier { value };
        __asm__ ( "mov %0, %%cr0" : : "r"(carrier) );
    }

    auto cr2 () -> size4
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr2, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr2 (size4 value)
    {
        carrier4 carrier { value };
        __asm__ ( "mov %0, %%cr2" : : "r"(carrier) );
    }

    auto cr3 () -> size4
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr3, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr3 (size4 value)
    {
        carrier4 carrier { value };
        __asm__ ( "mov %0, %%cr3" : : "r"(carrier) );
    }

    auto cr4 () -> size4
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr4 (size4 value)
    {
        carrier4 carrier { value };
        __asm__ ( "mov %0, %%cr4" : : "r"(carrier) );
    }

    // Segment descriptor registers.

    auto gdtr () -> segment_descriptor_table
    {
        segment_descriptor_table value;
        __asm__ ( "sgdt %0" : "=m"(value) : : );
        return value;
    }

    void gdtr (segment_descriptor_table value)
    {
        __asm__ ( "lgdt %0" : : "m"(value) : );
    }

    auto idtr () -> segment_descriptor_table
    {
        segment_descriptor_table value;
        __asm__ ( "sidt %0" : "=m"(value) : : );
        return value;
    }

    void idtr (segment_descriptor_table value)
    {
        __asm__ ( "lidt %0" : : "m"(value) : );
    }

    auto ldtr () -> segment_descriptor_table
    {
        segment_descriptor_table value;
        __asm__ ( "sldt %0" : "=m"(value) : : );
        return value;
    }

    void ldtr (segment_descriptor_table value)
    {
        __asm__ ( "lldt %0" : : "m"(value) : );
    }
}