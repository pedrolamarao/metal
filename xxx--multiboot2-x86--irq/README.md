Date: 2020-02-01

# summary

This program demonstrates enabling interrupts on i686-pc-elf soon after loading.

# build

We link the `.text` section at 0x1000 to ease the burden on emulators &mdash; a small amount of RAM will be enough.

# architecture

This program must satisfy the requirements for handling soft interrupts on the x86 processor.

1. The global descriptor table must be loaded.
2. The interrupt descriptor table must be loaded.
3. Interrupts must be enabled on the processor.

These requirements are satisfied using Aasgard's x86 library.

For (1), the GDT is defined in namespace scope with static storage duration and constant initialized by constexpr constructors and procedures. Our GDT defines a basic flat memory model for protected mode. We load it with `x86::load_global_descriptor_table`. We reload all segment registers with `x86::reload_segment_registers`. We check the GDTR has expected values with `x86::store_global_descriptor_table`.

We check everything is in order by calling a regular procedure.

For (2), the IDT is defined in namespace scope with static storage duration but zero initialized. the x86 interrupt "calling convention" is not supported by GCC. Therefore, the interrupt service routine is defined in assembly and declared `extern` in C++. Because taking the address of an extern procedure is not a constant expression, we cannot constant initialize the IDT. Therefore, we initialize the IDT at run time. We load it with `x86::load_interrupt_descriptor_table`. We check the GDTR has expected values with `x86::store_interrupt_descriptor_table`.

For (3) we just call `x86::enable_interrupts`.

We verify everything is in order by issuing a soft interrupt and doing I/O on a safe port.