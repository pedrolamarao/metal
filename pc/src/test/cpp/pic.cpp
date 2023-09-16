#include <pc/pic.h>

#include <gtest/gtest.h>

namespace
{
    template <unsigned Size>
    class port
    {
    public:

        typedef _BitInt(16) address_type;

        typedef _BitInt(Size * 8) data_type;

        port (address_type address) { }

        data_type read () { return data_type{}; }

        void write (data_type value) { }

    };

    TEST(pic, smoke)
    {
        pc::pic<port> pic { 0, 0 };
    }
}
