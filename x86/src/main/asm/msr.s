// Copyright (C) 2012, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax

// fastcall __x86_msr_read : ( id : dword, value : qword ptr ) -> (  )

.global __x86_msr_read
.type   __x86_msr_read, @function
__x86_msr_read:
    mov ebx, edx
	rdmsr
	mov dword ptr [ebx], eax
	mov dword ptr [ebx + 4], edx
	ret

// fastcall __x86_write_msr_32 : ( id : dword, value : dword )

.global __x86_msr_write_32
.type   __x86_msr_write_32, @function
__x86_msr_write_32:
	mov eax, edx
	mov edx, 0
	wrmsr
	ret

// fastcall __x86_msr_write_64 : ( id : dword, value : qword ptr )

.global __x86_msr_write_64
.type   __x86_msr_write_64, @function
__x86_msr_write_64:
    mov ebx, edx
	mov eax, dword ptr [ebx]
	mov edx, dword ptr [ebx + 4]
	wrmsr
	ret
