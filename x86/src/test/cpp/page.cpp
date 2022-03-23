#include <gtest/gtest.h>

#include <x86/_32/page.h>


namespace x86::_32
{
    // short_small_page_table_entry

    TEST(short_small_page_table_entry, zero)
    {
        size4 memory = 0;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, present)
    {
        size4 memory = 1;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_TRUE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_TRUE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, writable)
    {
        size4 memory = 1 << 1;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_TRUE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_TRUE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, user)
    {
        size4 memory = 1 << 2;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_TRUE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_TRUE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, write_through)
    {
        size4 memory = 1 << 3;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_TRUE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_TRUE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, cache)
    {
        size4 memory = 1 << 4;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_TRUE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_TRUE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, accessed)
    {
        size4 memory = 1 << 5;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_TRUE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        
        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_TRUE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, dirty)
    {
        size4 memory = 1 << 6;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_TRUE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        
        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_TRUE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, attribute)
    {
        size4 memory = 1 << 7;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(1,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        
        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(1,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, global)
    {
        size4 memory = 1 << 8;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_TRUE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_TRUE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, available)
    {
        size4 memory = 3 << 9;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(3,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(3,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_table_entry, address)
    {
        size4 memory = 0xFFFFF000;
        auto& reference = reinterpret_cast<short_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0xFFFFF000,reference.address());

        auto fields = short_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFFF };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0xFFFFF000,fields.address());
    }

    // short_small_page_directory_entry

    TEST(short_small_page_directory_entry, zero)
    {
        size4 memory = 0;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        
        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, present)
    {
        size4 memory = 1;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_TRUE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, writable)
    {
        size4 memory = 1 << 1;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_TRUE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, user)
    {
        size4 memory = 1 << 2;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_TRUE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, write_through)
    {
        size4 memory = 1 << 3;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_TRUE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, cache)
    {
        size4 memory = 1 << 4;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_TRUE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, accessed)
    {
        size4 memory = 1 << 5;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_TRUE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, available)
    {
        size4 memory = 3 << 9;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(3,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_small_page_directory_entry, address)
    {
        size4 memory = 0xFFFFF000;
        auto& reference = reinterpret_cast<short_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0xFFFFF000,reference.address());

        auto fields = short_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    // short_large_page_directory_entry

    TEST(short_large_page_directory_entry, zero)
    {
        size4 memory = 0;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());
        
        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, present)
    {
        size4 memory = 1;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_TRUE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_TRUE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, writable)
    {
        size4 memory = 1 << 1;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_TRUE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_TRUE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, user)
    {
        size4 memory = 1 << 2;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_TRUE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_TRUE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, write_through)
    {
        size4 memory = 1 << 3;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_TRUE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_TRUE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, cache)
    {
        size4 memory = 1 << 4;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_TRUE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_TRUE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, accessed)
    {
        size4 memory = 1 << 5;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_TRUE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_TRUE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, dirty)
    {
        size4 memory = 1 << 6;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_TRUE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_TRUE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, global)
    {
        size4 memory = 1 << 8;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_TRUE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_TRUE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, available)
    {
        size4 memory = 3 << 9;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(3,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(3,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, attribute)
    {
        size4 memory = 1 << 12;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(1,reference.attribute());
        ASSERT_EQ(0,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(1,fields.attribute());
        ASSERT_EQ(0,fields.address());
    }

    TEST(short_large_page_directory_entry, address)
    {
        size4 memory = 0xFFDFE000;
        auto& reference = reinterpret_cast<short_large_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_EQ(0x00FFFFC00000,reference.address());

        auto fields = short_large_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0x3FF };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_EQ(0x00FFFFC00000,fields.address());
    }
    
    // long_small_page_table_entry

    TEST(long_small_page_table_entry, zero)
    {
        size8 memory = 0;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, present)
    {
        size8 memory = 1;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_TRUE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_TRUE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, writable)
    {
        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_TRUE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_TRUE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, user)
    {
        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_TRUE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_TRUE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, write_through)
    {
        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_TRUE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_TRUE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, cache)
    {
        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_TRUE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_TRUE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, accessed)
    {
        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_TRUE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());
        
        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_TRUE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, dirty)
    {
        size8 memory = 1 << 6;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_TRUE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());
        
        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_TRUE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, attribute)
    {
        size8 memory = 1 << 7;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(1,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());
        
        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(1,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, global)
    {
        size8 memory = 1 << 8;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_TRUE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_TRUE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, available)
    {
        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(3,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(3,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, address)
    {
        size8 memory = 0xFEDCBA9876000;
        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0xFEDCBA9876000,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFEDCBA9876, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0xFEDCBA9876000,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_table_entry, executable)
    {
        size8 memory = size8{1} << 63;

        auto& reference = reinterpret_cast<long_small_page_table_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_FALSE(reference.dirty());
        ASSERT_EQ(0,reference.attribute());
        ASSERT_FALSE(reference.global());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_TRUE(reference.executable());

        auto fields = long_small_page_table_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_FALSE(fields.dirty());
        ASSERT_EQ(0,fields.attribute());
        ASSERT_FALSE(fields.global());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_TRUE(fields.executable());
    }
    
    // long_small_page_directory_entry

    TEST(long_small_page_directory_entry, zero)
    {
        size8 memory = 0;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, present)
    {
        size8 memory = 1;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_TRUE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_TRUE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, writable)
    {
        size8 memory = 1 << 1;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_TRUE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 1, 0, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_TRUE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, user)
    {
        size8 memory = 1 << 2;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_TRUE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 1, 0, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_TRUE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, write_through)
    {
        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_TRUE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 0, 1, 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_TRUE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, cache)
    {
        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_TRUE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_TRUE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, accessed)
    {
        size8 memory = 1 << 5;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_TRUE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());
        
        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 1, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_TRUE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, available)
    {
        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(3,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 3, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(3,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, address)
    {
        size8 memory = 0xFEDCBA9876000;
        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0xFEDCBA9876000,reference.address());
        ASSERT_FALSE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0xFEDCBA9876, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0xFEDCBA9876000,fields.address());
        ASSERT_FALSE(fields.executable());
    }

    TEST(long_small_page_directory_entry, executable)
    {
        size8 memory = size8{1} << 63;

        auto& reference = reinterpret_cast<long_small_page_directory_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.writable());
        ASSERT_FALSE(reference.user());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_FALSE(reference.accessed());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());
        ASSERT_TRUE(reference.executable());

        auto fields = long_small_page_directory_entry { 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.writable());
        ASSERT_FALSE(fields.user());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_FALSE(fields.accessed());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
        ASSERT_TRUE(fields.executable());
    }
    
    // small_page_directory_pointer_extended_entry

    TEST(small_page_directory_pointer_extended_entry, zero)
    {
        size8 memory = 0;
        auto& reference = reinterpret_cast<small_page_directory_pointer_extended_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = small_page_directory_pointer_extended_entry { 0, 0, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(small_page_directory_pointer_extended_entry, present)
    {
        size8 memory = 1;
        auto& reference = reinterpret_cast<small_page_directory_pointer_extended_entry&>(memory);
        ASSERT_TRUE(reference.present());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = small_page_directory_pointer_extended_entry { 1, 0, 0, 0, 0 };
        ASSERT_TRUE(fields.present());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(small_page_directory_pointer_extended_entry, write_through)
    {
        size8 memory = 1 << 3;
        auto& reference = reinterpret_cast<small_page_directory_pointer_extended_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_TRUE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = small_page_directory_pointer_extended_entry { 0, 1, 0, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_TRUE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(small_page_directory_pointer_extended_entry, cache)
    {
        size8 memory = 1 << 4;
        auto& reference = reinterpret_cast<small_page_directory_pointer_extended_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.write_through());
        ASSERT_TRUE(reference.cache());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = small_page_directory_pointer_extended_entry { 0, 0, 1, 0, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.write_through());
        ASSERT_TRUE(fields.cache());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(small_page_directory_pointer_extended_entry, available)
    {
        size8 memory = 3 << 9;
        auto& reference = reinterpret_cast<small_page_directory_pointer_extended_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_EQ(3,reference.available());
        ASSERT_EQ(0,reference.address());

        auto fields = small_page_directory_pointer_extended_entry { 0, 0, 0, 3, 0 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_EQ(3,fields.available());
        ASSERT_EQ(0,fields.address());
    }

    TEST(small_page_directory_pointer_extended_entry, address)
    {
        size8 memory = 0xFEDCBA9876000;
        auto& reference = reinterpret_cast<small_page_directory_pointer_extended_entry&>(memory);
        ASSERT_FALSE(reference.present());
        ASSERT_FALSE(reference.write_through());
        ASSERT_FALSE(reference.cache());
        ASSERT_EQ(0,reference.available());
        ASSERT_EQ(0xFEDCBA9876000,reference.address());

        auto fields = small_page_directory_pointer_extended_entry { 0, 0, 0, 0, 0xFEDCBA9876 };
        ASSERT_FALSE(fields.present());
        ASSERT_FALSE(fields.write_through());
        ASSERT_FALSE(fields.cache());
        ASSERT_EQ(0,fields.available());
        ASSERT_EQ(0xFEDCBA9876000,fields.address());
    }
}