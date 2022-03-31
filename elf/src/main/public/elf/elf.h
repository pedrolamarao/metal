// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/size.h>

namespace elf
{
    using size  = ps::size;
    using size1 = ps::size1;
    using size2 = ps::size2;
    using size4 = ps::size4;
    using size8 = ps::size8;

    constexpr auto EI_NIDENT { 16 };

    struct prologue
    {
        size1 mag0;
        size1 mag1;
        size1 mag2;
        size1 mag3;
        size1 type;
        size1 data;
        size1 version;
        size1 os;
        size1 abi;
        size1 padding [7];
    };

    static_assert(sizeof(prologue) == 16, "unexpected size of prologue");

    enum class machine : size1
    {
        EM_386    = 3,
        EM_X86_64 = 62,
    };

    struct header_32
    {
        prologue ident;
        size2    type;
        machine  machine;
        size4    version;
        size4    entry;
        size4    phoff;
        size4    shoff;
        size4    flags;
        size2    ehsize;
        size2    phentsize;
        size2    phnum;
        size2    shentsize;
        size2    shnum;
        size2    shstrndx;
     };

     static_assert(sizeof(header_32) == 52, "unexpected size of header_32");

    struct header_64
    {
        prologue ident;
        size2    type;
        size2    machine;
        size4    version;
        size8    entry;
        size8    phoff;
        size8    shoff;
        size4    flags;
        size2    ehsize;
        size2    phentsize;
        size2    phnum;
        size2    shentsize;
        size2    shnum;
        size2    shstrndx;
     };

     static_assert(sizeof(header_64) == 64, "unexpected size of header_64");
};