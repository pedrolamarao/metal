// Copyright (C) 2012,2013,2014,2015,2016,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>
#include <x86/instructions.h>
#include <x86/registers.h>


// Interface.

namespace x86
{
    //! Types.
    //! @{

    //! Code segment descriptor.

    class code_segment_descriptor
    {
        size4 _limit_low    : 16 {};
        size4 _base_low     : 16 {};
        size4 _base_middle  :  8 {};
        size4 _accessed     :  1 {};
        size4 _readable     :  1 {};
        size4 _conforming   :  1 {};
        size4 _type         :  1 { 1 };
        size4 _user         :  1 { 1 };
        size4 _privilege    :  2 {};
        size4 _present      :  1 {};
        size4 _limit_high   :  4 {};
        size4 _available    :  1 {};
        size4 _long         :  1 {};
        size4 _operand      :  1 {};
        size4 _granularity  :  1 {};
        size4 _base_high    :  8 {};

    public:

        //! Default constructor.

        constexpr
        code_segment_descriptor () = default;

        //! Field constructor.

        constexpr
        code_segment_descriptor (
            unsigned _ExtInt(16) limit_low,
            unsigned _ExtInt(16) base_low,
            unsigned _ExtInt(8)  base_middle,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(1)  readable,
            unsigned _ExtInt(1)  conforming,
            unsigned _ExtInt(2)  privilege,
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(4)  limit_high,
            unsigned _ExtInt(1)  available,
            unsigned _ExtInt(1)  is_long,
            unsigned _ExtInt(1)  operand,
            unsigned _ExtInt(1)  granularity,
            unsigned _ExtInt(8)  base_high
        );

        //! Semantic constructor.

        constexpr
        code_segment_descriptor (
            size4 base,
            size4 limit,
            bool accessed,
            bool readable,
            bool conforming,
            unsigned _ExtInt(2) privilege,
            bool present,
            unsigned _ExtInt(1) available,
            bool is_64bit,
            bool is_32bit,
            bool is_4kb
        );

        auto base () const -> size4 ;

        auto limit () const -> size4 ;

        auto accessed () const -> bool ;

        auto readable () const -> bool ;

        auto conforming () const -> bool ;

        auto privilege () const -> unsigned _ExtInt(2) ;

        auto present () const -> bool ;

        auto available () const -> unsigned _ExtInt(1) ;

        auto is_64bit () const -> bool ;

        auto is_32bit () const -> bool ;

        auto is_4kb () const -> bool ;
    };

    static_assert(sizeof(code_segment_descriptor) == 8, "unexpected size of code_segment_descriptor");

    //! Data segment descriptor.

    class data_segment_descriptor
    {
        size4 _limit_low    : 16 {};
        size4 _base_low     : 16 {};
        size4 _base_middle  :  8 {};
        size4 _accessed     :  1 {};
        size4 _writable     :  1 {};
        size4 _expand_down  :  1 {};
        size4 _type         :  1 { 0 };
        size4 _user         :  1 { 1 };
        size4 _privilege    :  2 {};
        size4 _present      :  1 {};
        size4 _limit_high   :  4 {};
        size4 _available    :  1 {};
        size4 _zero         :  1 { 0 };
        size4 _operand      :  1 {};
        size4 _granularity  :  1 {};
        size4 _base_high    :  8 {};

    public:

        //! Default constructor.

        constexpr
        data_segment_descriptor () = default;

        //! Field constructor.

        constexpr
        data_segment_descriptor (
            unsigned _ExtInt(16) limit_low,
            unsigned _ExtInt(16) base_low,
            unsigned _ExtInt(8)  base_middle,
            unsigned _ExtInt(1)  accessed,
            unsigned _ExtInt(1)  writable,
            unsigned _ExtInt(1)  expand_down,
            unsigned _ExtInt(2)  privilege,
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(4)  limit_high,
            unsigned _ExtInt(1)  available,
            unsigned _ExtInt(1)  operand,
            unsigned _ExtInt(1)  granularity,
            unsigned _ExtInt(8)  base_high
        );

