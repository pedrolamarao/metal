Date: 2021-08-13

# test

One of this project's aims is to define a technique, complementary to unit testing, for the 
automated execution of "bare metal" test programs.

## psys test protocol

Psys test programs shall define these symbols:

* `__test_control`
* `__test_debug`
* `__test_finish`
* `__test_start`

When test execution reaches location `__test_start`, testing started.

When test execution reaches location `__test_finish`, testing finished.

During testing, whenever the value stored in location `__test_debug` is observed to change,
this fact must be reported together with the old and new values.

During testing, whenever the value stored in location `__test_control` is observed to change,
the facts must be reported:

* `old == 0` -> testing stage `new` entered
* `new == 0` -> testing stage `old` failed
* `default`  -> testing stages `old` suceeded, `new` entered 

## psys test driver

Psys tests are currently executed by a driver combining QEMU and GDB.

Test programs are executed in an appropriate QEMU system emulator with debugging support.

Test program execution is observed by driving GDB connected to QEMU.
Through GDB/MI, the driver sets breakpoints and watchpoints to observe test progress.

A time limit guards against programs terminating abnormally.