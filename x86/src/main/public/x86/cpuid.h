// Copyright (C) 2012, 2013, 2014, 2015, 2016, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>


//! Declarations

namespace x86
{
  //! True if cpuid is supported

  auto has_cpuid () -> bool ;

  //! CPU identification information

  class cpuid
  {
  public:

    constexpr
    cpuid () ;

    constexpr
    cpuid ( ps::size4 a, ps::size4 b, ps::size4 c, ps::size4 d ) ;

    //! @pre has_cpuid()
    //! @pre feature <= cpuid(0).a()

    static
    auto load ( ps::size4 feature, ps::size4 variant ) -> cpuid ;

    //! @pre has_cpuid()
    //! @pre feature <= cpuid(0).a()

    static
    auto load ( ps::size4 feature ) -> cpuid ;

    constexpr
    auto a () const -> ps::size4 ;

    constexpr
    auto b () const -> ps::size4 ;

    constexpr
    auto c () const -> ps::size4 ;

    constexpr
    auto d () const -> ps::size4 ;

  private:

    ps::size4 _a;
    ps::size4 _b;
    ps::size4 _c;
    ps::size4 _d;

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
}

//! Inline definitions

namespace x86
{
  namespace internal
  {
      extern "C"
      [[gnu::fastcall]]
      ps::size4 _x86_cpu_age ();

      extern "C"
      [[gnu::fastcall]]
      void _x86_cpuid (ps::size4 leaf, ps::size4 extra, cpuid * id);
  }

  inline
  auto has_cpuid () -> bool
  {
    return internal::_x86_cpu_age() >= 4;
  }

  inline constexpr
  cpuid::cpuid () : _a{}, _b{}, _c{}, _d{}
  {

  }

  inline constexpr
  cpuid::cpuid ( ps::size4 a, ps::size4 b, ps::size4 c, ps::size4 d ) : _a{a}, _b{b}, _c{c}, _d{d}
  {

  }

  inline
  auto cpuid::load ( ps::size4 feature, ps::size4 variant ) -> cpuid
  {
    cpuid _r;
    internal::_x86_cpuid(feature, variant, &_r);
    return _r;
  }

  inline
  auto cpuid::load ( ps::size4 feature ) -> cpuid
  {
    return load(feature, 0);
  }

  inline constexpr
  auto cpuid::a () const -> ps::size4
  {
    return _a;
  }

  inline constexpr
  auto cpuid::b () const -> ps::size4
  {
    return _b;
  }

  inline constexpr
  auto cpuid::c () const -> ps::size4
  {
    return _c;
  }

  inline constexpr
  auto cpuid::d () const -> ps::size4
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
