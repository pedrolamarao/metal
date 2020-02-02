// Copyright (C) 2012,2013,2014,2015,2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

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
    std::uint8_t  checksum;
    char     oem_id [6];
    std::uint8_t  revision;
    std::uint32_t address;

    // since revision 1
    std::uint32_t length;
    std::uint64_t extended_address;
    std::uint8_t  extended_checksum;
    std::uint8_t  reserved [3];
  };

  constexpr
  auto revision ( root_system_description_pointer const & x ) -> std::uint8_t ;

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
    std::uint32_t length;
    std::uint8_t  revision;
    std::uint8_t  checksum;
    char     oem_id [6];
    char     oem_table_id [8];
    std::uint32_t oem_revision;
    std::uint32_t creator_id;
    std::uint32_t creator_revision;
  };

  auto revision ( system_description const & x ) -> std::uint8_t ;

  auto is_valid ( system_description const & x ) -> bool ;

  //! Root System Description with narrow pointers

  struct narrow_root_system_description
  {
    system_description header;

    std::uint32_t pointers [];
  };

  auto is_valid ( narrow_root_system_description const & x ) -> bool ;

  auto begin ( narrow_root_system_description const & x ) -> std::uint32_t const * ;

  auto end ( narrow_root_system_description const & x ) -> std::uint32_t const * ;

  //! Root System Description with wide pointers

  struct wide_root_system_description
  {
    system_description header;

    std::uint64_t pointers [];
  };

  auto is_valid ( wide_root_system_description const & x ) -> bool ;

  auto begin ( wide_root_system_description const & x ) -> std::uint64_t const * ;

  auto end ( wide_root_system_description const & x ) -> std::uint64_t const * ;

  //! Generic memory address

  struct generic_address
  {
    std::uint8_t  space;
    std::uint8_t  width;
    std::uint8_t  offset;
    std::uint8_t  access;
    std::uint64_t address;
  };

  //! Fixed System Description

  struct fixed_system_description
  {
      system_description base;

      std::uint32_t FirmwareCtrl;
      std::uint32_t Dsdt;
      std::uint8_t  Reserved;
      std::uint8_t  PreferredPowerManagementProfile;
      std::uint16_t SCI_Interrupt;
      std::uint32_t SMI_CommandPort;
      std::uint8_t  AcpiEnable;
      std::uint8_t  AcpiDisable;
      std::uint8_t  S4BIOS_REQ;
      std::uint8_t  PSTATE_Control;
      std::uint32_t PM1aEventBlock;
      std::uint32_t PM1bEventBlock;
      std::uint32_t PM1aControlBlock;
      std::uint32_t PM1bControlBlock;
      std::uint32_t PM2ControlBlock;
      std::uint32_t PMTimerBlock;
      std::uint32_t GPE0Block;
      std::uint32_t GPE1Block;
      std::uint8_t  PM1EventLength;
      std::uint8_t  PM1ControlLength;
      std::uint8_t  PM2ControlLength;
      std::uint8_t  PMTimerLength;
      std::uint8_t  GPE0Length;
      std::uint8_t  GPE1Length;
      std::uint8_t  GPE1Base;
      std::uint8_t  CStateControl;
      std::uint16_t WorstC2Latency;
      std::uint16_t WorstC3Latency;
      std::uint16_t FlushSize;
      std::uint16_t FlushStride;
      std::uint8_t  DutyOffset;
      std::uint8_t  DutyWidth;
      std::uint8_t  DayAlarm;
      std::uint8_t  MonthAlarm;
      std::uint8_t  Century;

      // since ACPI 2.0

      std::uint16_t        BootArchitectureFlags;
      std::uint8_t         Reserved2;
      std::uint32_t        Flags;
      generic_address ResetReg;
      std::uint8_t         ResetValue;
      std::uint8_t         Reserved3[3];
      std::uint64_t        X_FirmwareControl;
      std::uint64_t        X_Dsdt;
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

    std::uint32_t local_apic_address;
    std::uint32_t flags;
  };

  enum class apic_structure_type : std::uint8_t
  {
    local_apic             = 0,
    io_apic                = 1,
    input_source_override  = 2,
    non_maskable_interrupt = 3,
    local_apic_nmi         = 4
  };

  struct apic_description
  {
    std::uint8_t type;
    std::uint8_t length;
  };

  struct local_apic_description
  {
    apic_description base;

    std::uint8_t  processor;
    std::uint8_t  id;
    std::uint32_t flags;
  };

  struct io_apic_description
  {
    apic_description base;

    std::uint8_t  id;
    std::uint8_t  reserved0;
    std::uint32_t address;
    std::uint32_t system_vector_base;
  };

  struct input_source_override_description
  {
    apic_description base;

    std::uint8_t  bus;
    std::uint8_t  source;
    std::uint32_t global_system_interrupt_vector;
    std::uint16_t flags;
  };

  struct nmi_source_description
  {
    apic_description base;

    std::uint16_t flags;
    std::uint32_t global_system_interrupt_vector;
  };

  struct local_apic_nmi_description
  {
    apic_description base;

    std::uint8_t  processor;
    std::uint16_t flags;
    std::uint8_t  pin;
  };

}


//! Inline procedure definitions

namespace acpi
{
  inline constexpr
  auto revision ( root_system_description_pointer const & x ) -> std::uint8_t
  {
    return x.revision;
  }

  inline
  auto is_valid_r0 ( root_system_description_pointer const & x ) -> bool
  {
    std::uint8_t sum = 0;
    std::uint8_t const * i = (std::uint8_t const *)(& x);
    std::uint8_t const * e = i + 20;
    for (; i != e; ++i) sum += (* i);
    return (sum == 0);
  }

  inline
  auto is_valid_r1 ( root_system_description_pointer const & x ) -> bool
  {
    std::uint8_t sum = 0;
    std::uint8_t const * i = (std::uint8_t const *)(& x);
    std::uint8_t const * e = i + 36;
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
    std::uint8_t sum = 0;
    std::uint8_t const * i = (std::uint8_t const *)(& x);
    std::uint8_t const * e = i + x.length;
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
  auto begin ( narrow_root_system_description const & x ) -> std::uint32_t const *
  {
    return x.pointers;
  }

  inline
  auto end ( narrow_root_system_description const & x ) -> std::uint32_t const *
  {
    auto const count = (x.header.length - sizeof(acpi::system_description)) / sizeof(std::uint32_t);
    return x.pointers + count;
  }

  inline
  auto begin ( wide_root_system_description const & x ) -> std::uint64_t const *
  {
    return x.pointers;
  }

  inline
  auto end ( wide_root_system_description const & x ) -> std::uint64_t const *
  {
    auto const count = (x.header.length - sizeof(acpi::system_description)) / sizeof(std::uint64_t);
    return x.pointers + count;
  }

}

