// Copyright (C) 2020,2021,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

import br.dev.pedrolamarao.metal.psys;
import br.dev.pedrolamarao.metal.x86;

namespace psys { void main (); }

void psys::main ()
{
    _test_control = 1;
    _test_control = -1;
    return;
}