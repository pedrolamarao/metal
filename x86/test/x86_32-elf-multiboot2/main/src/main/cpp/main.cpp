// Copyright (C) 2020, 2021 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/information.h>

#include <x86/test.h>


//! Multiboot2 application procedure.

void main ( multiboot2::information_list & response )
{
    _test_control = 1;

    if ((& response) == nullptr) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}