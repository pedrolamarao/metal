// Copyright (C) 2012,2013,2014,2015,2016,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/instructions.h>


// Interface.

namespace x86
{
  //! Data types
  //! @{

  //! CPU identification information

  class cpuid
  {
  public:

    constexpr
    cpuid () ;

    constexpr
    cpuid ( size a, size b, size c, size d ) ;

    //! @pre has_cpuid()
    //! @pre feature <= cpuid(0).a()

    static
    auto load ( size feature, size variant ) -> cpuid ;

    //! @pre has_cpuid()
    //! @pre feature <= cpuid(0).a()

    static
    auto load ( size feature ) -> cpuid ;

    constexpr
    auto a () const -> size ;

    constexpr
    auto b () const -> size ;

    constexpr
    auto c () const -> size ;

    constexpr
    auto d () const -> size ;

  private:

    size _a;
    size _b;
    size _c;
    size _d;

  };

  class cpuid_1
  {
      cpuid _cpuid;

  public:

      //! @brief Object
      //! @{

      cpuid_1 ( x86::cpuid cpuid );

      static
      auto load () -> cpuid_1 ;

      //! @}

      //! @brief Properties
      //! @{

      auto has_local_apic () const -> bool;

      auto has_msr () const -> bool;

      //! @}

  };

  //! @}

    //! Operators.
    //! @{

    //! Age of this processor.

    auto cpu_age () -> size;

    //! This processor supports the processor identification (cpuid) instruction.

    auto has_cpuid () -> bool ;

    //! @}
}

//! Inline definitions

namespace x86
{
  inline
  auto has_cpuid () -> bool
  {
    return cpu_age() >= 4;
  }

  inline constexpr
  cpuid::cpuid () : _a{}, _b{}, _c{}, _d{}
  {

  }

  inline constexpr
  cpuid::cpuid ( size a, size b, size c, size d ) : _a{a}, _b{b}, _c{c}, _d{d}
  {

  }

  inline
  auto cpuid::load ( size feature, size variant ) -> cpuid
  {
    auto [a, b, c, d] = cpuid2(feature,variant);
    return cpuid { a, b, c, d};
  }

  inline
  auto cpuid::load ( size feature ) -> cpuid
  {
    auto [a, b, c, d] = cpuid2(feature);
    return cpuid { a, b, c, d};
  }

  inline constexpr
  auto cpuid::a () const -> size
  {
    return _a;
  }

  inline constexpr
  auto cpuid::b () const -> size
  {
    return _b;
  }

  inline constexpr
  auto cpuid::c () const -> size
  {
    return _c;
  }

  inline constexpr
  auto cpuid::d () const -> size
  {
    return _d;
  }

  inline
  cpuid_1::cpuid_1 ( x86::cpuid cpuid ) : _cpuid{cpuid} { }

  inline
  auto cpuid_1::load () -> cpuid_1
  {
    return cpuid_1( x86::cpuid::load(1, 0) );
  }

  inline
  auto cpuid_1::has_local_apic () const -> bool
  {
      return (_cpuid.d() & (1 << 11)) != 0;
  }

  inline
  auto cpuid_1::has_msr () const -> bool
  {
      return (_cpuid.d() & (1 << 5)) != 0;
  }
}
