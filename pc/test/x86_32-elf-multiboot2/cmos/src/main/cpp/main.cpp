// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>

#include <x86/port.h>

#include <pc/cmos.h>


//! Multiboot2 minimal request for ELF program

namespace
{
    struct request_type
    {
        multiboot2::header_prologue prologue;
        multiboot2::end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constinit
    request_type request =
    {
        { multiboot2::architecture_type::x86, sizeof(request), },
        { },
    };
}

//! Psys test protocol

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
	[[gnu::used]] unsigned volatile _test_debug {};
    extern "C" [[gnu::used]] void _test_start () {};
    extern "C" [[gnu::used]] void _test_finish () {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list & mbi )
{
    pc::cmos<x86::port> cmos { 0x70, 0x71 };
    
    // Note: CMOS RTC values must be fixed by the system emulator

    _test_control = 10;
    
    auto status_B = cmos.read(0x0B, false);
    
    // CMOS RTC time format

    _test_control = 20;
    
    auto format_24 = (status_B & 0x02) == 0x02;
    
    if (! format_24) {
    	_test_control = 0;
    	return;
    }
    
    // CMOS RTC date format

    _test_control = 30;
    
    auto format_Binary = (status_B & 0x04) == 0x04;

    if (format_Binary) {
    	_test_control = 0;
    	return;
    }

    // CMOS RTC year

    _test_control = 40;

    if (cmos.read(0x09, false) != 0x20) {
    	_test_control = 0;
    	return;
    }

    // CMOS RTC month

    _test_control = 50;

    if (cmos.read(0x08, false) != 0x07) {
    	_test_control = 0;
    	return;
    }

    // CMOS RTC day of month

    _test_control = 60;

    if (cmos.read(0x07, false) != 0x24) {
    	_test_control = 0;
    	return;
    }

    // CMOS RTC hour

    _test_control = 70;

    if (cmos.read(0x04, false) != 0x22) {
    	_test_control = 0;
    	return;
    }

    // CMOS RTC minute

    _test_control = 80;

    if (cmos.read(0x02, false) != 0x46) {
    	_test_control = 0;
    	return;
    }

    _test_control = -1;
    return;
}

namespace multiboot2
{
    //! Multiboot2 entry point

    extern "C"
    constinit
    unsigned char __multiboot2_stack [ 0x4000 ] {};

    extern "C"
    [[gnu::naked]]
    void __multiboot2_start ()
    {
        __asm__
        {
            mov esp, offset __multiboot2_stack + 0x4000
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