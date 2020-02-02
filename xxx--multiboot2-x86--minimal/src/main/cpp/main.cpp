// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>


namespace
{
  using namespace multiboot2;

  struct
  {
    header_prologue prologue;
    end_request     end;
  }
  constexpr request __attribute__(( used, section(".multiboot2") )) =
  {
    { architecture_type::x86, sizeof(request), },
    { },
  };

  multiboot2::end_information * end_item = nullptr;
  multiboot2::command_line_information * command_line_item = nullptr;
  multiboot2::loader_name_information * loader_name_item = nullptr;
  multiboot2::modules_information * modules_item = nullptr;
  multiboot2::basic_memory_information * basic_memory_item = nullptr;
  multiboot2::boot_device_information * boot_device_item = nullptr;
  multiboot2::memory_map_information * memory_map_item = nullptr;
  multiboot2::vbe_information * vbe_item = nullptr;
  multiboot2::framebuffer_information * framebuffer_item = nullptr;
  multiboot2::elf_symbols_information * elf_symbols_item = nullptr;
  multiboot2::apm_information * apm_item = nullptr;
  multiboot2::efi32_information * efi32_item = nullptr;
  multiboot2::efi64_information * efi64_item = nullptr;
  multiboot2::smbios_information * smbios_item = nullptr;
  multiboot2::acpi_information * acpi_old_item = nullptr;
  multiboot2::acpi_information * acpi_new_item = nullptr;
  multiboot2::network_information * network_item = nullptr;
}

//! Multiboot2 client entry
//!
//! @see start.S

extern "C"
void __attribute__((fastcall)) main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
  using namespace multiboot2;

  if (magic != information_magic) return;

  for (auto i = begin(mbi), j = end(mbi); i != j; i = next(i))
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

  return;
}
