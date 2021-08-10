# Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

.global _x86_exception
.type   _x86_exception, STT_FUNC
_x86_exception:
    incl _x86_exception_counter
	iret

.global _x86_interrupt_master
.type   _x86_interrupt_master, STT_FUNC
_x86_interrupt_master:
    incl _x86_interrupt_master_counter
    mov $0x20, %al
    out %al, $0x20
	iret

.global _x86_interrupt_slave
.type   _x86_interrupt_slave, STT_FUNC
_x86_interrupt_slave:
    incl _x86_interrupt_slave_counter
    mov $0x20, %al
    out %al, $0xA0
    out %al, $0x20
	iret

.global _x86_interrupt_free
.type   _x86_interrupt_free, STT_FUNC
_x86_interrupt_free:
    incl _x86_interrupt_free_counter
	iret

.global _test_sandbox
.type   _test_sandbox, STT_FUNC
_test_sandbox:
    mov $0x34, %al
    out %al, $0x43
    mov $0x10000, %ax
    out %al, $0x40
    mov %ah, %al
    out %al, $0x40
    ret
