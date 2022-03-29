#include <gtest/gtest.h>

#include <x86/segments.h>


// code_segment_descriptor

namespace x86
{
    TEST(code_segment_descriptor, zero)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, 0 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, base)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0xFFFFFFFF,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0xFFFF0000, 0xFF0000FF };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0xFFFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF };
        test(fields);

        auto semantic = code_segment_descriptor {
            0xFFFFFFFF, 0, false, false, false, 0, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, limit)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0xFFFFF,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0x0000FFFF, 0x000F0000 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0xF, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0xFFFFF, false, false, false, 0, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, accessed)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 8 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, true, false, false, 0, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, readable)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 9 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, true, false, 0, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, conforming)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_TRUE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 10 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, true, 0, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, privilege)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(3,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{3} << 13 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 3, false, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, present)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_TRUE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 15 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 0, true, 0, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, available)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(1,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 20 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 0, false, 1, false, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, long_mode)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_TRUE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 21 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, true, false, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, operand_size)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_TRUE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 22 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, false, true, false
        };
        test(semantic);
    }

    TEST(code_segment_descriptor, granularity)
    {
        auto test = [] (code_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.readable());
            ASSERT_FALSE(value.conforming());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_64bit());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_TRUE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 23 };
        auto& reference = reinterpret_cast<code_segment_descriptor&>(memory);
        test(reference);

        auto fields = code_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
        test(fields);

        auto semantic = code_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, false, false, true
        };
        test(semantic);
    }
}

// data_segment_descriptor

namespace x86
{
    TEST(data_segment_descriptor, zero)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, 0 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, base)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0xFFFFFFFF,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0xFFFF0000, 0xFF0000FF };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0xFFFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF };
        test(fields);

        auto semantic = data_segment_descriptor {
            0xFFFFFFFF, 0, false, false, false, 0, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, limit)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0xFFFFF,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0x0000FFFF, 0x000F0000 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0xFFFF, 0, 0, 0, 0, 0, 0, 0, 0xF, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0xFFFFF, false, false, false, 0, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, accessed)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 8 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, true, false, false, 0, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, writable)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 9 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, true, false, 0, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, expand_down)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 10 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, true, 0, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, privilege)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(3,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{3} << 13 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, false, 3, false, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, present)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_TRUE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 15 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, false, 0, true, 0, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, available)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(1,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 20 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, false, 0, false, 1, false, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, operand_size)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_TRUE(value.is_32bit());
            ASSERT_FALSE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 22 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, true, false
        };
        test(semantic);
    }

    TEST(data_segment_descriptor, granularity)
    {
        auto test = [] (data_segment_descriptor& value) {
            ASSERT_EQ(0,value.base());
            ASSERT_EQ(0,value.limit());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.expand_down());
            ASSERT_EQ(0,value.privilege());
            ASSERT_FALSE(value.present());
            ASSERT_EQ(0,value.available());
            ASSERT_FALSE(value.is_32bit());
            ASSERT_TRUE(value.is_4kb());
        };

        size4 memory [2] { 0, size4{1} << 23 };
        auto& reference = reinterpret_cast<data_segment_descriptor&>(memory);
        test(reference);

        auto fields = data_segment_descriptor { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
        test(fields);

        auto semantic = data_segment_descriptor {
            0, 0, false, false, false, 0, false, 0, false, true
        };
        test(semantic);
    }
}