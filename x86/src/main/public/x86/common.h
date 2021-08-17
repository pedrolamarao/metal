// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace x86
{
  using size1 = ps::size1;
  using size2 = ps::size2;
  using size4 = ps::size4;
  using size8 = ps::size8;

  //! Data types.
  //! @{

  //! Descriptor type.

  using descriptor_type = unsigned _ExtInt(4);

  //! Privilege level.

  using privilege_level = unsigned _ExtInt(2);

  //! Descriptor.

  class descriptor
  {
  public:

    constexpr
    descriptor () ;

    constexpr
    descriptor ( size4 low, size4 high ) ;

    auto is_present () const -> bool ;

    auto is_system () const -> bool ;

    auto privilege () const -> privilege_level ;

    auto type () const -> descriptor_type ;

  protected:

    size4 _low;
    size4 _high;

  };

  static_assert(sizeof(descriptor) == 8, "unexpected size of descriptor");

  //! System table register.

  struct [[gnu::packed]] system_table_register
  {
    size2 size;
    size4 offset;
  };

  static_assert(sizeof(system_table_register) == 6, "unexpected size of system_table_register");

  bool operator== (system_table_register x, system_table_register y);

  //! Segment selector.

  class segment_selector
  {
  public:

    constexpr
    segment_selector () ;

    constexpr explicit
    segment_selector ( size2 );

    constexpr
    segment_selector ( size2 index, bool is_ldt, privilege_level );

    explicit
    operator size2 () const;

    bool operator== ( segment_selector ) const;

  private:

    size2 _value;

  };

  static_assert(sizeof(segment_selector) == 2, "unexpected size of segment_selector");

  //! @}

    //! Primitive procedures.
    //! @{

    void halt ();

    void pause ();

    //! @}
}

//! Definitions

namespace x86
{
  // Descriptor.

  constexpr inline
  descriptor::descriptor () : _low{}, _high{} { } ;

  constexpr inline
  descriptor::descriptor ( size4 low, size4 high ) : _low{low}, _high{high} { }

  inline
  auto descriptor::is_present () const -> bool { return (_high >> 15) & 0b1; }

  inline
  auto descriptor::is_system () const -> bool { return ((_high >> 12) & 0b1) == 0; }

  inline
  auto descriptor::privilege () const -> privilege_level { return (_high >> 13) & 0b11; }

  inline
  auto descriptor::type () const -> descriptor_type { return (_high >> 8) & 0b1111; }

  inline
  bool operator== ( system_table_register x, system_table_register y )
  {
    return x.size == y.size && x.offset == y.offset;
  }

  inline
  bool operator!= ( system_table_register x, system_table_register y )
  {
    return x.size != y.size || x.offset != y.offset;
  }

  constexpr inline
  segment_selector::segment_selector () : _value{}
  { }

  constexpr inline
  segment_selector::segment_selector ( size2 value ) : _value{value}
  { }

  constexpr inline
  segment_selector::segment_selector ( size2 index, bool is_ldt, privilege_level privilege ) :
    _value { index << 3 | size2{is_ldt} << 2 | privilege }
  { }

  inline
  segment_selector::operator size2 () const { return _value; }

  inline
  bool segment_selector::operator== (segment_selector other) const { return _value == other._value; }
}