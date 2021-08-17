// Copyright (C) 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/cpuid.h>

namespace x86
{
    // Primitive procedures.

    // #TODO: Clang cannot do extended assembler with extended integers

    static_assert(sizeof(unsigned char) == 1, "unexpected size of unsigned char");
    static_assert(sizeof(unsigned short) == 2, "unexpected size of unsigned short");
    static_assert(sizeof(unsigned int) == 4, "unexpected size of unsigned int");
    static_assert(sizeof(unsigned long long) == 8, "unexpected size of unsigned long long");

    void cpuid_ ( size4 feature, size4 variant, size4 * a, size4 * b, size4 * c, size4 * d )
    {
        unsigned int const _f { feature };
        unsigned int const _v { variant };
        unsigned int _a;
        unsigned int _b;
        unsigned int _c;
        unsigned int _d;
        __asm__ volatile ( "cpuid" : "=a"(_a), "=b"(_b), "=c"(_c), "=d"(_d) : "0"(_f), "2"(_v) : );
        *a = _a;
        *b = _b;
        *c = _c;
        *d = _d;
    }
}