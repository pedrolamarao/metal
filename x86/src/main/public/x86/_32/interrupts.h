// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>
#include <x86/registers.h>
#include <x86/_32/descriptor.h>


// Interface.

namespace x86
{
  //! Types.
  //! @{

  //! Interrupt gate descriptor.

  class short_interrupt_gate_descriptor : public _32::descriptor
  {
  public:

    constexpr
    short_interrupt_gate_descriptor ();

    constexpr
    short_interrupt_gate_descriptor (
      segment_selector segment,
      size4 offset,
      bool is_present,
      bool must_cli,
      privilege_level privilege,
      bool is_32bit
    );

    short_interrupt_gate_descriptor (
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

    auto offset () const -> size4;

    auto segment () const -> segment_selector;

  };

  static_assert(sizeof(short_interrupt_gate_descriptor) == 8, "unexpected size of interrupt_gate_descriptor");

  //! @}

  //! Operators.
  //! @{

  //! Set the global descriptor table register (IDTR).

  template <unsigned N>
  void set_interrupt_descriptor_table ( short_interrupt_gate_descriptor const (& table) [N] );

  //! @}
}

// Implementation.

namespace x86
{
  constexpr inline
  short_interrupt_gate_descriptor::short_interrupt_gate_descriptor () : descriptor {}
  { }

  constexpr inline
  short_interrupt_gate_descriptor::short_interrupt_gate_descriptor (
    segment_selector segment,
    size4 offset,
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
      )
    }
  { }

  inline
  short_interrupt_gate_descriptor::short_interrupt_gate_descriptor (
    segment_selector segment,
    void (* offset)(),
    bool is_present,
    bool must_cli,
    privilege_level privilege,
    bool is_32bit
  )
  : short_interrupt_gate_descriptor { segment, halt_cast<size4>(offset), is_present, must_cli, privilege, is_32bit }
  { }

  inline
  auto short_interrupt_gate_descriptor::is_32bit () const -> bool { return (_w2 & 0x400) != 0; }

  inline
  auto short_interrupt_gate_descriptor::is_trap () const -> bool { return (_w2 & 0x100) != 0; }

  inline
  auto short_interrupt_gate_descriptor::must_cli () const -> bool { return (_w2 & 0x100) == 0; }

  inline
  auto short_interrupt_gate_descriptor::offset () const -> size4 {
    return (size4{_w3} << 16) | size4{_w0};
  }

  inline
  auto short_interrupt_gate_descriptor::segment () const -> segment_selector {
    return segment_selector { _w1 };
  }

  template <unsigned N>
  inline
  void set_interrupt_descriptor_table ( short_interrupt_gate_descriptor const (& table) [N] )
  {
    descriptor_table value { N * sizeof(short_interrupt_gate_descriptor), reinterpret_cast<size>(table) };
    idtr(value);
  }
}