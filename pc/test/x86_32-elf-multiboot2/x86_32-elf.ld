SECTIONS
{
    . = 0x1000;
    .multiboot2.start   : { *(.multiboot2.start) }
    .multiboot2.request : { *(.multiboot2.request) }
    .multiboot2.stack   : { *(.multiboot2.stack) }
}