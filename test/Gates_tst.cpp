#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Gates.h"
#include "Bit.h"

using ::testing::Return;

class NANDGateTest : public ::testing::TestWithParam<std::tuple<int, int, int>>
{
};

TEST_P(NANDGateTest, execute) 
{
  NANDGate NAND;

  int a = std::get<0>(GetParam());
  int b = std::get<1>(GetParam());
  int expected = std::get<2>(GetParam());

  Bit c = NAND.execute(Bit(a), Bit(b));
  EXPECT_TRUE(Bit(expected) == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        NANDGateTest,
        ::testing::Values(
                std::make_tuple(0, 0, 1),
                std::make_tuple(0, 1, 1),
                std::make_tuple(1, 0, 1),
                std::make_tuple(1, 1, 0)));

class NOTGateTest : public testing::Test 
{
};

TEST_F(NOTGateTest, execute) 
{
  NOTGate Not;

  Bit c = Not.execute(Bit(1));
  EXPECT_TRUE(c == 0);
  EXPECT_TRUE(c.get() == 0);

  c = Not.execute(Bit(0));
  EXPECT_TRUE(c == 1);
  EXPECT_TRUE(c.get() == 1);
}        

class ANDGateTest : public ::testing::TestWithParam<std::tuple<int, int, int>>
{
};

TEST_P(ANDGateTest, execute) 
{
  ANDGate And;

  int a = std::get<0>(GetParam());
  int b = std::get<1>(GetParam());
  int expected = std::get<2>(GetParam());

  Bit c = And.execute(Bit(a), Bit(b));
  EXPECT_TRUE(Bit(expected) == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        ANDGateTest,
        ::testing::Values(
                std::make_tuple(0, 0, 0),
                std::make_tuple(0, 1, 0),
                std::make_tuple(1, 0, 0),
                std::make_tuple(1, 1, 1)));
