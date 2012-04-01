// Copyright (C) 2012 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

// load_global_descriptor_table [ fastcall ] : ( base : address , limit : size ) -> ()

.global __load_global_descriptor_table

gdtr:
	.short 0
    .long 0

// TODO: this should be placed in the 'recyclable' section

__load_global_descriptor_table:
	mov %ecx, gdtr + 2
	mov %dx, gdtr
	lgdt gdtr
	ret

// reload_segment_registers [ fastcall ] : ( code : size , data : size ) -> ()

.global __reload_segment_registers

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
