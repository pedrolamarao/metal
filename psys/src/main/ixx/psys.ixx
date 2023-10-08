// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <psys/integer.h>
#include <psys/move.h>
#include <psys/port.h>
#include <psys/size.h>
#include <psys/test.h>

export module br.dev.pedrolamarao.metal.psys;

export namespace ps
{
    // integer
    using ::ps::integer;
    using ::ps::integer1;
    using ::ps::integer2;
    using ::ps::integer4;
    using ::ps::integer8;

    // move
    using ::ps::move;

    // port
    using ::ps::is_port;

    // size
    using ::ps::size;
    using ::ps::size1;
    using ::ps::size2;
    using ::ps::size4;
    using ::ps::size8;
}

export using ::_test_start;
export using ::_test_finish;
export using ::_test_control;
export using ::_test_debug;