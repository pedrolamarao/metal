// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <pc/cmos.h>

export module br.dev.pedrolamarao.metal.pc:cmos;

export namespace pc
{
    using ::pc::rtc_status_a;
    using ::pc::rtc_status_b;
    using ::pc::cmos;
}