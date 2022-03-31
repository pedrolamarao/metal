// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


void out1 ( unsigned short port, unsigned char data )
{
    __asm__ ( "outb %0, %1" : : "a"(data), "Nd"(port) : );
}

extern "C"
void _start ()
{
    out1(0xE9,'P');
    out1(0xE9,'S');
    out1(0xE9,'Y');
    out1(0xE9,'S');
}