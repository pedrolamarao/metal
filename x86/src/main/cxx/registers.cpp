// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/registers.h>

// NOTE: inline assembler in `att` syntax.

namespace x86
{
    // #XXX: LLVM 13 doesn't know how to do extended asm with _ExtInt
    struct carrier { size value; };

    static_assert(sizeof(carrier) == sizeof(size), "unexpected size of carrier");

    // Control registers.

    auto cr0 () -> size
    {
        carrier carrier;
        __asm__ ( "mov %%cr0, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr0 (size value)
    {
        carrier carrier { value };
        __asm__ ( "mov %0, %%cr0" : : "r"(carrier) );
    }

    auto cr2 () -> size
    {
        carrier carrier;
        __asm__ ( "mov %%cr2, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr2 (size value)
    {
        carrier carrier { value };
        __asm__ ( "mov %0, %%cr2" : : "r"(carrier) );
    }

    auto cr3 () -> size
    {
        carrier carrier;
        __asm__ ( "mov %%cr3, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr3 (size value)
    {
        carrier carrier { value };
        __asm__ ( "mov %0, %%cr3" : : "r"(carrier) );
    }

    auto cr4 () -> size
    {
        carrier carrier;
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        return carrier.value;
    }

    void cr4 (size value)
    {
        carrier carrier { value };
        __asm__ ( "mov %0, %%cr4" : : "r"(carrier) );
    }

    // Descriptor table registers.

    auto gdtr () -> descriptor_table
    {
        descriptor_table value;
        __asm__ ( "sgdt %0" : "=m"(value) : : );
        return value;
    }

    void gdtr (descriptor_table value)
    {
        __asm__ ( "lgdt %0" : : "m"(value) : );
    }

    auto idtr () -> descriptor_table
    {
        descriptor_table value;
        __asm__ ( "sidt %0" : "=m"(value) : : );
        return value;
    }

    void idtr (descriptor_table value)
    {
        __asm__ ( "lidt %0" : : "m"(value) : );
    }

    auto ldtr () -> descriptor_table
    {
        descriptor_table value;
        __asm__ ( "sldt %0" : "=m"(value) : : );
        return value;
    }

    void ldtr (descriptor_table value)
    {
        __asm__ ( "lldt %0" : : "m"(value) : );
    }

    // Segment descriptor registers.

    auto cs () -> segment_selector
    {
        segment_selector value {};
        __asm__ ( "mov %%cs, %0" : "=r"(value) );
        return value;
    }

    void cs (segment_selector value)
    {
        __asm__ ( "mov %0, %%cs" : : "r"(value) : );
    }

    auto ds () -> segment_selector
    {
        segment_selector value {};
        __asm__ ( "mov %%ds, %0" : "=r"(value) );
        return value;
    }

    void ds (segment_selector value)
    {
        __asm__ ( "mov %0, %%ds" : : "r"(value) : );
    }

    auto es () -> segment_selector
    {
        segment_selector value {};
        __asm__ ( "mov %%es, %0" : "=r"(value) );
        return value;
    }

    void es (segment_selector value)
    {
        __asm__ ( "mov %0, %%es" : : "r"(value) : );
    }

    auto fs () -> segment_selector
    {
        segment_selector value {};
        __asm__ ( "mov %%fs, %0" : "=r"(value) );
        return value;
    }

    void fs (segment_selector value)
    {
        __asm__ ( "mov %0, %%fs" : : "r"(value) : );
    }

    auto gs () -> segment_selector
    {
        segment_selector value {};
        __asm__ ( "mov %%gs, %0" : "=r"(value) );
        return value;
    }

    void gs (segment_selector value)
    {
        __asm__ ( "mov %0, %%gs" : : "r"(value) : );
    }

    auto ss () -> segment_selector
    {
        segment_selector value {};
        __asm__ ( "mov %%ss, %0" : "=r"(value) );
        return value;
    }

    void ss (segment_selector value)
    {
        __asm__ ( "mov %0, %%ss" : : "r"(value) : );
    }
}