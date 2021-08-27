extern "C"
{
    [[gnu::used]]
    void _test_start () {};

    [[gnu::used]]
    void _test_finish () {};

    [[gnu::used]]
    constinit
    decltype(sizeof(nullptr)) _test_control {};

    [[gnu::used]]
    constinit
    decltype(sizeof(nullptr)) _test_debug {};
}