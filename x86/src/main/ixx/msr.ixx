// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/msr.h>

export module br.dev.pedrolamarao.metal.x86:msr;

export namespace x86
{
    using ::x86::msr;
    using ::x86::get_msr;
    using ::x86::set_msr;
}