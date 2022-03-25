// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/_32/pages.h>

// NOTE: inline assembler in `att` syntax.

namespace x86::_32
{
    // #XXX: LLVM 13 doesn't know how to do extended asm with _ExtInt
    struct carrier4 { size4 value; };

    void disable_large_pages ()
    {
        carrier4 carrier;
        static_assert(sizeof(carrier) == 4, "unexpected size of carrier");
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        carrier.value &= ~(size4{1} << 4);
        __asm__ ( "mov %0, %%cr4" : : "r"(carrier) );
    }

    void disable_long_addresses ()
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        carrier.value &= ~(size4{1} << 5);
        __asm__ ( "mov %0, %%cr4" : : "r"(carrier) );
    }

    void disable_paging ()
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr0, %0" : "=r"(carrier) );
        carrier.value &= ~(size4{1} << 31);
        __asm__ ( "mov %0, %%cr0" : : "r"(carrier) );
    }

    void enable_large_pages ()
    {
        carrier4 carrier;
        static_assert(sizeof(carrier) == 4, "unexpected size of carrier");
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        carrier.value |= (size4{1} << 4);
        __asm__ ( "mov %0, %%cr4" : : "r"(carrier) );
    }

    void enable_long_addresses ()
    {
        carrier4 carrier;
        static_assert(sizeof(carrier) == 4, "unexpected size of carrier");
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        carrier.value |= (size4{1} << 5);
        __asm__ ( "mov %0, %%cr4" : : "r"(carrier) );
    }

    void enable_paging ()
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr0, %0" : "=r"(carrier) );
        carrier.value |= (size4{1} << 31);
        __asm__ ( "mov %0, %%cr0" : : "r"(carrier) );
    }

    auto is_large_pages () -> bool
    {
        carrier4 carrier;
        static_assert(sizeof(carrier) == 4, "unexpected size of carrier");
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        return (carrier.value & (size4{1} << 4)) != 0;
    }

    auto is_long_addresses () -> bool
    {
        carrier4 carrier;
        static_assert(sizeof(carrier) == 4, "unexpected size of carrier");
        __asm__ ( "mov %%cr4, %0" : "=r"(carrier) );
        return (carrier.value & (size4{1} << 5)) != 0;
    }

    auto is_paging () -> bool
    {
        carrier4 carrier;
        __asm__ ( "mov %%cr0, %0" : "=r"(carrier) );
        return (carrier.value & (size4{1} << 31)) != 0;
    }

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
