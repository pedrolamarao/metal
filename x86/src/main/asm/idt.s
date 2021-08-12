# Copyright (C) 2012, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax noprefix

# fastcall __x86_get_interrupt_descriptor_table_register ( system_table_register : dword ) -> ( )

.global __x86_get_interrupt_descriptor_table_register
.type   __x86_get_interrupt_descriptor_table_register, @function
__x86_get_interrupt_descriptor_table_register:
    sidt [ecx]
    ret

# fastcall __x86_set_interrupt_descriptor_table_register ( system_table_register : dword ) -> ( )

.global __x86_set_interrupt_descriptor_table_register
.type   __x86_set_interrupt_descriptor_table_register, @function
__x86_set_interrupt_descriptor_table_register:
    lidt [ecx]
    ret

# fastcall __x86_enable_interrupts () -> ()

.global __x86_enable_interrupts
.type   __x86_enable_interrupts, @function
__x86_enable_interrupts:
	sti
	ret

# fastcall __x86_disable_interrupts () -> ()

.global __x86_disable_interrupts
.type   __x86_disable_interrupts, @function
__x86_disable_interrupts:
	cli
	ret
