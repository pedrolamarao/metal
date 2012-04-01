#pragma once

#include <stdint.h>

namespace multiboot2
{
  //! End of range for Multiboot request object search
  constexpr uint32_t request_search = 32768;

  //! Alignment of Multiboot request object
  constexpr uint32_t request_alignment = 8;

  //! Multiboot request magic number
  constexpr uint32_t request_magic = 0xe85250d6;

  //! Multiboot information magic number
  constexpr uint32_t information_magic = 0x36d76289;

  //! Alignment of Multiboot modules
  constexpr uint32_t module_alignment = 0x00001000;

  //! Alignment of the Multiboot information object
  constexpr uint32_t information_alignment = 0x00000008;


  //! Multiboot request architecture

  enum class request_architecture : uint32_t
  {
    x86    = 0,
    mips32 = 4,
  };

  //! Multiboot request type

  enum class request_type : uint32_t
  {
    end         = 0,
    information = 1,
    address     = 2,
    entry       = 3,
    console     = 4,
    framebuffer = 5,
    module      = 6,
  };

  //! Multiboot request flag

  enum class request_flag : uint32_t
  {
    none     = 0,
    optional = 1,
  };

  //! Multiboot request header
  //!
  //! A Multiboot request object is composed of a header followed by one or more entries.

  struct request_header
  {
    uint32_t             magic;
    request_architecture architecture;
    uint32_t             size;
    uint32_t             checksum;
  };

  //! Multiboot request base
  //!
  //! A Multiboot request is composed of a header followed by type specific data.

  struct request_entry_base
  {
    request_type type;
    request_flag flags;
    uint32_t     size;
  };

  //! Multiboot request

  struct address_request
  {
    uint16_t type;
    uint16_t flags;
    uint32_t size;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
  };

  //! Multiboot request

  struct entry_address_request
  {
    uint16_t type;
    uint16_t flags;
    uint32_t size;
    uint32_t entry_addr;
  };

  //! Multiboot request

  struct console_flags_request
  {
    uint16_t type;
    uint16_t flags;
    uint32_t size;
    uint32_t console_flags;
  };

  //! Multiboot request

  struct framebuffer_request
  {
    uint16_t type;
    uint16_t flags;
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
  };

  //! Multiboot request

  struct module_align_request
  {
    uint16_t type;
    uint16_t flags;
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
  };

  //! Multiboot information type

  enum class information_type : uint32_t
  {
    end              = 0,
    command_line     = 1,
    boot_loader_name = 2,
    module           = 3,
    basic_memory     = 4,
    bios_boot_device = 5,
    memory_map       = 6,
    vbe_info         = 7,
    framebuffer      = 8,
    elf_symbols      = 9,
    apm_table        = 10,
    efi32            = 11,
    efi64            = 12,
    smbios           = 13,
    acpi_old         = 14,
    acpi_new         = 15,
    network          = 16,
  };

  //! Multiboot information header
  //!
  //! Multiboot information objects are composed of a header and a sequence of entries.

  struct information_header
  {
    uint32_t total;
    uint32_t reserved;
  };

  auto total (information_header const & x) -> uint32_t ;

  struct information_entry_base;

  auto begin (information_header const & x) -> information_entry_base const * ;

  auto end (information_header const & x) -> information_entry_base const * ;

  auto successor (information_entry_base const * x) -> information_entry_base const * ;

  //! Multiboot information entry base
  //!
  //! Multiboot information entries are composed of a base and type specific data.

  struct information_entry_base
  {
    information_type type;
    uint32_t         size;
  };

  auto type (information_entry_base const & x) -> information_type ;

  auto size (information_entry_base const & x) -> uint32_t ;

  //! Multiboot command line information

  struct command_line_information
  {
    information_entry_base base;

    char command [];
  };

  auto command (command_line_information const & x) -> char const * ;

  //! Multiboot boot loader name

  struct boot_loader_name_information
  {
    information_entry_base base;

    char name [];
  };

  auto name (boot_loader_name_information const & x) -> char const * ;

  //! Multiboot module information

  struct module_information
  {
    information_entry_base base;

    uint32_t start;
    uint32_t end;
    char     command [];
  };

  auto start (module_information const & x) -> uint32_t ;

  auto end (module_information const & x) -> uint32_t ;

  auto command (module_information const & x) -> char const * ;

  //! Multiboot basic memory information

  struct basic_memory_information
  {
    information_entry_base base;

    uint32_t lower;
    uint32_t upper;
  };

  auto lower (basic_memory_information const & x) -> uint32_t ;

  auto upper (basic_memory_information const & x) -> uint32_t ;

  //! Multiboot BIOS boot device information tag

  struct bios_boot_device_information
  {
    information_entry_base base;

    uint32_t device;
    uint32_t partition;
    uint32_t sub_partition;
  };

  auto device (bios_boot_device_information const & x) -> uint32_t ;

  auto partition (bios_boot_device_information const & x) -> uint32_t ;

  auto sub_partition (bios_boot_device_information const & x) -> uint32_t ;

  //! Multiboot memory map information
  //!
  //! Objects are composed of a header and one or more entries

  struct memory_map_information
  {
    information_entry_base base;

    uint32_t entry_size;
    uint32_t entry_version;
  };

