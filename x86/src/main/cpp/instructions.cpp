// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <x86/instructions.h>


// NOTE: inline assembler in `att` syntax.

namespace x86
{
    // #XXX: LLVM 13 doesn't know how to do extended asm with _ExtInt
    struct carrier { size data {}; };

    static_assert(sizeof(carrier) == sizeof(size), "unexpected size of carrier");

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
}