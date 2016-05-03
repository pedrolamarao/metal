// Copyright (C) 2015 Pedro Lamarão <pedro.lamarao@gmail.com>. All rights reserved.

#pragma once

#include <x86/cpuid.h>


namespace x86
{
	struct apic_location
	{
		uint32_t value;
		uint32_t unused0;
		uint32_t unused1;
		uint32_t unused2;
	};

	struct apic_r_location : public apic_location
	{
		constexpr explicit operator uint32_t () const { return value; }
	};

	struct apic_w_location : public apic_location
	{
		auto operator= (uint32_t x) -> apic_w_location & { value = x; return *this; }
	};

	struct apic_rw_location : public apic_location
	{
		constexpr explicit operator uint32_t () const { return value; }

		auto operator= (uint32_t x) -> apic_rw_location & { value = x; return *this; }
	};

	struct apic_memory_map
	{
		apic_location reserved_00;
		apic_location reserved_01;
		apic_r_location id;
		apic_r_location version;
		apic_location reserved_02;
		apic_location reserved_03;
		apic_location reserved_04;
		apic_location reserved_05;
		apic_location task_priority;
		apic_location arbitration_priority;
		apic_location processor_priority;
		apic_location eoi;
		apic_location remote_read;
		apic_location logical_destination;
		apic_location destination_format;
		apic_location spurious_interrupt_vector;
	};

	constexpr inline
	auto has_apic (cpuid const &) -> bool
	{
		return false;
	}

	constexpr inline
	auto is_apic_enabled (uint64_t location) -> bool
	{
		return false;
	}

	constexpr inline
	auto get_apic_memory_map (uint64_t location) -> apic_memory_map *
	{
		return nullptr;
	}
}
