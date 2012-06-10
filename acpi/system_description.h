// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


//! Declarations

namespace acpi
{

  //! Root System Description Pointer

  struct root_system_description_pointer
  {
    // since revision 0
    char     signature [8];
    uint8_t  checksum;
    char     oem_id [6];
    uint8_t  revision;
    uint32_t address;

    // since revision 1
    uint32_t length;
    uint64_t extended_address;
    uint8_t  extended_checksum;
    uint8_t  reserved [3];
  };

  constexpr
  auto revision ( root_system_description_pointer const & x ) -> uint8_t ;

  auto is_valid ( root_system_description_pointer const & x ) -> bool ;

  struct narrow_root_system_description ;

  constexpr
  auto narrow_address ( root_system_description_pointer const & x) -> narrow_root_system_description const * ;

  struct wide_root_system_description ;

  constexpr
  auto wide_address ( root_system_description_pointer const & x ) -> wide_root_system_description const * ;

  //! System Description

  struct system_description
  {
    char     signature [4];
    uint32_t length;
    uint8_t  revision;
    uint8_t  checksum;
    char     oem_id [6];
    char     oem_table_id [8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
  };

  auto revision ( system_description const & x ) -> uint8_t ;

  auto is_valid ( system_description const & x ) -> bool ;

  //! Root System Description with narrow pointers

  struct narrow_root_system_description
  {
    system_description header;

    uint32_t pointers [];
  };

  auto is_valid ( narrow_root_system_description const & x ) -> bool ;

  auto begin ( narrow_root_system_description const & x ) -> uint32_t const * ;

  auto end ( narrow_root_system_description const & x ) -> uint32_t const * ;

  //! Root System Description with wide pointers

  struct wide_root_system_description
  {
    system_description header;

    uint64_t pointers [];
  };

  auto is_valid ( wide_root_system_description const & x ) -> bool ;

  auto begin ( wide_root_system_description const & x ) -> uint64_t const * ;

  auto end ( wide_root_system_description const & x ) -> uint64_t const * ;

  //! Generic memory address

  struct generic_address
  {
    uint8_t  space;
    uint8_t  width;
    uint8_t  offset;
    uint8_t  access;
    uint64_t address;
  };

  //! Fixed System Description

  struct fixed_system_description
  {
      system_description base;

      uint32_t FirmwareCtrl;
      uint32_t Dsdt;
      uint8_t  Reserved;
      uint8_t  PreferredPowerManagementProfile;
      uint16_t SCI_Interrupt;
      uint32_t SMI_CommandPort;
      uint8_t  AcpiEnable;
      uint8_t  AcpiDisable;
      uint8_t  S4BIOS_REQ;
      uint8_t  PSTATE_Control;
      uint32_t PM1aEventBlock;
      uint32_t PM1bEventBlock;
      uint32_t PM1aControlBlock;
      uint32_t PM1bControlBlock;
      uint32_t PM2ControlBlock;
      uint32_t PMTimerBlock;
      uint32_t GPE0Block;
      uint32_t GPE1Block;
      uint8_t  PM1EventLength;
      uint8_t  PM1ControlLength;
      uint8_t  PM2ControlLength;
      uint8_t  PMTimerLength;
      uint8_t  GPE0Length;
      uint8_t  GPE1Length;
      uint8_t  GPE1Base;
      uint8_t  CStateControl;
      uint16_t WorstC2Latency;
      uint16_t WorstC3Latency;
      uint16_t FlushSize;
      uint16_t FlushStride;
      uint8_t  DutyOffset;
      uint8_t  DutyWidth;
      uint8_t  DayAlarm;
      uint8_t  MonthAlarm;
      uint8_t  Century;

      // since ACPI 2.0

