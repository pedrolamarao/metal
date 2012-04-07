// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

// TODO: this should be placed in the .recycle section

.type gdtr, STT_OBJECT

gdtr:
	.short 0
    .long 0

// x86::internal::__load_global_descriptor_table [ fastcall ] : ( base : address , limit : size ) -> ()

.global __load_global_descriptor_table
.type   __load_global_descriptor_table, STT_FUNC
.func   __load_global_descriptor_table

__load_global_descriptor_table:
	mov %ecx, gdtr + 2
	mov %dx, gdtr
	lgdt gdtr
	ret

.endfunc

// x86::internal::__reload_segment_registers [ fastcall ] : ( code : size , data : size ) -> ()

.global __reload_segment_registers
.type   __reload_segment_registers, STT_FUNC
.func   __reload_segment_registers

__reload_segment_registers:
	push %ecx
	mov $reload, %eax
	push %eax
	lret
reload:
	mov %dx, %ds
	mov %dx, %es
	mov %dx, %fs
	mov %dx, %gs
	mov %dx, %ss
	ret

.endfunc
