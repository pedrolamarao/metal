// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/start.h>


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
