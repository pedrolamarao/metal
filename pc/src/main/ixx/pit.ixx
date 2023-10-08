// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <pc/pit.h>

export module br.dev.pedrolamarao.metal.pc:pit;

export namespace pc
{
    using ::pc::pit_counter;
    using ::pc::pit_access;
    using ::pc::pit_mode;
    using ::pc::pit_format;
    using ::pc::pit_configure_command;
    using ::pc::pit_latch_command;
    using ::pc::pit_read_back_command;
    using ::pc::pit;
}