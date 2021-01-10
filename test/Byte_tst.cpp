#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Byte.h"
#include <iostream>

using ::testing::Return;

class ByteTest : public testing::Test 
{};

TEST_F(ByteTest, constructor) 
{
    Byte byte(0xAB); // 1010 1011

    std::string msg = byte.toString();
    EXPECT_STREQ(msg.c_str(), "10101011");
    EXPECT_EQ(byte.toInt(), 0xAB);
}

TEST_F(ByteTest, copyConstructor)  
{
    Byte byte0(0xAB);
    Byte byte1(byte0);

    EXPECT_EQ(byte0.toInt(), byte1.toInt());
}                

TEST_F(ByteTest, assignment) 
{
    Byte byte0(0xAB);
    Byte byte1(byte0);

    byte1 = byte0;

    EXPECT_EQ(byte0.toInt(), byte1.toInt());
}

TEST_F(ByteTest, assignmentUsingInt) 
{
    Byte byte = 0xAB;
    
    EXPECT_EQ(byte.toInt(), 0xAB);
}

TEST_F(ByteTest, equals) 
{
    Byte byte0(0xAB);
    Byte byte1(byte0);

    EXPECT_TRUE(byte0 == byte1);
}

TEST_F(ByteTest, NotEquals) 
{
    Byte byte0(0xAB);
    Byte byte1(0xAC);

    EXPECT_FALSE(byte0 == byte1);
}

TEST_F(ByteTest, equalsUsingInt) 
{
    Byte byte0(0xAB);

    EXPECT_TRUE(byte0 == 0xAB);
}

TEST_F(ByteTest, getPosition) 
{
    Byte byte(0xAB); // 1010 1011

    EXPECT_TRUE(byte.get(0) == Bit(Bit::ONE));
    EXPECT_TRUE(byte.get(1) == Bit(Bit::ONE));
    EXPECT_TRUE(byte.get(2) == Bit(Bit::ZERO));
    EXPECT_TRUE(byte.get(3) == Bit(Bit::ONE));
    EXPECT_TRUE(byte.get(4) == Bit(Bit::ZERO));
    EXPECT_TRUE(byte.get(5) == Bit(Bit::ONE));
    EXPECT_TRUE(byte.get(6) == Bit(Bit::ZERO));
    EXPECT_TRUE(byte.get(7) == Bit(Bit::ONE));
}

TEST_F(ByteTest, setPosition) 
{
    Byte byte(0xAB); // 1010 1011

    byte.set(1, Bit::ZERO);
    EXPECT_TRUE(byte.toInt() == 0xA9);
}

TEST_F(ByteTest, getPositionOutOfRange) 
{
    Byte byte(0xAB); // 1010 1011

    EXPECT_TRUE(byte.get(8) == Bit::ZERO);
}
