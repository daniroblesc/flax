#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Adder.h"

#include <iostream>

using ::testing::Return;


class AdderTest : public testing::Test 
{};

TEST_F(AdderTest, CalcDoubleWithOutCarryOut) 
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

TEST_F(AdderTest, AdderWithOutCarryOut) 
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

TEST_F(AdderTest, AdderWithCarryOut) 
{
    Adder adder;

    adder.update(Byte(0xF1), Byte(0xF1), false);

    Byte sum;
    bool carryOut;
    adder.output(sum, carryOut);

    EXPECT_EQ(0xE2, sum.toInt());
    EXPECT_TRUE(carryOut);
}


class AddGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool, bool, bool>>
{
};


TEST_P(AddGateTest, execute) 
{
  AddGate add;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool carryIn = std::get<2>(GetParam());

  add.update(a, b, carryIn);
  bool sum, carryOut;
  add.output(sum, carryOut);

  bool expectedCarryOut = std::get<3>(GetParam());
  bool expectedSum = std::get<4>(GetParam());

  EXPECT_TRUE(expectedSum == sum);
  EXPECT_TRUE(expectedCarryOut == carryOut);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        AddGateTest,
        ::testing::Values(
                //               A       B     Cin   Cout   S
                //-------------------------------------------------
                std::make_tuple(false, false, false, false, false),
                std::make_tuple(false, false, true,  false, true),
                std::make_tuple(false, true,  false, false, true),
                std::make_tuple(false, true,  true,  true,  false),
                std::make_tuple(true,  false, false, false, true),
                std::make_tuple(true,  false, true,  true,  false),
                std::make_tuple(true,  true,  false, true,  false),
                std::make_tuple(true,  true,  true,  true,  true)
                ));

