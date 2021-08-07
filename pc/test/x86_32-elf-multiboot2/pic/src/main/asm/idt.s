# Copyright (C) 2020,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

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
    mov $0, %al
    outb %al, $0x20
	iret

.global _x86_interrupt_slave
.type   _x86_interrupt_slave, STT_FUNC
_x86_interrupt_slave:
    incl _x86_interrupt_slave_counter
    mov $0, %al
    outb %al, $0xA0
    outb %al, $0x20
	iret

.global _x86_interrupt_free
.type   _x86_interrupt_free, STT_FUNC
_x86_interrupt_free:
    incl _x86_interrupt_free_counter
	iret
