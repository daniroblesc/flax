#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "circuit/Wire.h"
#include <iostream>

using ::testing::Return;

class WireTest : public testing::Test 
{};

TEST_F(WireTest, readWiresFromWireCollection) 
{
    WireCollection wires(0xAB); // 1010 1011

    EXPECT_TRUE(wires.output(0));
    EXPECT_TRUE(wires.output(1));
    EXPECT_FALSE(wires.output(2));
    EXPECT_TRUE(wires.output(3));

    EXPECT_FALSE(wires.output(4));
    EXPECT_TRUE(wires.output(5));
    EXPECT_FALSE(wires.output(6));
    EXPECT_TRUE(wires.output(7));

    EXPECT_EQ(wires.output(), 0xAB);
}

TEST_F(WireTest, updateWiresFromWireCollection) 
{
    WireCollection wires(0xAB); // 1010 1011

    wires.off(0);
    wires.off(1);
    wires.on(2);
    EXPECT_EQ(wires.output(), 0xAC);

    wires.set(0x98);
    EXPECT_EQ(wires.output(), 0x98);

}