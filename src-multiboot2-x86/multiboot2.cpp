// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include "config.h"

#include <aasgard/aasgard.h>

#include <multiboot2/multiboot2.h>

#include <x86/xapic.h>
#include <x86/x2apic.h>
#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>

#include "x86.h"

using namespace multiboot2;

//! Multiboot2 information request object

struct
{
  request_header     header;
  request_entry_base last;
}
request __attribute__(( used, aligned(8), section(".multiboot2") )) =
{
  {
    request_magic,
    request_architecture::x86,
    sizeof(request),
    (- (request_magic + (uint32_t)(request_architecture::x86) + sizeof(request))),
  },
  {
    request_type::end,
    request_flag::none,
    8,
  },
};

//! Multiboot2 client entry
//!
//! @see start.S

extern "C"
void multiboot2_entry ( uint32_t magic, multiboot2::information_header * mbi )
{
  if (magic != multiboot2::information_magic) return;

  if (not(is_aligned(mbi, 8))) return;

  load_global_descriptor_table();

  load_interrupt_descriptor_table();

  x86::enable_interrupts();

  // TODO: continue...

  return;
}
