// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86::_32
{
    //! Types.
    //! @{

    //! 32 bit page table entry.

    class short_page_table_entry
    {
        size4 _present       : 1 {};
        size4 _writable      : 1 {};
        size4 _user          : 1 {};
        size4 _write_through : 1 {};
        size4 _cache         : 1 {};
        size4 _accessed      : 1 {};
        size4 _dirty         : 1 {};
        size4 _attribute     : 1 {};
        size4 _global        : 1 {};
        size4 _available     : 3 {};
        size4 _address       : 20 {};
        
    public:

        //! Default constructor.

        constexpr
        short_page_table_entry () = default;

        //! Field constructor.

        constexpr
        short_page_table_entry (
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

        //! Page address.

        auto address () const -> size4;
    };

    static_assert(sizeof(short_page_table_entry) == 4, "unexpected size of short_page_table_entry");

    //! 32 bit, 4 KiB page directory entry.

    class short_small_page_directory_entry
    {
        size4 _present       : 1  {};
        size4 _writable      : 1  {};
        size4 _user          : 1  {};
        size4 _write_through : 1  {};
        size4 _cache         : 1  {};
        size4 _accessed      : 1  {};
        size4 _zero          : 3  { 0 };
        size4 _available     : 3  {};
        size4 _address       : 20 {};

    public:

        //! Default constructor.

        constexpr
        short_small_page_directory_entry () = default;

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
        size4 _large         : 1 = 1;
        size4 _global        : 1;
        size4 _available     : 3;
        size4 _attribute     : 1;
        size4 _address_high  : 8;
        size4 _zero          : 1 = 0;
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

        //! Page address.

        auto address () const -> size8;
    };

    static_assert(sizeof(short_large_page_directory_entry) == 4, "unexpected size of short_large_page_directory_entry");

    //! 64 bit page table entry.

    class long_page_table_entry
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
        long_page_table_entry (
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

        //! Page address.

        auto address () const -> size8;

        //! Page is executable.

        auto executable () const -> bool;
    };

    static_assert(sizeof(long_page_table_entry) == 8, "unexpected size of long_page_table_entry");

    //! 64 bit, 4 KiB page directory entry.

    class long_small_page_directory_entry
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
        long_small_page_directory_entry (
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

        //! Page table entry is present in memory.

        auto present () const -> bool;

        //! Page table entry is writable.

        auto writable () const -> bool;

        //! Page table entry is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page table entry has write through.

        auto write_through () const -> bool;

        //! Page table entry has cache.

        auto cache () const -> bool;

        //! Page table entry was accessed.

        auto accessed () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page table address.

        auto address () const -> size8;

        //! Page table entry is executable.

        auto executable () const -> bool;
    };

    static_assert(sizeof(long_small_page_directory_entry) == 8, "unexpected size of long_small_page_directory_entry");

    //! 64 bit, 2 MiB page directory entry.

    class long_large_page_directory_entry
    {
        size8 _present       :  1;
        size8 _writable      :  1;
        size8 _user          :  1;
        size8 _write_through :  1;
        size8 _cache         :  1;
        size8 _accessed      :  1;
        size8 _dirty         :  1;
        size8 _long          :  1 = 1;
        size8 _global        :  1;
        size8 _available     :  3;
        size8 _attribute     :  1;
        size8 _zero_0        :  8 = 0;
        size8 _address       : 31;
        size8 _zero_1        : 11 = 0;
        size8 _executable    :  1;

    public:

        //! Field constructor.

        constexpr
        long_large_page_directory_entry (
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
            unsigned _ExtInt(31) address,
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

        //! Page is global.

        auto global () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page attribute high bit.

        auto attribute () const -> unsigned _ExtInt(1);

        //! Page address.

        auto address () const -> size8;

        //! Page is executable.

        auto executable () const -> bool;
    };

    static_assert(sizeof(long_large_page_directory_entry) == 8, "unexpected size of long_large_page_directory_entry");

    //! Page directory pointer entry.

    class page_directory_pointer_entry
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
        page_directory_pointer_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address
        );

        //! Page directory is present in memory.

        auto present () const -> bool;

        //! Page directory has write through.

        auto write_through () const -> bool;

        //! Page directory has cache.

        auto cache () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page directory address.

        auto address () const -> size8;
    };

    static_assert(sizeof(page_directory_pointer_entry) == 8, "unexpected size of page_directory_pointer_entry");

    //! Short (i.e. non PAE) paging control.

    class short_paging_control
    {
        size4 _zero_0        : 3 = 0;
        size4 _write_through : 1;
        size4 _cache         : 1;
        size4 _zero_1        : 7 = 0;
        size4 _address       : 20;

    public:

        //! Default constructor.

        short_paging_control () = default;

        //! Field constructor.

        short_paging_control (
            unsigned _ExtInt(1) write_through,
            unsigned _ExtInt(1) cache,
            unsigned _ExtInt(20) address
        );

        //! Paging has write-through.

        auto write_through () const -> bool;

        //! Paging has cache.

        auto cache () const -> bool;

        //! Page directory pointer address.

        auto address () const -> size4;

    };

    static_assert(sizeof(short_paging_control) == 4, "unexpected size of short_paging_control");

    //! Long (i.e. PAE) paging control.

    class long_paging_control
    {
        size4 _zero_0        : 3 = 0;
        size4 _write_through : 1;
        size4 _cache         : 1;
        size4 _address       : 27;

    public:

        //! Default constructor.

        long_paging_control () = default;

        //! Field constructor.

        long_paging_control (
            unsigned _ExtInt(1) write_through,
            unsigned _ExtInt(1) cache,
            unsigned _ExtInt(26) address
        );

        //! Paging has write-through.

        auto write_through () const -> bool;

        //! Paging has cache.

        auto cache () const -> bool;

        //! Page directory pointer address.

        auto address () const -> size4;

    };

    static_assert(sizeof(long_paging_control) == 4, "unexpected size of long_paging_control");

    //! @}

    //! Operators.
    //! @{

    //! Gets the CR3 paging control register interpreted as short paging.

    auto get_short_paging_control_register () -> short_paging_control;

    //! Gets the CR3 paging control register interpreted as long paging.

    auto get_long_paging_control_register () -> long_paging_control;

    //! Sets the CR3 paging control register.

    void set_paging_control_register (short_paging_control value);

    //! Sets the CR3 paging control register.

    void set_paging_control_register (long_paging_control value);

    //! @}
}

