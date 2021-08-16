# Copyright (C) 2012, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax noprefix

# fastcall __x86_get_global_descriptor_table_register ( system_table_register : dword ) -> ( )

.global __x86_get_global_descriptor_table_register
.type   __x86_get_global_descriptor_table_register, @function
__x86_get_global_descriptor_table_register:
    sgdt [ecx]
    ret

# fastcall __x86_set_global_descriptor_table_register ( system_table_register : dword ) -> ( )

.global __x86_set_global_descriptor_table_register
.type   __x86_set_global_descriptor_table_register, @function
__x86_set_global_descriptor_table_register:
    lgdt [ecx]
    ret

# fastcall __x86_get_code_segment_register () -> ()
.global __x86_get_code_segment_register
.type   __x86_get_code_segment_register, @function
__x86_get_code_segment_register:
    mov ax, cs
    ret

# fastcall __x86_set_code_segment_register ( segment_selector : word ) -> ( )

.global __x86_set_code_segment_register
.type   __x86_set_code_segment_register, @function
__x86_set_code_segment_register:
	push ecx
	mov eax, offset .Lreload
	push eax
	retf
.Lreload:
    ret

# fastcall __x86_set_data_segment_registers ( segment_selector : word ) -> ()
.global __x86_set_data_segment_registers
.type   __x86_set_data_segment_registers, @function
__x86_set_data_segment_registers:
    mov ds, cx
    mov es, cx
    mov ss, cx
    mov fs, cx
    mov gs, cx
    ret