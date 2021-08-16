#pragma once

#include <x86/cpuid.h>

//! Declarations

namespace x86
{
  using ps::size4;
  using ps::size8;

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
    IA32_APIC_BASE   = 0x001B,
    IA32_MISC_ENABLE = 0x01A0,
  };

  //! Read value of model specific register
  //! @pre has_msr()

  auto read_msr (msr id) -> size8 ;

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, size4 value);

  //! Write value into model specific register
  //! @pre has_msr()

  void write_msr (msr id, size8 value);

}

//! Inline definitions

namespace x86
{

  namespace internal
  {
    extern "C" [[gnu::fastcall]] void __x86_msr_read (size4 id, size8 * value);
    extern "C" [[gnu::fastcall]] void __x86_msr_write_32 (size4 id, size4 value);
    extern "C" [[gnu::fastcall]] void __x86_msr_write_64 (size4 id, size8 * value);
  }

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

  inline
  auto read_msr (msr id) -> ps::size8
  {
    size8 value;
    internal::__x86_msr_read( size4(id), &value );
    return value;
  }

  inline
  void write_msr (msr id, ps::size4 value)
  {
    internal::__x86_msr_write_32( size4(id), value );
  }

  inline
  void write_msr (msr id, ps::size8 value)
  {
    internal::__x86_msr_write_64( size4(id), &value );
  }
}
