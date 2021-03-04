#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "circuit/ByteGates.h"

#include <iostream>
#include <memory>

using ::testing::Return;

class ByteGatesTest : public testing::Test 
{};

TEST_F(ByteGatesTest, NOTter) 
{
    NOTter inverter;

    Byte input = 0xBB; // 1011 1011
    inverter.update(input);

    Byte output = inverter.output();
    EXPECT_EQ(output, 0x44);
}

TEST_F(ByteGatesTest, NOTter2) 
{
    std::shared_ptr<WireCollection> wires = std::make_shared<WireCollection>(0xbb);

    NOTter inverter(wires);
    Byte output = inverter.output();
    EXPECT_EQ(output, 0x44);
}

TEST_F(ByteGatesTest, ANDer) 
{
    ANDer ANDer;

    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    ANDer.update(a, b);

    Byte output = ANDer.output();
    EXPECT_EQ(output, 0xAA);
}

TEST_F(ByteGatesTest, ORer) 
{
    ORer ORer;

    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    ORer.update(a, b);

    Byte output = ORer.output();
    EXPECT_EQ(output, 0xEB);
}

TEST_F(ByteGatesTest, XORer) 
{
    XORer xORer;

    Byte a = 0xAA; // 1010 1010
    Byte b = 0xEB; // 1110 1011
    xORer.update(a, b);

    Byte output = xORer.output();
    EXPECT_EQ(output, 0x41);
}

TEST_F(ByteGatesTest, ZReturnsFalse) 
{
    Zero z;

    z.update(0x31);

    EXPECT_FALSE(z.output());
}

TEST_F(ByteGatesTest, ZReturnsTrue) 
{
    Zero z;

    z.update(0x0);

    EXPECT_TRUE(z.output());
}