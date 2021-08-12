// Copyright (C) 2012,2013,2014,2015,2016,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <psys/integer.h>

#include <x86/common.h>

//! Declarations

namespace x86
{
  //! Interrupt gate descriptor
  //!
  //! Element of interrupt descriptor tables.

  class alignas(8) interrupt_gate_descriptor
  {
  public:

    constexpr
    interrupt_gate_descriptor ();

    constexpr
    interrupt_gate_descriptor ( segment_selector segment, ps::size4 address, ps::size1 access );

    interrupt_gate_descriptor ( segment_selector segment, void (* address) (), ps::size1 access );

    auto offset_lower () const { return _offset_lower; }

    auto segment () const { return _segment; }

    auto unused () const { return _unused; }

    auto type () const { return _type; }

    auto offset_upper () const { return _offset_upper; }

  private:

    ps::size2 _offset_lower;
    segment_selector _segment;
    ps::size1  _unused;
    ps::size1  _type;
    ps::size2 _offset_upper;

  };

  static_assert(sizeof(interrupt_gate_descriptor) == 8, "unexpected size of interrupt_gate_descriptor");

  //! Computes access field for interrupt gate descriptors

  constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege, bool is_present ) -> ps::size1 ;

  //! Computes access field for interrupt gate descriptors

  constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege ) -> ps::size1 ;

  //! Get the global descriptor table register

  auto get_interrupt_descriptor_table_register () -> system_table_register ;

  //! Set the global descriptor table register

  void set_interrupt_descriptor_table_register ( system_table_register value );

  //! Set the global descriptor table register

  template <unsigned N>
  void set_interrupt_descriptor_table_register ( interrupt_gate_descriptor const (& table) [N] );

  //! Enable interrupts on this processor

  void enable_interrupts ();

  //! Disables interrupts on this processor

  void disable_interrupts ();

}

//! Inline definitions

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

  inline constexpr
  interrupt_gate_descriptor::interrupt_gate_descriptor () :
    _offset_lower(),
    _segment(),
    _unused(),
    _type(),
    _offset_upper()
  { }

  inline constexpr
  interrupt_gate_descriptor::interrupt_gate_descriptor ( segment_selector segment, ps::size4 address, ps::size1 access ) :
    _offset_lower(address & 0xFFFF),
    _segment(segment),
    _unused(0),
    _type(access),
    _offset_upper(address >> 16)
  {

  }

  inline
  interrupt_gate_descriptor::interrupt_gate_descriptor ( segment_selector segment, void (* address) (), ps::size1 access ) :
    _offset_lower((ps::size4)(address) & 0xFFFF),
    _segment(segment),
    _unused(0),
    _type(access),
    _offset_upper((ps::size4)(address) >> 16)
  {

  }

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege, bool is_present ) -> ps::size1
  {
    return ((is_present ? 1 : 0) << 7)
         | (privilege << 5)
         | (0 << 4)
         | ((is_32bit ? 1 : 0) << 3)
         | (1 << 2)
         | (1 << 1)
         | (0)
         ;
  }

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, ps::size1 privilege ) -> ps::size1
  {
    return (1 << 7)
         | (privilege << 5)
         | (0 << 4)
         | ((is_32bit ? 1 : 0) << 3)
         | (1 << 2)
         | (1 << 1)
         | (0)
         ;
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
