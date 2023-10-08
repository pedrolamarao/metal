// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/instructions.h>

export module br.dev.pedrolamarao.metal.x86:instructions;

export namespace x86
{
    using ::x86::far_reference;
    using ::x86::call;
    using ::x86::cpuid_type;
    using ::x86::cpuid;
    using ::x86::cli;
    using ::x86::halt;
    using ::x86::in1;
    using ::x86::in2;
    using ::x86::in4;
    using ::x86::out1;
    using ::x86::out2;
    using ::x86::out4;
    using ::x86::pause;
    using ::x86::rdmsr;
    using ::x86::wrmsr;
}