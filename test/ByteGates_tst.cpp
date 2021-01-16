#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "circuit/ByteGates.h"

#include <iostream>

using ::testing::Return;

class ByteGatesTest : public testing::Test 
{};

TEST_F(ByteGatesTest, Notter) 
{
    Notter inverter;

    Byte input = 0xBB; // 1011 1011
    inverter.update(input);

    Byte output = inverter.output();
    EXPECT_EQ(output, 0x44);
}

TEST_F(ByteGatesTest, Ander) 
{
    Ander ander;

    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    ander.update(a, b);

    Byte output = ander.output();
    EXPECT_EQ(output, 0xAA);
}

TEST_F(ByteGatesTest, Orer) 
{
    Orer orer;

    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    orer.update(a, b);

    Byte output = orer.output();
    EXPECT_EQ(output, 0xEB);
}

TEST_F(ByteGatesTest, XOrer) 
{
    XOrer xorer;

    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    xorer.update(a, b);

    Byte output = xorer.output();
    EXPECT_EQ(output, 0x41);
}

TEST_F(ByteGatesTest, CalcDoubleWithOutCarryOut) 
{
    Adder adder;

    for (int a = 0x00; a < 0x7F; ++a)
    {
        bool carryIn = false;
        adder.update(Byte(a), Byte(a), carryIn);

        Byte sum;
        bool carryOut;
        adder.output(sum, carryOut);

        int expectedSum = a + a;

        EXPECT_EQ(expectedSum, sum.toInt());
        EXPECT_FALSE(carryOut);
    }
}

TEST_F(ByteGatesTest, AdderWithOutCarryOut) 
{
    Adder adder;

    for (int a = 0x00; a < 0x7F; ++a)
    {
        for (int b = 0x7f; b >= 0x00; --b)
        {
            bool carryIn = false;
            adder.update(Byte(a), Byte(b), carryIn);

            Byte sum;
            bool carryOut;
            adder.output(sum, carryOut);

            int expectedSum = a + b;

            EXPECT_EQ(expectedSum, sum.toInt());
            EXPECT_FALSE(carryOut);
        }
    }
}

TEST_F(ByteGatesTest, AdderWithCarryOut) 
{
    Adder adder;

    adder.update(Byte(0xF1), Byte(0xF1), false);

    Byte sum;
    bool carryOut;
    adder.output(sum, carryOut);

    EXPECT_EQ(0xE2, sum.toInt());
    EXPECT_TRUE(carryOut);
}

TEST_F(ByteGatesTest, ComparatorAGreaterThanB) 
{
    Comparator cmp;

    cmp.update(0xA1, 0x02);

    Byte c;
    bool equal, a_larger;
    cmp.output(c, equal, a_larger);

    EXPECT_FALSE(equal);
    EXPECT_TRUE(a_larger);
    EXPECT_EQ(0xA3, c.toInt());
}

TEST_F(ByteGatesTest, ComparatorBGreaterThanA) 
{
    Comparator cmp;

    cmp.update(0x31, 0xE2);

    Byte c;
    bool equal, a_larger;
    cmp.output(c, equal, a_larger);

    EXPECT_FALSE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0xD3, c.toInt());
}

TEST_F(ByteGatesTest, ComparatorAEqualB) 
{
    Comparator cmp;

    cmp.update(0x31, 0x31);

    Byte c;
    bool equal, a_larger;
    cmp.output(c, equal, a_larger);

    EXPECT_TRUE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0x0, c.toInt());
}

TEST_F(ByteGatesTest, ZReturnsFalse) 
{
    Z z;

    z.update(0x31);

    EXPECT_FALSE(z.output());
}

TEST_F(ByteGatesTest, ZReturnsTrue) 
{
    Z z;

    z.update(0x0);

    EXPECT_TRUE(z.output());
}