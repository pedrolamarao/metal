// Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/integer.h>
#include <psys/test.h>

#include <multiboot2/information.h>

#include <x86/cpuid.h>


namespace app
{
    void main ( multiboot2::information_list & mbi );
}

void app::main ( multiboot2::information_list & mbi )
{
    _test_control = 1;

    if (! x86::has_cpuid()) {
        _test_control = 0;
        return;
    }

    _test_control = 2;

    auto cpuid_0 = x86::cpuid::load(0);
    if (cpuid_0.a() == 0) {
        _test_control = 0;
        return;
    }

    _test_control = 3;

    auto cpuid_1 = x86::cpuid::load(1);
    if (cpuid_1.a() == 0) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}