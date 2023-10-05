// Copyright (C) 2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/start.h>
#include <psys/test.h>

#include <multiboot2/start.h>

import br.dev.pedrolamarao.metal.psys;

namespace multiboot2
{
    void main ( ps::size4 magic, multiboot2::information_list & response )
    {
        if (magic != information_magic) return;
        _test_start();
        psys::main();
        _test_finish();
    }
}