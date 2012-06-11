#include "system_description.h"


static_assert(__is_standard_layout(acpi::root_system_description_pointer), "acpi::root_system_description_pointer is not standard layout");

static_assert(__is_standard_layout(acpi::system_description), "acpi::system_description is not standard layout");

static_assert(__is_standard_layout(acpi::narrow_root_system_description), "acpi::narrow_root_system_description is not standard layout");

static_assert(__is_standard_layout(acpi::wide_root_system_description), "acpi::wide_root_system_description is not standard layout");

static_assert(__is_standard_layout(acpi::fixed_system_description), "acpi::fixed_system_description is not standard layout");

static_assert(__is_standard_layout(acpi::apic_system_description), "acpi::apic_system_description is not standard layout");

static_assert(__is_standard_layout(acpi::apic_description), "acpi::apic_description is not standard layout");

static_assert(__is_standard_layout(acpi::local_apic_description), "acpi::local_apic_description is not standard layout");

static_assert(__is_standard_layout(acpi::io_apic_description), "acpi::io_apic_description is not standard layout");
