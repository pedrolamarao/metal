// Copyright (C) 2012,2013,2014,2015,2016,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>
#include <x86/registers.h>


//! Declarations

namespace x86
{
    //! Types.
    //! @{

    //! Short interrupt gate descriptor.

    class short_interrupt_gate_descriptor
    {
        size2 _offset_low  : 16 {};
        size2 _segment     : 16 {};
        size1 _reserved    :  8 { 0 };
        size1 _trap        :  1 {};
        size1 _type1       :  1 { 1 };
        size1 _type2       :  1 { 1 };
        size1 _32bit       :  1 {};
        size1 _user        :  1 { 0 };
        size1 _privilege   :  2 {};
        size1 _present     :  1 {};
        size2 _offset_high : 16 {};

    public:

        //! Default constructor.

        constexpr
        short_interrupt_gate_descriptor () = default;

        //! Field constructor.

        constexpr
        short_interrupt_gate_descriptor (
            unsigned _ExtInt(16) offset_low,
            unsigned _ExtInt(16) segment,
            unsigned _ExtInt(1)  trap,
            unsigned _ExtInt(1)  is_32bit,
            unsigned _ExtInt(2)  privilege,
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(16) offset_high
        );

        //! Semantic constructor.

        constexpr
        short_interrupt_gate_descriptor (
            segment_selector segment,
            size4 offset,
            bool is_present,
            bool is_trap,
            privilege_level privilege,
            bool is_32bit
        );

        //! Semantic constructor.

        short_interrupt_gate_descriptor (
            segment_selector segment,
            void (* offset)(),
            bool is_present,
            bool is_trap,
            privilege_level privilege,
            bool is_32bit
        );

        auto is_32bit () const -> bool;

        auto is_present () const -> bool;

        auto is_trap () const -> bool;

        auto offset () const -> size4;

        auto privilege () const -> privilege_level;

        auto segment () const -> segment_selector;
    };

    static_assert(sizeof(short_interrupt_gate_descriptor) == 8, "unexpected size of short_interrupt_gate_descriptor");

    //! Long interrupt gate descriptor.

    class long_interrupt_gate_descriptor
    {
        size2 _offset_low  : 16 {};
        size2 _segment     : 16 {};
        size1 _reserved0   :  8 { 0 };
        size1 _trap        :  1 {};
        size1 _type1       :  1 { 1 };
        size1 _type2       :  1 { 1 };
        size1 _32bit       :  1 {};
        size1 _user        :  1 { 0 };
        size1 _privilege   :  2 {};
        size1 _present     :  1 {};
        size2 _offset_mid  : 16 {};
        size4 _offset_high : 32 {};
        size4 _reserved1   : 32 {};

    public:

        //! Default constructor.

        constexpr
        long_interrupt_gate_descriptor () = default;

        //! Field constructor.

        constexpr
        long_interrupt_gate_descriptor (
            unsigned _ExtInt(16) offset_low,
            unsigned _ExtInt(16) segment,
            unsigned _ExtInt(1)  trap,
            unsigned _ExtInt(1)  is_32bit,
            unsigned _ExtInt(2)  privilege,
            unsigned _ExtInt(1)  present,
            unsigned _ExtInt(16) offset_mid,
            unsigned _ExtInt(32) offset_high
        );

        //! Semantic constructor.

        constexpr
        long_interrupt_gate_descriptor (
            segment_selector segment,
            size8 offset,
            bool is_present,
            bool is_trap,
            privilege_level privilege,
            bool is_32bit
        );

        //! Semantic constructor.

        long_interrupt_gate_descriptor (
            segment_selector segment,
            void (* offset)(),
            bool is_present,
            bool is_trap,
            privilege_level privilege,
            bool is_32bit
        );

        auto is_32bit () const -> bool;

        auto is_present () const -> bool;

        auto is_trap () const -> bool;

        auto offset () const -> size8;

        auto privilege () const -> privilege_level;

        auto segment () const -> segment_selector;
    };

    static_assert(sizeof(long_interrupt_gate_descriptor) == 16, "unexpected size of long_interrupt_gate_descriptor");

    //! @}

    //! Operators.
    //! @{

    //! Set the interrupts descriptor table register (IDTR).

    template <unsigned N>
    void set_interrupt_descriptor_table ( short_interrupt_gate_descriptor const (& table) [N] );

    //! Set the interrupts descriptor table register (IDTR).

    template <unsigned N>
    void set_interrupt_descriptor_table ( long_interrupt_gate_descriptor const (& table) [N] );

    //! Enable interrupts on this processor.

    void enable_interrupts ();

    //! Disables interrupts on this processor.

    void disable_interrupts ();

    //! Interrupt this processor.

    template <unsigned N>
    void interrupt ();

    //! @}
}

//! Definitions

namespace x86
{
    constexpr
    short_interrupt_gate_descriptor::short_interrupt_gate_descriptor (
        unsigned _ExtInt(16) offset_low,
        unsigned _ExtInt(16) segment,
        unsigned _ExtInt(1)  trap,
        unsigned _ExtInt(1)  is_32bit,
        unsigned _ExtInt(2)  privilege,
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(16) offset_high
    ) :
        _offset_low { offset_low },
        _segment { segment },
        _trap { trap },
        _32bit { is_32bit },
        _privilege { privilege },
        _present { present },
        _offset_high { offset_high }
    { }

