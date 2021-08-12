// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace x86
{
  using size1 = ps::size1;
  using size2 = ps::size2;
  using size4 = ps::size4;

  //! System table registers
  //!
  //! Value for system table registers.

  struct [[gnu::packed]] system_table_register
  {
    size2 size;
    size4 offset;
  };

  static_assert(sizeof(system_table_register) == 6, "unexpected size of system_table_register");

  bool operator== (system_table_register x, system_table_register y);

  //! Segment selector
  //!
  //! Value of segment selector registers.

  class segment_selector
  {
  public:

    constexpr
    segment_selector () = default ;

    constexpr
    segment_selector ( size2 index, bool is_ldt, size1 privilege );

    constexpr
    auto value () const { return _value; }

  private:

    size2 _value;

  };

  static_assert(sizeof(segment_selector) == 2, "unexpected size of segment_selector");}

//! Definitions

namespace x86
{
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
  segment_selector::segment_selector (ps::size2 index, bool is_ldt, ps::size1 privilege) :
    _value((index << 3) | ((is_ldt ? 1 : 0) << 2) | (privilege & 3))
  { }
}