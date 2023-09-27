#include <x86/apic.h>


static_assert(__is_standard_layout(x86::apic_location), "x86::apic_location is not standard layout");

static_assert(__is_standard_layout(x86::apic_r_location), "x86::apic_r_location is not standard layout");

static_assert(__is_standard_layout(x86::apic_w_location), "x86::apic_w_location is not standard layout");

static_assert(__is_standard_layout(x86::apic_rw_location), "x86::apic_rw_location is not standard layout");

static_assert(__is_standard_layout(x86::apic_memory_map), "x86::apic_memory_map is not standard layout");
