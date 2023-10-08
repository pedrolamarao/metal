// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/common.h>

export module br.dev.pedrolamarao.metal.x86:common;

export namespace x86
{
  using ::x86::descriptor_type;
  using ::x86::privilege_level;
  using ::x86::segment_selector;
  using ::x86::halt_cast;
}