.att_syntax

.global _x86_interrupt_00
.type   _x86_interrupt_00, STT_FUNC
_x86_interrupt_00:
    # "fix" caller with NOP
    movl $0x90909090, _test_trap_DE_bad
    incl _x86_interrupt_00_counter
	iret

.global _x86_interrupt_03
.type   _x86_interrupt_03, STT_FUNC
_x86_interrupt_03:
    incl _x86_interrupt_03_counter
	iret

.global _x86_interrupt_04
.type   _x86_interrupt_04, STT_FUNC
_x86_interrupt_04:
    incl _x86_interrupt_04_counter
	iret

.global _x86_interrupt_05
.type   _x86_interrupt_05, STT_FUNC
_x86_interrupt_05:
    # "fix" caller with NOP
    movl $0x90909090, _test_trap_BR_bad
    incl _x86_interrupt_05_counter
	iret

.global _x86_interrupt_06
.type   _x86_interrupt_06, STT_FUNC
_x86_interrupt_06:
    # "fix" caller with NOP
    movl $0x90909090, _test_trap_UD_bad
    incl _x86_interrupt_06_counter
	iret

.global _x86_interrupt_FF
.type   _x86_interrupt_FF, STT_FUNC
_x86_interrupt_FF:
    incl _x86_interrupt_FF_counter
	iret