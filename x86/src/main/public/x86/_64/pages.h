// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>
#include <x86/registers.h>


// Interface.

namespace x86
{
    //! Types.
    //! @{

    //! Page table entry.

    class long_page_table_entry
    {
        size8 _present        :  1 {};
        size8 _writable       :  1 {};
        size8 _user           :  1 {};
        size8 _write_through  :  1 {};
        size8 _cache          :  1 {};
        size8 _accessed       :  1 {};
        size8 _dirty          :  1 {};
        size8 _attribute      :  1 {};
        size8 _global         :  1 {};
        size8 _available_low  :  3 {};
        size8 _address        : 40 {};
        size8 _available_high :  7 {};
        size8 _mpk            :  4 {};
        size8 _nonexecutable  :  1 {};

    public:
    
        //! Default constructor.
        
        constexpr
        long_page_table_entry () = default;

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
            unsigned _ExtInt(3)  available_low,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(7)  available_high,
            unsigned _ExtInt(4)  mpk,
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        constexpr
        long_page_table_entry (
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            bool dirty,
            unsigned _ExtInt(3) attribute,
            bool global,
            unsigned _ExtInt(10) available,
            size8 address,
            unsigned _ExtInt(4) mpk,
            bool nonexecutable
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

        //! Page is dirty.

        auto dirty () const -> bool;

        //! Page attribute.

        auto attribute () const -> unsigned _ExtInt(3);

        //! Page is global.

        auto global () const -> bool;

        //! Page was accessed.

        auto accessed () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(10);

        //! Page address.

        auto address () const -> size8;

        //! Page memory protection key.

        auto mpk () const -> unsigned _ExtInt(4);

        //! Page is not executable.

        auto nonexecutable () const -> bool;
    };

    static_assert(sizeof(long_page_table_entry) == 8, "unexpected size of long_page_table_entry");

    //! 4 KiB page directory entry.

    class long_small_page_directory_entry
    {
        size8 _present        :  1 {};
        size8 _writable       :  1 {};
        size8 _user           :  1 {};
        size8 _write_through  :  1 {};
        size8 _cache          :  1 {};
        size8 _accessed       :  1 {};
        size8 _ignored_0      :  1 { 0 };
        size8 _zero           :  1 { 0 };
        size8 _ignored_1      :  1 { 0 };
        size8 _available_low  :  3 {};
        size8 _address        : 40 {};
        size8 _available_high : 11 {};
        size8 _nonexecutable  :  1 {};

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
            unsigned _ExtInt(3)  available_low,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(11) available_high,
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        constexpr
        long_small_page_directory_entry (
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            unsigned _ExtInt(14) available,
            size8 address,
            bool nonexecutable
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

        auto available () const -> unsigned _ExtInt(14);

        //! Page table address.

        auto address () const -> size8;

        //! Page table is not executable.

        auto nonexecutable () const -> bool;
    };

    static_assert(sizeof(long_small_page_directory_entry) == 8, "unexpected size of long_small_page_directory_entry");

    //! 4 KiB page directory pointer entry.

    class long_small_page_directory_pointer_entry
    {
        size8 _present        :  1 {};
        size8 _writable       :  1 {};
        size8 _user           :  1 {};
        size8 _write_through  :  1 {};
        size8 _cache          :  1 {};
        size8 _accessed       :  1 {};
        size8 _ignored_0      :  1 { 0 };
        size8 _zero           :  1 { 0 };
        size8 _ignored_1      :  1 { 0 };
        size8 _available_low  :  3 {};
        size8 _address        : 40 {};
        size8 _available_high : 11 {};
        size8 _nonexecutable  :  1 {};

    public:

        //! Default constructor.

        constexpr
        long_small_page_directory_pointer_entry () = default;

        //! Field constructor.

        constexpr
        long_small_page_directory_pointer_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(3)  available_low,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(11) available_high,
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        constexpr
        long_small_page_directory_pointer_entry (
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            unsigned _ExtInt(14) available,
            size8 address,
            bool nonexecutable
        );

        //! Page directory is present in memory.

        auto present () const -> bool;

        //! Page directory is writable.

        auto writable () const -> bool;

        //! Page directory is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page directory has write through.

        auto write_through () const -> bool;

        //! Page directory has cache.

        auto cache () const -> bool;

        //! Page directory was accessed.

