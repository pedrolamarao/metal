// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/common.h>


//! Declarations

namespace x86
{

  //! Segment descriptor
  //!
  //! Element of global and local descriptor tables.

  class alignas(8) segment_descriptor
  {
  public:

    constexpr
    segment_descriptor () ;

    constexpr
    segment_descriptor ( ps::size4 base, ps::size4 limit, ps::size1 access, ps::size1 granularity ) ;

    constexpr
    auto access () { return _access; }

    constexpr
    auto base_lower () { return _base_lower; }

    constexpr
    auto base_middle () { return _base_middle; }

    constexpr
    auto base_upper () { return _base_upper; }

    constexpr
    auto granularity () { return _granularity; }

    constexpr
    auto limit_lower () { return _limit_lower; }

  private:

    ps::size2 _limit_lower;
    ps::size2 _base_lower;
    ps::size1 _base_middle;
    ps::size1 _access;
    ps::size1 _granularity;
    ps::size1 _base_upper;

  };

  static_assert(sizeof(segment_descriptor) == 8, "unexpected size of segment descriptor");


  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege, bool present ) -> ps::size1 ;

  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //!
  //! @post data_segment_access(true, may_write, expand_down, privilege, true)

  constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege ) -> ps::size1 ;

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  constexpr
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege, bool present ) -> ps::size1 ;

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //!
  //! @post code_segment_access(true, may_read, conforming, privilege, true)

  constexpr
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege ) -> ps::size1 ;

  //! Computes granularity field for code or data segments
  //!
  //! @param is_long      true if 64-bit addressing
  //! @param is_32bit     true if 32-bit addressing
  //! @param is_4kb       true if limit unit is 4kb
  //!
  //! @post segment_granularity(0, false, is_long, is_32bit, is_4kb)

  constexpr
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> ps::size1 ;

  //! Get the global descriptor table register

  auto get_global_descriptor_table_register () -> system_table_register ;

  //! Set the global descriptor table register

  void set_global_descriptor_table_register ( system_table_register value );

  //! Set the global descriptor table register

  template <unsigned N>
  void set_global_descriptor_table_register ( segment_descriptor const (& table) [N] );

  //! Set code segment register

  void set_code_segment_register ( segment_selector value );

}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
    [[gnu::fastcall]]
    void __x86_get_global_descriptor_table_register ( void * system_table_register );

    extern "C"
    [[gnu::fastcall]]
    void __x86_set_global_descriptor_table_register ( void * system_table_register );

    extern "C"
    [[gnu::fastcall]]
    void __x86_set_code_segment_register ( ps::size2 segment_selector );

  }

  // Segment descriptor

  inline constexpr
  segment_descriptor::segment_descriptor ( ) :
    _limit_lower(0),
    _base_lower(0),
    _base_middle(0),
    _access(0),
    _granularity(0),
    _base_upper(0)
  { }

  inline constexpr
  segment_descriptor::segment_descriptor ( ps::size4 base, ps::size4 limit, ps::size1 access, ps::size1 granularity ) :
    _limit_lower(limit & 0xFFFF),
    _base_lower(base & 0xFFFF),
    _base_middle((base >> 16) & 0xFF),
    _access(access),
    _granularity((granularity & 0xFFF0) | (limit & 0xF)),
    _base_upper((base >> 24) & 0xFF)
  {

  }

  inline constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege, bool present ) -> ps::size1
  {
    return (present ? 0x01 : 0x00) << 7
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x00) << 3
         | (expand_down ? 0x01 : 0x00) << 2
         | (may_write ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto data_segment_access ( bool may_write, bool expand_down, ps::size1 privilege ) -> ps::size1
  {
    return (1 << 7)
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x00) << 3
         | (expand_down ? 0x01 : 0x00) << 2
         | (may_write ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege, bool present ) -> ps::size1
  {
    return (present ? 0x01 : 0x00) << 7
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x01) << 3
         | (conforming ? 0x01 : 0x00) << 2
         | (may_read ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto code_segment_access ( bool may_read, bool conforming, ps::size1 privilege ) -> ps::size1
  {
    return (1 << 7)
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x01) << 3
         | (conforming ? 0x01 : 0x00) << 2
         | (may_read ? 0x01 : 0x00) << 1
         | (0)
         ;
  }

  inline constexpr
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> ps::size1
  {
    return (is_4kb ? 0x01 : 0x00) << 7
         | (is_32bit ? 0x01 : 0x00) << 6
         | (is_long ? 0x01 : 0x00) << 5
         | (0)
         ;
  }

  // Global descriptor table register

  inline
  system_table_register get_global_descriptor_table_register ()
  {
    system_table_register value;
    internal::__x86_get_global_descriptor_table_register(& value);
    return value;
  }

  inline
  void set_global_descriptor_table_register ( system_table_register value )
  {
    internal::__x86_set_global_descriptor_table_register(& value);
  }

  template <unsigned N>
  inline
  void set_global_descriptor_table_register ( segment_descriptor const (& table) [N] )
  {
    system_table_register value {
        ((N * sizeof(segment_descriptor)) - 1),
        reinterpret_cast<ps::size4>(table)
    };
    internal::__x86_set_global_descriptor_table_register(& value);
  }

  // Segment selector registers

  inline
  void set_code_segment_register ( segment_selector x )
  {
    internal::__x86_set_code_segment_register(x.value());
  }
}
