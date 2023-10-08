#include <gtest/gtest.h>

import br.dev.pedrolamarao.metal.psys;
import br.dev.pedrolamarao.metal.x86;

// short_page_table_entry

namespace x86
{
    using size4 = ps::size4;
    using size8 = ps::size8;

    TEST(short_page_table_entry, zero)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 0;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, present)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, true, false, false, false, false, false, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, writable)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 1;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, true, false, false, false, false, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, user)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 2;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, true, false, false, false, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, write_through)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 3;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, true, false, false, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, cache)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 4;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, true, false, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, accessed)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 5;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, true, false, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, dirty)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 6;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, false, true, 0, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, attribute)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(4,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 7;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, false, false, 7, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, global)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_TRUE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 8;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, true, 0, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, available)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 3 << 9;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, false, 3, 0
        };
        test(semantic);
    }

    TEST(short_page_table_entry, address)
    {
        auto test = [] (short_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFFFFF000,value.address());
        };

        size4 memory = 0xFFFFF000;
        auto& reference = reinterpret_cast<short_page_table_entry&>(memory);
        test(reference);

        auto fields = short_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFFF };
        test(fields);

        auto semantic = short_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, false, 0, 0xFFFFF000
        };
        test(semantic);
    }
}

// short_small_page_directory_entry

namespace x86
{
    TEST(short_small_page_directory_entry, zero)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 0;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, false, false, false, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, present)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0 };
        test(reference);

        auto semantic = short_small_page_directory_entry {
            {}, true, false, false, false, false, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, writable)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 1;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, true, false, false, false, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, user)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 2;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, true, false, false, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, write_through)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 3;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, false, true, false, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, cache)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 4;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, false, false, true, false, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, accessed)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 5;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, false, false, false, true, 0, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, available)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 3 << 9;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 3, 0 };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, false, false, false, false, 3, 0
        };
        test(semantic);
    }

    TEST(short_small_page_directory_entry, address)
    {
        auto test = [] (short_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFFFFF000,value.address());
        };

        size4 memory = 0xFFFFF000;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0xFFFFF };
        test(fields);

        auto semantic = short_small_page_directory_entry {
            {}, false, false, false, false, false, false, 0, 0xFFFFF000
        };
        test(semantic);
    }
}

// short_large_page_directory_entry

namespace x86
{
    TEST(short_large_page_directory_entry, zero)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 0;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, false, false, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, present)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            true, false, false, false, false, false, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, writable)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 1;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, true, false, false, false, false, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, user)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 2;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, true, false, false, false, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, write_through)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 3;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, true, false, false, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, cache)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 4;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, true, false, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, accessed)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 5;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, true, false, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, dirty)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 6;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, false, true, false, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, global)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_TRUE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 8;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, false, false, true, 0, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, available)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 3 << 9;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, false, false, false, 3, 0, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, attribute)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(4,value.attribute());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 1 << 12;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, false, false, false, 0, 7, 0
        };
        test(semantic);
    }

    TEST(short_large_page_directory_entry, address)
    {
        auto test = [] (short_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0x00FFFFC00000,value.address());
        };

        size4 memory = 0xFFDFE000;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0x3FF };
        test(fields);

        auto semantic = short_large_page_directory_entry {
            false, false, false, false, false, false, false, false, 0, 0, 0x00FFFFC00000
        };
        test(semantic);

        auto four_mb = short_large_page_directory_entry {
            false, false, false, false, false, false, false, false, 0, 0, 0x400000
        };
        ASSERT_EQ(0x400000,four_mb.address());
    }

    TEST(short_large_page_directory_entry, bits)
    {
        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        auto& memory = reinterpret_cast<size4&>(fields);
        ASSERT_EQ(1,(memory>> 7)&1);
        ASSERT_EQ(0,(memory>>21)&1);
    }
}

// short_paging

