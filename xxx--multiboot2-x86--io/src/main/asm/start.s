.att_syntax

.text

.set STACK_SIZE , 0x4000

.comm stack , STACK_SIZE

// extern "C" void exception ( std::uint32_t level, std::uint32_t error )

.extern exception

.align 4
.global __00_exception_handler
.type __00_exception_handler, STT_FUNC
.func
__00_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x00
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __01_exception_handler
.type __01_exception_handler, STT_FUNC
.func
__01_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x01
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __02_exception_handler
.type __02_exception_handler, STT_FUNC
.func
__02_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x02
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __03_exception_handler
.type __03_exception_handler, STT_FUNC
.func
__03_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x03
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __04_exception_handler
.type __04_exception_handler, STT_FUNC
.func
__04_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x04
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __05_exception_handler
.type __05_exception_handler, STT_FUNC
.func
__05_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x05
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __06_exception_handler
.type __06_exception_handler, STT_FUNC
.func
__06_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x06
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __07_exception_handler
.type __07_exception_handler, STT_FUNC
.func
__07_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x07
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __08_exception_handler
.type __08_exception_handler, STT_FUNC
.func
__08_exception_handler:
	pusha
	cld
	pushl $0x08
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __09_exception_handler
.type __09_exception_handler, STT_FUNC
.func
__09_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x09
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __0A_exception_handler
.type __0A_exception_handler, STT_FUNC
.func
__0A_exception_handler:
	pusha
	cld
	pushl $0x0A
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __0B_exception_handler
.type __0B_exception_handler, STT_FUNC
.func
__0B_exception_handler:
	pusha
	cld
	pushl $0x0B
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __0C_exception_handler
.type __0C_exception_handler, STT_FUNC
.func
__0C_exception_handler:
	pusha
	cld
	pushl $0x0C
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __0D_exception_handler
.type __0D_exception_handler, STT_FUNC
.func
__0D_exception_handler:
	pusha
	cld
	pushl $0x0D
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __0E_exception_handler
.type __0E_exception_handler, STT_FUNC
.func
__0E_exception_handler:
	pusha
	cld
	pushl $0x0E
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __0F_exception_handler
.type __0F_exception_handler, STT_FUNC
.func
__0F_exception_handler:
	pusha
	cld
	pushl $0x0F
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __10_exception_handler
.type __10_exception_handler, STT_FUNC
.func
__10_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x10
	call exception
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __11_exception_handler
.type __11_exception_handler, STT_FUNC
.func
__11_exception_handler:
	pusha
	cld
	pushl $0x11
	call exception
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __12_exception_handler
.type __12_exception_handler, STT_FUNC
.func
__12_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x12
	call exception
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __13_exception_handler
.type __13_exception_handler, STT_FUNC
.func
__13_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x13
	call exception
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __14_exception_handler
.type __14_exception_handler, STT_FUNC
.func
__14_exception_handler:
	pusha
	cld
	pushl $0x00
	pushl $0x14
	call exception
	addl $4, %esp
	popa
	iret
.endfunc

// extern "C" void interrupt ( std::uint32_t level )

.extern interrupt

.align 4
.global __interrupt_handler
.type __interrupt_handler, STT_FUNC
.func
__interrupt_handler:
	pusha
	cld
	pushl $0xFF
	call interrupt
	addl $8, %esp
	popa
	iret
.endfunc

.align 4
.global __20_interrupt_handler
.type __20_interrupt_handler, STT_FUNC
.func
__20_interrupt_handler:
	pusha
	cld
	pushl $0x20
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __21_interrupt_handler
.type __21_interrupt_handler, STT_FUNC
.func
__21_interrupt_handler:
	pusha
	cld
	pushl $0x21
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __22_interrupt_handler
.type __22_interrupt_handler, STT_FUNC
.func
__22_interrupt_handler:
	pusha
	cld
	pushl $0x22
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __23_interrupt_handler
.type __23_interrupt_handler, STT_FUNC
.func
__23_interrupt_handler:
	pusha
	cld
	pushl $0x23
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __24_interrupt_handler
.type __24_interrupt_handler, STT_FUNC
.func
__24_interrupt_handler:
	pusha
	cld
	pushl $0x24
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __25_interrupt_handler
.type __25_interrupt_handler, STT_FUNC
.func
__25_interrupt_handler:
	pusha
	cld
	pushl $0x25
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __26_interrupt_handler
.type __26_interrupt_handler, STT_FUNC
.func
__26_interrupt_handler:
	pusha
	cld
	pushl $0x26
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __27_interrupt_handler
.type __27_interrupt_handler, STT_FUNC
.func
__27_interrupt_handler:
	pusha
	cld
	pushl $0x27
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __28_interrupt_handler
.type __28_interrupt_handler, STT_FUNC
.func
__28_interrupt_handler:
	pusha
	cld
	pushl $0x28
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __29_interrupt_handler
.type __29_interrupt_handler, STT_FUNC
.func
__29_interrupt_handler:
	pusha
	cld
	pushl $0x29
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __2A_interrupt_handler
.type __2A_interrupt_handler, STT_FUNC
.func
__2A_interrupt_handler:
	pusha
	cld
	pushl $0x2A
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __2B_interrupt_handler
.type __2B_interrupt_handler, STT_FUNC
.func
__2B_interrupt_handler:
	pusha
	cld
	pushl $0x2B
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __2C_interrupt_handler
.type __2C_interrupt_handler, STT_FUNC
.func
__2C_interrupt_handler:
	pusha
	cld
	pushl $0x2C
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __2D_interrupt_handler
.type __2D_interrupt_handler, STT_FUNC
.func
__2D_interrupt_handler:
	pusha
	cld
	pushl $0x2D
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __2E_interrupt_handler
.type __2E_interrupt_handler, STT_FUNC
.func
__2E_interrupt_handler:
	pusha
	cld
	pushl $0x2E
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

.align 4
.global __2F_interrupt_handler
.type __2F_interrupt_handler, STT_FUNC
.func
__2F_interrupt_handler:
	pusha
	cld
	pushl $0x2F
	call interrupt
	addl $4, %esp
	popa
	iret
.endfunc

// extern "C" void [[gnu::fastcall]] main ( std::uint32_t magic, multiboot2::information_list & mbi )

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

.Lloop:
    hlt
    jmp .Lloop
