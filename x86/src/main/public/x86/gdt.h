// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/common.h>


// Declarations.

namespace x86
{
  using ps::size1;
  using ps::size2;
  using ps::size4;
  using ps::size8;

  //! Data types.
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
        size4 base_00_15
      ) ;

  };

  static_assert(sizeof(segment_descriptor) == 8, "unexpected size of segment descriptor");

  //! Code segment descriptor type.

  constexpr
  auto code_segment ( bool conforming, bool readable, bool accessed ) -> descriptor_type ;

  //! Data segment descriptor type.

  constexpr
  auto data_segment ( bool downwards, bool writable, bool accessed ) -> descriptor_type ;

  //! @}

    //! Primitive procedures.
    //! @{

    //! @}

  //! Interface types.
  //! @{

  // GDT register.

  //! Get the global descriptor table register

  auto get_global_descriptor_table_register () -> system_table_register ;

  //! Set the global descriptor table register

  void set_global_descriptor_table_register ( system_table_register value );

  //! Set the global descriptor table register

  template <unsigned N>
  void set_global_descriptor_table_register ( segment_descriptor const (& table) [N] );

  // CS register.

  //! Get code segment register

  auto get_code_segment_register () -> segment_selector ;

  //! Set code segment register

  void set_code_segment_register ( segment_selector value );

  // DS register.

  //! Set data segment register

  void set_data_segment_register ( segment_selector value );

  // SS register.

  //! Set stack segment register

  void set_stack_segment_register ( segment_selector value );

  // ES, FS, GS registers.

  //! Set extra segment registers

  void set_extra_segment_registers ( segment_selector value );

  //! @}
}

// Definitions.

namespace x86
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
    size4 base_00_15
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
    }
  { }

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
    segment_descriptor {
      (base  >> 16) & 0xFF,
      size4{type},
      size4{privilege},
      size4{is_present},
      (limit >> 16) & 0xF,
      size4{is_available},
      size4{is_32bit},
      size4{is_4kb},
      (base  >> 24) & 0xFF,
      (limit >>  0) & 0xFFFF,
      (base  >>  0) & 0xFFFF,
    }
  { }

  inline
  auto segment_descriptor::base () const -> size4 {
    return ((_low  >> 16) & 0x0000FFFF)
         | ((_high << 16) & 0x00FF0000)
         | ((_high      ) & 0xFF000000);
  }

  inline
  auto segment_descriptor::limit () const -> size4 {
    return (_low  & 0x0000FFFF)
         | (_high & 0x000F0000);
  }

  inline
  auto segment_descriptor::is_available () const -> bool { return (_high >> 20) & 1; }

  inline
  auto segment_descriptor::is_64bit () const -> bool { return (_high >> 21) & 1; }

  inline
  auto segment_descriptor::is_32bit () const -> bool { return (_high >> 22) & 1; }

  inline
  auto segment_descriptor::is_4kb () const -> bool { return (_high >> 23) & 1; }

  constexpr inline
  auto code_segment ( bool conforming, bool readable, bool accessed ) -> descriptor_type {
    return (1 << 3) | (conforming << 2) | (readable << 1) | accessed;
  }

  constexpr inline
  auto data_segment ( bool downwards, bool writable, bool accessed ) -> descriptor_type {
    return (0 << 3) | (downwards << 2) | (writable << 1) | accessed;
  }

  // Global descriptor table register

  template <unsigned N>
  inline
  void set_global_descriptor_table_register ( segment_descriptor const (& table) [N] )
  {
    system_table_register value {
        ((N * sizeof(segment_descriptor)) - 1),
        reinterpret_cast<ps::size4>(table)
    };
    set_global_descriptor_table_register(value);
  }
}