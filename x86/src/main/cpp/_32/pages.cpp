// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/pages.h>
#include <x86/registers.h>

// NOTE: inline assembler in `att` syntax.

namespace x86::_32
{
    auto get_short_paging () -> short_paging
    {
        short_paging value;
        __asm__ ( "mov %%cr3, %0" : "=r"(value) );
        return value;
    }

    auto get_long_paging () -> long_paging
    {
        long_paging value;
        __asm__ ( "mov %%cr3, %0" : "=r"(value) );
        return value;
    }

    void set_paging (short_paging value)
    {
        __asm__ ( "mov %0, %%cr3" : : "r"(value) );
    }

    void set_paging (long_paging value)
    {
        __asm__ ( "mov %0, %%cr3" : : "r"(value) );
    }
}
