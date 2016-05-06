// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

idtr:
	.short 0
	.long 0

// x86::internal::__load_global_descriptor_table [ fastcall ] : ( base, limit ) -> ()

.global __load_interrupt_descriptor_table
.type   __load_interrupt_descriptor_table, STT_FUNC
.func   __load_interrupt_descriptor_table

__load_interrupt_descriptor_table:
	mov %ecx, idtr + 2
	mov %dx, idtr
	lidt idtr
	ret

.endfunc


// x86::internal::__store_interrupt_descriptor_table [ fastcall ] : ( idt : ptr(qword) ) -> ()

.global __store_interrupt_descriptor_table
.type   __store_interrupt_descriptor_table, STT_FUNC
.func   __store_interrupt_descriptor_table

__store_interrupt_descriptor_table:
	movl 4(%esp), %eax
	sidt (%eax)
	ret

.endfunc

// x86::internal::__enable_interrupts [ fastcall ] : () -> ()

.global __enable_interrupts
.type   __enable_interrupts, STT_FUNC
.func   __enable_interrupts

__enable_interrupts:
	sti
	ret

.endfunc

// x86::internal::__disable_interrupts [ fastcall ] : () -> ()

.global __disable_interrupts
.type   __disable_interrupts, STT_FUNC
.func   __disable_interrupts

__disable_interrupts:
	cli
	ret

.endfunc
