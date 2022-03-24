// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/page.h>

// NOTE: inline assembler in `att` syntax.

namespace x86::_32
{
    auto get_short_paging_control_register () -> short_paging_control
    {
        short_paging_control value;
        __asm__ ( "mov %%cr3, %0" : "=r"(value) );
        return value;
    }

    auto get_long_paging_control_register () -> long_paging_control
    {
        long_paging_control value;
        __asm__ ( "mov %%cr3, %0" : "=r"(value) );
        return value;
    }

    void set_paging_control_register (short_paging_control value)
    {
        __asm__ ( "mov %0, %%cr3" : : "r"(value) );
    }

    void set_paging_control_register (long_paging_control value)
    {
        __asm__ ( "mov %0, %%cr3" : : "r"(value) );
    }
}
