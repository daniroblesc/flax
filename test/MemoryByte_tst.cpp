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

    Byte read = mb.output();
    EXPECT_EQ(read.toInt(), 0x00);
}

TEST_F(MemoryByteTest, saveAByte) 
{
    MemoryByte m;

    Byte I1(0xAB); // 1010 1011

    // update input
    m.update(I1);
    // enable set bit
    m.set();
    // check if output is the saved input
    Byte O1 = m.output();
    EXPECT_TRUE(I1 == O1);

    Byte I2(0xD8); // 1101 1000
    // update input
    m.update(I2);
    // enable set bit
    m.set();
    // check if output is the saved input
    Byte O2 = m.output();
    EXPECT_TRUE(I2 == O2);
}

TEST_F(MemoryByteTest, doNotSaveIfSetBitIsUnset) 
{
    MemoryByte m;

    Byte I1(0xAB); // 1010 1011

    // update input
    m.update(I1);
    // do not enable set bit...

    // check if output is the saved input
    Byte O1 = m.output();
    EXPECT_FALSE(I1 == O1);
}