    constexpr inline
    short_interrupt_gate_descriptor::short_interrupt_gate_descriptor (
        segment_selector segment,
        size4 offset,
        bool is_present,
        bool is_trap,
        privilege_level privilege,
        bool is_32bit
    ) :
        _offset_low { static_cast<size2>(offset & 0xFFFF) },
        _segment { size2{segment} },
        _trap { is_trap },
        _32bit { is_32bit },
        _privilege { privilege },
        _present { is_present },
        _offset_high { static_cast<size2>((offset >> 16) & 0xFFFF) }
    { }

    inline
    short_interrupt_gate_descriptor::short_interrupt_gate_descriptor (
        segment_selector segment,
        void (* offset)(),
        bool is_present,
        bool is_trap,
        privilege_level privilege,
        bool is_32bit
    )
        : short_interrupt_gate_descriptor { segment, halt_cast<size4>(offset), is_present, is_trap, privilege, is_32bit }
    { }

    inline
    auto short_interrupt_gate_descriptor::is_32bit () const -> bool { return _32bit; }

    inline
    auto short_interrupt_gate_descriptor::is_present () const -> bool { return _present; }

    inline
    auto short_interrupt_gate_descriptor::is_trap () const -> bool { return _trap; }

    inline
    auto short_interrupt_gate_descriptor::privilege () const -> privilege_level { return _privilege; }

    inline
    auto short_interrupt_gate_descriptor::offset () const -> size4 { return (_offset_high << 16) | _offset_low; }

    inline
    auto short_interrupt_gate_descriptor::segment () const -> segment_selector { return segment_selector { _segment }; }
    constexpr
    long_interrupt_gate_descriptor::long_interrupt_gate_descriptor (
        unsigned _ExtInt(16) offset_low,
        unsigned _ExtInt(16) segment,
        unsigned _ExtInt(1)  trap,
        unsigned _ExtInt(1)  is_32bit,
        unsigned _ExtInt(2)  privilege,
        unsigned _ExtInt(1)  present,
        unsigned _ExtInt(16) offset_mid,
        unsigned _ExtInt(32) offset_high
    ) :
        _offset_low { offset_low },
        _segment { segment },
        _trap { trap },
        _32bit { is_32bit },
        _privilege { privilege },
        _present { present },
        _offset_mid { offset_mid },
        _offset_high { offset_high }
    { }

    constexpr inline
    long_interrupt_gate_descriptor::long_interrupt_gate_descriptor (
        segment_selector segment,
        size8 offset,
        bool is_present,
        bool is_trap,
        privilege_level privilege,
        bool is_32bit
    ) :
        _offset_low { static_cast<size2>(offset & 0xFFFF) },
        _segment { size2{segment} },
        _trap { is_trap },
        _32bit { is_32bit },
        _privilege { privilege },
        _present { is_present },
        _offset_mid { static_cast<size2>((offset >> 16) & 0xFFFF) },
        _offset_high { static_cast<size4>((offset >> 32) & 0xFFFFFFFF) }
    { }

    inline
    long_interrupt_gate_descriptor::long_interrupt_gate_descriptor (
        segment_selector segment,
        void (* offset)(),
        bool is_present,
        bool is_trap,
        privilege_level privilege,
        bool is_32bit
    )
    : long_interrupt_gate_descriptor { segment, reinterpret_cast<size8>(offset), is_present, is_trap, privilege, is_32bit }
    { }

    inline
    auto long_interrupt_gate_descriptor::is_32bit () const -> bool { return _32bit; }

    inline
    auto long_interrupt_gate_descriptor::is_present () const -> bool { return _present; }

    inline
    auto long_interrupt_gate_descriptor::is_trap () const -> bool { return _trap; }

    inline
    auto long_interrupt_gate_descriptor::privilege () const -> privilege_level { return _privilege; }

    inline
    auto long_interrupt_gate_descriptor::offset () const -> size8 {
        return size8{_offset_high} << 32 | size8{_offset_mid} << 16 | size8{_offset_low};
    }

    inline
    auto long_interrupt_gate_descriptor::segment () const -> segment_selector { return segment_selector { _segment }; }

    template <unsigned N>
    inline
    void set_interrupt_descriptor_table ( short_interrupt_gate_descriptor const (& table) [N] )
    {
        descriptor_table value { N * sizeof(short_interrupt_gate_descriptor), reinterpret_cast<size>(table) };
        idtr(value);
    }

    template <unsigned N>
    inline
    void set_interrupt_descriptor_table ( long_interrupt_gate_descriptor const (& table) [N] )
    {
        descriptor_table value { N * sizeof(long_interrupt_gate_descriptor), reinterpret_cast<size>(table) };
        idtr(value);
    }

    template <unsigned N>
    inline
    void interrupt ()
    {
        __asm__ volatile ("int %0" : : "N"(N) : "cc", "memory");
    }
}