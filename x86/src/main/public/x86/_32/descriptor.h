// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/size.h>

#include <x86/common.h>


// Interface.

namespace x86::_32
{
  using ps::size2;
  using ps::size4;

  using x86::descriptor_type;
  using x86::privilege_level;

  //! Descriptor.

  class descriptor
  {
  public:

    constexpr
    descriptor () ;

    constexpr
    descriptor ( size2 w0, size2 w1, size2 w3, size2 w4 ) ;

    auto is_present () const -> bool ;

    auto is_system () const -> bool ;

    auto privilege () const -> privilege_level ;

    auto type () const -> descriptor_type ;

  protected:

    size2 _w0;
    size2 _w1;
    size2 _w2;
    size2 _w3;

  };

  static_assert(sizeof(descriptor) == 8, "unexpected size of descriptor");
}

// Implementation.

namespace x86::_32
{
  // Descriptor.

  constexpr inline
  descriptor::descriptor () : _w0{}, _w1{}, _w2{}, _w3{} { } ;

  constexpr inline
  descriptor::descriptor ( size2 w0, size2 w1, size2 w2, size2 w3 ) :
    _w0{w0}, _w1{w1}, _w2{w2}, _w3{w3}
  { }

  inline
  auto descriptor::is_present () const -> bool { return (_w2 & 0x8000) != 0; }

  inline
  auto descriptor::privilege () const -> privilege_level { return (_w2 >> 13) & 0b11; }

  inline
  auto descriptor::is_system () const -> bool { return (_w2 & 0x1000) == 0; }

  inline
  auto descriptor::type () const -> descriptor_type { return (_w2 >> 8) & 0b1111; }
}