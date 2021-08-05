// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <psys/integer.h>

#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Multiboot 2 request

namespace
{
    using namespace multiboot2;

    struct request_type
    {
        header_prologue prologue;
        end_request     end;
    };

    [[gnu::used, gnu::section(".multiboot2")]]
    constexpr request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { },
    };
}

//! Test result

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
}

//! Multiboot2 entry point

extern "C"
void main ( ps::size4 magic, multiboot2::information_list * response )
{
    _test_control = 1;

    if (magic == 0) {
        _test_control = 0;
        return;
    }

    _test_control = 2;

    if (response == 0) {
        _test_control = 0;
        return;
    }

    _test_control = 3;

    if (magic != multiboot2::information_magic) {
        _test_control = 0;
        return;
    }

    _test_control = -1;
    return;
}
