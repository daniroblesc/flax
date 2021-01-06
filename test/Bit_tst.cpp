#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Bit.h"

using ::testing::Return;

class BitTest : public testing::Test 
{};

TEST_F(BitTest, enable) 
{
    Bit bit(0);

    bit.on();
    EXPECT_EQ(1, bit.get());
}

TEST_F(BitTest, disable) 
{
    Bit bit(1);

    bit.off();
    EXPECT_EQ(0, bit.get());
}

TEST_F(BitTest, assignment) 
{
    Bit bit0(1);
    Bit bit1;

    bit1 = bit0;

    EXPECT_EQ(bit0.get(), bit1.get());
}

TEST_F(BitTest, copyConstructor) 
{
    Bit bit0(1);
    Bit bit1(bit0);

    EXPECT_EQ(bit0.get(), bit1.get());
}

TEST_F(BitTest, equals) 
{
    Bit bit0(1);
    Bit bit1(bit0);

    EXPECT_TRUE(bit0 == bit1);
}

TEST_F(BitTest, NotEquals) 
{
    Bit bit0(1);
    Bit bit1(0);

    EXPECT_FALSE(bit0 == bit1);
}

TEST_F(BitTest, equalsUsingInt) 
{
    Bit bit0(1);

    EXPECT_TRUE(bit0 == 1);
}

TEST_F(BitTest, NotEqualsUsingInt) 
{
    Bit bit0(1);

    EXPECT_FALSE(bit0 == 0);
}

TEST_F(BitTest, equalsUsingBool) 
{
    Bit bit0(1);

    EXPECT_TRUE(bit0 == true);
}

TEST_F(BitTest, NotEqualsUsingBool) 
{
    Bit bit0(1);

    EXPECT_FALSE(bit0 == false);
}