// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>
#include <psys/start.h>
#include <psys/test.h>

#include <x86/segments.h>
#include <x86/identification.h>
#include <x86/interrupts.h>
#include <x86/msr.h>


void psys::main ()
{
    using namespace x86;

    size step { 1 };

    // cpuid?

    _test_control = step++;

    if (! has_cpuid()) {
        _test_control = 0;
        return;
    }

    // msr?

    _test_control = step++;

    if (! has_msr()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;

    if (! has_local_apic()) {
        _test_control = 0;
        return;
    }

    _test_control = step++;

    auto value = rdmsr( static_cast<size4>(msr::APIC_BASE) );
    if ((value & 0xFFFFFFFFFFFF0000) != 0x00000000FEE00000) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}