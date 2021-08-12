# Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax noprefix

.global __test_trap_DE
.type   __test_trap_DE, @function
__test_trap_DE:
    pushad
    # prepare zero divisor
    mov eax, 0
.global __test_trap_DE_bad
__test_trap_DE_bad:
    # divide by zero
    div eax, eax
    nop
    nop
    nop
    popad
    ret

.global __test_trap_BP
.type   __test_trap_BP, @function
__test_trap_BP:
    pushad
    # trap breakpoint
    int3
    popad
    ret

.global __test_trap_OF
.type   __test_trap_OF, @function
__test_trap_OF:
    pushad
    # cause arithmetic overflow flag to set
    mov al, 0x7F
    inc al
    # trap if arithmetic overflow
    into
    popad
    ret

.global __test_trap_BR
.type   __test_trap_BR, @function
__test_trap_BR:
    pushad
    # push array upper bound
    mov eax, 1
    push eax
    # push array lower bound
    mov eax, 0
    push eax
    # prepare array index
    mov eax, 4
.global __test_trap_BR_bad
__test_trap_BR_bad:
    # test array index
    bound eax, [esp]
    nop
    nop
    nop
    # pop array
    add esp, 8
    popad
    ret

.global __test_trap_UD
.type   __test_trap_UD, @function
__test_trap_UD:
    pushad
.global __test_trap_UD_bad
__test_trap_UD_bad:
    # convenient undefined instruction
    ud2
    nop
    nop
    nop
    popad
    ret
