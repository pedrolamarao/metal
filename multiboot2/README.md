# aasgard &mdash; Multiboot 2

The Multiboot2 library offers components for programming the Multiboot2 specification.

It enables easy definition of Multiboot2 headers and parsing Multiboot2 information structures.

## Examples

### Minimal Multiboot2 header

Objective: define a minimal Multiboot2 header for the x86 architecture placed in a special ELF section.

The minimal header contains a prologue followed by the end tag.

We use compiler attributes to disable undesired optimizations and to place the header in a special ELF section.

```c++
#include <multiboot2/multiboot2.h>

namespace
{
  using namespace multiboot2;

  struct
  {
    header_prologue  prologue;
    end_request      end;
  }
  constexpr request __attribute__(( used, section(".multiboot2") )) =
  {
    { architecture_type::x86, sizeof(request), },
    { },
  };
}
```

### Multiboot2 header requests framebuffer support

Objective: define a Multiboot2 header that requests framebuffer support.

This header must contain the framebuffer tag with useful values for width, heigth and depth. In this example we request a 1024x768 framebuffer with 32 bits color depth.

```c++
#include <multiboot2/header.h>


namespace
{
  using namespace multiboot2;

  struct
  {
    header_prologue      prologue;
    framebuffer_request  framebuffer;
    end_request          end;
  }
  constexpr request __attribute__(( used, section(".multiboot2") )) =
  {
    { architecture_type::x86, sizeof(request), },
    { 1024, 768, 32 },
    { },
  };
}
```


### Inspect Multiboot2 information list

Objective: iterate the Multiboot2 information list and inspect each item.

We assume the program has done whatever is necessary to jump into procedures defined in C++.

```c++
#include <multiboot2/multiboo2.h>

void multiboot2_information_iterate ( multiboot2::information_header & mbi )
{    
  using namespace multiboot2;

  if (magic != information_magic) return;

  unsigned total = 0;

  information_item * end_item = nullptr;
  command_line_information * command_line_item = nullptr;
  loader_name_information * loader_name_item = nullptr;
  modules_information * modules_item = nullptr;
  basic_memory_information * basic_memory_item = nullptr;
  boot_device_information * boot_device_item = nullptr;
  memory_map_information * memory_map_item = nullptr;
  vbe_information * vbe_item = nullptr;
  framebuffer_information * framebuffer_item = nullptr;
  elf_symbols_information * elf_symbols_item = nullptr;
  apm_information * apm_item = nullptr;
  efi32_information * efi32_item = nullptr;
  efi64_information * efi64_item = nullptr;
  smbios_information * smbios_item = nullptr;
  acpi_information * acpi_old_item = nullptr;
  acpi_information * acpi_new_item = nullptr;
  network_information * network_item = nullptr;

  for (auto i = begin(mbi), j = end(mbi); i != j; i = next(i))
  {
    ++total;

    using type = multiboot2::information_type;
    switch (i->type)
    {
      case type::end: end_item = i; break;
      case type::command_line: command_line_item = reinterpret_cast<command_line_information*>(i); break;
      case type::loader_name: loader_name_item = reinterpret_cast<loader_name_information*>(i); break;
      case type::modules: modules_item = reinterpret_cast<modules_information*>(i); break;
      case type::basic_memory: basic_memory_item = reinterpret_cast<basic_memory_information*>(i); break;
      case type::boot_device: boot_device_item = reinterpret_cast<boot_device_information*>(i); break;
      case type::memory_map: memory_map_item = reinterpret_cast<memory_map_information*>(i); break;
      case type::vbe_info: vbe_item = reinterpret_cast<vbe_information*>(i); break;
      case type::framebuffer: framebuffer_item = reinterpret_cast<framebuffer_information*>(i); break;
      case type::elf_symbols: elf_symbols_item = reinterpret_cast<elf_symbols_information*>(i); break;
      case type::apm_table: apm_item = reinterpret_cast<apm_information*>(i); break;
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
```


## Components

All components are declared in `namespace multiboot2`.

* `header.h`
  * `header_prologue`
  * `address_request`
  * `entry_address_request`
  * `console_request`
  * `framebuffer_request`
  * `module_alignment_request`
* `information.h`
  * `information_list`
  * `command_line_information`
  * `loader_name_information`
  * `module_information`
  * `basic_memory_information`
  * `boot_device_information`
  * `memory_map_information`
  * `elf_symbols_information`
  * `apm_information`
  * `vbe_information`
  * `framebuffer_information`
  * `efi32_information`
  * `efi64_information`
  * `smbios_information`
  * `acpi_information`
  * `network_information`

## References

* [Multiboot2] &mdash; "The Multiboot Specification", version 1.6, [:link:](http://download-mirror.savannah.gnu.org/releases/grub/phcoder/multiboot.pdf)