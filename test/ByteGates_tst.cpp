#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "circuit/ByteGates.h"

using ::testing::Return;

class NotterTest : public testing::Test 
{};

TEST_F(NotterTest, output) 
{
    Notter inverter;

    Byte input = 0xBB; // 1011 1011
    inverter.update(input);

    Byte output = inverter.output();
    EXPECT_EQ(output, 0x44);
}