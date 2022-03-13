#include <gtest/gtest.h>

#include <x86/_32/descriptor.h>
#include <x86/_64/descriptor.h>


namespace
{
    TEST(descriptor_32, zero)
    {
        x86::_32::descriptor descriptor {};
        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_32, max)
    {
        auto descriptor = x86::_32::descriptor::max();
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
    }

    TEST(descriptor_32, is_present)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b10000000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_32, privilege)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b01000000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(2,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_32, is_system)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b00010000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_32, type)
    {
        ps::size1 bytes [8] {
            0, 0, 0, 0,
            0, 0b00001000, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_32::descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(8,descriptor.type());
    }

    TEST(descriptor_64, zero)
    {
        x86::_64::descriptor descriptor {};
        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_64, max)
    {
        auto descriptor = x86::_64::descriptor::max();
        ASSERT_TRUE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(3,descriptor.privilege());
        ASSERT_EQ(15,descriptor.type());
    }

    TEST(descriptor_64, is_present)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b10000000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::descriptor&>(bytes);

        ASSERT_TRUE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_64, privilege)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b01000000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(2,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_64, is_system)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b00010000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_FALSE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(0,descriptor.type());
    }

    TEST(descriptor_64, type)
    {
        ps::size1 bytes [16] {
            0, 0, 0, 0,
            0, 0b00001000, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        };

        auto& descriptor = reinterpret_cast<x86::_64::descriptor&>(bytes);

        ASSERT_FALSE(descriptor.is_present());
        ASSERT_TRUE(descriptor.is_system());
        ASSERT_EQ(0,descriptor.privilege());
        ASSERT_EQ(8,descriptor.type());
    }
}