# Copyright (C) 2012, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax

# __x86_cpu_age [ fastcall ] : ( ) -> ( age )

.global _x86_cpu_age
_x86_cpu_age:

    # load EFLAGS: ecx keeps the original value
	pushfd
    pop eax
    mov ecx, eax

    # detect i386: can we flip EFLAGS AC?
    mov edx, 3
    # flip AC flag
	xor eax, 0x40000
	# store EFLAGS with flipped AC flag
	push eax
	popfd
	# load EFLAGS
    pushfd
    pop eax
    # terminate if AC flag did not change
    xor eax, ecx
    jz _x86_cpu_age_end

    # restore EFLAGS
    push ecx
    popfd
    mov eax, ecx

    # detect i486: can we flip EFLAGS ID?
    mov edx, 4
    # flip ID flag
    xor eax, 0x200000
	# store EFLAGS with flipped ID flag
	push eax
	popfd
	# load EFLAGS
    pushfd
    pop eax
    # terminate if ID flag did not change
    xor eax, ecx
    jz _x86_cpu_age_end

    # detect i586
    mov edx, 5

_x86_cpu_age_end:

    # restore EFLAGS
    push ecx
    popfd

    # return detected CPU age
    mov eax, edx
	ret

# _x86_cpuid [ fastcall ] : ( feature, variant, cpuid ) -> ()

.global _x86_cpuid
_x86_cpuid:
	mov	esi, dword ptr [esp + 4]
	mov eax, ecx
	mov ecx, edx
	cpuid
	mov	dword ptr [esi], eax
	mov	dword ptr [esi + 4], ebx
	mov	dword ptr [esi + 8], ecx
	mov	dword ptr [esi + 12], edx
	ret 4
