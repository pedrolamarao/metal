#include <x86/port.h>

namespace x86
{
    // Primitive procedures.

    // #TODO: Clang cannot do extended assembler with extended integers

    static_assert(sizeof(unsigned char) == 1, "unexpected size of unsigned char");
    static_assert(sizeof(unsigned short) == 2, "unexpected size of unsigned short");
    static_assert(sizeof(unsigned int) == 4, "unexpected size of unsigned int");
    static_assert(sizeof(unsigned long long) == 8, "unexpected size of unsigned long long");

    auto in1 ( size2 port ) -> size1
    {
        unsigned short const _port { port };
        unsigned char data;
        __asm__ ( "inb %1, %0" : "=a"(data) : "Nd"(_port) : );
        return data;
    }

    auto in2 ( size2 port ) -> size2
    {
        unsigned short const _port { port };
        unsigned short data;
        __asm__ ( "inw %1, %0" : "=a"(data) : "Nd"(_port) : );
        return data;
    }

    auto in4 ( size2 port ) -> size4
    {
        unsigned short const _port { port };
        unsigned int data;
        __asm__ ( "inl %1, %0" : "=a"(data) : "Nd"(_port) : );
        return data;
    }

    void out1 ( size2 port, size1 data )
    {
        unsigned short const _port { port };
        unsigned char const _data { data };
        __asm__ ( "outb %0, %1" : : "a"(_data), "Nd"(_port) : );
    }

    void out2 ( size2 port, size2 data )
    {
        unsigned short const _port { port };
        unsigned short const _data { data };
        __asm__ ( "outw %0, %1" : : "a"(_data), "Nd"(_port) : );
    }

    void out4 ( size2 port, size4 data )
    {
        unsigned short const _port { port };
        unsigned int const _data { data };
        __asm__ ( "outl %0, %1" : : "a"(_data), "Nd"(_port) : );
    }
}