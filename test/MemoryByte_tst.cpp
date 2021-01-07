#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MemoryByte.h"

using ::testing::Return;

class MemoryByteTest : public testing::Test 
{};

TEST_F(MemoryByteTest, constructor) 
{
    MemoryByte mb;

    Byte read = mb.read();
    EXPECT_EQ(read.get(), 0x00);
}

TEST_F(MemoryByteTest, write) 
{
    MemoryByte m;

    Byte I1(0xAB); // 1010 1011
    m.write(I1);
    Byte O1 = m.read();
    EXPECT_TRUE(I1 == O1);

    Byte I2(0xD8); // 1101 1000
    m.write(I2);
    Byte O2 = m.read();
    EXPECT_TRUE(I2 == O2);
}
