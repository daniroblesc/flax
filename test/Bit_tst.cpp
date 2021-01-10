#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "circuit/Bit.h"

using ::testing::Return;

class BitTest : public testing::Test 
{};

TEST_F(BitTest, enable) 
{
    Bit bit(Bit::ZERO);

    bit.set(Bit::ONE);
    EXPECT_EQ(Bit::ONE, bit.get());
}

TEST_F(BitTest, disable) 
{
    Bit bit(Bit::ONE);

    bit.set(Bit::ZERO);
    EXPECT_EQ(Bit::ZERO, bit.get());
}

TEST_F(BitTest, assignment) 
{
    Bit bit0(Bit::ONE);
    Bit bit1;

    bit1 = bit0;

    EXPECT_EQ(bit0.get(), bit1.get());
}

TEST_F(BitTest, assignmentUsingInt) 
{
    Bit bit = Bit::ONE;
    
    EXPECT_EQ(bit.get(), Bit::ONE);
}

TEST_F(BitTest, copyConstructor) 
{
    Bit bit0(Bit::ONE);
    Bit bit1(bit0);

    EXPECT_EQ(bit0.get(), bit1.get());
}

TEST_F(BitTest, equals) 
{
    Bit bit0(Bit::ONE);
    Bit bit1(bit0);

    EXPECT_TRUE(bit0 == bit1);
}

TEST_F(BitTest, NotEquals) 
{
    Bit bit0(Bit::ONE);
    Bit bit1(Bit::ZERO);

    EXPECT_FALSE(bit0 == bit1);
}

TEST_F(BitTest, equalsUsingInt) 
{
    Bit bit(Bit::ONE);

    EXPECT_TRUE(bit == Bit::ONE);
}

TEST_F(BitTest, NotEqualsUsingInt) 
{
    Bit bit(Bit::ONE);

    EXPECT_FALSE(bit == Bit::ZERO);
}