        auto accessed () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(14);

        //! Page directory address.

        auto address () const -> size8;

        //! Page directory is not executable.

        auto nonexecutable () const -> bool;
    };

    static_assert(sizeof(long_small_page_directory_pointer_entry) == 8, "unexpected size of long_small_page_directory_pointer_entry");

    //! Page map entry.

    class long_page_map_entry
    {
        size8 _present        :  1 {};
        size8 _writable       :  1 {};
        size8 _user           :  1 {};
        size8 _write_through  :  1 {};
        size8 _cache          :  1 {};
        size8 _accessed       :  1 {};
        size8 _ignored_0      :  1 { 0 };
        size8 _zero           :  1 { 0 };
        size8 _ignored_1      :  1 { 0 };
        size8 _available_low  :  3 {};
        size8 _address        : 40 {};
        size8 _available_high : 11 {};
        size8 _nonexecutable  :  1 {};

    public:

        //! Default constructor.

        constexpr
        long_page_map_entry () = default;

        //! Field constructor.

        constexpr
        long_page_map_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(3)  available_low,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(11) available_high,
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        constexpr
        long_page_map_entry (
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            unsigned _ExtInt(14) available,
            size8 address,
            bool nonexecutable
        );

        //! Page directory pointer is present in memory.

        auto present () const -> bool;

        //! Page directory pointer is writable.

        auto writable () const -> bool;

        //! Page directory pointer is accessible by user (i.e. DPL 0).

        auto user () const -> bool;

        //! Page directory pointer has write through.

        auto write_through () const -> bool;

        //! Page directory pointer has cache.

        auto cache () const -> bool;

        //! Page directory pointer was accessed.

        auto accessed () const -> bool;

        //! Bits available to software.

        auto available () const -> unsigned _ExtInt(14);

        //! Page directory pointer address.

        auto address () const -> size8;

        //! Page directory pointer is not executable.

        auto nonexecutable () const -> bool;

    };

    static_assert(sizeof(long_page_map_entry) == 8, "unexpected size of long_page_map_entry ");

    //! Paging control register (CR3).

    class long_paging
    {
        size8 _zero_0        :  3 { 0 };
        size8 _write_through :  1 {};
        size8 _cache         :  1 {};
        size8 _zero_1        :  7 { 0 };
        size8 _address       : 40 {};
        size8 _zero_2        : 12 { 0 };

    public:

        //! Default constructor.

        constexpr
        long_paging () = default;

        //! Field constructor.

        constexpr
        long_paging (
            unsigned _ExtInt(1) write_through,
            unsigned _ExtInt(1) cache,
            unsigned _ExtInt(40) address
        );

        //! Semantic constructor.

        constexpr
        long_paging (
            decltype(nullptr) ignored,
            bool write_through,
            bool cache,
            size8 address
        );

        //! long_paging has write-through.

        auto write_through () const -> bool;

        //! long_paging has cache.

        auto cache () const -> bool;

        //! Page directory (pointer) table address.

        auto address () const -> size8;

    };

    static_assert(sizeof(long_paging) == 8, "unexpected size of long_paging");

    //! @}

    //! Operators.
    //! @{

    //! Gets the paging control register (CR3).

    auto get_long_paging () -> long_paging;

    //! Sets the paging control register (CR3).

    void set_paging (long_paging value);

