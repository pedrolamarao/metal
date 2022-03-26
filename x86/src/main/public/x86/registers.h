// Copyright (C) 2022 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/common.h>


// Interface.

namespace x86
{
    //! Control registers.
    //! @{

    auto cr0 () -> size;

    void cr0 (size);

    auto cr2 () -> size;

    void cr2 (size);

    auto cr3 () -> size;

    void cr3 (size);

    auto cr4 () -> size;

    void cr4 (size);

    //! @}

    //! Segment descriptor registers.
    //! @{

    struct [[gnu::packed]] segment_descriptor_table
    {
        size2    size;
        ps::size offset;
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