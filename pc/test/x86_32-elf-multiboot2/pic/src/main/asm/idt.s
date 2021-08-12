# Copyright (C) 2020,2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

.macro __x86_trap NN
 .global __x86_exception_\NN\()
 .type   __x86_exception_\NN\(), @function
 .align 4
 __x86_exception_\NN\():
     incl __x86_exception_counter
     iret
.endm

.macro __x86_fault NN
 .global __x86_exception_\NN\()
 .type   __x86_exception_\NN\(), @function
 .align 4
 __x86_exception_\NN\():
     incl __x86_exception_counter
     iret
.endm

.macro __x86_fault_code NN
 .global __x86_exception_\NN\()
 .type   __x86_exception_\NN\(), @function
 .align 4
 __x86_exception_\NN\():
     incl __x86_exception_counter
     add $4, %esp
     iret
.endm

__x86_fault      00
__x86_fault      01
__x86_trap       02
__x86_trap       03
__x86_trap       04
__x86_fault      05
__x86_fault      06
__x86_fault      07
__x86_fault_code 08
__x86_fault      09
__x86_fault_code 0A
__x86_fault_code 0B
__x86_fault_code 0C
__x86_fault_code 0D
__x86_fault_code 0E
__x86_trap       0F
__x86_fault      10
__x86_fault_code 11
__x86_fault      12
__x86_fault      13
__x86_fault      14
__x86_fault_code 15
__x86_trap       16
__x86_trap       17
__x86_trap       18
__x86_trap       19
__x86_trap       1A
__x86_trap       1B
__x86_trap       1C
__x86_trap       1D
__x86_trap       1E
__x86_trap       1F

.global __x86_interrupt_master
.type   __x86_interrupt_master, STT_FUNC
.align 4
__x86_interrupt_master:
    incl __x86_interrupt_master_counter
    mov $0x20, %al
    outb %al, $0x20
	iret

.global __x86_interrupt_slave
.type   __x86_interrupt_slave, STT_FUNC
.align 4
__x86_interrupt_slave:
    incl __x86_interrupt_slave_counter
    mov $0x20, %al
    outb %al, $0xA0
    outb %al, $0x20
	iret

.global __x86_interrupt
.type   __x86_interrupt, STT_FUNC
.align 4
__x86_interrupt:
    incl __x86_interrupt_counter
	iret
