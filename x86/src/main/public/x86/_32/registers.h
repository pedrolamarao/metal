// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86::_32
{
    //! Control registers.
    //! @{

    auto cr0 () -> size4;

    void cr0 (size4);

    auto cr2 () -> size4;

    void cr2 (size4);

    auto cr3 () -> size4;

    void cr3 (size4);

    auto cr4 () -> size4;

    void cr4 (size4);

    //! @}

    //! Segment descriptor registers.
    //! @{

    struct [[gnu::packed]] segment_descriptor_table
    {
        size2 size;
        size4 offset;
    };

    auto gdtr () -> segment_descriptor_table;

    void gdtr (segment_descriptor_table);

    auto idtr () -> segment_descriptor_table;

    void idtr (segment_descriptor_table);

    auto ldtr () -> segment_descriptor_table;

    void ldtr (segment_descriptor_table);

    //! @}

    //! Segment selector registers.
    //! @{

    auto cs () -> segment_selector;

    void cs (segment_selector);

    auto ds () -> segment_selector;

    void ds (segment_selector);

    auto es () -> segment_selector;

    void es (segment_selector);

    auto fs () -> segment_selector;

    void fs (segment_selector);

    auto gs () -> segment_selector;

    void gs (segment_selector);

    auto ss () -> segment_selector;

    void ss (segment_selector);

    //! @}
}