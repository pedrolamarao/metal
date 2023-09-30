// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/integer.h>
#include <psys/start.h>
#include <psys/test.h>

#include <x86/identification.h>


void psys::main ()
{
    _test_control = 1;

    if (! x86::has_cpuid()) {
        _test_control = 0;
        return;
    }

    _test_control = 2;

    auto cpuid_0 = x86::cpuid(0);
    if (cpuid_0.a == 0) {
        _test_control = 0;
        return;
    }

    _test_control = 3;

    auto cpuid_1 = x86::cpuid(1);
    if (cpuid_1.a == 0) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}