#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ByteEnabler.h"

using ::testing::Return;

class ByteEnablerTest : public testing::Test 
{};

TEST_F(ByteEnablerTest, executeEnable) 
{
    ByteEnabler enabler;
    Byte input = 0xAB;

    Byte output = enabler.execute(input);

    EXPECT_EQ(output.get(), 0xAB);
}

TEST_F(ByteEnablerTest, executeDisable) 
{
    ByteEnabler enabler;
    Byte input = 0xAB;

    Byte output = enabler.execute(input, Bit(0));

    EXPECT_EQ(output.get(), 0x00);
}