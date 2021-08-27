// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <psys/integer.h>

#include <multiboot2/information.h>

#include <x86/cpuid.h>


//! Psys test protocol

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
    [[gnu::used]] unsigned volatile _test_debug {};

    void _test_start () { }
    void _test_finish () { }
}

//! Multiboot2 application procedure.

void main ( ps::size4 magic, multiboot2::information_list & mbi )
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