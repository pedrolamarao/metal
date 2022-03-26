// Copyright (C) 2020,2021,2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>
#include <psys/start.h>
#include <psys/test.h>

#include <x86/ports.h>

#include <pc/cmos.h>


void psys::main ()
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