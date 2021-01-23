#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Comparator.h"

#include <iostream>

using ::testing::Return;

class CompGateTest : public ::testing::TestWithParam<std::tuple<bool, bool, bool, bool, bool>>
{};

TEST_P(CompGateTest, execute) 
{
  CompGate comp;

  bool A = std::get<0>(GetParam());
  bool B = std::get<1>(GetParam());
  comp.update(A, B, true, false);

  bool c, equal, a_larger;
  comp.output(c, equal, a_larger);

  bool expectedC = std::get<2>(GetParam());
  bool expectedEqual = std::get<3>(GetParam());
  bool expectedALarger = std::get<4>(GetParam());

  EXPECT_TRUE(expectedC == c);
  EXPECT_TRUE(expectedEqual == equal);
  EXPECT_TRUE(expectedALarger == a_larger);
}

INSTANTIATE_TEST_CASE_P(
        execute,
        CompGateTest,
        ::testing::Values(
                //                 A     B     C    equal  a_larger
                //--------------------------------------------------------
                std::make_tuple(false, true,  true,  false, false ),
                std::make_tuple(true,  false, true,  false, true  ),
                std::make_tuple(false, false, false, true,  false ),
                std::make_tuple(true,  true,  false, true,  false )
        ));
        
class ComparatorTest : public testing::Test 
{};



TEST_F(ComparatorTest, ComparatorAGreaterThanB) 
{
    Comparator cmp;

    cmp.update(0xA1, 0x02);

    Byte c;
    bool equal, a_larger;
    cmp.output(c, equal, a_larger);

    EXPECT_FALSE(equal);
    EXPECT_TRUE(a_larger);
    EXPECT_EQ(0xA3, c.toInt());
}

TEST_F(ComparatorTest, ComparatorBGreaterThanA) 
{
    Comparator cmp;

    cmp.update(0x31, 0xE2);

    Byte c;
    bool equal, a_larger;
    cmp.output(c, equal, a_larger);

    EXPECT_FALSE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0xD3, c.toInt());
}

TEST_F(ComparatorTest, ComparatorAEqualB) 
{
    Comparator cmp;

    cmp.update(0x31, 0x31);

    Byte c;
    bool equal, a_larger;
    cmp.output(c, equal, a_larger);

    EXPECT_TRUE(equal);
    EXPECT_FALSE(a_larger);
    EXPECT_EQ(0x0, c.toInt());
}
