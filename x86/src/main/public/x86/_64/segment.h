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

    auto base () const -> size8 ;

    auto limit () const -> size4 ;

    auto is_accessed () const -> bool ;

    auto is_available () const -> bool ;

    auto is_32bit () const -> bool ;

    auto is_4kb () const -> bool ;

  };

  static_assert(sizeof(segment_descriptor) == 16, "unexpected size of segment_descriptor");

  //! Global descriptor table register.

  struct [[gnu::packed]] global_descriptor_table_register
  {
    size2 size;
    size8 offset;
  };

  constexpr
  auto operator== ( global_descriptor_table_register, global_descriptor_table_register) -> bool;

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
  constexpr inline
  segment_descriptor::segment_descriptor ( ) : descriptor { } { } ;

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
      static_cast<size4>(
        base >> 32
      ),
      0
    }
  { }

  inline
  auto segment_descriptor::base () const -> size8 {
    return ((size8{_q4} << 32) & 0xFFFFFFFF00000000) |
           ((size8{_w3} << 16) & 0x00000000FF000000) |
           ((size8{_w2} << 16) & 0x0000000000FF0000) |
           ((size8{_w1}      ) & 0x000000000000FFFF);
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

  constexpr inline
  auto operator== ( global_descriptor_table_register x, global_descriptor_table_register y ) -> bool
  {
    return (x.size == y.size) && (x.offset == y.offset);
  }

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