        //! Semantic constructor.

        constexpr
        data_segment_descriptor (
            size4 base,
            size4 limit,
            bool accessed,
            bool writable,
            bool expand_down,
            unsigned _ExtInt(2) privilege,
            bool present,
            unsigned _ExtInt(1) available,
            bool is_32bit,
            bool is_4kb
        );

        auto base () const -> size4 ;

        auto limit () const -> size4 ;

        auto accessed () const -> bool ;

        auto writable () const -> bool ;

        auto expand_down () const -> bool ;

        auto privilege () const -> unsigned _ExtInt(2) ;

        auto present () const -> bool ;

        auto available () const -> unsigned _ExtInt(1) ;

        auto is_32bit () const -> bool ;

        auto is_4kb () const -> bool ;
    };

    static_assert(sizeof(data_segment_descriptor) == 8, "unexpected size of data_segment_descriptor");

    //! @}

    //! Operators.
    //! @{

    //! Call to far memory reference.

    void far_call ( segment_selector segment, void (* target) () );

    //! Set code segment register (CS).

    void set_code_segment ( segment_selector value );

    //! Set data segment registers (DS, ES, FS, GS, SS).

    void set_data_segments ( segment_selector value );

    //! Set global descriptor table register (GDTR).

    void set_global_descriptor_table (void* table, size2 size);

  //! @}
}

// Implementation: code_segment_descriptor

namespace x86
{
    constexpr inline
    code_segment_descriptor::code_segment_descriptor (
        unsigned _ExtInt(16) limit_low,
        unsigned _ExtInt(16) base_low,
        unsigned _ExtInt(8)  base_middle,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(1)  readable,
        unsigned _ExtInt(1)  conforming,
        unsigned _ExtInt(2)  privilege,
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(4)  limit_high,
        unsigned _ExtInt(1)  available,
        unsigned _ExtInt(1)  is_long,
        unsigned _ExtInt(1)  operand,
        unsigned _ExtInt(1)  granularity,
        unsigned _ExtInt(8)  base_high
    ) :
        _limit_low{limit_low},
        _base_low{base_low},
        _base_middle{base_middle},
        _accessed{accessed},
        _readable{readable},
        _conforming{conforming},
        _privilege{privilege},
        _present{present},
        _limit_high{limit_high},
        _available{available},
        _long{is_long},
        _operand{operand},
        _granularity{granularity},
        _base_high{base_high}
    { }

    constexpr inline
    code_segment_descriptor::code_segment_descriptor (
        size4 base,
        size4 limit,
        bool accessed,
        bool readable,
        bool conforming,
        unsigned _ExtInt(2) privilege,
        bool present,
        unsigned _ExtInt(1) available,
        bool is_long,
        bool operand,
        bool granularity
    ) :
        _limit_low { limit & 0xFFFF },
        _base_low { base & 0xFFFF },
        _base_middle { (base >> 16) & 0xFF },
        _accessed{accessed},
        _readable{readable},
        _conforming{conforming},
        _privilege{privilege},
        _present{present},
        _limit_high { (limit >> 16) & 0xF },
        _available{available},
        _long{is_long},
        _operand{operand},
        _granularity{granularity},
        _base_high { (base >> 24) & 0xFF }
    { }

    inline
    auto code_segment_descriptor::base () const -> size4 { return (_base_high << 24) | (_base_middle << 16) | _base_low; };

    inline
    auto code_segment_descriptor::limit () const -> size4 { return (_limit_high << 16) | _limit_low; };

    inline
    auto code_segment_descriptor::accessed () const -> bool { return _accessed; };

    inline
    auto code_segment_descriptor::readable () const -> bool { return _readable; };

    inline
    auto code_segment_descriptor::conforming () const -> bool { return _conforming; };

    inline
    auto code_segment_descriptor::privilege () const -> unsigned _ExtInt(2) { return _privilege; };

