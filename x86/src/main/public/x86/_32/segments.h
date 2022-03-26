// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>
#include <x86/_32/descriptor.h>


// Interface.

namespace x86::_32
{
  //! Types.
  //! @{

  //! Segment descriptor.

  class segment_descriptor : public descriptor
  {
  public:

    constexpr
    segment_descriptor () ;

    constexpr
    segment_descriptor (
      size4 base,
      size4 limit,
      descriptor_type type,
      privilege_level privilege,
      bool is_present,
      bool is_available,
      bool is_32bit,
      bool is_4kb
    ) ;

    auto base () const -> size4 ;

    auto limit () const -> size4 ;

    auto is_accessed () const -> bool ;

    auto is_available () const -> bool ;

    auto is_32bit () const -> bool ;

    auto is_4kb () const -> bool ;

  };

  static_assert(sizeof(segment_descriptor) == 8, "unexpected size of segment_descriptor");

  //! @}

  //! Operators.
  //! @{

  //! Sets the global descriptor table register.

  template <unsigned N>
  void set_global_descriptor_table ( segment_descriptor const (& table) [N] );

  //! @}
}

// Implementation.

namespace x86::_32
{
  constexpr inline
  segment_descriptor::segment_descriptor ( ) : descriptor { } { } ;

  constexpr inline
  segment_descriptor::segment_descriptor (
    size4 base,
    size4 limit,
    descriptor_type type,
    privilege_level privilege,
    bool is_present,
    bool is_available,
    bool is_32bit,
    bool is_4kb
  ) :
    descriptor {
      static_cast<size2>(
        limit & 0xFFFF
      ),
      static_cast<size2>(
        base & 0xFFFF
      ),
      static_cast<size2>(
        (is_present ? 1 : 0) << 15 |
        size2{privilege} << 13 |
        1 << 12 |
        size2{type} << 8 |
        (base >> 16) & 0x00FF
      ),
      static_cast<size2>(
        (base >> 16) & 0xFF00 |
        (is_4kb ? 1 : 0) << 7 |
        (is_32bit ? 1 : 0) << 6 |
        (is_available ? 1 : 0) << 4 |
        (limit >> 16) & 0x000F
      ),
    }
  { }

  inline
  auto segment_descriptor::base () const -> size4 {
    return ((size4{_w3} << 16) & 0xFF000000) | ((size4{_w2} << 16) & 0x00FF0000) | (size4{_w1} & 0x0000FFFF);
  }

  inline
  auto segment_descriptor::limit () const -> size4 {
    return ((size4{_w3} << 16) & 0x000F0000) | (size4{_w0} & 0x0000FFFF);
  }

  inline
  auto segment_descriptor::is_accessed () const -> bool { return (_w2 & 1) != 0; }

  inline
  auto segment_descriptor::is_available () const -> bool { return (_w3 & 0x10) != 0; }

  inline
  auto segment_descriptor::is_32bit () const -> bool { return (_w3 & 0x40) != 0; }

  inline
  auto segment_descriptor::is_4kb () const -> bool { return (_w3 & 0x80) != 0; }

  template <unsigned N>
  inline
  void set_global_descriptor_table ( segment_descriptor const (& table) [N] )
  {
    descriptor_table value {
        ((N * sizeof(segment_descriptor)) - 1),
        reinterpret_cast<size>(table)
    };
    gdtr(value);
  }
}
