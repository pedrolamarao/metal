.att_syntax

.text

.set STACK_SIZE , 0x4000

.comm stack , STACK_SIZE

//! Multiboot2 client entry point
//!
//! @param %eax  value of Multiboot information magic number
//! @param %ebx  address of Multiboot2 information object

.global _start

_start:

    movl $(stack + STACK_SIZE), %esp

    push $0
    popf

    push %ebx
    push %eax
    call multiboot2_entry

loop:
    hlt
    jmp loop
