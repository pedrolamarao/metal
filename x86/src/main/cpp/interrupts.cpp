// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/idt.h>

namespace x86
{
    // Primitive procedures.

    void sti ()
    {
        __asm__ volatile ( "sti" : : : );
    }

    void cli ()
    {
        __asm__ volatile ( "cli" : : : );
    }

    // Interface types.

    system_table_register get_interrupt_descriptor_table_register ()
    {
        system_table_register value;
        __asm__ ( "sidtl %0" : "=m"(value) : : );
        return value;
    }

    void set_interrupt_descriptor_table_register ( system_table_register value )
    {
        __asm__ ( "lidtl %0" : : "m"(value) : );
    }
}