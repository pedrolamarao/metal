#pragma once

#include <psys/size.h>

namespace ps
{
    using integer1 = signed _BitInt( 8);
    using integer2 = signed _BitInt(16);
    using integer4 = signed _BitInt(32);
    using integer8 = signed _BitInt(64);

    using integer  = signed _BitInt(sizeof(nullptr) * 8);
}