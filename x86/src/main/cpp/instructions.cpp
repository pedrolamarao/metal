// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/instructions.h>


// NOTE: inline assembler in `att` syntax.

namespace x86
{
    // #XXX: LLVM 13 doesn't know how to do extended asm with _ExtInt

    struct carrier { size data {}; };
    static_assert(sizeof(carrier) == sizeof(size), "unexpected size of carrier");

    struct carrier4 { size4 data {}; };
    static_assert(sizeof(carrier4) == sizeof(size4), "unexpected size of carrier4");

    struct carrier8 { size8 data {}; };
    static_assert(sizeof(carrier8) == sizeof(size8), "unexpected size of carrier8");

    auto cpuid2 (size feature, size variant) -> cpuid_type
    {
        carrier a { feature }, b {}, c { variant }, d {};
        __asm__ ( "cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(a), "c"(c) );
        return { a.data, b.data, c.data, d.data  };
    }

    void halt ()
    {
        __asm__ ( "hlt" : );
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