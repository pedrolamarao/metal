#pragma once

extern "C"
{
    //! Psys test start.
    //!
    //! When control reaches this address,
    //! test driver understands test has started.

    extern
    void _test_start ();

    //! Psys test finish.
    //!
    //! When control reaches this address,
    //! test driver understands test has finished.

    extern
    void _test_finish ();

    //! Psys test control.
    //!
    //! When the value at this location changes,
    //! test driver understands test has progressed.

    extern
    decltype(sizeof(nullptr)) volatile _test_control;

    //! Psys test debug.
    //!
    //! When the value at this location changes,
    //! test driver logs the old and new values.

    extern
    decltype(sizeof(nullptr)) volatile _test_debug;
}