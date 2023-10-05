// Copyright (C) 2012,2013,2014,2015,2016,2021,2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

import br.dev.pedrolamarao.metal.psys;

//! Declarations

namespace x86
{
  using size  = ps::size;
  using size1 = ps::size1;
  using size2 = ps::size2;
  using size4 = ps::size4;
  using size8 = ps::size8;

  //! Data types.
  //! @{

  //! Descriptor type.

  using descriptor_type = unsigned _BitInt(4);

  //! Privilege level.

  using privilege_level = unsigned _BitInt(2);

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

    template <typename T, typename U>
    auto halt_cast (U* address)
    {
      auto offset = reinterpret_cast<size>(address);
      auto narrow = static_cast<T>(offset);
      if (narrow != offset) { while (true) __asm__ ( "hlt" : ); }
      return narrow;
    }

    //! @}
}

//! Definitions

namespace x86
{
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