// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include "config.h"

#include <cstdint>
#include <cstring>
#include <tuple>

#include <aasgard/aasgard.h>

#include <multiboot2/multiboot2.h>

#include <x86/apic.h>
#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>
#include <x86/pic.h>

#include <acpi/system_description.h>

#include "x86.h"


//! ACPI Multiple APIC information analysis

auto acpi_io_apic_description ( acpi::apic_system_description const & x ) -> acpi::io_apic_description const *
{
  using namespace acpi;

  for (auto i = begin(x), e = end(x); i != e; ++i)
    if (i->type == apic_description_type::io_apic)
      return (io_apic_description const *) i;

  return nullptr;
}

//! Multiboot2 ACPI information analysis

typedef std::tuple
        <
         acpi::fixed_system_description const * ,
         acpi::apic_system_description  const *
        >
        multiboot2_acpi_result ;

auto multiboot2_acpi_narrow ( acpi::narrow_root_system_description const & x ) -> multiboot2_acpi_result
{
  using namespace acpi;

  fixed_system_description const * fixed = nullptr;
  apic_system_description  const * apic  = nullptr;

  if (not(is_valid(x))) return multiboot2_acpi_result(fixed, apic);

  for (auto i = begin(x), e = end(x); i != e; ++i)
  {
    auto p = (system_description const *) (* i);

    if (not(is_valid(* p))) continue;

    if (std::memcmp(p->signature, "FACP", 4) == 0)      fixed = (fixed_system_description const *) p;
    else if (std::memcmp(p->signature, "APIC", 4) == 0) apic  = (apic_system_description const *)  p;
  }

  return multiboot2_acpi_result(fixed, apic);
}

auto multiboot2_acpi_wide ( acpi::wide_root_system_description const & x ) -> multiboot2_acpi_result
{
  using namespace acpi;

  fixed_system_description const * acpi_fixed = nullptr;
  apic_system_description const * acpi_apic = nullptr;

  if (not(is_valid(x))) return multiboot2_acpi_result(acpi_fixed, acpi_apic);

  for (auto i = begin(x), e = end(x); i != e; ++i)
  {
    auto p = (system_description const *) (* i);

    if (not(is_valid(* p))) continue;

    if (std::memcmp(p->signature, "FACP", 4) == 0)      acpi_fixed = (fixed_system_description const *) p;
    else if (std::memcmp(p->signature, "APIC", 4) == 0) acpi_apic  = (apic_system_description const *)  p;
  }

  return multiboot2_acpi_result(acpi_fixed, acpi_apic);
}

auto multiboot2_acpi ( multiboot2::information_header const & mbi ) -> multiboot2_acpi_result
{
  using namespace multiboot2;
  using namespace acpi;

  root_system_description_pointer const * acpi_rsdp = nullptr;

  for (auto i = begin(mbi), e = end(mbi); i != e; i = successor(i))
  {
    if (type(* i) == information_type::acpi_new
        || type(* i) == information_type::acpi_old)
    {
      acpi_rsdp = (root_system_description_pointer const *) rsdp( (acpi_information const &)(* i) );
      break;
    }
  }

  if (acpi_rsdp == nullptr)       return multiboot2_acpi_result(nullptr, nullptr);
  if (not(is_valid(* acpi_rsdp))) return multiboot2_acpi_result(nullptr, nullptr);

  if (revision(* acpi_rsdp) == 0) return multiboot2_acpi_narrow(* acpi::narrow_address(* acpi_rsdp));
  else                            return multiboot2_acpi_wide(* acpi::wide_address(* acpi_rsdp));
}

//! Multiboot2 client entry
//!
//! @see start.S

x86::cpuid cpuid_0;

x86::cpuid cpuid_1;

acpi::fixed_system_description const * acpi_fixed = nullptr;

acpi::apic_system_description const * acpi_apic = nullptr;

extern "C"
void multiboot2_entry ( uint32_t magic, multiboot2::information_header * mbi )
{
  // multiboot2

  if (magic != multiboot2::information_magic) return;

  if (not(is_aligned(mbi, 8))) return;

  std::tie(acpi_fixed, acpi_apic) = multiboot2_acpi(* mbi);

  // x86

  if (not(x86::has_cpuid())) return;

  cpuid_0 = x86::cpuid(0);

  cpuid_1 = x86::cpuid(1);

  load_global_descriptor_table();

  load_interrupt_descriptor_table();

  x86::enable_interrupts();

  // APIC

  do
  {
    if (not(x86::has_msr(cpuid_1))) break;

    if (not(x86::has_apic(cpuid_1))) break;

    auto local_apic_base = x86::read_msr(x86::msr::IA32_APIC_BASE);

    auto is_local_apic_enabled = x86::is_apic_enabled(local_apic_base);

    auto local_apic_map = x86::get_apic_memory_map(local_apic_base);

    auto local_apic_id = (uint32_t) local_apic_map->id;

    auto local_apic_version = (uint32_t) local_apic_map->version;

    auto io_apic_description = acpi_io_apic_description(* acpi_apic);

    auto io_apic_address = io_apic_description->address;

    // TODO: configure APIC

    // TODO: enable APIC
  }
  while (false);


  // TODO: configure keyboard

  // TODO: echo keyboard to ?

  // TODO: configure serial

  // TODO: echo keyboard to serial

  // TODO: actually discover devices -- ACPI!?

  return;
}
