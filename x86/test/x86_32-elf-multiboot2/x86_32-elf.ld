PHDRS
{
    multiboot2  PT_LOAD       FLAGS(5) ;
    text        PT_LOAD       FLAGS(5) ;
    data        PT_LOAD       FLAGS(6) ;
    stack       PT_GNU_STACK           ;
}

SECTIONS
{
    . = 0x1000;
    .multiboot2.start   : { *(.multiboot2.start) }   :multiboot2
    .multiboot2.request : { *(.multiboot2.request) } :multiboot2
    .multiboot2.stack   : { *(.multiboot2.stack) }   :multiboot2

    .text               : { *(.text*) }              :text

    .data               : { *(.data*)                :data
    .bss                : { *(.bss*) }               :data
}

ENTRY(multiboot2_start)