// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/identification.h>

export module br.dev.pedrolamarao.metal.x86:identification;

export namespace x86
{
    using ::x86::find_age;
    using ::x86::has_cpuid;
    using ::x86::has_local_apic;
    using ::x86::has_long_mode;
    using ::x86::has_msr;
}