namespace x86
{
    TEST(short_paging, zero)
    {
        auto test = [] (short_paging& value) {
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 0;
        auto& reference = reinterpret_cast<short_paging&>(memory);
        test(reference);

        auto fields = short_paging { 0, 0, 0 };
        test(fields);

        auto semantic = short_paging { {}, false, false, 0 };
        test(semantic);
    }

    TEST(short_paging, write_through)
    {
        auto test = [] (short_paging& value) {
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = size4{1} << 3;
        auto& reference = reinterpret_cast<short_paging&>(memory);
        test(reference);

        auto fields = short_paging { 1, 0, 0 };
        test(fields);

        auto semantic = short_paging { {}, true, false, 0 };
        test(semantic);
    }

    TEST(short_paging, cache)
    {
        auto test = [] (short_paging& value) {
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = size4{1} << 4;
        auto& reference = reinterpret_cast<short_paging&>(memory);
        test(reference);

        auto fields = short_paging { 0, 1, 0 };
        test(fields);

        auto semantic = short_paging { {}, false, true, 0 };
        test(semantic);
    }

    TEST(short_paging, address)
    {
        auto test = [] (short_paging& value) {
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0xFECDB000,value.address());
        };

        size4 memory = 0xFECDB000;
        auto& reference = reinterpret_cast<short_paging&>(memory);
        test(reference);

        auto fields = short_paging { 0, 0, 0xFECDB };
        test(fields);

        auto semantic = short_paging { {}, false, false, 0xFECDB000 };
        test(semantic);
    }
}

// extended_page_table_entry

namespace x86
{
    TEST(extended_page_table_entry, zero)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, present)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, true, false, false, false, false, false, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, writable)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, true, false, false, false, false, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, user)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, true, false, false, false, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, write_through)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, true, false, false, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, cache)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, true, false, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, accessed)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, true, false, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, dirty)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 6;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, false, true, 0, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, attribute)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(4,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 7;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, false, false, 7, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, global)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_TRUE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 8;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, true, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, available)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, false, 3, 0, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, address)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFEDCBA9876000,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFEDCBA9876000;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFEDCBA9876, 0 };
        test(fields);

        auto semantic = extended_page_table_entry {
            {}, false, false, false, false, false, false, false, 0, false, 0, 0xFEDCBA9876000, false
        };
        test(semantic);
    }

    TEST(extended_page_table_entry, nonexecutable)
    {
        auto test = [] (extended_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<extended_page_table_entry&>(memory);
        test(reference);

        auto fields = extended_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = extended_page_table_entry { {}, false, false, false, false, false, false, false, 0, false, 0, 0, true };
        test(semantic);
    }
}

// extended_small_page_directory_entry

namespace x86
{
    TEST(extended_small_page_directory_entry, zero)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, present)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, true, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, writable)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, true, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, user)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, true, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, write_through)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, true, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, cache)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, false, true, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, accessed)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, false, false, true, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, available)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 3, 0, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, false, false, false, 3, 0, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, address)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFEDCBA9876000,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFEDCBA9876000;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0xFEDCBA9876, 0 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, false, false, false, 0, 0xFEDCBA9876000, false
        };
        test(semantic);
    }

    TEST(extended_small_page_directory_entry, nonexecutable)
    {
        auto test = [] (extended_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<extended_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = extended_small_page_directory_entry {
            {}, false, false, false, false, false, false, 0, 0, true
        };
        test(semantic);
    }
}

// extended_large_page_directory_entry

namespace x86
{
    TEST(extended_large_page_directory_entry, zero)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, present)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, true, false, false, false, false, false, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, writable)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, true, false, false, false, false, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, user)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, true, false, false, false, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, write_through)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, true, false, false, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, cache)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, true, false, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, accessed)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, true, false, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, dirty)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 6;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, true, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, global)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_TRUE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 8;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, false, true, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, available)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, false, false, 3, 0, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, attribute)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(4,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 12;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, false, false, 0, 7, 0, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, address)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0xFFFFFFFE00000,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFFFFFFFE00000;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7FFFFFFF, 0 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, false, false, 0, 0, 0xFFFFFFFE00000, false
        };
        test(semantic);
    }

    TEST(extended_large_page_directory_entry, nonexecutable)
    {
        auto test = [] (extended_large_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.attribute());
            ASSERT_EQ(0,value.address());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<extended_large_page_directory_entry&>(memory);
        test(reference);

        auto fields = extended_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = extended_large_page_directory_entry {
            {}, false, false, false, false, false, false, false, false, 0, 0, 0, true
        };
        test(semantic);
    }
}

// extended_page_directory_pointer_entry

