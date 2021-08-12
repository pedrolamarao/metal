# Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

.macro __x86_trap NN, TT
 .global __x86_interrupt_\NN\()
 .type   __x86_interrupt_\NN\(), @function
 .align 4
 __x86_interrupt_\NN\():
     # increment interrupt counter
     incl __x86_interrupt_\NN\()_counter
     iret
.endm

.macro __x86_fault NN, TT
 .global __x86_interrupt_\NN\()
 .type   __x86_interrupt_\NN\(), @function
 .align 4
 __x86_interrupt_\NN\():
     # "fix" caller with NOPs
     movl $0x90909090, __test_trap_\TT\()_bad
     # increment interrupt counter
     incl __x86_interrupt_\NN\()_counter
     iret
.endm

.macro __x86_fault_code NN, TT
 .global __x86_interrupt_\NN\()
 .type   __x86_interrupt_\NN\(), @function
 .align 4
 __x86_interrupt_\NN\():
     # "fix" caller with NOPs
     movl $0x90909090, __test_trap_\TT\()_bad
     # increment interrupt counter
     incl __x86_interrupt_\NN\()_counter
     # discard error code from stack
     add $4, %esp
     iret
.endm

__x86_fault      00, DE
__x86_trap       03, BP
__x86_trap       04, OF
__x86_fault      05, BR
__x86_fault      06, UD
__x86_fault_code 0B, NP
__x86_fault_code 0D, GP
__x86_trap       FF, FF