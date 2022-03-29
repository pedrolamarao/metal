// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/instructions.h>


// NOTE: inline assembler in `att` syntax.

namespace x86
{
    // #XXX: LLVM 13 doesn't know how to do extended asm with _ExtInt

    struct carrier { size data {}; };
    static_assert(sizeof(carrier) == sizeof(size), "unexpected size of carrier");

    struct carrier1 { size1 data {}; };
    static_assert(sizeof(carrier1) == sizeof(size1), "unexpected size of carrier1");

    struct carrier2 { size2 data {}; };
    static_assert(sizeof(carrier2) == sizeof(size2), "unexpected size of carrier2");

    struct carrier4 { size4 data {}; };
    static_assert(sizeof(carrier4) == sizeof(size4), "unexpected size of carrier4");

    struct carrier8 { size8 data {}; };
    static_assert(sizeof(carrier8) == sizeof(size8), "unexpected size of carrier8");

    void call ( far_reference target )
    {
        __asm__ ( "lcall *%0" : : "m"(target) );
    }

    auto cpuid (size feature, size variant) -> cpuid_type
    {
        carrier a { feature }, b {}, c { variant }, d {};
        __asm__ ( "cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(a), "c"(c) );
        return { a.data, b.data, c.data, d.data  };
    }

    void halt ()
    {
        __asm__ ( "hlt" : );
    }

    auto in1 ( size2 port ) -> size1
    {
        carrier2 _port { port };
        carrier1 _in {};
        __asm__ ( "inb %1, %0" : "=a"(_in) : "Nd"(_port) : );
        return _in.data;
    }

    auto in2 ( size2 port ) -> size2
    {
        carrier2 _port { port };
        carrier2 _in {};
        __asm__ ( "inw %1, %0" : "=a"(_in) : "Nd"(_port) : );
        return _in.data;
    }

    auto in4 ( size2 port ) -> size4
    {
        carrier2 _port { port };
        carrier4 _in {};
        __asm__ ( "inl %1, %0" : "=a"(_in) : "Nd"(_port) : );
        return _in.data;
    }

    void out1 ( size2 port, size1 data )
    {
        carrier2 _port { port };
        carrier1 _out { data };
        __asm__ ( "outb %0, %1" : : "a"(_out), "Nd"(_port) : );
    }

    void out2 ( size2 port, size2 data )
    {
        carrier2 _port { port };
        carrier2 _out { data };
        __asm__ ( "outw %0, %1" : : "a"(_out), "Nd"(_port) : );
    }

    void out4 ( size2 port, size4 data )
    {
        carrier2 _port { port };
        carrier4 _out { data };
        __asm__ ( "outl %0, %1" : : "a"(_out), "Nd"(_port) : );
    }

    void pause ()
    {
        __asm__ ( "pause" : );
    }

    auto rdmsr (size4 id) -> size8
    {
        carrier4 _id { id };
        carrier8 _value {};
        __asm__ ( "rdmsr " : "=A"(_value) : "c"(_id) : );
        return _value.data;
    }

    void wrmsr (size4 id, size8  value)
    {
        carrier4 _id { id };
        carrier8 _value { value };
        __asm__ ( "wrmsr " : : "c"(_id), "A"(_value) : );
    }
}