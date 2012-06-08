#include "idt.h"


static_assert(__is_standard_layout(x86::interrupt_gate_descriptor), "x86::interrupt_gate_descriptor is not standard layout");

static_assert(__is_trivial(x86::interrupt_gate_descriptor), "x86::interrupt_gate_descriptor is not trivial");
