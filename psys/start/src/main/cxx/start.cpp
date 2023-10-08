// Copyright (C) 2022,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

import br.dev.pedrolamarao.metal.multiboot2;
import br.dev.pedrolamarao.metal.psys;

namespace psys
{
    void main ();
}

namespace multiboot2
{
    void main ( ps::size4 magic, multiboot2::information_list & response )
    {
        if (magic != multiboot2::information_magic) return;
        _test_start();
        psys::main();
        _test_finish();
    }
}