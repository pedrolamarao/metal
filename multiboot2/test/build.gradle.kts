plugins {
    base
}

tasks.check { dependsOn(":multiboot2:test:x86_32-elf:check") }