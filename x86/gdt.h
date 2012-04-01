// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <aasgard/aasgard.h>

#include <stdint.h>

namespace x86
{
  namespace internal
  {
    extern "C" void __load_global_descriptor_table ( void * base, uint32_t limit ) __attribute__(( fastcall )) ;
    extern "C" void __reload_segment_registers ( uint32_t code, uint32_t data ) __attribute__(( fastcall )) ;
  }

  //! Segment descriptor
  //!
  //! Element of global and local descriptor tables.

  class segment_descriptor
  {

    uint16_t _limit_lower;
    uint16_t _base_lower;
    uint8_t  _base_middle;
    uint8_t  _access;
    uint8_t  _granularity;
    uint8_t  _base_upper;

  public:

    constexpr
    segment_descriptor () :
      _limit_lower(0),
      _base_lower(0),
      _base_middle(0),
      _access(0),
      _granularity(0),
      _base_upper(0)
    {

    }

    constexpr
    segment_descriptor ( uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity ) :
      _limit_lower(limit & 0xFFFF),
      _base_lower(base & 0xFFFF),
      _base_middle((base >> 16) & 0xFF),
      _access(access),
      _granularity((granularity & 0xFFF0) | (limit & 0xF)),
      _base_upper((base >> 24) & 0xFF)
    {

    }

  }
  __attribute__(( packed ));

  //! Computes access field for data segment
  //!
  //! @param accessed     true if was accessed
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  inline constexpr
  auto data_segment_access ( bool accessed, bool may_write, bool expand_down, uint8_t privilege, bool present ) -> uint8_t
  {
    return (present ? 0x01 : 0x00) << 7
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x00) << 3
         | (expand_down ? 0x01 : 0x00) << 2
         | (may_write ? 0x01 : 0x00) << 1
         | (accessed ? 0x01 : 0x00)
         ;
  }

  //! Computes access field for data segment
  //!
  //! @param may_write    true if writable
  //! @param expand_down  true if expands down
  //! @param privilege    privilege level
  //!
  //! @post data_segment_access(true, may_write, expand_down, privilege, true)

  inline constexpr
  auto data_segment_access ( bool may_write, bool expand_down, uint8_t privilege ) -> uint8_t
  {
    return (1 << 7)
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x00) << 3
         | (expand_down ? 0x01 : 0x00) << 2
         | (may_write ? 0x01 : 0x00) << 1
         | (1)
         ;
  }

  //! Computes access field for code segments
  //!
  //! @param accessed     true if was accessed
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //! @param present      true if present in memory

  inline constexpr
  auto code_segment_access ( bool accessed, bool may_read, bool conforming, uint8_t privilege, bool present ) -> uint8_t
  {
    return (present ? 0x01 : 0x00) << 7
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x01) << 3
         | (conforming ? 0x01 : 0x00) << 2
         | (may_read ? 0x01 : 0x00) << 1
         | (accessed ? 0x01 : 0x00)
         ;
  }

  //! Computes access field for code segments
  //!
  //! @param may_read     true if readable
  //! @param conforming   true if conforming
  //! @param privilege    privilege level
  //!
  //! @post code_segment_access(true, may_read, conforming, privilege, true)

  inline constexpr
  auto code_segment_access ( bool may_read, bool conforming, uint8_t privilege ) -> uint8_t
  {
    return (1 << 7)
         | (privilege & 0x03) << 5
         | (0x01) << 4
         | (0x01) << 3
         | (conforming ? 0x01 : 0x00) << 2
         | (may_read ? 0x01 : 0x00) << 1
         | (1)
         ;
  }

  //! Computes granularity field for code or data segments
  //!
  //! @param limit_upper  upper byte of segment limit
  //! @param free         unused, non-reserved bit
  //! @param is_long      true if 64-bit addressing
  //! @param is_32bit     true if 32-bit addressing
  //! @param is_4kb       true if limit unit is 4kb

  inline constexpr
  auto segment_granularity ( uint8_t limit_upper, bool free, bool is_long, bool is_32bit, bool is_4kb ) -> uint8_t
  {
    return (is_4kb ? 0x01 : 0x00) << 7
         | (is_32bit ? 0x01 : 0x00) << 6
         | (is_long ? 0x01 : 0x00) << 5
         | (free ? 0x01 : 0x00) << 4
         | (limit_upper & 0x0F)
         ;
  }

  //! Computes granularity field for code or data segments
  //!
  //! @param is_long      true if 64-bit addressing
  //! @param is_32bit     true if 32-bit addressing
  //! @param is_4kb       true if limit unit is 4kb
  //!
  //! @post segment_granularity(0, false, is_long, is_32bit, is_4kb)

  inline constexpr
  auto segment_granularity ( bool is_long, bool is_32bit, bool is_4kb ) -> uint8_t
  {
    return (is_4kb ? 0x01 : 0x00) << 7
         | (is_32bit ? 0x01 : 0x00) << 6
         | (is_long ? 0x01 : 0x00) << 5
         | (0 << 4)
         ;
  }

  //! Loads global descriptor table as array of descriptors
  //!
  //! @param table  array of descriptors
  //! @param count  count of descriptors in array

  inline
  void load_global_descriptor_table ( segment_descriptor * table, uint16_t count )
  {
    internal::__load_global_descriptor_table(table, ((count * sizeof(segment_descriptor)) - 1));
  }

  //! Loads segment registers with new selectors
  //!
  //! @param code  index of descriptor on global descriptor table
  //! @param data  index of descriptor on global descriptor table
  //!
  //! @post load code in CD then data in DS, ES, FS, GS and SS

  inline
  void reload_segment_registers ( uint16_t code, uint16_t data )
  {
    internal::__reload_segment_registers((code * 8), (data * 8));
  }
}
