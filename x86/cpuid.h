// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


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

    //! @pre has_cpuid()
    //! @pre id <= cpuid(0).a()

    cpuid (uint32_t id, uint32_t extra) ;

    //! @pre has_cpuid()
    //! @pre id <= cpuid(0).a()

    cpuid (uint32_t id) ;

    constexpr
    auto a () -> uint32_t ;

    constexpr
    auto b () -> uint32_t ;

    constexpr
    auto c () -> uint32_t ;

    constexpr
    auto d () -> uint32_t ;

  private:

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

  };

}

//! Inline definitions

namespace x86
{

  namespace internal
  {

    extern "C"
    bool __has_cpuid () __attribute__(( fastcall )) ;

    extern "C"
    void __read_cpuid (uint32_t leaf, uint32_t extra, cpuid & out) __attribute__(( fastcall )) ;

  }

  inline
  auto has_cpuid () -> bool
  {
    return internal::__has_cpuid();
  }

  inline constexpr
  cpuid::cpuid () : eax(), ebx(), ecx(), edx()
  {

  }

  inline
  cpuid::cpuid (uint32_t id, uint32_t extra) : eax(0), ebx(0), ecx(0), edx(0)
  {
    internal::__read_cpuid(id, extra, (* this));
  }

  inline
  cpuid::cpuid (uint32_t id) : cpuid(id, 0)
  {

  }

  inline constexpr
  auto cpuid::a () -> uint32_t
  {
    return eax;
  }

  inline constexpr
  auto cpuid::b () -> uint32_t
  {
    return ebx;
  }

  inline constexpr
  auto cpuid::c () -> uint32_t
  {
    return ecx;
  }

  inline constexpr
  auto cpuid::d () -> uint32_t
  {
    return edx;
  }

}
