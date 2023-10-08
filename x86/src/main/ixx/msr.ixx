// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

export module br.dev.pedrolamarao.metal.x86:msr;

import br.dev.pedrolamarao.metal.psys;

import :instructions;

export namespace x86
{
    //! Model-specific registers (MSR).

    enum class msr : ps::size4
    {
        APIC_BASE   = 0x0000001B,
        MISC_ENABLE = 0x000001A0,
        EFER        = 0xC0000080,
    };

    //! Get model-specific register (MSR).

    auto get_msr (msr id) -> ps::size8
    {
        return rdmsr( static_cast<ps::size4>(id) );
    }

    //! Set model-specific register (MSR).

    void set_msr (msr id, ps::size8 value)
    {
        wrmsr( static_cast<ps::size4>(id), value );
    }
}