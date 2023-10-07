// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

import br.dev.pedrolamarao.metal.multiboot2;
import br.dev.pedrolamarao.metal.multiboot2.start;

//! Start code.

namespace sandbox
{
    void main ();
}

//! The multiboot2 loader has done all the work!

namespace multiboot2
{
    void main (ps::size4 magic, multiboot2::information_list & information)
    {
        sandbox::main();
    }
}
