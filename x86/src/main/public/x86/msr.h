// Copyright (C) 2012,2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/instructions.h>

//! Declarations

namespace x86
{
  //! Standard procedures.
  //! @{

  //! True if model specific registers are supported
  //! @pre x = cpuid(1)

  constexpr
  auto has_msr (cpuid x) -> bool ;

  //! True if model specific registers are supported
  //! @pre has_cpuid()

  auto has_msr () -> bool ;

  //! Model specific registers

  enum class msr : size4
  {
    IA32_APIC_BASE   = 0x0000001B,
    IA32_MISC_ENABLE = 0x000001A0,
    EFER             = 0xC0000080,
  };

  //! Read value of model specific register
  //! @pre has_msr()

  inline
  auto read_msr (msr id) -> size8
  {
    return rdmsr( static_cast<size4>(id) );
  }

  //! @}
}

//! Inline definitions

namespace x86
{
  inline constexpr
  auto has_msr (cpuid x) -> bool
  {
    return (x.d() & 0b10000) != 0 ;
  }

  inline
  auto has_msr () -> bool
  {
    return has_msr(cpuid::load(1));
  }
}
