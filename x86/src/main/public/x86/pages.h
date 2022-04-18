// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/registers.h>


// Interface.

namespace x86
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

    class extended_page_entry
    {
        size8 _present       :  1 {};
        size8 _writable      :  1 {};
        size8 _user          :  1 {};
        size8 _write_through :  1 {};
        size8 _cache         :  1 {};
        size8 _accessed      :  1 {};
        size8 _dirty         :  1 {};
        size8 _attribute     :  1 {};
        size8 _global        :  1 {};
        size8 _available     :  3 {};
        size8 _address       : 40 {};
        size8 _zero          : 11 { 0 };
        size8 _nonexecutable :  1 {};

    public:

        //! Default constructor.

        constexpr
        extended_page_entry () = default;

        //! Field constructor.

        constexpr
        extended_page_entry (
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
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        extended_page_entry (
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

        //! Page is not executable.

        auto nonexecutable () const -> bool;
    };

    static_assert(sizeof(extended_page_entry) == 8, "unexpected size of extended_page_entry");

    //! 64 bit, 4 KiB page directory entry.

    class extended_small_page_directory_entry
    {
        size8 _present       :  1 {};
        size8 _writable      :  1 {};
        size8 _user          :  1 {};
        size8 _write_through :  1 {};
        size8 _cache         :  1 {};
        size8 _accessed      :  1 {};
        size8 _zero_0        :  3 { 0 };
        size8 _available     :  3 {};
        size8 _address       : 40 {};
        size8 _zero_1        : 11 { 0 };
        size8 _nonexecutable :  1 {};

    public:

        //! Default constructor.

        constexpr
        extended_small_page_directory_entry () = default;

        //! Field constructor.

        constexpr
        extended_small_page_directory_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  user,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address,
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        extended_small_page_directory_entry (
            decltype(nullptr) ignored,
            bool present,
            bool writable,
            bool user,
            bool write_through,
            bool cache,
            bool accessed,
            unsigned _ExtInt(3) available,
            size8 address,
            bool nonexecutable
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

        //! Page table entry is not executable.

        auto nonexecutable () const -> bool;
    };

    static_assert(sizeof(extended_small_page_directory_entry) == 8, "unexpected size of extended_small_page_directory_entry");

    //! 64 bit, 2 MiB page directory entry.

    class extended_large_page_directory_entry
    {
        size8 _present       :  1 {};
        size8 _writable      :  1 {};
        size8 _user          :  1 {};
        size8 _write_through :  1 {};
        size8 _cache         :  1 {};
        size8 _accessed      :  1 {};
        size8 _dirty         :  1 {};
        size8 _long          :  1 { 1 };
        size8 _global        :  1 {};
        size8 _available     :  3 {};
        size8 _attribute     :  1 {};
        size8 _zero_0        :  8 { 0 };
        size8 _address       : 31 {};
        size8 _zero_1        : 11 { 0 };
        size8 _nonexecutable :  1 {};

    public:

        //! Default constructor.

        constexpr
        extended_large_page_directory_entry () = default;

        //! Field constructor.

        constexpr
        extended_large_page_directory_entry (
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
            unsigned _ExtInt(1)  nonexecutable
        );

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        extended_large_page_directory_entry (
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

        auto nonexecutable () const -> bool;
    };

    static_assert(sizeof(extended_large_page_directory_entry) == 8, "unexpected size of extended_large_page_directory_entry");

    //! Page directory pointer entry.

    class extended_page_directory_pointer_entry
    {
        size8 _present       :  1 {};
        size8 _zero_0        :  2 { 0 };
        size8 _write_through :  1 {};
        size8 _cache         :  1 {};
        size8 _zero_1        :  4 { 0 };
        size8 _available     :  3 {};
        size8 _address       : 40 {};
        size8 _zero_2        : 12 { 0 };

    public:

        //! Default constructor.

        constexpr
        extended_page_directory_pointer_entry () = default;

        //! Field constructor.

        constexpr
        extended_page_directory_pointer_entry (
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(1)  write_through,
            unsigned _ExtInt(1)  cache,
            unsigned _ExtInt(3)  available,
            unsigned _ExtInt(40) address
        );

        //! Semantic constructor.

        // #XXX: useless extra parameter for overload disambiguation.

        constexpr
        extended_page_directory_pointer_entry (
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

    static_assert(sizeof(extended_page_directory_pointer_entry) == 8, "unexpected size of extended_page_directory_pointer_entry");

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

    //! Extended (i.e. PAE) paging control.

    class extended_paging
    {
        size4 _zero_0        : 3  { 0 };
        size4 _write_through : 1  {};
        size4 _cache         : 1  {};
        size4 _address       : 27 {};

    public:

        //! Default constructor.

        constexpr
        extended_paging () = default;

        //! Field constructor.

        constexpr
        extended_paging (
            unsigned _ExtInt(1) write_through,
            unsigned _ExtInt(1) cache,
            unsigned _ExtInt(27) address
        );

        //! Semantic constructor.

        constexpr
        extended_paging (
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

    static_assert(sizeof(extended_paging) == 4, "unexpected size of extended_paging");

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

    //! Gets the paging control register (CR3) interpreted as short paging.

    auto get_short_paging () -> short_paging;

    //! Gets the paging control register (CR3) interpreted as extended paging.

    auto get_extended_paging () -> extended_paging;

    //! Gets the paging control register (CR3).

    auto get_long_paging () -> long_paging;

    //! Sets the paging control register (CR3).

    void set_paging (short_paging value);

    //! Sets the paging control register (CR3).

    void set_paging (extended_paging value);

    //! Sets the paging control register (CR3).

    void set_paging (long_paging value);

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

// Implementation: short_page_entry

namespace x86
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
}

// Implementation: short_small_page_directory_entry

namespace x86
{
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
}

// Implementation: short_large_page_directory_entry

namespace x86
{
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
}

// Implementation: short_paging

namespace x86
{
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
}

// Implementation: extended_page_entry

namespace x86
{
    constexpr inline
    extended_page_entry::extended_page_entry (
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
        _available{available},
        _address{address},
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    extended_page_entry::extended_page_entry (
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
        _available{available},
        _address{address>>12},
        _nonexecutable{nonexecutable}
    { }

    inline
    auto extended_page_entry::present () const -> bool { return _present; }

    inline
    auto extended_page_entry::writable () const -> bool { return _writable; }

    inline
    auto extended_page_entry::user () const -> bool { return _user; }

    inline
    auto extended_page_entry::write_through () const -> bool { return _write_through; }

    inline
    auto extended_page_entry::cache () const -> bool { return _cache; }

    inline
    auto extended_page_entry::accessed () const -> bool { return _accessed; }

    inline
    auto extended_page_entry::dirty () const -> bool { return _dirty; }

    inline
    auto extended_page_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto extended_page_entry::global () const -> bool { return _global; }

    inline
    auto extended_page_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto extended_page_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto extended_page_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: extended_small_page_directory_entry

namespace x86
{
    constexpr inline
    extended_small_page_directory_entry::extended_small_page_directory_entry (
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  user,
        unsigned _ExtInt(1)  write_through,
        unsigned _ExtInt(1)  cache,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(3)  available,
        unsigned _ExtInt(40) address,
        unsigned _ExtInt(1)  nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available{available},
        _address{address},
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    extended_small_page_directory_entry::extended_small_page_directory_entry (
        decltype(nullptr),
        bool present,
        bool writable,
        bool user,
        bool write_through,
        bool cache,
        bool accessed,
        unsigned _ExtInt(3) available,
        size8 address,
        bool nonexecutable
    ) :
        _present{present},
        _writable{writable},
        _user{user},
        _write_through{write_through},
        _cache{cache},
        _accessed{accessed},
        _available{available},
        _address{address>>12},
        _nonexecutable{nonexecutable}
    { }

    inline
    auto extended_small_page_directory_entry::present () const -> bool { return _present; }

    inline
    auto extended_small_page_directory_entry::writable () const -> bool { return _writable; }

    inline
    auto extended_small_page_directory_entry::user () const -> bool { return _user; }

    inline
    auto extended_small_page_directory_entry::write_through () const -> bool { return _write_through; }

    inline
    auto extended_small_page_directory_entry::cache () const -> bool { return _cache; }

    inline
    auto extended_small_page_directory_entry::accessed () const -> bool { return _accessed; }

    inline
    auto extended_small_page_directory_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto extended_small_page_directory_entry::address () const -> size8 { return size8{_address} << 12; }

    inline
    auto extended_small_page_directory_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: extended_large_page_directory_entry

namespace x86
{
    constexpr inline
    extended_large_page_directory_entry::extended_large_page_directory_entry (
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
        unsigned _ExtInt(1)  nonexecutable
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
        _nonexecutable{nonexecutable}
    { }

    constexpr inline
    extended_large_page_directory_entry::extended_large_page_directory_entry (
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
        bool nonexecutable
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
        _nonexecutable{nonexecutable}
    { }

    inline
    auto extended_large_page_directory_entry::present () const -> bool { return _present; }

    inline
    auto extended_large_page_directory_entry::writable () const -> bool { return _writable; }

    inline
    auto extended_large_page_directory_entry::user () const -> bool { return _user; }

    inline
    auto extended_large_page_directory_entry::write_through () const -> bool { return _write_through; }

    inline
    auto extended_large_page_directory_entry::cache () const -> bool { return _cache; }

    inline
    auto extended_large_page_directory_entry::accessed () const -> bool { return _accessed; }

    inline
    auto extended_large_page_directory_entry::dirty () const -> bool { return _dirty; }

    inline
    auto extended_large_page_directory_entry::global () const -> bool { return _global; }

    inline
    auto extended_large_page_directory_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto extended_large_page_directory_entry::attribute () const -> unsigned _ExtInt(3) { return _attribute << 2; }

    inline
    auto extended_large_page_directory_entry::address () const -> size8 { return size8{_address} << 21; }

    inline
    auto extended_large_page_directory_entry::nonexecutable () const -> bool { return _nonexecutable; }
}

// Implementation: extended_page_directory_pointer_entry

namespace x86
{
    constexpr inline
    extended_page_directory_pointer_entry::extended_page_directory_pointer_entry (
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
    extended_page_directory_pointer_entry::extended_page_directory_pointer_entry (
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
    auto extended_page_directory_pointer_entry::present () const -> bool { return _present; }

    inline
    auto extended_page_directory_pointer_entry::write_through () const -> bool { return _write_through; }

    inline
    auto extended_page_directory_pointer_entry::cache () const -> bool { return _cache; }

    inline
    auto extended_page_directory_pointer_entry::available () const -> unsigned _ExtInt(3) { return _available; }

    inline
    auto extended_page_directory_pointer_entry::address () const -> size8 { return size8{_address} << 12; }
}

// Implementation: extended_paging

namespace x86
{
    constexpr inline
    extended_paging::extended_paging (
        unsigned _ExtInt(1) write_through,
        unsigned _ExtInt(1) cache,
        unsigned _ExtInt(27) address
    ) :
        _write_through{write_through},
        _cache{cache},
        _address{address}
    { }

    constexpr inline
    extended_paging::extended_paging (
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
    auto extended_paging::write_through () const -> bool { return _write_through; }

    inline
    auto extended_paging::cache () const -> bool { return _cache; }

    inline
    auto extended_paging::address () const -> size4 { return size4{_address} << 5; }
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

    inline
    auto long_paging::write_through () const -> bool { return _write_through; }

    inline
    auto long_paging::cache () const -> bool { return _cache; }

    inline
    auto long_paging::address () const -> size8 { return _address << 12; }
}

// Implementation: operators

namespace x86
{
    inline
    auto get_short_paging () -> short_paging
    {
        size value = cr3();
        return reinterpret_cast<short_paging&>(value);
    }

    inline
    void set_paging (short_paging value)
    {
        cr3( reinterpret_cast<size&>(value) );
    }

    inline
    auto get_extended_paging () -> extended_paging
    {
        size value = cr3();
        return reinterpret_cast<extended_paging&>(value);
    }

    inline
    void set_paging (extended_paging value)
    {
        cr3( reinterpret_cast<size&>(value) );
    }

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
