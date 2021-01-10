#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/ByteEnabler.h"

using ::testing::Return;

class ByteEnablerTest : public testing::Test 
{};

TEST_F(ByteEnablerTest, getEoutputOnceBitEIsEnabled) 
{
     ByteEnabler E;
    Byte input = 0xAB;

    // update the input
    E.update(input);
    // enable 'e' bit
    E.enable();
    // get the output
    Byte output = E.output();

    EXPECT_EQ(output.toInt(), 0xAB);
}

TEST_F(ByteEnablerTest, doNotGetOutputIfEBitIsNotSet) 
{
    ByteEnabler E;
    Byte input = 0xAB;

    // update the input
    E.update(input);
    // not enable 'e' bit...

    // get the output
    Byte output = E.output();

    EXPECT_FALSE(output.toInt() == 0xAB);
}
