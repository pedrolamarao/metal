// Copyright (C) 2020 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.


#include <multiboot2/header.h>
#include <multiboot2/information.h>


//! Multiboot 2 request

namespace multiboot2
{
    struct request_type
    {
        header_prologue        prologue;
        entry_address_request  address;
        end_request            end;
    };

    // Assumption: the .text section begins with _start at address 0x1000

    [[gnu::used, gnu::section(".multiboot2")]]
    constinit
    request_type request =
    {
        { architecture_type::x86, sizeof(request), },
        { tag_type::entry, 0, sizeof(entry_address_request), 0x1000 },
        { },
    };
}

//! Psys test protocol

extern "C"
{
    [[gnu::used]] unsigned volatile _test_control {};
	[[gnu::used]] unsigned volatile _test_debug {};
}
