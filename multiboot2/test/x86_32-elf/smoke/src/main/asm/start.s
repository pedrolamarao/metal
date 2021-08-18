// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.att_syntax

.set STACK_SIZE , 0x4000
.comm stack , STACK_SIZE

.global _start
.type   _start, STT_FUNC
__multiboot2_start:
        jmp     multiboot_entry
        .align  8
multiboot_header:
        .long   0xe85250d6
        .long   0
        .long   multiboot_header_end - multiboot_header
        .long   -(0xe85250d6 + 0 + (multiboot_header_end - multiboot_header))
multiboot_end:
        .short 0
        .short 0
        .long 8
multiboot_header_end:
multiboot_entry:
        movl    $(stack + 0x4000), %esp
        pushl   $0
        popf
        pushl   %ebx
        pushl   %eax
.global _test_start
_test_start:
        movb    $1, _test_control
        movb    $2, _test_control
        movb    $3, _test_control
.global _test_finish
_test_finish:
        nop
loop:   hlt
        jmp     loop
