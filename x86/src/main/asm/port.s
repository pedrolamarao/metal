# Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

.intel_syntax noprefix

# fastcall __x86_port_read_08 ( address : dword ) -> ( data : byte )

.global __x86_port_read_08
.type   __x86_port_read_08, @function
__x86_port_read_08:
    mov dx, cx
    in al, dx
    ret

# fastcall __x86_port_read_16 ( address : word ) -> ( data : word )

.global __x86_port_read_16
.type   __x86_port_read_16, @function
__x86_port_read_16:
    mov dx, cx
    in ax, dx
    ret

# fastcall __x86_port_read_32 ( address : word ) -> ( data : dword )

.global __x86_port_read_32
.type   __x86_port_read_32, @function
__x86_port_read_32:
    mov dx, cx
    in eax, dx
    ret

# fastcall __x86_port_write_08 ( data : byte, address : dword ) -> ( )

.global __x86_port_write_08
.type   __x86_port_write_08, @function
__x86_port_write_08:
    mov al, cl
    out dx, al
    ret

# fastcall __x86_port_write_16 ( data : word, address : word ) -> ( )

.global __x86_port_write_16
.type   __x86_port_write_16, @function
__x86_port_write_16:
    mov ax, cx
    out dx, ax
    ret

# fastcall __x86_port_write_32 ( data : dword, address : word ) -> ( )

.global __x86_port_write_32
.type   __x86_port_write_32, @function
__x86_port_write_32:
    mov eax, ecx
    out dx, eax
    ret