// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

namespace x86
{
  namespace internal
  {
    extern "C" void __load_interrupt_descriptor_table ( void * base, uint32_t limit ) __attribute__(( fastcall )) ;
    extern "C" void __enable_interrupts () __attribute__(( fastcall )) ;
    extern "C" void __disable_interrupts () __attribute__(( fastcall )) ;
  }

  class interrupt_gate_descriptor
  {

    uint16_t _offset_lower;
    uint16_t _segment;
    uint8_t  _unused;
    uint8_t  _type;
    uint16_t _offset_upper;

  public:

    constexpr
    interrupt_gate_descriptor () :
      _offset_lower(0),
      _segment(0),
      _unused(0),
      _type(0),
      _offset_upper(0)
    {

    }

    constexpr
    interrupt_gate_descriptor ( uint16_t segment, uint32_t address, uint8_t access ) :
      _offset_lower(address & 0xFFFF),
      _segment(segment),
      _unused(0),
      _type(access),
      _offset_upper(address >> 16)
    {

    }

    constexpr
    interrupt_gate_descriptor ( uint16_t segment, void * address, uint8_t access ) :
      _offset_lower((uint32_t)(address) & 0xFFFF),
      _segment(segment),
      _unused(0),
      _type(access),
      _offset_upper((uint32_t)(address) >> 16)
    {

    }

    constexpr
    interrupt_gate_descriptor ( uint16_t segment, void (* address) (), uint8_t access ) :
      _offset_lower((uint32_t)(address) & 0xFFFF),
      _segment(segment),
      _unused(0),
      _type(access),
      _offset_upper((uint32_t)(address) >> 16)
    {

    }

    void set ( uint16_t segment, uint32_t address, uint16_t access )
    {
      _offset_lower = address & 0xFFFF;
      _segment = segment;
      _type = access;
      _offset_upper = address >> 16;
    }

    void set ( uint16_t segment, void * address, uint16_t access )
    {
      set(segment, (uint32_t)(address), access);
    }

    void set ( uint16_t segment, void (* address) (), uint16_t access )
    {
      set(segment, (uint32_t)(address), access);
    }

  }
  __attribute(( packed ));

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, uint8_t privilege, bool is_present ) -> uint8_t
  {
    return ((is_present ? 1 : 0) << 7)
         | (privilege << 5)
         | ((is_32bit ? 1 : 0) << 3)
         | (1 << 2)
         | (1 << 1)
         ;
  }

  inline constexpr
  auto interrupt_gate_access ( bool is_32bit, uint8_t privilege ) -> uint8_t
  {
    return (1 << 7)
         | (privilege << 5)
         | ((is_32bit ? 1 : 0) << 3)
         | (1 << 2)
         | (1 << 1)
         ;
  }

  inline
  void load_interrupt_descriptor_table ( interrupt_gate_descriptor * table, uint32_t count )
  {
    internal::__load_interrupt_descriptor_table(table, ((count * sizeof(interrupt_gate_descriptor)) - 1));
  }

  inline
  void enable_interrupts ()
  {
    internal::__enable_interrupts();
  }

  inline
  void disable_interrupts ()
  {
    internal::__disable_interrupts();
  }

}