    //! @}
}

// Implementation: long_page_table_entry

namespace x86
{
    constexpr inline
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
        unsigned _ExtInt(3)  available_low,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(7)  available_high,
        unsigned _ExtInt(4)  mpk,
        unsigned _ExtInt(1)  nonexecutable
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
        _available_low{available_low},
        _address{address},
        _available_high{available_high},
        _mpk{mpk},
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    long_page_table_entry::long_page_table_entry (
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        bool dirty,
        unsigned _ExtInt(3) attribute,
        bool global,
        unsigned _ExtInt(10) available,
        size8 address,
        unsigned _ExtInt(4) mpk,
        bool nonexecutable
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
        _available_low{available},
        _address{address>>12},
        _available_high{available>>3},
        _mpk{mpk},
        _nonexecutable{nonexecutable}
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
    auto long_page_table_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto long_page_table_entry::global () const -> bool { return _global; }

    inline
    auto long_page_table_entry::available () const -> unsigned _ExtInt(10) { return (_available_high << 3) | _available_low; }

    inline
    auto long_page_table_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_page_table_entry::mpk () const -> unsigned _ExtInt(4) { return _mpk; }

    inline
    auto long_page_table_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: long_small_page_directory_entry

namespace x86
{
    constexpr inline
    long_small_page_directory_entry::long_small_page_directory_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(3)  available_low,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(11) available_high,
        unsigned _ExtInt(1)  nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available_low{available_low},
        _address{address},
        _available_high{available_high},
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    long_small_page_directory_entry::long_small_page_directory_entry (
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        unsigned _ExtInt(14) available,
        size8 address,
        bool nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available_low{available},
        _address{address>>12},
        _available_high{available>>3},
        _nonexecutable{nonexecutable}
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
    auto long_small_page_directory_entry::available () const -> unsigned _ExtInt(14) { return (_available_high << 3) | _available_low; }

    inline
    auto long_small_page_directory_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_small_page_directory_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: long_small_page_directory_pointer_entry

namespace x86
{
    constexpr inline
    long_small_page_directory_pointer_entry::long_small_page_directory_pointer_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(3)  available_low,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(11) available_high,
        unsigned _ExtInt(1)  nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available_low{available_low},
        _address{address},
        _available_high{available_high},
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    long_small_page_directory_pointer_entry::long_small_page_directory_pointer_entry (
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        unsigned _ExtInt(14) available,
        size8 address,
        bool nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available_low{available},
        _address{address>>12},
        _available_high{available>>3},
        _nonexecutable{nonexecutable}
    { }

    inline
    auto long_small_page_directory_pointer_entry::present () const -> bool { return _present; }

    inline
    auto long_small_page_directory_pointer_entry::writable () const -> bool { return _writable; }

    inline
    auto long_small_page_directory_pointer_entry::user () const -> bool { return _user; }

    inline
    auto long_small_page_directory_pointer_entry::write_through () const -> bool { return _write_through; }

    inline
    auto long_small_page_directory_pointer_entry::cache () const -> bool { return _cache; }

    inline
    auto long_small_page_directory_pointer_entry::accessed () const -> bool { return _accessed; }

    inline
    auto long_small_page_directory_pointer_entry::available () const -> unsigned _ExtInt(14) { return (_available_high << 3) | _available_low; }

    inline
    auto long_small_page_directory_pointer_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_small_page_directory_pointer_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: long_page_map_entry

namespace x86
{
    constexpr inline
    long_page_map_entry::long_page_map_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(3)  available_low,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(11) available_high,
        unsigned _ExtInt(1)  nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available_low{available_low},
        _address{address},
        _available_high{available_high},
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    long_page_map_entry::long_page_map_entry (
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        unsigned _ExtInt(14) available,
        size8 address,
        bool nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available_low{available},
        _address{address>>12},
        _available_high{available>>3},
        _nonexecutable{nonexecutable}
    { }

    inline
    auto long_page_map_entry::present () const -> bool { return _present; }

    inline
    auto long_page_map_entry::writable () const -> bool { return _writable; }

    inline
    auto long_page_map_entry::user () const -> bool { return _user; }

    inline
    auto long_page_map_entry::write_through () const -> bool { return _write_through; }

    inline
    auto long_page_map_entry::cache () const -> bool { return _cache; }

    inline
    auto long_page_map_entry::accessed () const -> bool { return _accessed; }

    inline
    auto long_page_map_entry::available () const -> unsigned _ExtInt(14) { return (_available_high << 3) | _available_low; }

    inline
    auto long_page_map_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto long_page_map_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: long_paging

namespace x86
{
    constexpr inline
    long_paging::long_paging (
        unsigned _ExtInt(1) write_through,
        unsigned _ExtInt(1) cache,
        unsigned _ExtInt(40) address
    ) :
        _write_through { write_through },
        _cache { cache },
        _address { address }
    { }

    constexpr inline
    long_paging::long_paging (
        decltype(nullptr) ignored,
        bool write_through,
        bool cache,
        size8 address
    ) :
        _write_through { write_through },
        _cache { cache },
        _address { address >> 12 }
    { }

    auto long_paging::write_through () const -> bool { return _write_through; }

    auto long_paging::cache () const -> bool { return _cache; }

    auto long_paging::address () const -> size8 { return _address << 12; }
}
