// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/information.h>

#include <x86/cpuid.h>
#include <x86/gdt.h>
#include <x86/idt.h>
#include <x86/msr.h>


//! Test result

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
    [[gnu::used]] unsigned volatile _test_debug {};

    void _test_start () { }
    void _test_finish () { }
}

//! Multiboot2 entry point

void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    using namespace x86;

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

    auto value = x86::read_msr(msr::IA32_APIC_BASE);
    if ((value & 0xFFFFFFFFFFFF0000) != 0x00000000FEE00000) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}

namespace multiboot2
{
    //! Multiboot2 entry point

    extern
    unsigned char stack [ 0x4000 ];

    extern "C"
    [[gnu::naked]]
    void __multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset stack + 0x4000
            xor ecx, ecx
            push ecx
            popf
            call _test_start
            push ebx
            push eax
            call main
            call _test_finish
            __multiboot2_halt:
            hlt
            jmp __multiboot2_halt
        }
    }
}