#include <gtest/gtest.h>
#include <pb/memory.h>


TEST(MemoryTests, InitFixedTest)
{
    pb::MemoryGrowthPolicyFixed fixed_policy;
    pb::Memory memory(fixed_policy, 1024);

    memory.initialize();

    ASSERT_EQ(memory.current_size(), 1024);
}

/**
 * This test checks that the automatic initialization of memory works correctly.
 * It initializes the memory with a fixed growth policy and checks that the current size is as expected
 */
TEST(MemoryTests, WriteFixedNotInitialized)
{
    pb::MemoryGrowthPolicyFixed fixed_policy;
    pb::Memory memory(fixed_policy, 1024);

    ASSERT_EQ(memory.write("test", 4, 0), 4);
}

TEST(MemoryTests, ExceedFixedTest)
{
    pb::MemoryGrowthPolicyFixed fixed_policy;
    pb::Memory memory(fixed_policy, 10);

    memory.initialize();

    ASSERT_THROW(memory.write("01234567890", 11, 0), std::runtime_error);
}