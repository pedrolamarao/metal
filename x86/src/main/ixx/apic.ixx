// Copyright (C) 2023 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

module;

#include <x86/apic.h>

export module br.dev.pedrolamarao.metal.x86:apic;

export namespace x86
{
	using ::x86::apic_location;
	using ::x86::apic_r_location;
	using ::x86::apic_w_location;
	using ::x86::apic_rw_location;
	using ::x86::apic_memory_map;
	using ::x86::has_apic;
	using ::x86::is_apic_enabled;
	using ::x86::get_apic_memory_map;
}