// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/msr.h>

namespace x86
{
    // Primitive procedures.

    // #TODO: Clang cannot do extended assembler with extended integers

    static_assert(sizeof(unsigned char) == 1, "unexpected size of unsigned char");
    static_assert(sizeof(unsigned short) == 2, "unexpected size of unsigned short");
    static_assert(sizeof(unsigned int) == 4, "unexpected size of unsigned int");
    static_assert(sizeof(unsigned long long) == 8, "unexpected size of unsigned long long");

    auto rdmsr (size4 id) -> size8
    {
        unsigned int const _id { id };
        unsigned long long _value;
        __asm__ ( "rdmsr " : "=A"(_value) : "c"(_id) : );
        return _value;
    }

    void wrmsr (size4 id, size8  value)
    {
        unsigned int const _id { id };
        unsigned long long _value { value };
        __asm__ ( "wrmsr " : : "c"(_id), "A"(_value) : );
    }
}