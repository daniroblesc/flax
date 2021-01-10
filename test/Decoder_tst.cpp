#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Decoder.h"

using ::testing::Return;

class Decoder2X4Test : public testing::Test 
{};

TEST_F(Decoder2X4Test, singleTest)
{
    Decoder2X4 decoder;

    decoder.update(Bit::ZERO, Bit::ZERO);
    EXPECT_EQ(0x00, decoder.outputToInt());
    EXPECT_TRUE(Bit(Bit::ONE) == decoder.output(0));
    
    decoder.update(Bit::ONE, Bit::ZERO);
    EXPECT_EQ(0x01, decoder.outputToInt());
    EXPECT_TRUE(Bit(Bit::ONE) == decoder.output(1));

    decoder.update(Bit::ZERO, Bit::ONE);
    EXPECT_EQ(0x02, decoder.outputToInt());
    EXPECT_TRUE(Bit(Bit::ONE) == decoder.output(2));

    decoder.update(Bit::ONE, Bit::ONE);
    EXPECT_EQ(0x03, decoder.outputToInt());
    EXPECT_TRUE(Bit(Bit::ONE) == decoder.output(3));
}



class Decoder4X16TestAPI : public ::testing::TestWithParam<std::tuple<int, int>>
{};

TEST_P(Decoder4X16TestAPI, output)
{
    Decoder4X16 decoder;

    Byte input(std::get<0>(GetParam()));
    decoder.update(input);

    EXPECT_EQ(std::get<1>(GetParam()), decoder.outputToInt());
    EXPECT_TRUE(Bit(Bit::ONE) == decoder.output(std::get<1>(GetParam())));
}

INSTANTIATE_TEST_CASE_P(
        output,
        Decoder4X16TestAPI,
        ::testing::Values(
                //             input output
                //----------------------------
                std::make_tuple(0x00, 0),
                std::make_tuple(0x01, 1),
                std::make_tuple(0x02, 2),
                std::make_tuple(0x03, 3),

                std::make_tuple(0x04, 4),
                std::make_tuple(0x05, 5),
                std::make_tuple(0x06, 6),
                std::make_tuple(0x07, 7),

                std::make_tuple(0x08, 8),
                std::make_tuple(0x09, 9),
                std::make_tuple(0x0A, 10),
                std::make_tuple(0x0B, 11),

                std::make_tuple(0x0C, 12),
                std::make_tuple(0x0D, 13),
                std::make_tuple(0x0E, 14),
                std::make_tuple(0x0F, 15)));

class Decoder4X16Test : public testing::Test 
{};

TEST_F(Decoder4X16Test, singleTest)
{
    Decoder4X16 decoder;

    // 0xB = 1011b = 11d
    decoder.update(Bit(Bit::ONE), Bit(Bit::ONE), Bit(Bit::ZERO), Bit(Bit::ONE));

    EXPECT_EQ(11, decoder.outputToInt());
}

class Decoder8X256Test : public testing::Test 
{};

TEST_F(Decoder8X256Test, singleTest)
{
    Decoder8X256 decoder;

    for (int b = 0x00; b <= 0xFF; ++b)
    {
        decoder.update(Byte(b));
        EXPECT_EQ(b, decoder.outputToInt());
    }    
}