#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Byte.h"

using ::testing::Return;

class ByteEnableBitTest : public ::testing::TestWithParam<std::tuple<int, int, int>>
{};

TEST_P(ByteEnableBitTest, enableBit) 
{
    int input = std::get<0>(GetParam());
    int position = std::get<1>(GetParam());
    int output = std::get<2>(GetParam());

    Byte byte(input);

    byte.on(position);
    EXPECT_EQ(output, byte.get());
}

INSTANTIATE_TEST_CASE_P(
        enable,
        ByteEnableBitTest,
        ::testing::Values(
                std::make_tuple(0xF0, 0, 0xF1),
                std::make_tuple(0xF0, 1, 0xF2),
                std::make_tuple(0xF0, 2, 0xF4),
                std::make_tuple(0xF0, 3, 0xF8),
                std::make_tuple(0x0F, 4, 0x1F),
                std::make_tuple(0x0F, 5, 0x2F),
                std::make_tuple(0x0F, 6, 0x4F),
                std::make_tuple(0x0F, 7, 0x8F)));


class ByteDisableBitTest : public ::testing::TestWithParam<std::tuple<int, int, int>>
{};

TEST_P(ByteDisableBitTest, disableBit) 
{
    int input = std::get<0>(GetParam());
    int position = std::get<1>(GetParam());
    int output = std::get<2>(GetParam());

    Byte byte(input);

    byte.off(position);
    EXPECT_EQ(output, byte.get());
}

INSTANTIATE_TEST_CASE_P(
        disable,
        ByteDisableBitTest,
        ::testing::Values(
                std::make_tuple(0xFF, 0, 0xFE),
                std::make_tuple(0xFF, 1, 0xFD),
                std::make_tuple(0xFF, 2, 0xFB),
                std::make_tuple(0xFF, 3, 0xF7),
                std::make_tuple(0xFF, 4, 0xEF),
                std::make_tuple(0xFF, 5, 0xDF),
                std::make_tuple(0xFF, 6, 0xBF),
                std::make_tuple(0xFF, 7, 0x7F)));                

class ByteTest : public testing::Test 
{};

TEST_F(ByteTest, copyConstructor) 
{
    Byte byte0(0xAB);
    Byte byte1(byte0);

    EXPECT_EQ(byte0.get(), byte1.get());
}                

TEST_F(ByteTest, assignment) 
{
    Byte byte0(0xAB);
    Byte byte1(byte0);

    byte1 = byte0;

    EXPECT_EQ(byte0.get(), byte1.get());
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
    Byte byte0(0xAB); // 1010 1011

    EXPECT_TRUE(byte0.get(0) == Bit(1));
    EXPECT_TRUE(byte0.get(1) == Bit(1));
    EXPECT_TRUE(byte0.get(2) == Bit(0));
    EXPECT_TRUE(byte0.get(3) == Bit(1));
    EXPECT_TRUE(byte0.get(4) == Bit(0));
    EXPECT_TRUE(byte0.get(5) == Bit(1));
    EXPECT_TRUE(byte0.get(6) == Bit(0));
    EXPECT_TRUE(byte0.get(7) == Bit(1));
}

TEST_F(ByteTest, setPosition) 
{
    Byte byte(0xAB); // 1010 1011

    byte.set(Bit(0), 1);
    EXPECT_TRUE(byte.get() == 0xA9);
}