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
