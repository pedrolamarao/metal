// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#include <multiboot2/information.h>
#include <multiboot2/start.h>

#include <psys/test.h>


//! Modular application test.

namespace multiboot2
{
    void main ( ps::size4 magic, multiboot2::information_list & response )
    {
        _test_start();
        unsigned step { 1 };

        // Test if loaded from the expected loader.

        _test_control = step++;
        if (magic != information_magic) {
            _test_control = 0;
            return;
        }

        // Find module: expect exactly one.

        _test_control = step++;

        unsigned count { 0 };
        modules_information * module {};

        for (auto i = begin(response), j = end(response); i != j; i = next(i))
        {
            using type = multiboot2::information_type;
            switch (i->type)
            {
            case type::modules:
                ++count;
                module = reinterpret_cast<modules_information*>(i);
                break;
            default:
                break;
            }
        }

        if (count != 1) {
            _test_control = 0;
            return;
        }

        // Call module entry point: expect them to be regular procedures.

        _test_control = step++;
        // #TODO: locate module entry point.
        // #TODO: call module entry point.
        _test_control = 0;

        _test_control = -1;
        _test_finish();
    }
}