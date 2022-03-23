// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86::_32
{
    //! Types.
    //! @{

    //! 32 bit, 4 KiB page table entry.

    class short_small_page_table_entry
    {
        size4 _present       : 1;
        size4 _writable      : 1;
        size4 _user          : 1;
        size4 _write_through : 1;
        size4 _cache         : 1;
        size4 _accessed      : 1;
        size4 _dirty         : 1;
        size4 _attribute     : 1;
        size4 _global        : 1;
        size4 _available     : 3;
        size4 _address       : 20;
        
    public:

        //! Field constructor.

        constexpr
        short_small_page_table_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(1)  dirty,
            unsigned _ExtInt(1)  attribute,
            unsigned _ExtInt(1)  global,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(20) address
        );

        //! Page is present in memory.

        auto present () const -> bool;

        //! Page is writable.

        auto writable () const -> bool;

        //! Page is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page has write through.

        auto write_through () const -> bool;

        //! Page has cache.

        auto cache () const -> bool;

        //! Page was accessed.

        auto accessed () const -> bool;

        //! Page is dirty.

        auto dirty () const -> bool;

        //! Page attribute high bit.

        auto attribute () const -> unsigned _ExtInt(1);

        //! Page is global.

        auto global () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page base address.

        auto address () const -> size4;
    };

    static_assert(sizeof(short_small_page_table_entry) == 4, "unexpected size of short_small_page_table_entry");

    //! 32 bit, 4 KiB page directory entry.

    class short_small_page_directory_entry
    {
        size4 _present       : 1;
        size4 _writable      : 1;
        size4 _user          : 1;
        size4 _write_through : 1;
        size4 _cache         : 1;
        size4 _accessed      : 1;
        size4 _dirty         : 1;
        size4 _large         : 1;
        size4 _global        : 1;
        size4 _available     : 3;
        size4 _address       : 20;

    public:

        //! Field constructor.

        constexpr
        short_small_page_directory_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(20) address
        );

        //! Page table is present in memory.

        auto present () const -> bool;

        //! Page table is writable.

        auto writable () const -> bool;

        //! Page table is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page table has write-through.

        auto write_through () const -> bool;

        //! Page table has cache.

        auto cache () const -> bool;

        //! Page table was accessed.

        auto accessed () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page table address.

        auto address () const -> size4;
    };

    static_assert(sizeof(short_small_page_directory_entry) == 4, "unexpected size of short_small_page_directory_entry");

    //! 32 bit, 4 MiB page directory entry.

    class short_large_page_directory_entry
    {
        size4 _present       : 1;
        size4 _writable      : 1;
        size4 _user          : 1;
        size4 _write_through : 1;
        size4 _cache         : 1;
        size4 _accessed      : 1;
        size4 _dirty         : 1;
        size4 _large         : 1;
        size4 _global        : 1;
        size4 _available     : 3;
        size4 _attribute     : 1;
        size4 _address_high  : 8;
        size4 _ignored       : 1;
        size4 _address_low   : 10;

    public:

        //! Field constructor.

        constexpr
        short_large_page_directory_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(1)  dirty,
            unsigned _ExtInt(1)  global,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(1)  attribute,
            unsigned _ExtInt(8)  address_high,
            unsigned _ExtInt(10) address_low
        );

        //! Page is present in memory.

        auto present () const -> bool;

        //! Page is writable.

        auto writable () const -> bool;

        //! Page is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page has write-through.

        auto write_through () const -> bool;

        //! Page has cache.

        auto cache () const -> bool;

        //! Page was accessed.

        auto accessed () const -> bool;

        //! Page is dirty.

        auto dirty () const -> bool;

        //! Page is global.

        auto global () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page attribute high bit.

        auto attribute () const -> unsigned _ExtInt(1);

        //! Page base address.

        auto address () const -> size8;
    };

    static_assert(sizeof(short_large_page_directory_entry) == 4, "unexpected size of short_large_page_directory_entry");

    //! Page table 64 bit entry for 4 KiB pages.

    class small_page_table_extended_entry
    {
        size8 _present       :  1;
        size8 _writable      :  1;
        size8 _user          :  1;
        size8 _write_through :  1;
        size8 _cache         :  1;
        size8 _accessed      :  1;
        size8 _dirty         :  1;
        size8 _attribute     :  1;
        size8 _global        :  1;
        size8 _available     :  3;
        size8 _address       : 40;
        size8 _zero          : 11 = 0;
        size8 _executable    :  1;

    public:

        //! Field constructor.

        constexpr
        small_page_table_extended_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(1)  dirty,
            unsigned _ExtInt(1)  attribute,
            unsigned _ExtInt(1)  global,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(1)  executable
        );

        //! Page is present in memory.

        auto present () const -> bool;

        //! Page is writable.

        auto writable () const -> bool;

        //! Page is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page has write through.

        auto write_through () const -> bool;

        //! Page has cache.

        auto cache () const -> bool;

        //! Page was accessed.

        auto accessed () const -> bool;

        //! Page is dirty.

        auto dirty () const -> bool;

        //! Page attribute high bit.

        auto attribute () const -> unsigned _ExtInt(1);

        //! Page is global.

        auto global () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page base address.

        auto address () const -> size8;

        //! Page is executable.

        auto executable () const -> bool;
    };

    static_assert(sizeof(small_page_table_extended_entry) == 8, "unexpected size of small_page_table_extended_entry");

    //! Page directory 64 bit entry for 4 KiB pages.

    class small_page_directory_extended_entry
    {
        size8 _present       :  1;
        size8 _writable      :  1;
        size8 _user          :  1;
        size8 _write_through :  1;
        size8 _cache         :  1;
        size8 _accessed      :  1;
        size8 _zero_0        :  3 = 0;
        size8 _available     :  3;
        size8 _address       : 40;
        size8 _zero_1        : 11 = 0;
        size8 _executable    :  1;

    public:

        //! Field constructor.

        constexpr
        small_page_directory_extended_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(1)  executable
        );

        //! Page table is present in memory.

        auto present () const -> bool;

        //! Page table is writable.

        auto writable () const -> bool;

        //! Page table is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page table has write through.

        auto write_through () const -> bool;

        //! Page table has cache.

        auto cache () const -> bool;

        //! Page table was accessed.

        auto accessed () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page base address.

        auto address () const -> size8;

        //! Page is executable.

        auto executable () const -> bool;
    };

    static_assert(sizeof(small_page_directory_extended_entry) == 8, "unexpected size of small_page_directory_extended_entry");

    //! Page directory pointer 64 bit entry for 4 KiB pages.

    class small_page_directory_pointer_extended_entry
    {
        size8 _present       :  1;
        size8 _zero_0        :  2 = 0;
        size8 _write_through :  1;
        size8 _cache         :  1;
        size8 _zero_1        :  4 = 0;
        size8 _available     :  3;
        size8 _address       : 40;
        size8 _zero_2        : 12 = 0;

    public:

        //! Field constructor.

        constexpr
        small_page_directory_pointer_extended_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address
        );

        //! Page table is present in memory.

        auto present () const -> bool;

        //! Page table has write through.

        auto write_through () const -> bool;

        //! Page table has cache.

        auto cache () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page base address.

        auto address () const -> size8;
    };

    static_assert(sizeof(small_page_directory_pointer_extended_entry) == 8, "unexpected size of small_page_directory_pointer_extended_entry");
}

