#pragma once

#include <psys/size.h>

namespace ps
{
    using integer1 = signed _ExtInt( 8);
    using integer2 = signed _ExtInt(16);
    using integer4 = signed _ExtInt(32);
    using integer8 = signed _ExtInt(64);

    using integer  = signed _ExtInt(sizeof(nullptr) * 8);
}