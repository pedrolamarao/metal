// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


//! Module data.

constinit unsigned data { 123 };

//! Module entry point.

extern "C"
void _start ()
{
    if (data != 123) {
        __asm__ volatile (
            "cli\n"
            "1:\n"
            "hlt\n"
            "jmp 1b\n"
            :
        );
    }
}