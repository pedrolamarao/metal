#pragma once

namespace ps
{
    using size1 = unsigned _BitInt( 8);
    using size2 = unsigned _BitInt(16);
    using size4 = unsigned _BitInt(32);
    using size8 = unsigned _BitInt(64);

    using size  = unsigned _BitInt(sizeof(nullptr) * 8);
}