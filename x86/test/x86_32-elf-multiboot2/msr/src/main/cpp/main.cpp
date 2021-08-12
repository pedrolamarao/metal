// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>


//! Multiboot2 minimal request for ELF program

namespace
{
    struct request_type
    {
        multiboot2::header_prologue prologue;
        multiboot2::end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constexpr request_type request =
    {
        { multiboot2::architecture_type::x86, sizeof(request), },
        { },
    };
}

//! Test result

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
    [[gnu::used]] unsigned volatile _test_debug {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    // multiboot2

    _test_control = 1;

    if (magic != multiboot2::information_magic) {
        _test_control = 0;
        return;
    }

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

    auto value = x86::read_msr(0x1B);
    if ((value & 0xFFFFFFFFFFFF0000) != 0x00000000FEE00000) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
