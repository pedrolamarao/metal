#include <gtest/gtest.h>

import br.dev.pedrolamarao.metal.elf;

namespace elf
{
    TEST(prologue, smoke)
    {
        auto value = prologue{};
    }
}

namespace elf
{
    TEST(header_32, smoke)
    {
        auto value = header_32{};
    }
}

namespace elf
{
    TEST(header_64, smoke)
    {
        auto value = header_64{};
    }
}

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
