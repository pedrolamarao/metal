// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/pages.h>
#include <x86/_32/registers.h>

// NOTE: inline assembler in `att` syntax.

namespace x86::_32
{
    void disable_large_pages ()
    {
        cr4( cr4() & ~(size4{1} << 4) );
    }

    void disable_long_addresses ()
    {
        cr4( cr4() & ~(size4{1} << 5) );
    }

    void disable_paging ()
    {
        cr0( cr0() & ~(size4{1} << 31) );
    }

    void enable_large_pages ()
    {
        cr4( cr4() | (size4{1} << 4) );
    }

    void enable_long_addresses ()
    {
        cr4( cr4() | (size4{1} << 5) );
    }

    void enable_paging ()
    {
        cr0( cr0() | (size4{1} << 31) );
    }

    auto is_large_pages () -> bool
    {
        return (cr4() & (size4{1} << 4)) != 0;
    }

    auto is_long_addresses () -> bool
    {
        return (cr4() & (size4{1} << 5)) != 0;
    }

    auto is_paging () -> bool
    {
        return (cr0() & (size4{1} << 31)) != 0;
    }

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
