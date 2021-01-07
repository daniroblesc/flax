#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MemoryByte.h"

using ::testing::Return;

class MemoryByteTest : public testing::Test 
{};

TEST_F(MemoryByteTest, save) 
{
    MemoryByte m;

    Byte I1(0xAB); // 1010 1011
    m.save(I1);
    Byte O1 = m.get();
    EXPECT_TRUE(I1 == O1);

    Byte I2(0xD8); // 1101 1000
    m.save(I2);
    Byte O2 = m.get();
    EXPECT_TRUE(I2 == O2);
}
