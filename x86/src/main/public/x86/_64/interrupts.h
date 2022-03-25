// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>
#include <x86/_64/descriptor.h>


// Interface.

namespace x86::_64
{
  //! Types.
  //! @{

  //! Interrupt gate descriptor.

  class interrupt_gate_descriptor : public descriptor
  {
  public:

    constexpr
    interrupt_gate_descriptor ();

    constexpr
    interrupt_gate_descriptor (
      segment_selector segment,
      size8 offset,
      bool is_present,
      bool must_cli,
      privilege_level privilege,
      bool is_32bit
    );

    interrupt_gate_descriptor (
      segment_selector segment,
      void (* offset)(),
      bool is_present,
      bool must_cli,
      privilege_level privilege,
      bool is_32bit
    );

    auto is_32bit () const -> bool;

    auto is_trap () const -> bool;

    auto must_cli () const -> bool;

    auto offset () const -> size8;

    auto segment () const -> segment_selector;

  };

  static_assert(sizeof(interrupt_gate_descriptor) == 16, "unexpected size of interrupt_gate_descriptor");

  //! Interrupt descriptor table register.

  struct [[gnu::packed]] interrupt_descriptor_table_register
  {
    size2 size;
    size8 offset;
  };

  constexpr
  auto operator== ( interrupt_descriptor_table_register, interrupt_descriptor_table_register) -> bool;

  static_assert(sizeof(interrupt_descriptor_table_register) == 10, "unexpected size of interrupt_descriptor_table_register");

  //! @}

  //! Operators.
  //! @{

  //! Get the global descriptor table register

  auto get_interrupt_descriptor_table () -> interrupt_descriptor_table_register ;

  //! Set the global descriptor table register

  void set_interrupt_descriptor_table_register ( interrupt_descriptor_table_register value );

  //! Set the global descriptor table register

  template <unsigned N>
  void set_interrupt_descriptor_table_register ( interrupt_gate_descriptor const (& table) [N] );

  //! @}
}

// Implementation.

namespace x86::_64
{
  constexpr inline
  interrupt_gate_descriptor::interrupt_gate_descriptor () : descriptor {}
  { }

  constexpr inline
  interrupt_gate_descriptor::interrupt_gate_descriptor (
    segment_selector segment,
    size8 offset,
    bool is_present,
    bool must_cli,
    privilege_level privilege,
    bool is_32bit
  )
  : descriptor {
      static_cast<size2>(
        offset & 0xFFFF
      ),
      static_cast<size2>(
        segment
      ),
      static_cast<size2>(
        (is_present ? 1 : 0) << 15 |
        size2{privilege}     << 13 |
        (is_32bit ? 1 : 0)   << 11 |
        1                    << 10 |
        1                    <<  9 |
        (must_cli ? 0 : 1)
      ),
      static_cast<size2>(
        (offset >> 16) & 0xFFFF
      ),
      static_cast<size4>(
        offset >> 32
      ),
      0
    }
  { }

  inline
  interrupt_gate_descriptor::interrupt_gate_descriptor (
    segment_selector segment,
    void (* offset)(),
    bool is_present,
    bool must_cli,
    privilege_level privilege,
    bool is_32bit
  )
  : interrupt_gate_descriptor { segment, reinterpret_cast<size>(offset), is_present, must_cli, privilege, is_32bit }
  { }

  inline
  auto interrupt_gate_descriptor::is_32bit () const -> bool { return (_w2 & 0x400) != 0; }

  inline
  auto interrupt_gate_descriptor::is_trap () const -> bool { return (_w2 & 0x100) != 0; }

  inline
  auto interrupt_gate_descriptor::must_cli () const -> bool { return (_w2 & 0x100) == 0; }

  inline
  auto interrupt_gate_descriptor::offset () const -> size8 {
    return ((size8{_q4} << 32) & 0xFFFFFFFF00000000) |
           ((size8{_w3} << 16) & 0x00000000FFFF0000) |
            (size8{_w0}        & 0x000000000000FFFF);
  }

  inline
  auto interrupt_gate_descriptor::segment () const -> segment_selector {
    return segment_selector { _w1 };
  }

  constexpr inline
  auto operator== ( interrupt_descriptor_table_register x, interrupt_descriptor_table_register y ) -> bool
  {
    return (x.size == y.size) && (x.offset == y.offset);
  }

  template <unsigned N>
  inline
  void set_interrupt_descriptor_table_register ( interrupt_gate_descriptor const (& table) [N] )
  {
    interrupt_descriptor_table_register value {
      N * sizeof(interrupt_gate_descriptor),
      reinterpret_cast<ps::size>(table)
    };
    set_interrupt_descriptor_table_register(value);
  }
}