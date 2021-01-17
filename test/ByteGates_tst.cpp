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