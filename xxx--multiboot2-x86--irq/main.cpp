// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstddef>
#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>


namespace
{
  using namespace multiboot2;

  struct
  {
    header_prologue prologue;
    end_request     end;
  }
  constexpr multiboot2_header __attribute__(( used, section(".multiboot2") )) =
  {
    { architecture_type::x86, sizeof(multiboot2_header), },
    { },
  };

  multiboot2::end_information const * end_item = nullptr;
  multiboot2::command_line_information const  * command_line_item = nullptr;
  multiboot2::loader_name_information const  * loader_name_item = nullptr;
  multiboot2::modules_information const  * modules_item = nullptr;
  multiboot2::basic_memory_information const  * basic_memory_item = nullptr;
  multiboot2::boot_device_information const  * boot_device_item = nullptr;
  multiboot2::memory_map_information const  * memory_map_item = nullptr;
  multiboot2::vbe_information const  * vbe_item = nullptr;
  multiboot2::framebuffer_information const  * framebuffer_item = nullptr;
  multiboot2::elf_symbols_information const  * elf_symbols_item = nullptr;
  multiboot2::apm_information const  * apm_item = nullptr;
  multiboot2::efi32_information const  * efi32_item = nullptr;
  multiboot2::efi64_information const  * efi64_item = nullptr;
  multiboot2::smbios_information const  * smbios_item = nullptr;
  multiboot2::acpi_information const  * acpi_old_item = nullptr;
  multiboot2::acpi_information const  * acpi_new_item = nullptr;
  multiboot2::network_information const  * network_item = nullptr;

  void parse_multiboot2_information ( multiboot2::information_list & list )
  {
	  for (auto i = begin(list), j = end(list); i != j; i = next(i))
	  {
	    using type = multiboot2::information_type;
	    switch (i->type)
	    {
	      case type::end: end_item = reinterpret_cast<end_information*>(i); break;
	      case type::command_line: command_line_item = reinterpret_cast<command_line_information*>(i); break;
	      case type::loader_name: loader_name_item = reinterpret_cast<loader_name_information*>(i); break;
	      case type::modules: modules_item = reinterpret_cast<modules_information*>(i); break;
	      case type::basic_memory: basic_memory_item = reinterpret_cast<basic_memory_information*>(i); break;
	      case type::boot_device: boot_device_item = reinterpret_cast<boot_device_information*>(i); break;
	      case type::memory_map: memory_map_item = reinterpret_cast<memory_map_information*>(i); break;
	      case type::vbe: vbe_item = reinterpret_cast<vbe_information*>(i); break;
	      case type::framebuffer: framebuffer_item = reinterpret_cast<framebuffer_information*>(i); break;
	      case type::elf_symbols: elf_symbols_item = reinterpret_cast<elf_symbols_information*>(i); break;
	      case type::apm: apm_item = reinterpret_cast<apm_information*>(i); break;
	      case type::efi32: efi32_item = reinterpret_cast<efi32_information*>(i); break;
	      case type::efi64: efi64_item = reinterpret_cast<efi64_information*>(i); break;
	      case type::smbios: smbios_item = reinterpret_cast<smbios_information*>(i); break;
	      case type::acpi_old: acpi_old_item = reinterpret_cast<acpi_information*>(i); break;
	      case type::acpi_new: acpi_new_item = reinterpret_cast<acpi_information*>(i); break;
	      case type::network: network_item = reinterpret_cast<network_information*>(i); break;
	    }
	  }
  }
}

namespace
{
  using namespace x86;

  constexpr segment_descriptor global_descriptor_table [5] __attribute__((aligned(8), section(".gdt"))) =
  {
    { },
    { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
    { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
    { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
    { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
  };

  using gate_descriptor = x86::interrupt_gate_descriptor;

  gate_descriptor interrupt_descriptor_table [256] __attribute__((aligned(8), section(".idt"))) =
  { };

  extern "C"
  void __interrupt_service_routine ();
}

//! Multiboot2 client entry
//!
//! @see start.S

extern "C"
void __attribute__((fastcall)) main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
  if (magic != multiboot2::information_magic) return;

  x86::load_global_descriptor_table(global_descriptor_table);

  x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

  std::uint64_t gdt { 0xFFFFFFFFFFFFFFFF };
  x86::internal::__store_global_descriptor_table(gdt);

  if (((5 * sizeof(segment_descriptor)) - 1) != (gdt & 0xFFFF)) return;
  if (std::uint32_t(& global_descriptor_table) != ((gdt >> 16) & 0xFFFFFFFF)) return;

  parse_multiboot2_information(mbi);

  for (auto i = 0U, j = 256U; i != j; ++i)
  {
    interrupt_descriptor_table[i] = { 0x8, __interrupt_service_routine, interrupt_gate_access(true, 0) };
  }

  x86::load_interrupt_descriptor_table(interrupt_descriptor_table, 256);

  std::uint64_t idt { 0xFFFFFFFFFFFFFFFF };
  x86::internal::__store_interrupt_descriptor_table(idt);

  if ((256 * sizeof(interrupt_gate_descriptor)) != (idt & 0xFFFF)) return;
  if (std::uint32_t(& interrupt_descriptor_table) != ((idt >> 16) & 0xFFFFFFFF)) return;

  asm volatile ( "sti" );

  return;
}
