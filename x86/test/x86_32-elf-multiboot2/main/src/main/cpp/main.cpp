// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/information.h>


//! Test result

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
    [[gnu::used]] unsigned volatile _test_debug {};
}

//! Multiboot2 entry point

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