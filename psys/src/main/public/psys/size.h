#pragma once

namespace ps
{
    using size1 = unsigned _ExtInt( 8);
    using size2 = unsigned _ExtInt(16);
    using size4 = unsigned _ExtInt(32);
    using size8 = unsigned _ExtInt(64);

    using size  = unsigned _ExtInt(sizeof(nullptr) * 8);
}