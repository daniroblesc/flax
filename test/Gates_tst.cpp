#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Gates.h"

using ::testing::Return;

class NANDGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool>>
{
};

TEST_P(NANDGateTest, execute) 
{
  NANDGate gate;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool expected = std::get<2>(GetParam());

  bool c = gate.execute(a, b);
  EXPECT_EQ(expected, c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        NANDGateTest,
        ::testing::Values(
                std::make_tuple(false, false, true),
                std::make_tuple(false, true,  true),
                std::make_tuple(true,  false, true),
                std::make_tuple(true,  true,  false)));

class NOTGateTest : public testing::Test 
{
};

TEST_F(NOTGateTest, execute) 
{
  NOTGate gate;

  bool c = gate.execute(true);
  EXPECT_FALSE(c);

  c = gate.execute(false);
  EXPECT_TRUE(c);
}        

class ANDGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool>>
{
};

TEST_P(ANDGateTest, execute) 
{
  ANDGate gate;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool expected = std::get<2>(GetParam());

  bool c = gate.execute(a, b);
  EXPECT_EQ(expected, c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        ANDGateTest,
        ::testing::Values(
                std::make_tuple(false, false, false),
                std::make_tuple(false, true,  false),
                std::make_tuple(true,  false, false),
                std::make_tuple(true,  true,  true)));
