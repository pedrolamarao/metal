.intel_syntax noprefix

.global _test_trap_DE
_test_trap_DE:
    mov eax, 0
    nop
    nop
.global _test_trap_DE_bad
_test_trap_DE_bad:
    div eax, eax
    nop
    nop
    ret

.global _test_trap_BP
_test_trap_BP:
    int3
    ret

.global _test_trap_OF
_test_trap_OF:
    mov al, 0x7F
    inc al
    into
    ret

.global _test_trap_BR
_test_trap_BR:
    xor eax, eax
    push eax
    push eax
    mov eax, 1
    nop
    nop
.global _test_trap_BR_bad
_test_trap_BR_bad:
    bound eax, [esp]
    nop
    nop
    pop eax
    pop eax
    ret

.global _test_trap_UD
_test_trap_UD:
    nop
    nop
.global _test_trap_UD_bad
_test_trap_UD_bad:
    ud2
    nop
    nop
    ret
