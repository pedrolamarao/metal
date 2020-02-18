Date: 2020-02-15

# summary

`gradle-qemu` teaches Gradle how to run QEMU processes.

Use it together with `cpp-application`.

# use

Create new tasks with type `QemuExec`.

Let `binary` be a `GrubRescueCompile`:

```gradle
tasks.register("qemuRescue_${binary.name}", aasgard.gradle.qemu.QemuExec) {
    system 'i386'
    cdrom binary.get().target
}
```

## references

_TODO_
