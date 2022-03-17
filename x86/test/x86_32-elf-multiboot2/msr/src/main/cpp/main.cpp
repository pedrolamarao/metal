// Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>
#include <psys/start.h>
#include <psys/test.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>


void psys::main ()
{
    using namespace x86;

    // cpuid

    _test_control = 2;

    if (! x86::has_cpuid()) {
        _test_control = 0;
        return;
    }

    // msr

    _test_control = 3;

    auto cpuid_1 = x86::cpuid_1::load();

    if (! cpuid_1.has_msr()) {
        _test_control = 0;
        return;
    }

    _test_control = 4;

    if (! cpuid_1.has_local_apic()) {
        _test_control = 0;
        return;
    }

    _test_control = 5;

    auto value = x86::read_msr(msr::IA32_APIC_BASE);
    if ((value & 0xFFFFFFFFFFFF0000) != 0x00000000FEE00000) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}