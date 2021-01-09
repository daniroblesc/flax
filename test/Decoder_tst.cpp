#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Decoder.h"

using ::testing::Return;

class Decoder2X4Test : public ::testing::TestWithParam<std::tuple<Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue>>
{};

TEST_P(Decoder2X4Test, execute) 
{
    Decoder2X4 decoder;

    Bit::e_BitValue a = std::get<0>(GetParam());
    Bit::e_BitValue b = std::get<1>(GetParam());
    
    std::vector<Bit> inputs;
    inputs.push_back(Bit(a));
    inputs.push_back(Bit(b));

    decoder.update(inputs);
    std::vector<Bit> output = decoder.output();

    Bit::e_BitValue _0_0 = std::get<2>(GetParam());
    Bit::e_BitValue _0_1 = std::get<3>(GetParam());
    Bit::e_BitValue _1_0 = std::get<4>(GetParam());
    Bit::e_BitValue _1_1 = std::get<5>(GetParam());

    EXPECT_TRUE(output[0].get() == _0_0);
    EXPECT_TRUE(output[1].get() == _0_1);
    EXPECT_TRUE(output[2].get() == _1_0);
    EXPECT_TRUE(output[3].get() == _1_1);
    
    EXPECT_TRUE(decoder.output(0) == _0_0);
    EXPECT_TRUE(decoder.output(1) == _0_1);
    EXPECT_TRUE(decoder.output(2) == _1_0);
    EXPECT_TRUE(decoder.output(3) == _1_1);

}

INSTANTIATE_TEST_CASE_P(
        execute,
        Decoder2X4Test,
        ::testing::Values(
                //                  a          b        0/0        0/1         1/0       1/1
                //-------------------------------------------------------------------------------         
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE)));


class Decoder3X8Test : public ::testing::TestWithParam<std::tuple<Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue>>
{};

TEST_P(Decoder3X8Test, execute) 
{
    Decoder3X8 decoder;

    Bit::e_BitValue a = std::get<0>(GetParam());
    Bit::e_BitValue b = std::get<1>(GetParam());
    Bit::e_BitValue c = std::get<2>(GetParam());
    
    std::vector<Bit> inputs;
    inputs.push_back(Bit(a));
    inputs.push_back(Bit(b));
    inputs.push_back(Bit(c));

    decoder.update(inputs);
    std::vector<Bit> output = decoder.output();

    Bit::e_BitValue _0_0_0 = std::get<3>(GetParam());
    Bit::e_BitValue _0_0_1 = std::get<4>(GetParam());
    Bit::e_BitValue _0_1_0 = std::get<5>(GetParam());
    Bit::e_BitValue _0_1_1 = std::get<6>(GetParam());
    Bit::e_BitValue _1_0_0 = std::get<7>(GetParam());
    Bit::e_BitValue _1_0_1 = std::get<8>(GetParam());
    Bit::e_BitValue _1_1_0 = std::get<9>(GetParam());
    Bit::e_BitValue _1_1_1 = std::get<10>(GetParam());

    EXPECT_TRUE(output[0].get() == _0_0_0);
    EXPECT_TRUE(output[1].get() == _0_0_1);
    EXPECT_TRUE(output[2].get() == _0_1_0);
    EXPECT_TRUE(output[3].get() == _0_1_1);
    EXPECT_TRUE(output[4].get() == _1_0_0);
    EXPECT_TRUE(output[5].get() == _1_0_1);
    EXPECT_TRUE(output[6].get() == _1_1_0);
    EXPECT_TRUE(output[7].get() == _1_1_1);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        Decoder3X8Test,
        ::testing::Values(
                //                  a          b         c       0/0/0      0/0/1      0/1/0      0/1/1      1/0/0      1/0/1      1/1/0      1/1/1
                //--------------------------------------------------------------------------------------------------------------------------------------         
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE)));


class Decoder4X16TestFirstByte : public ::testing::TestWithParam<std::tuple<Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, 
                                                                   Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, 
                                                                   Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue>>
{};

