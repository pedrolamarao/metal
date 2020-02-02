// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <cstdint>


//! Declarations

namespace multiboot2
{
  //! @brief Multiboot2 header alignment

  constexpr unsigned header_alignment = 8;

  //! @brief Multiboot2 header tag alignment

  constexpr unsigned tag_alignment = 8;

  //! @brief Multiboot2 header magic number

  constexpr std::uint32_t header_magic = 0xe85250d6;

  //! @brief Multiboot2 request architecture

  enum class architecture_type : std::uint32_t
  {
    x86    = 0,
    mips32 = 4,
  };


  //! @brief Multiboot2 header tag type

  enum class tag_type : std::uint16_t
  {
    end         = 0,
    information = 1,
    address     = 2,
    entry       = 3,
    console     = 4,
    framebuffer = 5,
    module      = 6,
  };


  //! @brief Multiboot2 header prologue
  //!
  //! Multiboot2 headers have a prologue and a list of tags.

  struct alignas(header_alignment) header_prologue
  {
    std::uint32_t      magic;
    architecture_type  architecture;
    std::uint32_t      size;
    std::uint32_t      checksum;

    constexpr
    header_prologue (architecture_type architecture, std::uint32_t size);
  };

  //! @brief Multiboot2 tag list end

  struct alignas(tag_alignment) end_request
  {
    tag_type      type  = tag_type::end;
    std::uint16_t flags = 0;
    std::uint32_t size  = 8;
  };

  //! @brief Multiboot2 request for loading a.out

  struct alignas(tag_alignment) address_request
  {
    tag_type      type;
    std::uint16_t flags;
    std::uint32_t size;

    std::uint32_t header_addr;
    std::uint32_t load_addr;
    std::uint32_t load_end_addr;
    std::uint32_t bss_end_addr;
  };

  //! @brief Multiboot2 request for loading ELF

  struct alignas(tag_alignment) entry_address_request
  {
    tag_type      type;
    std::uint16_t flags;
    std::uint32_t size;

    std::uint32_t entry_addr;
  };

  //! @brief Multiboot2 request for console support

  struct alignas(tag_alignment) console_request
  {
    tag_type      type;
    std::uint16_t flags;
    std::uint32_t size;

    std::uint32_t console_flags;

    constexpr
    console_request (std::uint16_t flags, std::uint32_t console_flags);

    constexpr explicit
    console_request (std::uint32_t console_flags);
  };

  //! @brief Multiboot2 request for framebuffer support

  struct alignas(tag_alignment) framebuffer_request
  {
    tag_type      type;
    std::uint16_t flags;
    std::uint32_t size;

    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t depth;

    constexpr
    framebuffer_request (std::uint16_t flags, std::uint32_t width, std::uint32_t height, std::uint32_t depth);

    constexpr
    framebuffer_request (std::uint32_t width, std::uint32_t height, std::uint32_t depth);
  };

  //! @brief Multiboot2 request for module alignment

  struct alignas(tag_alignment) module_alignment_request
  {
    tag_type      type;
    std::uint16_t flags;
    std::uint32_t size;

    std::uint32_t unused [3];

    constexpr explicit
    module_alignment_request (std::uint16_t f);

    constexpr
    module_alignment_request ();
  };

}

//! Inline definitions

namespace multiboot2
{

  constexpr
  header_prologue::header_prologue (architecture_type a, std::uint32_t s) :
    magic(header_magic), architecture(a), size(s),
    checksum(- (header_magic + (std::uint32_t)(architecture_type::x86) + s))
  { }

  constexpr
  console_request::console_request (std::uint16_t f, std::uint32_t cf) :
    type(tag_type::console), flags(f), size(sizeof(console_request)), console_flags(cf)
  { }

  constexpr
  console_request::console_request (std::uint32_t cf) :
    type(tag_type::console), flags(1), size(sizeof(console_request)), console_flags(cf)
  { }

  constexpr
  framebuffer_request::framebuffer_request (std::uint16_t f, std::uint32_t w, std::uint32_t h, std::uint32_t d) :
    type(tag_type::framebuffer), flags(f), size(sizeof(framebuffer_request)), width(w), height(h), depth(d)
  { }

  constexpr
  framebuffer_request::framebuffer_request (std::uint32_t w, std::uint32_t h, std::uint32_t d) :
    type(tag_type::framebuffer), flags(1), size(sizeof(framebuffer_request)), width(w), height(h), depth(d)
  { }

  constexpr inline
  module_alignment_request::module_alignment_request (std::uint16_t f) :
    type(tag_type::module), flags(f), size(sizeof(module_alignment_request)), unused{0,0,0}
  { }

  constexpr inline
  module_alignment_request::module_alignment_request () :
    type(tag_type::module), flags(1), size(sizeof(module_alignment_request)), unused{0,0,0}
  { }

}
