#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Gates.h"
#include "Bit.h"

using ::testing::Return;

class NANDGateTest : public ::testing::TestWithParam<std::tuple<Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue>>
{
};

TEST_P(NANDGateTest, execute) 
{
  NANDGate NAND;

  Bit::e_BitValue a = std::get<0>(GetParam());
  Bit::e_BitValue b = std::get<1>(GetParam());
  Bit::e_BitValue expected = std::get<2>(GetParam());

  NAND.update(Bit(a), Bit(b));
  Bit c = NAND.output();
  EXPECT_TRUE(Bit(expected) == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        NANDGateTest,
        ::testing::Values(
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ONE),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ONE),
                std::make_tuple(Bit::ONE,  Bit::ZERO, Bit::ONE),
                std::make_tuple(Bit::ONE,  Bit::ONE,  Bit::ZERO)));

class NOTGateTest : public testing::Test 
{
};

TEST_F(NOTGateTest, execute) 
{
  NOTGate Not;

  Not.update(Bit(Bit::ONE));
  Bit c = Not.output();
  EXPECT_TRUE(c == Bit::ZERO);
  EXPECT_TRUE(c.get() == Bit::ZERO);

  Not.update(Bit(Bit::ZERO));
  c = Not.output();
  EXPECT_TRUE(c == Bit::ONE);
  EXPECT_TRUE(c.get() == Bit::ONE);
}        

class ANDGateTest : public ::testing::TestWithParam<std::tuple<Bit::e_BitValue, Bit::e_BitValue, Bit::e_BitValue>>
{
};

TEST_P(ANDGateTest, execute) 
{
  ANDGate And;

  Bit::e_BitValue a = std::get<0>(GetParam());
  Bit::e_BitValue b = std::get<1>(GetParam());
  Bit::e_BitValue expected = std::get<2>(GetParam());

  And.update(Bit(a), Bit(b));
  Bit c = And.output();
  EXPECT_TRUE(Bit(expected) == c);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        ANDGateTest,
        ::testing::Values(
                std::make_tuple(Bit::ZERO, Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ZERO, Bit::ONE,  Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ZERO, Bit::ZERO),
                std::make_tuple(Bit::ONE,  Bit::ONE,  Bit::ONE)));

TEST_F(ANDGateTest, executeInputVectorReturnTrue)
{
  std::vector<Bit> inputs;
  inputs.push_back(Bit(Bit::ONE));
  inputs.push_back(Bit(Bit::ONE));
  inputs.push_back(Bit(Bit::ONE));
  inputs.push_back(Bit(Bit::ONE));

  ANDGate And;
  And.update(inputs);
  Bit c = And.output();
  EXPECT_TRUE(Bit(Bit::ONE) == c);
}

TEST_F(ANDGateTest, executeInputVectorReturnFalse)
{
  std::vector<Bit> inputs;
  inputs.push_back(Bit(Bit::ONE));
  inputs.push_back(Bit(Bit::ONE));
  inputs.push_back(Bit(Bit::ONE));
  inputs.push_back(Bit(Bit::ZERO));

  ANDGate And;
  And.update(inputs);
  Bit c = And.output();
  EXPECT_TRUE(Bit(Bit::ZERO) == c);
}