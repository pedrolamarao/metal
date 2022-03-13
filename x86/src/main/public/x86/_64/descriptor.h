// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/common.h>


// Interface.

namespace x86::_64
{
  using ps::size1;
  using ps::size2;
  using ps::size4;
  using ps::size8;

  //! Descriptor.

  class descriptor
  {
  public:

    constexpr
    descriptor () ;

    constexpr
    descriptor ( size4 q0, size4 q1, size4 q2, size4 q3 ) ;

    static constexpr
    auto max () -> descriptor ;

    auto is_present () const -> bool ;

    auto is_system () const -> bool ;

    auto privilege () const -> privilege_level ;

    auto type () const -> descriptor_type ;

  protected:

    size4 _00;
    size4 _32;
    size4 _64;
    size4 _96;

  };

  static_assert(sizeof(descriptor) == 16, "unexpected size of descriptor");
}

// Implementation.

namespace x86::_64
{
  // Descriptor.

  constexpr inline
  descriptor::descriptor () : _00{}, _32{}, _64{}, _96{} { } ;

  constexpr inline
  descriptor::descriptor ( size4 q0, size4 q1, size4 q2, size4 q3 ) : _00{q0}, _32{q1}, _64{q2}, _96{q3} { }

  constexpr inline
  auto descriptor::max () -> descriptor { return descriptor{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF}; }

  inline
  auto descriptor::is_present () const -> bool { return ((_32 >> 15) & 1) == 1; }

  inline
  auto descriptor::is_system () const -> bool { return ((_32 >> 12) & 1) == 0; }

  inline
  auto descriptor::privilege () const -> privilege_level { return (_32 >> 13) & 0b11; }

  inline
  auto descriptor::type () const -> descriptor_type { return (_32 >> 8) & 0b1111; }
}