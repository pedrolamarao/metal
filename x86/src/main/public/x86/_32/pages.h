// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86::_32
{
    //! Types.
    //! @{

    //! 32 bit page entry.

    class short_page_entry
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
        short_page_entry () = default;

        //! Field constructor.

        constexpr
        short_page_entry (
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

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        short_page_entry (
            decltype(nullptr) ignored,
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            bool dirty,
            unsigned _ExtInt(3) attribute,
            bool global,
            unsigned _ExtInt(3) available,
            size4 address
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

        auto attribute () const -> unsigned _ExtInt(3);

        //! Page is global.

        auto global () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page address.

        auto address () const -> size4;
    };

    static_assert(sizeof(short_page_entry) == 4, "unexpected size of short_page_entry");

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

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        short_small_page_directory_entry (
            decltype(nullptr) ignored,
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            unsigned _ExtInt(3) available,
            size4 address
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
        size4 _present       : 1  {};
        size4 _writable      : 1  {};
        size4 _user          : 1  {};
        size4 _write_through : 1  {};
        size4 _cache         : 1  {};
        size4 _accessed      : 1  {};
        size4 _dirty         : 1  {};
        size4 _large         : 1  {1};
        size4 _global        : 1  {};
        size4 _available     : 3  {};
        size4 _attribute     : 1  {};
        size4 _address_high  : 8  {};
        size4 _zero          : 1  {0};
        size4 _address_low   : 10 {};

    public:

        //! Default constructor.

        constexpr
        short_large_page_directory_entry () = default;

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

        //! Semantic constructor.

        constexpr
        short_large_page_directory_entry (
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            bool dirty,
            bool global,
            unsigned _ExtInt(3) available,
            unsigned _ExtInt(3) attribute,
            size8 address
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

        auto attribute () const -> unsigned _ExtInt(3);

        //! Page address.

        auto address () const -> size8;
    };

    static_assert(sizeof(short_large_page_directory_entry) == 4, "unexpected size of short_large_page_directory_entry");

    //! 64 bit page entry.

    class long_page_entry
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
    
        //! Default constructor.
        
        constexpr
        long_page_entry () = default;

        //! Field constructor.

        constexpr
        long_page_entry (
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

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        long_page_entry (
            decltype(nullptr) ignored,
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            bool dirty,
            unsigned _ExtInt(3) attribute,
            bool global,
            unsigned _ExtInt(3) available,
            size8 address,
            bool executable
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

        auto attribute () const -> unsigned _ExtInt(3);

        //! Page is global.

        auto global () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page address.

        auto address () const -> size8;

        //! Page is executable.

        auto executable () const -> bool;
    };

    static_assert(sizeof(long_page_entry) == 8, "unexpected size of long_page_entry");

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

        //! Default constructor.

        constexpr
        long_small_page_directory_entry () = default;

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

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        long_small_page_directory_entry (
            decltype(nullptr) ignored,
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            unsigned _ExtInt(3) available,
            size8 address,
            bool executable
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

        //! Default constructor.
        
        constexpr
        long_large_page_directory_entry () = default;

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

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        long_large_page_directory_entry (
            decltype(nullptr) ignored,
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            bool dirty,
            bool global,
            unsigned _ExtInt(3) available,
            unsigned _ExtInt(3) attribute,
            size8 address,
            bool executable
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

        auto attribute () const -> unsigned _ExtInt(3);

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

        //! Default constructor.

        constexpr
        page_directory_pointer_entry () = default;

        //! Field constructor.

        constexpr
        page_directory_pointer_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address
        );

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        page_directory_pointer_entry (
            decltype(nullptr) ignored,
            bool present,
            bool write_through,
            bool cache,
            unsigned _ExtInt(3) available,
            size8 address
        );

        //! Page directory is present in memory.

        auto present () const -> bool;

        //! Page directory has write through.

        auto write_through () const -> bool;

        //! Page directory has cache.

        auto cache () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(3);

        //! Page directory table address.

        auto address () const -> size8;
    };

    static_assert(sizeof(page_directory_pointer_entry) == 8, "unexpected size of page_directory_pointer_entry");

    //! Short (i.e. non PAE) paging control.

    class short_paging
    {
        size4 _zero_0        : 3  { 0 };
        size4 _write_through : 1  {};
        size4 _cache         : 1  {};
        size4 _zero_1        : 7  { 0 };
        size4 _address       : 20 {};

    public:

        //! Default constructor.

        constexpr
        short_paging () = default;

        //! Field constructor.

        constexpr
        short_paging (
            unsigned _ExtInt(1) write_through,
            unsigned _ExtInt(1) cache,
            unsigned _ExtInt(20) address
        );

        //! Semantic constructor.

        // #XXX: useless extra parameter to disambiguate constructors

        constexpr
        short_paging (
            decltype(nullptr) ignored,
            bool write_through,
            bool cache,
            size4 address
        );

        //! Paging has write-through.

        auto write_through () const -> bool;

        //! Paging has cache.

        auto cache () const -> bool;

        //! Page directory (pointer) table address.

        auto address () const -> size4;

    };

    static_assert(sizeof(short_paging) == 4, "unexpected size of short_paging");

    //! Long (i.e. PAE) paging control.

    class long_paging
    {
        size4 _zero_0        : 3  { 0 };
        size4 _write_through : 1  {};
        size4 _cache         : 1  {};
        size4 _address       : 27 {};

    public:

        //! Default constructor.

        constexpr
        long_paging () = default;

        //! Field constructor.

        constexpr
        long_paging (
            unsigned _ExtInt(1) write_through,
            unsigned _ExtInt(1) cache,
            unsigned _ExtInt(27) address
        );

        //! Semantic constructor.

        constexpr
        long_paging (
            decltype(nullptr) ignored,
            bool write_through,
            bool cache,
            size4 address
        );

        //! Paging has write-through.

        auto write_through () const -> bool;

        //! Paging has cache.

        auto cache () const -> bool;

        //! Page directory (pointer) table address.

        auto address () const -> size4;

    };

    static_assert(sizeof(long_paging) == 4, "unexpected size of long_paging");

    //! @}

    //! Operators.
    //! @{

    //! Gets the paging control register (CR3) interpreted as short paging.

    auto get_short_paging () -> short_paging;

    //! Gets the paging control register (CR3) interpreted as long paging.

    auto get_long_paging () -> long_paging;

    //! Sets the paging control register (CR3).

    void set_paging (short_paging value);

    //! Sets the paging control register (CR3).

    void set_paging (long_paging value);

    //! @}
}

// Implementation.

namespace x86::_32
{
    constexpr inline
    short_page_entry::short_page_entry (
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

    constexpr inline
    short_page_entry::short_page_entry (
        decltype(nullptr),
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        bool dirty,
        unsigned _ExtInt(3) attribute,
        bool global,
        unsigned _ExtInt(3) available,
        size4 address
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{dirty},
        _attribute{attribute>>2},
        _global{global},
        _available{available},
        _address{address>>12}
    { }

    inline
    auto short_page_entry::present () const -> bool { return _present; }

    inline
    auto short_page_entry::writable () const -> bool { return _writable; }

    inline
    auto short_page_entry::user () const -> bool { return _user; }

    inline
    auto short_page_entry::write_through () const -> bool { return _write_through; }

    inline
    auto short_page_entry::cache () const -> bool { return _cache; }

    inline
    auto short_page_entry::accessed () const -> bool { return _accessed; }

    inline
    auto short_page_entry::dirty () const -> bool { return _dirty; }

    inline
    auto short_page_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto short_page_entry::global () const -> bool { return _global; }

    inline
    auto short_page_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto short_page_entry::address () const -> size4 { return size4{_address} << 12; }

    constexpr inline
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

    constexpr inline
    short_small_page_directory_entry::short_small_page_directory_entry (
        decltype(nullptr),
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        unsigned _ExtInt(3) available,
        size4 address
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available{available},
        _address{address>>12}
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

    constexpr inline
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

    constexpr inline
    short_large_page_directory_entry::short_large_page_directory_entry (
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        bool dirty,
        bool global,
        unsigned _ExtInt(3) available,
        unsigned _ExtInt(3) attribute,
        size8 address
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
        _attribute{attribute>>2},
        _address_high{static_cast<size4>(address>>32)},
        _address_low{static_cast<size4>(address>>22)}
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
    auto short_large_page_directory_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto short_large_page_directory_entry::address () const -> size8 { return (size8{_address_high} << 32) | (size8{_address_low} << 22); }

    constexpr inline
    long_page_entry::long_page_entry (
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

    constexpr inline
    long_page_entry::long_page_entry (
        decltype(nullptr),
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        bool dirty,
        unsigned _ExtInt(3) attribute,
        bool global,
        unsigned _ExtInt(3) available,
        size8 address,
        bool executable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _dirty{dirty},
        _attribute{attribute>>2},
        _global{global},
        _available{available},
        _address{address>>12},
        _executable{executable}
    { }
    
    inline
    auto long_page_entry::present () const -> bool { return _present; }

    inline
    auto long_page_entry::writable () const -> bool { return _writable; }

    inline
    auto long_page_entry::user () const -> bool { return _user; }

    inline
    auto long_page_entry::write_through () const -> bool { return _write_through; }

    inline
    auto long_page_entry::cache () const -> bool { return _cache; }

    inline
    auto long_page_entry::accessed () const -> bool { return _accessed; }

    inline
    auto long_page_entry::dirty () const -> bool { return _dirty; }

    inline
    auto long_page_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto long_page_entry::global () const -> bool { return _global; }

    inline
    auto long_page_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto long_page_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_page_entry::executable () const -> bool { return _executable; }

    constexpr inline
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

    constexpr inline
    long_small_page_directory_entry::long_small_page_directory_entry (
        decltype(nullptr),
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        unsigned _ExtInt(3) available,
        size8 address,
        bool executable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available{available},
        _address{address>>12},
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

    constexpr inline
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

    constexpr inline
    long_large_page_directory_entry::long_large_page_directory_entry (
        decltype(nullptr),
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        bool dirty,
        bool global,
        unsigned _ExtInt(3) available,
        unsigned _ExtInt(3) attribute,
        size8 address,
        bool executable
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
        _address{address>>21},
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
    auto long_large_page_directory_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto long_large_page_directory_entry::address () const -> size8 { return size8{_address} << 21; }

    inline
    auto long_large_page_directory_entry::executable () const -> bool { return _executable; }

    constexpr inline
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

    constexpr inline
    page_directory_pointer_entry::page_directory_pointer_entry (
        decltype(nullptr),
        bool present,
        bool write_through,
        bool cache,
        unsigned _ExtInt(3) available,
        size8 address
    ) :
        _present{present},
        _write_through{write_through},
        _cache{cache},
        _available{available},
        _address{address>>12}
    { }

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

    constexpr inline
    short_paging::short_paging (
        unsigned _ExtInt(1) write_through,
        unsigned _ExtInt(1) cache,
        unsigned _ExtInt(20) address
    ) :
        _write_through{write_through},
        _cache{cache},
        _address{address}
    { }

    constexpr inline
    short_paging::short_paging (
        decltype(nullptr),
        bool write_through,
        bool cache,
        size4 address
    ) :
        _write_through{write_through},
        _cache{cache},
        _address{address >> 12}
    { }

    inline
    auto short_paging::write_through () const -> bool { return _write_through; }

    inline
    auto short_paging::cache () const -> bool { return _cache; }

    inline
    auto short_paging::address () const -> size4 { return size4{_address} << 12; }

    constexpr inline
    long_paging::long_paging (
        unsigned _ExtInt(1) write_through,
        unsigned _ExtInt(1) cache,
        unsigned _ExtInt(27) address
    ) :
        _write_through{write_through},
        _cache{cache},
        _address{address}
    { }

    constexpr inline
    long_paging::long_paging (
        decltype(nullptr),
        bool write_through,
        bool cache,
        size4 address
    ) :
        _write_through{write_through},
        _cache{cache},
        _address{address >> 5}
    { }

    inline
    auto long_paging::write_through () const -> bool { return _write_through; }

    inline
    auto long_paging::cache () const -> bool { return _cache; }

    inline
    auto long_paging::address () const -> size4 { return size4{_address} << 5; }
}