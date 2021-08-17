// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/common.h>

//! Declarations

namespace x86
{
  //! Data types.
  //! @{

  //! Gate descriptor.

  class gate_descriptor : public descriptor
  {
  public:

    constexpr
    gate_descriptor ();

    constexpr
    gate_descriptor ( size4 low, size4 high );

    auto segment () const -> segment_selector;

  };

  static_assert(sizeof(gate_descriptor) == 8, "unexpected size of gate_descriptor");

  //! Interrupt gate descriptor.

  class interrupt_gate_descriptor : public gate_descriptor
  {
  public:

    constexpr
    interrupt_gate_descriptor ();

    constexpr
    interrupt_gate_descriptor (
      segment_selector segment, ps::size4 offset,
      bool is_32bit, bool must_cli,
      privilege_level privilege, bool is_present
    );

    interrupt_gate_descriptor (
      segment_selector segment, void (* offset) (),
      bool is_32bit, bool must_cli,
      privilege_level, bool is_present
    );

    auto is_32bit () const -> bool;

    auto must_cli () const -> bool;

    auto offset () const -> size4;

  protected:

    constexpr
    interrupt_gate_descriptor ( size4 segment, size4 offset, size4 type, size4 access );

  };

  static_assert(sizeof(interrupt_gate_descriptor) == 8, "unexpected size of interrupt_gate_descriptor");

  //! @}

  //! Interface types.
  //! @{

  //! Get the global descriptor table register

  auto get_interrupt_descriptor_table_register () -> system_table_register ;

  //! Set the global descriptor table register

  void set_interrupt_descriptor_table_register ( system_table_register value );

  //! Set the global descriptor table register

  template <unsigned N>
  void set_interrupt_descriptor_table_register ( interrupt_gate_descriptor const (& table) [N] );

  //! @}

  //! Enable interrupts on this processor

  void enable_interrupts ();

  //! Disables interrupts on this processor

  void disable_interrupts ();

}

//! Definitions

namespace x86
{

  namespace internal
  {

    extern "C"
    [[gnu::fastcall]]
    void __x86_get_interrupt_descriptor_table_register ( void * system_table_register );

    extern "C"
    [[gnu::fastcall]]
    void __x86_set_interrupt_descriptor_table_register ( void * system_table_register );

    extern "C"
    [[gnu::fastcall]]
    void __x86_enable_interrupts ();

    extern "C"
    [[gnu::fastcall]]
    void __x86_disable_interrupts ();

  }

  // Gate descriptor.

  constexpr inline
  gate_descriptor::gate_descriptor () : descriptor{} { }

  constexpr inline
  gate_descriptor::gate_descriptor ( size4 low, size4 high ) : descriptor{low,high} { }

  inline
  auto gate_descriptor::segment () const -> segment_selector {
    return segment_selector { static_cast<size2>(_low >> 16) };
  }

  // Interrupt gate descriptor.

  constexpr inline
  interrupt_gate_descriptor::interrupt_gate_descriptor () : gate_descriptor {}
  { }

  constexpr inline
  interrupt_gate_descriptor::interrupt_gate_descriptor (
    size4 segment, size4 offset, size4 type, size4 access
  )
  : gate_descriptor {
       (offset  & 0xFFFF) <<  0
     | (segment         ) << 16
     ,
       (offset & 0xFFFF0000)
     |  type              <<  8
     |  access            << 12
    }
  { }

  constexpr inline
  interrupt_gate_descriptor::interrupt_gate_descriptor (
    segment_selector segment, size4 offset,
    bool is_32bit, bool must_cli,
    privilege_level privilege, bool is_present
  )
  : interrupt_gate_descriptor {
      size2{segment}, offset,
      size4{is_32bit} << 3 | 1 << 2 | 1 << 1 | size4{ ! must_cli },
      size4{is_present} << 3 | size4{privilege} << 1
    }
  { }

  inline
  interrupt_gate_descriptor::interrupt_gate_descriptor (
    segment_selector segment, void (* offset) (),
    bool is_32bit, bool must_cli,
    privilege_level privilege, bool is_present
  )
  : interrupt_gate_descriptor {
      size2{segment}, reinterpret_cast<size4>(offset),
      size4{is_32bit} << 3 | 1 << 2 | 1 << 1 | size4{ ! must_cli },
      size4{is_present} << 3 | size4{privilege} << 1
    }
  { }

  inline
  auto interrupt_gate_descriptor::is_32bit () const -> bool { return (_high >> 11) & 1; }

  inline
  auto interrupt_gate_descriptor::must_cli () const -> bool { return ((_high >> 8) & 1) == 0; }

  inline
  auto interrupt_gate_descriptor::offset () const -> size4 {
    return (_low & 0x0000FFFF) | (_high & 0xFFFF0000);
  }

  // Interrupt descriptor table register

  inline
  system_table_register get_interrupt_descriptor_table_register ()
  {
    system_table_register value;
    internal::__x86_get_interrupt_descriptor_table_register(& value);
    return value;
  }

  inline
  void set_interrupt_descriptor_table_register ( system_table_register value )
  {
    internal::__x86_set_interrupt_descriptor_table_register(& value);
  }

  template <unsigned N>
  inline
  void set_interrupt_descriptor_table_register ( interrupt_gate_descriptor const (& table) [N] )
  {
    system_table_register value { N * sizeof(interrupt_gate_descriptor), reinterpret_cast<ps::size4>(table) };
    internal::__x86_set_interrupt_descriptor_table_register(& value);
  }

  inline
  void enable_interrupts ()
  {
    internal::__x86_enable_interrupts();
  }

  inline
  void disable_interrupts ()
  {
    internal::__x86_disable_interrupts();
  }

  template <int N>
  inline
  void interrupt ()
  {
      __asm__ ("int %0\n" : : "N"(N) : "cc", "memory");
  }
}
