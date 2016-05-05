.att_syntax

.text

.set STACK_SIZE , 0x4000

.comm stack , STACK_SIZE

// extern "C"
// void __attribute__((fastcall)) main ( std::uint32_t magic, multiboot2::information_list & mbi )

.extern main

//! Multiboot2 client entry point
//!
//! @param %eax  Multiboot2 information magic number
//! @param %ebx  Multiboot2 information list address

.global _start

_start:

    movl $(stack + STACK_SIZE), %esp

    push $0
    popf

    mov %eax,%ecx
    mov %ebx,%edx
    call main

loop:
    hlt
    jmp loop