// Implementation.

namespace x86::_32
{
    inline constexpr
    short_page_table_entry::short_page_table_entry (
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
    auto short_page_table_entry::present () const -> bool { return _present; }

    inline
    auto short_page_table_entry::writable () const -> bool { return _writable; }

    inline
    auto short_page_table_entry::user () const -> bool { return _user; }

    inline
    auto short_page_table_entry::write_through () const -> bool { return _write_through; }

    inline
    auto short_page_table_entry::cache () const -> bool { return _cache; }

    inline
    auto short_page_table_entry::accessed () const -> bool { return _accessed; }

    inline
    auto short_page_table_entry::dirty () const -> bool { return _dirty; }

    inline
    auto short_page_table_entry::attribute () const -> unsigned _ExtInt(1) { return _attribute; }

    inline
    auto short_page_table_entry::global () const -> bool { return _global; }

    inline
    auto short_page_table_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto short_page_table_entry::address () const -> size4 { return size4{_address} << 12; }

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
    auto short_small_page_directory_entry::address () const -> size4 { return size4{_address} << 12; }

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
    long_page_table_entry::long_page_table_entry (
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
    auto long_page_table_entry::present () const -> bool { return _present; }

    inline
    auto long_page_table_entry::writable () const -> bool { return _writable; }

    inline
    auto long_page_table_entry::user () const -> bool { return _user; }

    inline
    auto long_page_table_entry::write_through () const -> bool { return _write_through; }

    inline
    auto long_page_table_entry::cache () const -> bool { return _cache; }

    inline
    auto long_page_table_entry::accessed () const -> bool { return _accessed; }

    inline
    auto long_page_table_entry::dirty () const -> bool { return _dirty; }

    inline
    auto long_page_table_entry::attribute () const -> unsigned _ExtInt(1) { return _attribute; }

    inline
    auto long_page_table_entry::global () const -> bool { return _global; }

    inline
    auto long_page_table_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto long_page_table_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_page_table_entry::executable () const -> bool { return _executable; }

    inline constexpr
    long_small_page_directory_entry::long_small_page_directory_entry (
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
    auto long_small_page_directory_entry::present () const -> bool { return _present; }

    inline
    auto long_small_page_directory_entry::writable () const -> bool { return _writable; }

    inline
    auto long_small_page_directory_entry::user () const -> bool { return _user; }

    inline
    auto long_small_page_directory_entry::write_through () const -> bool { return _write_through; }

    inline
    auto long_small_page_directory_entry::cache () const -> bool { return _cache; }

    inline
    auto long_small_page_directory_entry::accessed () const -> bool { return _accessed; }

    inline
    auto long_small_page_directory_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto long_small_page_directory_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_small_page_directory_entry::executable () const -> bool { return _executable; }

    inline constexpr
    long_large_page_directory_entry::long_large_page_directory_entry (
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
        unsigned _ExtInt(31) address,
        unsigned _ExtInt(1)  executable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{dirty},
        _global{global},
        _available{available},
        _attribute{attribute},
        _address{address},
        _executable{executable}
    { }

    inline
    auto long_large_page_directory_entry::present () const -> bool { return _present; }

    inline
    auto long_large_page_directory_entry::writable () const -> bool { return _writable; }

    inline
    auto long_large_page_directory_entry::user () const -> bool { return _user; }

    inline
    auto long_large_page_directory_entry::write_through () const -> bool { return _write_through; }

    inline
    auto long_large_page_directory_entry::cache () const -> bool { return _cache; }

    inline
    auto long_large_page_directory_entry::accessed () const -> bool { return _accessed; }

    inline
    auto long_large_page_directory_entry::dirty () const -> bool { return _dirty; }

    inline
    auto long_large_page_directory_entry::global () const -> bool { return _global; }

    inline
    auto long_large_page_directory_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto long_large_page_directory_entry::attribute () const -> unsigned _ExtInt(1) { return _attribute; }

    inline
    auto long_large_page_directory_entry::address () const -> size8 { return size8{_address} << 21; }

    inline
    auto long_large_page_directory_entry::executable () const -> bool { return _executable; }

    inline constexpr
    page_directory_pointer_entry::page_directory_pointer_entry (
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
    short_paging_control::short_paging_control (
        unsigned _ExtInt(1) write_through,
        unsigned _ExtInt(1) cache,
        unsigned _ExtInt(20) address
    ) :
        _write_through{write_through},
        _cache{cache},
        _address{address}
    { }

    inline
    auto short_paging_control::write_through () const -> bool { return _write_through; }

    inline
    auto short_paging_control::cache () const -> bool { return _cache; }

    inline
    auto short_paging_control::address () const -> size4 { return size4{_address} << 12; }

    inline
    auto page_directory_pointer_entry::present () const -> bool { return _present; }

    inline
    auto page_directory_pointer_entry::write_through () const -> bool { return _write_through; }

    inline
    auto page_directory_pointer_entry::cache () const -> bool { return _cache; }

    inline
    auto page_directory_pointer_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto page_directory_pointer_entry::address () const -> size8 { return size8{_address} << 12; }
}