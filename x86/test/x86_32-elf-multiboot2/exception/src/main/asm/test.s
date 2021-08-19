# Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax noprefix

.global __raise_DE
.type   __raise_DE, @function
__raise_DE:
    pushad
    # prepare zero divisor
    mov eax, 0
.global __raise_DE_bad
__raise_DE_bad:
    # divide by zero
    div eax, eax
    nop
    nop
    nop
    popad
    ret

.global __raise_BP
.type   __raise_BP, @function
__raise_BP:
    pushad
    # trap breakpoint
    int3
    popad
    ret

.global __raise_OF
.type   __raise_OF, @function
__raise_OF:
    pushad
    # cause arithmetic overflow flag to set
    mov al, 0x7F
    inc al
    # trap if arithmetic overflow
    into
    popad
    ret

.global __raise_BR
.type   __raise_BR, @function
__raise_BR:
    pushad
    # push array upper bound
    mov eax, 1
    push eax
    # push array lower bound
    mov eax, 0
    push eax
    # prepare array index
    mov eax, 4
.global __raise_BR_bad
__raise_BR_bad:
    # test array index
    bound eax, [esp]
    nop
    nop
    nop
    # pop array
    add esp, 8
    popad
    ret

.global __raise_UD
.type   __raise_UD, @function
__raise_UD:
    pushad
.global __raise_UD_bad
__raise_UD_bad:
    # convenient undefined instruction
    ud2
    nop
    nop
    nop
    popad
    ret

.global __raise_NP
.type   __raise_NP, @function
__raise_NP:
    pushad
    # save GS register
    mov ax, gs
    # prepare segment selector for non-present data segment
    mov bx, 0x30
.global __raise_NP_bad
__raise_NP_bad:
    mov gs, bx
    nop
    nop
    nop
    nop
    # restore GS register
    mov gs, ax
    popad
    ret

.global __raise_GP
.type   __raise_GP, @function
__raise_GP:
    pushad
    # save GS register
    mov ax, gs
    # prepare segment selector for execute-only code segment
    mov bx, 0x38
.global __raise_GP_bad
__raise_GP_bad:
    mov gs, bx
    nop
    nop
    nop
    nop
    # restore GS register
    mov gs, ax
    popad
    ret
