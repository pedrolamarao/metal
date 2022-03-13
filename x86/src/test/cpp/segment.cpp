#include <gtest/gtest.h>

#include <x86/_32/segment.h>
#include <x86/_64/segment.h>


namespace
{
    TEST(segment_32, zero)
    {
        x86::_32::segment_descriptor descriptor {};
        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, flat)
    {
        x86::_32::segment_descriptor descriptor { 0, 0xFFFFF, 15, 3, true, true, true, true, };
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_32, max)
    {
        auto descriptor = x86::_32::segment_descriptor::max();
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFFFFFFFF,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_32, is_present)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b10000000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, privilege)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b01000000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(2,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, is_system)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b00010000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, type)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b00001000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(8,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, is_4kb)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0, 0b10000000, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_32, is_32bit)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0, 0b01000000, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_32, is_available)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0, 0b00010000, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, zero)
    {
        x86::_64::segment_descriptor descriptor {};
        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, flat)
    {
        x86::_64::segment_descriptor descriptor { 0, 0xFFFFF, 15, 3, true, true, true, true, };
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, max)
    {
        auto descriptor = x86::_64::segment_descriptor::max();
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
        ASSERT_EQ(0xFFFFFFFFFFFFFFFF,descriptor.base());
        ASSERT_EQ(0xFFFFF,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, is_present)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b10000000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, privilege)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b01000000, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(2,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, is_system)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b00010000, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, type)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b00001000, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(8,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, is_4kb)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0, 0b10000000, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_TRUE(descriptor.is_4kb());
    }

    TEST(segment_64, is_32bit)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0, 0b01000000, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_FALSE(descriptor.is_available());
        ASSERT_TRUE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }

    TEST(segment_64, is_available)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0, 0b00010000, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::segment_descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
        ASSERT_EQ(0,descriptor.base());
        ASSERT_EQ(0,descriptor.limit());
        ASSERT_TRUE(descriptor.is_available());
        ASSERT_FALSE(descriptor.is_32bit());
        ASSERT_FALSE(descriptor.is_4kb());
    }
}