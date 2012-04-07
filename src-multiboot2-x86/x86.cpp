// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include "config.h"

#include <x86/gdt.h>
#include <x86/idt.h>

#include "x86.h"

using namespace x86;

//! @{

//! Global descriptor table adequate for SYSENTER/SYSEXIT

segment_descriptor global_descriptor_table [5] __attribute__(( used, aligned(8), section(".gdt") )) =
{
  segment_descriptor { },
  segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 0), segment_granularity(false, true, true) },
  segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 0), segment_granularity(false, true, true) },
  segment_descriptor { 0, 0xFFFFFFFF, code_segment_access(true, false, 3), segment_granularity(false, true, true) },
  segment_descriptor { 0, 0xFFFFFFFF, data_segment_access(true, false, 3), segment_granularity(false, true, true) },
};

void load_global_descriptor_table ()
{
  load_global_descriptor_table(global_descriptor_table, 5);
  reload_segment_registers(1, 2);
}

//! @}

//! @{

//!  Division by Zero Exception is number 0
extern "C" void __division_by_zero_start ();

//! Debug Exception is number 1
extern "C" void __debug_start ();

//! Non-Maskable Interrupt is number 2
extern "C" void __nmi_start ();

//! Breakpoint Exception is number 3
extern "C" void __breakpoint_start ();

//! Overflow Exception is number 4
extern "C" void __overflow_start ();

//! Bound Range Exceeded Exception is number 5
extern "C" void __bound_range_exceeded_start ();

//! Invalid Opcode Exception is number 6
extern "C" void __invalid_opcode_start ();

//! Device not Available Exception is number 7
extern "C" void __device_not_available_start ();

//! Double Fault Exception is number 8
extern "C" void __double_fault_start ();

//! Invalid TSS Exception is number 10
extern "C" void __invalid_tss_start ();

//! Segment not Present Exception is number 11
extern "C" void __segment_not_present_start ();

//! Stack Fault Exception is number 12
extern "C" void __stack_fault_start ();

//! General Protection Fault Exception is number 13
extern "C" void __general_protection_fault_start ();

//! Page Fault Exception is number 14
extern "C" void __page_fault_start ();

//! Floating-Point Unit Error Exception is number 16
extern "C" void __fpu_error_start ();

//! Alignment Check Exception is number 17
extern "C" void __alignment_fault_start ();

//! Machine Check Exception is number 18
extern "C" void __machine_fault_start ();

//! SIMD Floating-Point Exception is number 19
extern "C" void __simd_fault_start ();

//! User-Defined Interrupt is any from number 32 to 255
extern "C" void __user_interrupt_start ();

//! Interrupt descriptor table

interrupt_gate_descriptor interrupt_descriptor_table [256] __attribute__(( used, aligned(8), section(".idt") )) =
{
  interrupt_gate_descriptor { 8, 0xFFEFEEDE, interrupt_gate_access(true, 0) },
};

void load_interrupt_descriptor_table ()
{
  // TODO: find a way to const-initialize the table

  interrupt_descriptor_table[0].set ( 8, __division_by_zero_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[1].set ( 8, __debug_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[2].set ( 8, __nmi_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[3].set ( 8, __breakpoint_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[4].set ( 8, __overflow_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[5].set ( 8, __bound_range_exceeded_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[6].set ( 8, __invalid_opcode_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[7].set ( 8, __device_not_available_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[8].set ( 8, __double_fault_start, interrupt_gate_access(true, 0) );
  //
  interrupt_descriptor_table[10].set ( 8, __invalid_tss_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[11].set ( 8, __segment_not_present_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[12].set ( 8, __stack_fault_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[13].set ( 8, __general_protection_fault_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[14].set ( 8, __page_fault_start, interrupt_gate_access(true, 0) );
  //
  interrupt_descriptor_table[16].set ( 8, __fpu_error_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[17].set ( 8, __alignment_fault_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[18].set ( 8, __machine_fault_start, interrupt_gate_access(true, 0) );
  interrupt_descriptor_table[19].set ( 8, __simd_fault_start, interrupt_gate_access(true, 0) );
  //
  interrupt_descriptor_table[32].set ( 8, __user_interrupt_start, interrupt_gate_access(true, 0) );

  x86::load_interrupt_descriptor_table(interrupt_descriptor_table, 256);
}

//! @}
