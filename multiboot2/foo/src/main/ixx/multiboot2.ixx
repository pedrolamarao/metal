// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <multiboot2/header.h>
#include <multiboot2/information.h>

export module br.dev.pedrolamarao.metal.multiboot2;

export namespace multiboot2
{
    // header
    using ::multiboot2::header_alignment;
    using ::multiboot2::tag_alignment;
    using ::multiboot2::header_magic;
    using ::multiboot2::architecture_type;
    using ::multiboot2::tag_type;
    using ::multiboot2::header_prologue;
    using ::multiboot2::end_request;
    using ::multiboot2::address_request;
    using ::multiboot2::entry_address_request;
    using ::multiboot2::console_request;
    using ::multiboot2::framebuffer_request;
    using ::multiboot2::module_alignment_request;

    // information
    using ::multiboot2::information_magic;
    using ::multiboot2::information_alignment;
    using ::multiboot2::information_list;
    using ::multiboot2::information_type;
    namespace internal { using ::multiboot2::internal::information_item; }
    using ::multiboot2::begin;
    using ::multiboot2::end;
    using ::multiboot2::next;
    using ::multiboot2::end_information;
    using ::multiboot2::command_line_information;
    using ::multiboot2::loader_name_information;
    using ::multiboot2::modules_information;
    using ::multiboot2::basic_memory_information;
    using ::multiboot2::boot_device_information;
    using ::multiboot2::memory_map_information;
    using ::multiboot2::elf_symbols_information;
    using ::multiboot2::apm_information;
    using ::multiboot2::vbe_information;
    using ::multiboot2::framebuffer_information;
    using ::multiboot2::efi32_information;
    using ::multiboot2::efi64_information;
    using ::multiboot2::smbios_information;
    using ::multiboot2::acpi_information;
    using ::multiboot2::network_information;
}
