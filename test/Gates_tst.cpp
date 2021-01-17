#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "circuit/BitGates.h"

using ::testing::Return;

class NANDGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool>>
{
};

TEST_P(NANDGateTest, execute) 
{
  NANDGate NAND;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool expected = std::get<2>(GetParam());

  NAND.update(a, b);
  bool c = NAND.output();
  EXPECT_TRUE(expected == c);
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
  NOTGate Not;

  Not.update(true);
  bool c = Not.output();
  EXPECT_TRUE(c == false);
  
  Not.update(false);
  c = Not.output();
  EXPECT_TRUE(c == true);
}        

class ANDGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool>>
{
};

TEST_P(ANDGateTest, execute) 
{
  ANDGate And;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool expected = std::get<2>(GetParam());

  And.update(a, b);
  bool c = And.output();
  EXPECT_TRUE(expected == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        ANDGateTest,
        ::testing::Values(
                std::make_tuple(false, false, false),
                std::make_tuple(false, true,  false),
                std::make_tuple(true,  false, false),
                std::make_tuple(true,  true,  true)));

TEST_F(ANDGateTest, executeInputVectorReturnTrue)
{
  std::vector<bool> inputs;
  inputs.push_back(true);
  inputs.push_back(true);
  inputs.push_back(true);
  inputs.push_back(true);

  ANDGate And;
  And.update(inputs);
  bool c = And.output();
  EXPECT_TRUE(true == c);
}

TEST_F(ANDGateTest, executeInputVectorReturnFalse)
{
  std::vector<bool> inputs;
  inputs.push_back(true);
  inputs.push_back(true);
  inputs.push_back(true);
  inputs.push_back(false);

  ANDGate And;
  And.update(inputs);
  bool c = And.output();
  EXPECT_TRUE(false == c);
}

class ORGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool>>
{
};

TEST_P(ORGateTest, execute) 
{
  ORGate Or;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool expected = std::get<2>(GetParam());

  Or.update(a, b);
  bool c = Or.output();
  EXPECT_TRUE(expected == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        ORGateTest,
        ::testing::Values(
                std::make_tuple(false, false, false),
                std::make_tuple(false, true,  true),
                std::make_tuple(true,  false, true),
                std::make_tuple(true,  true,  true)));


class XORGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool>>
{
};

TEST_P(XORGateTest, execute) 
{
  XORGate Xor;

  bool a = std::get<0>(GetParam());
  bool b = std::get<1>(GetParam());
  bool expected = std::get<2>(GetParam());

  Xor.update(a, b);
  bool c = Xor.output();
  EXPECT_TRUE(expected == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        XORGateTest,
        ::testing::Values(
                std::make_tuple(false, false, false),
                std::make_tuple(false, true,  true),
                std::make_tuple(true,  false, true),
                std::make_tuple(true,  true,  false)));


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

