// Copyright (C) 2020,2021,2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/start.h>
#include <psys/test.h>

import br.dev.pedrolamarao.metal.psys;

void psys::main ()
{
    _test_control = 1;
    _test_control = -1;
    return;
}