TEST_P(Decoder4X16TestFirstByte, execute) 
{
    Decoder4X16 decoder;

    Bit::e_BitValue a = std::get<0>(GetParam());
    Bit::e_BitValue b = std::get<1>(GetParam());
    Bit::e_BitValue c = std::get<2>(GetParam());
    Bit::e_BitValue d = std::get<3>(GetParam());

    std::vector<Bit> inputs;
    inputs.push_back(Bit(a));
    inputs.push_back(Bit(b));
    inputs.push_back(Bit(c));
    inputs.push_back(Bit(d));

    decoder.update(inputs);
    std::vector<Bit> output = decoder.output();

    Bit::e_BitValue _0_0_0_0 = std::get<4>(GetParam());
    Bit::e_BitValue _0_0_0_1 = std::get<5>(GetParam());
    Bit::e_BitValue _0_0_1_0 = std::get<6>(GetParam());
    Bit::e_BitValue _0_0_1_1 = std::get<7>(GetParam());
    Bit::e_BitValue _0_1_0_0 = std::get<8>(GetParam());
    Bit::e_BitValue _0_1_0_1 = std::get<9>(GetParam());
    Bit::e_BitValue _0_1_1_0 = std::get<10>(GetParam());
    Bit::e_BitValue _0_1_1_1 = std::get<11>(GetParam());

    EXPECT_TRUE(output[0].get() == _0_0_0_0);
    EXPECT_TRUE(output[1].get() == _0_0_0_1);
    EXPECT_TRUE(output[2].get() == _0_0_1_0);
    EXPECT_TRUE(output[3].get() == _0_0_1_1);
    EXPECT_TRUE(output[4].get() == _0_1_0_0);
    EXPECT_TRUE(output[5].get() == _0_1_0_1);
    EXPECT_TRUE(output[6].get() == _0_1_1_0);
    EXPECT_TRUE(output[7].get() == _0_1_1_1);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        Decoder4X16TestFirstByte,
        ::testing::Values(
                //                  a         b          c          d       0/0/0/0     0/0/0/1   0/0/1/0     0/0/1/1     0/1/0/0   0/1/0/1    0/1/1/0   0/1/1/1
                //-------------------------------------------------------------------------------------------------------------------------------------------------         
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE)));

class Decoder4X16TestSecondByte : public ::testing::TestWithParam<std::tuple<Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, 
                                                                   Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, 
                                                                   Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue>>
{};

TEST_P(Decoder4X16TestSecondByte, execute) 
{
    Decoder4X16 decoder;

    Bit::e_BitValue a = std::get<0>(GetParam());
    Bit::e_BitValue b = std::get<1>(GetParam());
    Bit::e_BitValue c = std::get<2>(GetParam());
    Bit::e_BitValue d = std::get<3>(GetParam());

    std::vector<Bit> inputs;
    inputs.push_back(Bit(a));
    inputs.push_back(Bit(b));
    inputs.push_back(Bit(c));
    inputs.push_back(Bit(d));

    decoder.update(inputs);
    std::vector<Bit> output = decoder.output();

    Bit::e_BitValue _1_0_0_0 = std::get<4>(GetParam());
    Bit::e_BitValue _1_0_0_1 = std::get<5>(GetParam());
    Bit::e_BitValue _1_0_1_0 = std::get<6>(GetParam());
    Bit::e_BitValue _1_0_1_1 = std::get<7>(GetParam());
    Bit::e_BitValue _1_1_0_0 = std::get<8>(GetParam());
    Bit::e_BitValue _1_1_0_1 = std::get<9>(GetParam());
    Bit::e_BitValue _1_1_1_0 = std::get<10>(GetParam());
    Bit::e_BitValue _1_1_1_1 = std::get<11>(GetParam());

    EXPECT_TRUE(output[8].get()  == _1_0_0_0);
    EXPECT_TRUE(output[9].get()  == _1_0_0_1);
    EXPECT_TRUE(output[10].get() == _1_0_1_0);
    EXPECT_TRUE(output[11].get() == _1_0_1_1);
    EXPECT_TRUE(output[12].get() == _1_1_0_0);
    EXPECT_TRUE(output[13].get() == _1_1_0_1);
    EXPECT_TRUE(output[14].get() == _1_1_1_0);
    EXPECT_TRUE(output[15].get() == _1_1_1_1);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        Decoder4X16TestSecondByte,
        ::testing::Values(
                //                  a        b          c          d       1/0/0/0     1/0/0/1   1/0/1/0     1/0/1/1     1/1/0/0   1/1/0/1    1/1/1/0   1/1/1/1
                //-------------------------------------------------------------------------------------------------------------------------------------------------         
                std::make_tuple(Bit::ONE, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ZERO, Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ONE,  Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE,  Bit::ZERO),
                std::make_tuple(Bit::ONE, Bit::ONE,  Bit::ONE,  Bit::ONE,  Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ZERO, Bit::ONE)));                
