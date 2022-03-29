// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/registers.h>
#include <x86/_32/pages.h>
#include <x86/_64/pages.h>


// Interface.

namespace x86
{
    //! Operators.
    //! @{

    //! Disable large pages (CR4.PSE).

    void disable_large_pages ();

    //! Disable long addresses (CR4.PAE).

    void disable_long_addresses ();

    //! Disable paging (CR0.PG).

    void disable_paging ();

    //! Enable large pages (CR4.PSE).

    void enable_large_pages ();

    //! Enable long addresses (CR4.PAE).

    void enable_long_addresses ();

    //! Enable paging (CR0.PG).

    void enable_paging ();

    //! Is large pages enabled (CR4.PSE)?

    auto is_large_pages () -> bool;

    //! Is long addresses enabled (CR4.PAE)?

    auto is_long_addresses () -> bool;

    //! Is paging enabled (CR0.PG)?

    auto is_paging () -> bool;

    //! @}
}

// Implementation.

namespace x86
{
    inline
    void disable_large_pages ()
    {
        cr4( cr4() & ~(size4{1} << 4) );
    }

    inline
    void disable_long_addresses ()
    {
        cr4( cr4() & ~(size4{1} << 5) );
    }

    inline
    void disable_paging ()
    {
        cr0( cr0() & ~(size4{1} << 31) );
    }

    inline
    void enable_large_pages ()
    {
        cr4( cr4() | (size4{1} << 4) );
    }

    inline
    void enable_long_addresses ()
    {
        cr4( cr4() | (size4{1} << 5) );
    }

    inline
    void enable_paging ()
    {
        cr0( cr0() | (size4{1} << 31) );
    }

    inline
    auto is_large_pages () -> bool
    {
        return (cr4() & (size4{1} << 4)) != 0;
    }

    inline
    auto is_long_addresses () -> bool
    {
        return (cr4() & (size4{1} << 5)) != 0;
    }

    inline
    auto is_paging () -> bool
    {
        return (cr0() & (size4{1} << 31)) != 0;
    }
}