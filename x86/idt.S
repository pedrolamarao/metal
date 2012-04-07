// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

// x86::internal::__load_global_descriptor_table [ fastcall ] : ( base, limit ) -> ()

.global __load_interrupt_descriptor_table

idtr:
	.short 0
	.long 0

__load_interrupt_descriptor_table:
	mov %ecx, idtr + 2
	mov %dx, idtr
	lidt idtr
	ret

// x86::internal::__enable_interrupts [ fastcall ] : () -> ()

.global __enable_interrupts

__enable_interrupts:
	sti
	ret

// x86::internal::__disable_interrupts [ fastcall ] : () -> ()

.global __disable_interrupts

__disable_interrupts:
	cli
	ret
