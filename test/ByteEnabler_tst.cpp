#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ByteEnabler.h"

using ::testing::Return;

class ByteEnablerTest : public testing::Test 
{};

TEST_F(ByteEnablerTest, enable) 
{
    ByteEnabler enabler;
    Byte input = 0xAB;

    enabler.load(input);
    Byte output = enabler.enable();

    EXPECT_EQ(output.get(), 0xAB);
}
