// Copyright (C) 2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

import br.dev.pedrolamarao.metal.psys;

namespace elf
{
    using size  = ps::size;
    using size1 = ps::size1;
    using size2 = ps::size2;
    using size4 = ps::size4;
    using size8 = ps::size8;

    //! ELF machine type.

    enum class machine : size2
    {
        EM_386    = 3,
        EM_X86_64 = 62,
    };

    //! ELF segment type.

    enum class segment : size4
    {
        load = 1,
    };

    //! ELF header prologue.

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

    //! ELF 32-bit header.

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

    //! ELF 32-bit segment header.

    struct segment_32
    {
        segment type;
        size4 offset;
        size4 vaddr;
        size4 paddr;
        size4 filesz;
        size4 memsz;
        size4 flags;
        size4 align;
    };

    static_assert(sizeof(segment_32) == 32, "unexpected size of segment_32");

    //! ELF 64-bit header.

    struct header_64
    {
        prologue ident;
        size2    type;
        machine  machine;
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

    //! ELF 64-bit segment header.

    struct segment_64
    {
        segment type;
        size4 flags;
        size8 offset;
        size8 vaddr;
        size8 paddr;
        size8 filesz;
        size8 memsz;
        size8 align;
    };

    static_assert(sizeof(segment_64) == 56, "unexpected size of segment_64");
};