      uint16_t        BootArchitectureFlags;
      uint8_t         Reserved2;
      uint32_t        Flags;
      generic_address ResetReg;
      uint8_t         ResetValue;
      uint8_t         Reserved3[3];
      uint64_t        X_FirmwareControl;
      uint64_t        X_Dsdt;
      generic_address X_PM1aEventBlock;
      generic_address X_PM1bEventBlock;
      generic_address X_PM1aControlBlock;
      generic_address X_PM1bControlBlock;
      generic_address X_PM2ControlBlock;
      generic_address X_PMTimerBlock;
      generic_address X_GPE0Block;
      generic_address X_GPE1Block;
  };

  //! Multiple APIC system description

  struct apic_system_description
  {
    system_description base;

    uint32_t local_apic_address;
    uint32_t flags;
  };

  enum class apic_structure_type : uint8_t
  {
    local_apic             = 0,
    io_apic                = 1,
    input_source_override  = 2,
    non_maskable_interrupt = 3,
    local_apic_nmi         = 4
  };

  struct apic_description
  {
    uint8_t type;
    uint8_t length;
  };

  struct local_apic_description
  {
    apic_description base;

    uint8_t  processor;
    uint8_t  id;
    uint32_t flags;
  };

  struct io_apic_description
  {
    apic_description base;

    uint8_t  id;
    uint8_t  reserved0;
    uint32_t address;
    uint32_t system_vector_base;
  };

  struct input_source_override_description
  {
    apic_description base;

    uint8_t  bus;
    uint8_t  source;
    uint32_t global_system_interrupt_vector;
    uint16_t flags;
  };

  struct nmi_source_description
  {
    apic_description base;

    uint16_t flags;
    uint32_t global_system_interrupt_vector;
  };

  struct local_apic_nmi_description
  {
    apic_description base;

    uint8_t  processor;
    uint16_t flags;
    uint8_t  pin;
  };

}


//! Inline procedure definitions

namespace acpi
{
  inline constexpr
  auto revision ( root_system_description_pointer const & x ) -> uint8_t
  {
    return x.revision;
  }

  inline
  auto is_valid_r0 ( root_system_description_pointer const & x ) -> bool
  {
    uint8_t sum = 0;
    uint8_t const * i = (uint8_t const *)(& x);
    uint8_t const * e = i + 20;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid_r1 ( root_system_description_pointer const & x ) -> bool
  {
    uint8_t sum = 0;
    uint8_t const * i = (uint8_t const *)(& x);
    uint8_t const * e = i + 36;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid ( root_system_description_pointer const & x ) -> bool
  {
    if (revision(x) == 0) return is_valid_r0(x);
    else                  return is_valid_r1(x);
  }

  inline
  constexpr
  auto narrow_address ( root_system_description_pointer const & x) -> narrow_root_system_description const *
  {
    return (narrow_root_system_description const *)(x.address);
  }

  inline
  constexpr
  auto wide_address ( root_system_description_pointer const & x) -> wide_root_system_description const *
  {
    return (wide_root_system_description const *)(x.extended_address);
  }


  inline
  auto is_valid ( system_description const & x ) -> bool
  {
    uint8_t sum = 0;
    uint8_t const * i = (uint8_t const *)(& x);
    uint8_t const * e = i + x.length;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid ( narrow_root_system_description const & x ) -> bool
  {
    return is_valid(x.header);
  }

  inline
  auto is_valid ( wide_root_system_description const & x ) -> bool
  {
    return is_valid(x.header);
  }

  inline
  auto begin ( narrow_root_system_description const & x ) -> uint32_t const *
  {
    return x.pointers;
  }

  inline
  auto end ( narrow_root_system_description const & x ) -> uint32_t const *
  {
    auto const count = (x.header.length - sizeof(acpi::system_description)) / sizeof(uint32_t);
    return x.pointers + count;
  }

  inline
  auto begin ( wide_root_system_description const & x ) -> uint64_t const *
  {
    return x.pointers;
  }

  inline
  auto end ( wide_root_system_description const & x ) -> uint64_t const *
  {
    auto const count = (x.header.length - sizeof(acpi::system_description)) / sizeof(uint64_t);
    return x.pointers + count;
  }

}