    inline
    auto code_segment_descriptor::present () const -> bool { return _present; };

    inline
    auto code_segment_descriptor::available () const -> unsigned _ExtInt(1) { return _available; };

    inline
    auto code_segment_descriptor::is_64bit () const -> bool { return _long; };

    inline
    auto code_segment_descriptor::is_32bit () const -> bool { return _operand; };

    inline
    auto code_segment_descriptor::is_4kb () const -> bool { return _granularity; };
}

// Implementation: data_segment_descriptor

namespace x86
{
    constexpr inline
    data_segment_descriptor::data_segment_descriptor (
        unsigned _ExtInt(16) limit_low,
        unsigned _ExtInt(16) base_low,
        unsigned _ExtInt(8)  base_middle,
        unsigned _ExtInt(1)  accessed,
        unsigned _ExtInt(1)  writable,
        unsigned _ExtInt(1)  expand_down,
        unsigned _ExtInt(2)  privilege,
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(4)  limit_high,
        unsigned _ExtInt(1)  available,
        unsigned _ExtInt(1)  operand,
        unsigned _ExtInt(1)  granularity,
        unsigned _ExtInt(8)  base_high
    ) :
        _limit_low{limit_low},
        _base_low{base_low},
        _base_middle{base_middle},
        _accessed{accessed},
        _writable{writable},
        _expand_down{expand_down},
        _privilege{privilege},
        _present{present},
        _limit_high{limit_high},
        _available{available},
        _operand{operand},
        _granularity{granularity},
        _base_high{base_high}
    { }

    constexpr inline
    data_segment_descriptor::data_segment_descriptor (
        size4 base,
        size4 limit,
        bool accessed,
        bool writable,
        bool expand_down,
        unsigned _ExtInt(2) privilege,
        bool present,
        unsigned _ExtInt(1) available,
        bool operand,
        bool granularity
    ) :
        _limit_low { limit & 0xFFFF },
        _base_low { base & 0xFFFF },
        _base_middle { (base >> 16) & 0xFF },
        _accessed{accessed},
        _writable{writable},
        _expand_down{expand_down},
        _privilege{privilege},
        _present{present},
        _limit_high { (limit >> 16) & 0xF },
        _available{available},
        _operand{operand},
        _granularity{granularity},
        _base_high { (base >> 24) & 0xFF }
    { }

    inline
    auto data_segment_descriptor::base () const -> size4 { return (_base_high << 24) | (_base_middle << 16) | _base_low; };

    inline
    auto data_segment_descriptor::limit () const -> size4 { return (_limit_high << 16) | _limit_low; };

    inline
    auto data_segment_descriptor::accessed () const -> bool { return _accessed; };

    inline
    auto data_segment_descriptor::writable () const -> bool { return _writable; };

    inline
    auto data_segment_descriptor::expand_down () const -> bool { return _expand_down; };

    inline
    auto data_segment_descriptor::privilege () const -> unsigned _ExtInt(2) { return _privilege; };

    inline
    auto data_segment_descriptor::present () const -> bool { return _present; };

    inline
    auto data_segment_descriptor::available () const -> unsigned _ExtInt(1) { return _available; };

    inline
    auto data_segment_descriptor::is_32bit () const -> bool { return _operand; };

    inline
    auto data_segment_descriptor::is_4kb () const -> bool { return _granularity; };
}

// Implementation: operators

namespace x86
{
    inline
    void far_call ( segment_selector segment, void (* target) () )
    {
        call({ reinterpret_cast<size>(target), static_cast<size2>(segment) });
    }

    inline
    void set_data_segments ( segment_selector value )
    {
        ds(value);
        es(value);
        fs(value);
        gs(value);
        ss(value);
    }

    //! @pre 0 < size <= 0xFFFF

    inline
    void set_global_descriptor_table (void* table, size2 size)
    {
        gdtr({ size - size2{1}, reinterpret_cast<x86::size>(table) });
    }
}