// Implementation.

namespace x86::_32
{
    inline constexpr
    short_small_page_table_entry::short_small_page_table_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(1)  dirty,
        unsigned _ExtInt(1)  attribute,
        unsigned _ExtInt(1)  global,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(20) address
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{dirty},
        _attribute{attribute},
        _global{global},
        _available{available},
        _address{address}
    { }

    inline
    auto short_small_page_table_entry::present () const -> bool { return _present; }

    inline
    auto short_small_page_table_entry::writable () const -> bool { return _writable; }

    inline
    auto short_small_page_table_entry::user () const -> bool { return _user; }

    inline
    auto short_small_page_table_entry::write_through () const -> bool { return _write_through; }

    inline
    auto short_small_page_table_entry::cache () const -> bool { return _cache; }

    inline
    auto short_small_page_table_entry::accessed () const -> bool { return _accessed; }

    inline
    auto short_small_page_table_entry::dirty () const -> bool { return _dirty; }

    inline
    auto short_small_page_table_entry::attribute () const -> unsigned _ExtInt(1) { return _attribute; }

    inline
    auto short_small_page_table_entry::global () const -> bool { return _global; }

    inline
    auto short_small_page_table_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto short_small_page_table_entry::address () const -> size4 { return _address << 12; }

    inline constexpr
    short_small_page_directory_entry::short_small_page_directory_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(20) address
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{0},
        _large{0},
        _global{0},
        _available{available},
        _address{address}
    { }

    inline
    auto short_small_page_directory_entry::present () const -> bool { return _present; }

    inline
    auto short_small_page_directory_entry::writable () const -> bool { return _writable; }

    inline
    auto short_small_page_directory_entry::user () const -> bool { return _user; }

    inline
    auto short_small_page_directory_entry::write_through () const -> bool { return _write_through; }

    inline
    auto short_small_page_directory_entry::cache () const -> bool { return _cache; }