namespace x86
{
    TEST(extended_page_directory_pointer_entry, zero)
    {
        auto test = [] (extended_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<extended_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = extended_page_directory_pointer_entry { 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_directory_pointer_entry { {}, false, false, false, 0, 0 };
        test(semantic);
    }

    TEST(extended_page_directory_pointer_entry, present)
    {
        auto test = [] (extended_page_directory_pointer_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<extended_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = extended_page_directory_pointer_entry { 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_directory_pointer_entry { {}, true, false, false, 0, 0 };
        test(semantic);
    }

    TEST(extended_page_directory_pointer_entry, write_through)
    {
        auto test = [] (extended_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<extended_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = extended_page_directory_pointer_entry { 0, 1, 0, 0, 0 };
        test(fields);

        auto semantic = extended_page_directory_pointer_entry { {}, false, true, false, 0, 0 };
        test(semantic);
    }

    TEST(extended_page_directory_pointer_entry, cache)
    {
        auto test = [] (extended_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<extended_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = extended_page_directory_pointer_entry { 0, 0, 1, 0, 0 };
        test(fields);

        auto semantic = extended_page_directory_pointer_entry { {}, false, false, true, 0, 0 };
        test(semantic);
    }

    TEST(extended_page_directory_pointer_entry, available)
    {
        auto test = [] (extended_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(3,value.available());
            ASSERT_EQ(0,value.address());
        };

        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<extended_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = extended_page_directory_pointer_entry { 0, 0, 0, 3, 0 };
        test(fields);

        auto semantic = extended_page_directory_pointer_entry { {}, false, false, false, 3, 0 };
        test(semantic);
    }

    TEST(extended_page_directory_pointer_entry, address)
    {
        auto test = [] (extended_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFEDCBA9876000,value.address());
        };

        size8 memory = 0xFEDCBA9876000;
        auto& reference = reinterpret_cast<extended_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = extended_page_directory_pointer_entry { 0, 0, 0, 0, 0xFEDCBA9876 };
        test(fields);

        auto semantic = extended_page_directory_pointer_entry { {}, false, false, false, 0, 0xFEDCBA9876000 };
        test(semantic);
    }
}

// extended_paging

namespace x86
{
    TEST(extended_paging, zero)
    {
        auto test = [] (extended_paging& value) {
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = 0;
        auto& reference = reinterpret_cast<extended_paging&>(memory);
        test(reference);

        auto fields = extended_paging { 0, 0, 0 };
        test(fields);

        auto semantic = extended_paging { {}, false, false, 0 };
        test(semantic);
    }

    TEST(extended_paging, write_through)
    {
        auto test = [] (extended_paging& value) {
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = size4{1} << 3;
        auto& reference = reinterpret_cast<extended_paging&>(memory);
        test(reference);

        auto fields = extended_paging { 1, 0, 0 };
        test(fields);

        auto semantic = extended_paging { {}, true, false, 0 };
        test(semantic);
    }

    TEST(extended_paging, cache)
    {
        auto test = [] (extended_paging& value) {
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_EQ(0,value.address());
        };

        size4 memory = size4{1} << 4;
        auto& reference = reinterpret_cast<extended_paging&>(memory);
        test(reference);

        auto fields = extended_paging { 0, 1, 0 };
        test(fields);

        auto semantic = extended_paging { {}, false, true, 0 };
        test(semantic);
    }

    TEST(extended_paging, address)
    {
        auto test = [] (extended_paging& value) {
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_EQ(0xFEDCBA80,value.address());
        };

        size4 memory = 0xFEDCBA80;
        auto& reference = reinterpret_cast<extended_paging&>(memory);
        test(reference);

        auto fields = extended_paging { 0, 0, 0x7F6E5D4 };
        test(fields);

        auto semantic = extended_paging { {}, false, false, 0xFEDCBA80 };
        test(semantic);
    }
}

// long_page_table_entry
    
namespace x86
{
    TEST(long_page_table_entry_64, zero)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, present)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            true, false, false, false, false, false, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, writable)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, true, false, false, false, false, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, user)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, true, false, false, false, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, write_through)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, true, false, false, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, cache)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, true, false, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, accessed)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, true, false, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, dirty)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_TRUE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 6;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, true, 0, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, attribute)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(4,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 7;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 7, false, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, global)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_TRUE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 8;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 0, true, 0, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, available)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0x3FF,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0x7F0000000000E00;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7, 0, 0x7F, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 0, false, 0x3FF, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, address)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFFFFFFFFFF000,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFFFFFFFFFF000;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFFFFFFFF, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 0, false, 0, 0xFFFFFFFFFF000, 0, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, mpk)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0xF,value.mpk());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = size8{0xF} << 59;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xF, 0 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 0, false, 0, 0, 0xF, false
        };
        test(semantic);
    }

    TEST(long_page_table_entry_64, nonexecutable)
    {
        auto test = [] (long_page_table_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_FALSE(value.dirty());
            ASSERT_EQ(0,value.attribute());
            ASSERT_FALSE(value.global());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_EQ(0,value.mpk());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<long_page_table_entry&>(memory);
        test(reference);

        auto fields = long_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = long_page_table_entry {
            false, false, false, false, false, false, false, 0, false, 0, 0, 0, true
        };
        test(semantic);
    }
}

