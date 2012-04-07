// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

.global __division_by_zero_start

__division_by_zero_start:
	iret

.global __debug_start

__debug_start:
	iret

.global __nmi_start

__nmi_start:
	iret

.global __breakpoint_start

__breakpoint_start:
	iret

.global __overflow_start

__overflow_start:
	iret

.global __bound_range_exceeded_start

__bound_range_exceeded_start:
	iret

.global __invalid_opcode_start

__invalid_opcode_start:
	iret

.global __device_not_available_start

__device_not_available_start:
	iret

.global __double_fault_start

__double_fault_start:
	iret

.global __invalid_tss_start

__invalid_tss_start:
	iret

.global __segment_not_present_start

__segment_not_present_start:
	iret

.global __stack_fault_start

__stack_fault_start:
	iret

.global __general_protection_fault_start

__general_protection_fault_start:
	iret

.global __page_fault_start

__page_fault_start:
	iret

.global __fpu_error_start

__fpu_error_start:
	iret

.global __alignment_fault_start

__alignment_fault_start:
	iret

.global __machine_fault_start

__machine_fault_start:
	iret

.global __simd_fault_start

__simd_fault_start:
	iret

.global __user_interrupt_start

__user_interrupt_start:
	iret
