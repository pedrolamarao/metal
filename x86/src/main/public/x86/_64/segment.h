// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/_64/descriptor.h>


// Interface.

namespace x86::_64
{
  using ps::size1;
  using ps::size2;
  using ps::size4;
  using ps::size8;

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
      size8 base,
      size4 limit,
      descriptor_type type,
      privilege_level privilege,
      bool is_present,
      bool is_available,
      bool is_32bit,
      bool is_4kb
    ) ;

    static constexpr
    auto max () -> segment_descriptor ;

    auto base () const -> size8 ;

    auto limit () const -> size4 ;

    auto is_available () const -> bool ;

    auto is_64bit () const -> bool ;

    auto is_32bit () const -> bool ;

    auto is_4kb () const -> bool ;

  protected:

      constexpr
      segment_descriptor (
        size4 base_16_23,
        size4 type,
        size4 privilege,
        size4 is_present,
        size4 limit_16_19,
        size4 is_available,
        size4 is_32bit,
        size4 is_4kb,
        size4 base_24_31,
        size4 limit_00_15,
        size4 base_00_15,
        size4 base_32_63
      ) ;

  };

  static_assert(sizeof(segment_descriptor) == 16, "unexpected size of segment_descriptor");

  //! Global descriptor table register.

  struct [[gnu::packed]] global_descriptor_table_register
  {
    size2 size;
    size8 offset;
  };

  static_assert(sizeof(global_descriptor_table_register) == 10, "unexpected size of global_descriptor_table_register");

  //! @}
  //! Operators.
  //! @{

  //! Gets the global descriptor table register

  auto get_global_descriptor_table_register () -> global_descriptor_table_register ;

  //! Sets the global descriptor table register.

  void set_global_descriptor_table_register ( global_descriptor_table_register value );

  //! Sets the global descriptor table register.

  template <unsigned N>
  void set_global_descriptor_table_register ( segment_descriptor const (& table) [N] );

  //! @}
}

// Implementation.

namespace x86::_64
{
  // Segment descriptor.

  constexpr inline
  segment_descriptor::segment_descriptor ( ) : descriptor { } { } ;

  constexpr inline
  segment_descriptor::segment_descriptor (
    size4 base_16_23,
    size4 type,
    size4 privilege,
    size4 is_present,
    size4 limit_16_19,
    size4 is_available,
    size4 is_32bit,
    size4 is_4kb,
    size4 base_24_31,
    size4 limit_00_15,
    size4 base_00_15,
    size4 base_32_63
  ) :
    descriptor {
        limit_00_15  << 0
      | base_00_15   << 16
      ,
        base_16_23   << 0
      | type         << 8
      | 1            << 12
      | privilege    << 13
      | is_present   << 15
      | limit_16_19  << 16
      | is_available << 20
      | 0            << 21
      | is_32bit     << 22
      | is_4kb       << 23
      | base_24_31   << 24
      ,
      base_32_63
      ,
      0
    }
  { }

  constexpr inline
  segment_descriptor::segment_descriptor (
    size8 base,
    size4 limit,
    descriptor_type type,
    privilege_level privilege,
    bool is_present,
    bool is_available,
    bool is_32bit,
    bool is_4kb
  ) :
    segment_descriptor {
      static_cast<size4>(base >> 16) & 0xFF,
      size4{type},
      size4{privilege},
      size4{is_present},
      (limit >> 16) & 0xF,
      size4{is_available},
      size4{is_32bit},
      size4{is_4kb},
      static_cast<size4>(base >> 24) & 0xFF,
      (limit >> 0) & 0xFFFF,
      static_cast<size4>(base >>  0) & 0xFFFF,
      static_cast<size4>(base >> 32) & 0xFFFFFFFF
    }
  { }

  constexpr inline
  auto segment_descriptor::max () -> segment_descriptor {
    return segment_descriptor { 0xFFFFFFFFFFFFFFFF, 0xFFFFF, 15, 3, true, true, true, true };
  }

  inline
  auto segment_descriptor::base () const -> size8 {
    return ((size8{_00} >> 16) & 0x000000000000FFFF)
         | ((size8{_32} << 16) & 0x0000000000FF0000)
         | ((size8{_32}      ) & 0x00000000FF000000)
         | ((size8{_64} << 32) & 0xFFFFFFFF00000000);
  }

  inline
  auto segment_descriptor::limit () const -> size4 {
    return (_00 & 0xFFFF0)
         | (_32 & 0x0000F);
  }

  inline
  auto segment_descriptor::is_available () const -> bool { return (_32 >> 20) & 1; }

  inline
  auto segment_descriptor::is_64bit () const -> bool { return (_32 >> 21) & 1; }

  inline
  auto segment_descriptor::is_32bit () const -> bool { return (_32 >> 22) & 1; }

  inline
  auto segment_descriptor::is_4kb () const -> bool { return (_32 >> 23) & 1; }

  template <unsigned N>
  inline
  void set_global_descriptor_table_register ( segment_descriptor const (& table) [N] )
  {
    global_descriptor_table_register value {
        ((N * sizeof(segment_descriptor)) - 1),
        reinterpret_cast<ps::size4>(table)
    };
    set_global_descriptor_table_register(value);
  }
}