Date: 2020-02-15

# summary

`gradle-grub` teaches Gradle how to compile GRUB images.

Use it together with `cpp-application`.

# use

Create new tasks with type `GrubStandaloneCompile` or `GrubRescueCompile`.

Let `binary` be a `CppExecutable`:

```gradle
tasks.register("grubRescue_${binary.name}", aasgard.gradle.grub.GrubRescueCompile) {
    binaryName binary.name
    sources 'src/main/grub', binary.linkerTask()
}
```

## `aasgard.gradle.grub.GrubRescueCompile`

Properties:

- `binaryName` — unique name of binary configuration
- `install` — modules to install
- `load` — modules to pre-load
- `sources` — configurable file collection of sources

## references

_TODO_
