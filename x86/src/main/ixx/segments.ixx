// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/segments.h>

export module br.dev.pedrolamarao.metal.x86:segments;

export namespace x86
{
    using ::x86::code_segment_descriptor;
    using ::x86::data_segment_descriptor;
    using ::x86::far_call;
    using ::x86::set_code_segment;
    using ::x86::set_data_segments;
    using ::x86::set_global_descriptor_table;
}