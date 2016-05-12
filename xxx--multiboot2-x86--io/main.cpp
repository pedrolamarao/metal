// Copyright (C) 2016 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <cstddef>
#include <cstdint>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/gdt.h>
#include <x86/idt.h>

#include <pc/cmos.h>
#include <pc/pic.h>


namespace
{
  using multiboot2::architecture_type;
  using multiboot2::end_request;
  using multiboot2::header_prologue;

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
}

namespace
{
  using x86::segment_descriptor;
  using x86::code_segment_access;
  using x86::data_segment_access;
  using x86::segment_granularity;

  constexpr segment_descriptor global_descriptor_table [5] __attribute__((aligned(8), section(".gdt"))) =
  {
    { },
    { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
    { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
    { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
    { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
  };
}

extern "C" void __interrupt_handler ();

extern "C" void __00_exception_handler ();
extern "C" void __01_exception_handler ();
extern "C" void __02_exception_handler ();
extern "C" void __03_exception_handler ();
extern "C" void __04_exception_handler ();
extern "C" void __05_exception_handler ();
extern "C" void __06_exception_handler ();
extern "C" void __07_exception_handler ();
extern "C" void __08_exception_handler ();
extern "C" void __09_exception_handler ();
extern "C" void __0A_exception_handler ();
extern "C" void __0B_exception_handler ();
extern "C" void __0C_exception_handler ();
extern "C" void __0D_exception_handler ();
extern "C" void __0E_exception_handler ();
extern "C" void __0F_exception_handler ();
extern "C" void __10_exception_handler ();
extern "C" void __11_exception_handler ();
extern "C" void __12_exception_handler ();
extern "C" void __13_exception_handler ();
extern "C" void __14_exception_handler ();

extern "C" void __20_interrupt_handler ();
extern "C" void __21_interrupt_handler ();
extern "C" void __22_interrupt_handler ();
extern "C" void __23_interrupt_handler ();
extern "C" void __24_interrupt_handler ();
extern "C" void __25_interrupt_handler ();
extern "C" void __26_interrupt_handler ();
extern "C" void __27_interrupt_handler ();
extern "C" void __28_interrupt_handler ();
extern "C" void __29_interrupt_handler ();
extern "C" void __2A_interrupt_handler ();
extern "C" void __2B_interrupt_handler ();
extern "C" void __2C_interrupt_handler ();
extern "C" void __2D_interrupt_handler ();
extern "C" void __2E_interrupt_handler ();
extern "C" void __2F_interrupt_handler ();

void io_wait ()
{
  asm volatile ("jmp 1f");
  asm volatile ("1:");
  asm volatile ("jmp 2f");
  asm volatile ("2:");
}

extern "C" void exception (std::uint32_t level, std::uint32_t error)
{
  return;
}

extern "C" void interrupt (std::uint32_t level)
{
  return;
}

//! Multiboot2 client entry
//!
//! @see start.S

extern "C"
void __attribute__((fastcall)) main ( std::uint32_t magic, multiboot2::information_list & mbi )
{
  // assert Multiboot2 load

  if (magic != multiboot2::information_magic) return;

  // load GDT

  x86::load_global_descriptor_table(global_descriptor_table);

  x86::reload_segment_registers(x86::segment_selector(1, false, 0), x86::segment_selector(2, false, 0));

  // load IDT

  using x86::interrupt_gate_access;
  using x86::interrupt_gate_descriptor;

  interrupt_gate_descriptor idt [] =
  {
    // 0x00
    { 0x8, __00_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __01_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __02_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __03_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __04_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __05_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __06_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __07_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __08_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __09_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __0A_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __0B_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __0C_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __0D_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __0E_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __0F_exception_handler, interrupt_gate_access(true, 0) },
    // 0x10
    { 0x8, __10_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __11_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __12_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __13_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __14_exception_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __interrupt_handler, interrupt_gate_access(true, 0) },
    // 0x20
    { 0x8, __20_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __21_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __22_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __23_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __24_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __25_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __26_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __27_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __28_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __29_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __2A_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __2B_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __2C_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __2D_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __2E_interrupt_handler, interrupt_gate_access(true, 0) },
    { 0x8, __2F_interrupt_handler, interrupt_gate_access(true, 0) },
  };

  x86::load_interrupt_descriptor_table(idt);

  // initialize PIC

  // ICW1
  asm volatile ("mov $0x11, %al");
  asm volatile ("outb %al, $0x20");
  asm volatile ("outb %al, $0xA0");
  io_wait();
  // ICW2
  asm volatile ("mov $0x20, %al");
  asm volatile ("outb %al, $0x21");
  asm volatile ("mov $0x28, %al");
  asm volatile ("outb %al, $0xA1");
  io_wait();
  // ICW3
  asm volatile ("mov $0x04, %al");
  asm volatile ("outb %al, $0x21");
  asm volatile ("mov $0x02, %al");
  asm volatile ("outb %al, $0xA1");
  io_wait();
  // ICW4
  asm volatile ("mov $0x01, %al");
  asm volatile ("outb %al, $0x21");
  asm volatile ("outb %al, $0xA1");
  // OCW2
  asm volatile ("mov $0x00, %al");
  asm volatile ("outb %al, $0x21");
  asm volatile ("outb %al, $0xA1");

  // enable interrupts

  asm volatile ( "sti" );

  return;
}
