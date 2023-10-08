// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/interrupts.h>

export module br.dev.pedrolamarao.metal.x86:interrupts;

export namespace x86
{
    using ::x86::short_interrupt_gate_descriptor;
    using ::x86::long_interrupt_gate_descriptor;
    using ::x86::set_interrupt_descriptor_table;
    using ::x86::set_interrupt_descriptor_table;
    using ::x86::enable_interrupts;
    using ::x86::disable_interrupts;
    using ::x86::interrupt;
}