// long_small_page_directory_entry
    
namespace x86
{
    TEST(long_small_page_directory_entry_64, zero)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, present)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            true, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, writable)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, true, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, user)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, true, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, write_through)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, true, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, cache)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, false, true, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, accessed)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, false, false, true, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, available)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0x3FFF,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0x7FF0000000000E00;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0x7, 0, 0x7FF, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, false, false, false, 0x3FFF, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, address)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFFFFFFFFFF000,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFFFFFFFFFF000;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0xFFFFFFFFFF, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, false, false, false, 0, 0xFFFFFFFFFF000, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_entry_64, nonexecutable)
    {
        auto test = [] (long_small_page_directory_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = long_small_page_directory_entry {
            false, false, false, false, false, false, 0, 0, true
        };
        test(semantic);
    }
}

// long_small_page_directory_pointer_entry
    
namespace x86
{
    TEST(long_small_page_directory_pointer_entry_64, zero)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, present)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            true, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, writable)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, true, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, user)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, true, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, write_through)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, true, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, cache)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, false, true, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, accessed)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, false, false, true, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, available)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0x3FFF,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0x7FF0000000000E00;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 0, 0, 0, 0x7, 0, 0x7FF, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, false, false, false, 0x3FFF, 0, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, address)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFFFFFFFFFF000,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFFFFFFFFFF000;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 0, 0, 0, 0, 0xFFFFFFFFFF, 0, 0 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, false, false, false, 0, 0xFFFFFFFFFF000, false
        };
        test(semantic);
    }

    TEST(long_small_page_directory_pointer_entry_64, nonexecutable)
    {
        auto test = [] (long_small_page_directory_pointer_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<long_small_page_directory_pointer_entry&>(memory);
        test(reference);

        auto fields = long_small_page_directory_pointer_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = long_small_page_directory_pointer_entry {
            false, false, false, false, false, false, 0, 0, true
        };
        test(semantic);
    }
}

// long_page_map_entry
    
namespace x86
{
    TEST(long_page_map_entry_64, zero)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, present)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_TRUE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            true, false, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, writable)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_TRUE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, true, false, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, user)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_TRUE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, true, false, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, write_through)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_TRUE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, true, false, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, cache)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_TRUE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, false, true, false, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, accessed)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_TRUE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, false, false, true, 0, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, available)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0x3FFF,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0x7FF0000000000E00;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 0, 0, 0, 0x7, 0, 0x7FF, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, false, false, false, 0x3FFF, 0, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, address)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0xFFFFFFFFFF000,value.address());
            ASSERT_FALSE(value.nonexecutable());
        };

        size8 memory = 0xFFFFFFFFFF000;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 0, 0, 0, 0, 0xFFFFFFFFFF, 0, 0 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, false, false, false, 0, 0xFFFFFFFFFF000, false
        };
        test(semantic);
    }

    TEST(long_page_map_entry_64, nonexecutable)
    {
        auto test = [] (long_page_map_entry& value) {
            ASSERT_FALSE(value.present());
            ASSERT_FALSE(value.writable());
            ASSERT_FALSE(value.user());
            ASSERT_FALSE(value.write_through());
            ASSERT_FALSE(value.cache());
            ASSERT_FALSE(value.accessed());
            ASSERT_EQ(0,value.available());
            ASSERT_EQ(0,value.address());
            ASSERT_TRUE(value.nonexecutable());
        };

        size8 memory = size8{1} << 63;
        auto& reference = reinterpret_cast<long_page_map_entry&>(memory);
        test(reference);

        auto fields = long_page_map_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        test(fields);

        auto semantic = long_page_map_entry {
            false, false, false, false, false, false, 0, 0, true
        };
        test(semantic);
    }
}