  struct memory_map_entry;

  auto begin (memory_map_information const & x) -> memory_map_entry const * ;

  auto end (memory_map_information const & x) -> memory_map_entry const * ;

  auto successor (memory_map_entry const * x) -> memory_map_entry const * ;

  //! Multiboot memory map type

  enum class memory_map_type : uint32_t
  {
    available = 1,
    reserved  = 2,
    acpi      = 3,
    nvs       = 4,
    badram    = 5,
  };

  //! Multiboot memory map entry

  struct memory_map_entry
  {
    uint64_t        address;
    uint64_t        length;
    memory_map_type type;
    uint32_t        reserved;
  };

  auto address (memory_map_entry const & x) -> void const * ;

  auto length (memory_map_entry const & x) -> uint64_t ;

  auto type (memory_map_entry const & x) -> memory_map_type ;

  //! Multiboot ELF symbols information

  struct elf_symbols_information
  {
    information_entry_base base;

    uint16_t num;
    uint16_t entsize;
    uint16_t shndx;
    uint16_t reserved;
  };

  // TODO: declare accessors

  //! Multiboot APM information

  struct apm_information
  {
    information_entry_base base;

    uint16_t version;
    uint16_t cseg;
    uint16_t offset;
    uint16_t cseg_16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t cseg_len;
    uint16_t cseg_16_len;
    uint16_t dseg_len;
  };

  // TODO: declare accessors

  //! Multiboot VBE information

  struct vbe_information
  {
    information_entry_base base;

    uint16_t mode;
    uint16_t interface_seg;
    uint16_t interface_off;
    uint16_t interface_len;
    uint16_t control_info;
    uint16_t mode_info;
  };

  // TODO: declare accessors

  //! Multiboot framebuffer type

  enum class framebuffer_type : uint32_t
  {
    indexed = 0,
    rgb = 1,
    ega = 2,
  };

  //! Multiboot framebuffer information

  struct framebuffer_information
  {
    information_entry_base base;

    uint64_t         address;
    uint32_t         pitch;
    uint32_t         width;
    uint32_t         height;
    uint8_t          bpp;
    framebuffer_type type;
    uint8_t          reserved;
  };

  // TODO: declare accessors

  //! Multiboot EFI32 information

  struct efi32_information
  {
    information_entry_base base;

    uint32_t pointer;
  };

  // TODO: declare accessors

  //! Multiboot EFI64 information

  struct efi64_information
  {
    information_entry_base base;

    uint64_t pointer;
  };

  // TODO: declare accessors

  //! Multiboot SMBIOS information

  struct smbios_information
  {
    information_entry_base base;

    uint8_t major;
    uint8_t minor;
    uint8_t reserved [6];
    uint8_t tables   [];
  };

  // TODO: declare accessors

  //! Multiboot ACPI information (old and new)

  struct acpi_information
  {
    information_entry_base base;

    uint8_t rsdp [];
  };

  // TODO: declare accessors

  //! Multiboot network information

  struct network_information
  {
    information_entry_base base;

    uint8_t dhcpack [];
  };

  // TODO: declare accessors

}

//! Inline procedure definitions

namespace multiboot2
{

  inline
  auto total (information_header const & x) -> uint32_t
  {
    return x.total;
  }

  inline
  auto begin (information_header const & x) -> information_entry_base const *
  {
    return (information_entry_base *)( (char *)(& x) + 8 );
  }

  inline
  auto end (information_header const & x) -> information_entry_base const *
  {
    return (information_entry_base *)( (char *)(& x) + x.total );
  }

  inline
  auto successor (information_entry_base const * x) -> information_entry_base const *
  {
    return (information_entry_base const *)( (char *)(x) + size(* x) );
  }

  inline
  auto type (information_entry_base const & x) -> information_type
  {
    return x.type;
  }

  inline
  auto size (information_entry_base const & x) -> uint32_t
  {
    return (x.size + uint32_t(7)) / uint32_t(8) * uint32_t(8);
  }

  inline
  auto begin (memory_map_information const & x) -> memory_map_entry const *
  {
    return (memory_map_entry *)((& x) + 16);
  }

  inline
  auto end (memory_map_information const & x) -> memory_map_entry const *
  {
    return (memory_map_entry *)((& x) + x.base.size);
  }

  inline
  auto successor (memory_map_entry const * x) -> memory_map_entry const *
  {
    return (memory_map_entry *)((char *)(x) + 24);
  }

  inline
  auto lower (basic_memory_information const & x) -> uint32_t
  {
    return x.lower;
  }

  inline
  auto upper (basic_memory_information const & x) -> uint32_t
  {
    return x.upper;
  }

  inline
  auto command (command_line_information const & x) -> char const *
  {
    return x.command;
  }

  inline
  auto address (memory_map_entry const & x) -> void const *
  {
    return (void *)(x.address);
  }

  inline
  auto length (memory_map_entry const & x) -> uint64_t
  {
    return x.length;
  }

  inline
  auto type (memory_map_entry const & x) -> memory_map_type
  {
    return (memory_map_type)(x.type);
  }

  inline
  auto name (boot_loader_name_information const & x) -> char const *
  {
    return x.name;
  }

}