    inline
    auto short_small_page_directory_entry::accessed () const -> bool { return _accessed; }

    inline
    auto short_small_page_directory_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto short_small_page_directory_entry::address () const -> size4 { return _address << 12; }

    inline constexpr
    short_large_page_directory_entry::short_large_page_directory_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(1)  dirty,
        unsigned _ExtInt(1)  global,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(1)  attribute,
        unsigned _ExtInt(8)  address_high,
        unsigned _ExtInt(10) address_low
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{dirty},
        _large{1},
        _global{global},
        _available{available},
        _attribute{attribute},
        _address_high{address_high},
        _address_low{address_low}
    { }

    inline
    auto short_large_page_directory_entry::present () const -> bool { return _present; }

    inline
    auto short_large_page_directory_entry::writable () const -> bool { return _writable; }

    inline
    auto short_large_page_directory_entry::user () const -> bool { return _user; }

    inline
    auto short_large_page_directory_entry::write_through () const -> bool { return _write_through; }

    inline
    auto short_large_page_directory_entry::cache () const -> bool { return _cache; }

    inline
    auto short_large_page_directory_entry::accessed () const -> bool { return _accessed; }

    inline
    auto short_large_page_directory_entry::dirty () const -> bool { return _dirty; }

    inline
    auto short_large_page_directory_entry::global () const -> bool { return _global; }

    inline
    auto short_large_page_directory_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto short_large_page_directory_entry::attribute () const -> unsigned _ExtInt(1) { return _attribute; }

    inline
    auto short_large_page_directory_entry::address () const -> size8 { return (size8{_address_high} << 32) | (size8{_address_low} << 22); }

    inline constexpr
    small_page_table_extended_entry::small_page_table_extended_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(1)  dirty,
        unsigned _ExtInt(1)  attribute,
        unsigned _ExtInt(1)  global,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(1)  executable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{dirty},
        _attribute{attribute},
        _global{global},
        _available{available},
        _address{address},
        _executable{executable}
    { }

    inline
    auto small_page_table_extended_entry::present () const -> bool { return _present; }

    inline
    auto small_page_table_extended_entry::writable () const -> bool { return _writable; }

    inline
    auto small_page_table_extended_entry::user () const -> bool { return _user; }

    inline
    auto small_page_table_extended_entry::write_through () const -> bool { return _write_through; }

    inline
    auto small_page_table_extended_entry::cache () const -> bool { return _cache; }

    inline
    auto small_page_table_extended_entry::accessed () const -> bool { return _accessed; }

    inline
    auto small_page_table_extended_entry::dirty () const -> bool { return _dirty; }

    inline
    auto small_page_table_extended_entry::attribute () const -> unsigned _ExtInt(1) { return _attribute; }

    inline
    auto small_page_table_extended_entry::global () const -> bool { return _global; }

    inline
    auto small_page_table_extended_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto small_page_table_extended_entry::address () const -> size8 { return _address << 12; }

    inline
    auto small_page_table_extended_entry::executable () const -> bool { return _executable; }

    inline constexpr
    small_page_directory_extended_entry::small_page_directory_extended_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(1)  executable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available{available},
        _address{address},
        _executable{executable}
    { }

    inline
    auto small_page_directory_extended_entry::present () const -> bool { return _present; }

    inline
    auto small_page_directory_extended_entry::writable () const -> bool { return _writable; }

    inline
    auto small_page_directory_extended_entry::user () const -> bool { return _user; }

    inline
    auto small_page_directory_extended_entry::write_through () const -> bool { return _write_through; }

    inline
    auto small_page_directory_extended_entry::cache () const -> bool { return _cache; }

    inline
    auto small_page_directory_extended_entry::accessed () const -> bool { return _accessed; }

    inline
    auto small_page_directory_extended_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto small_page_directory_extended_entry::address () const -> size8 { return _address << 12; }

    inline
    auto small_page_directory_extended_entry::executable () const -> bool { return _executable; }

    inline constexpr
    small_page_directory_pointer_extended_entry::small_page_directory_pointer_extended_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(40) address
    ) :
        _present{present},
        _write_through{write_through},
        _cache{cache},
        _available{available},
        _address{address}
    { }

    inline
    auto small_page_directory_pointer_extended_entry::present () const -> bool { return _present; }

    inline
    auto small_page_directory_pointer_extended_entry::write_through () const -> bool { return _write_through; }

    inline
    auto small_page_directory_pointer_extended_entry::cache () const -> bool { return _cache; }

    inline
    auto small_page_directory_pointer_extended_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto small_page_directory_pointer_extended_entry::address () const -> size8 { return _address << 12; }
}