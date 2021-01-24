#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Bus1.h"
#include "circuit/Bus.h"

#include <iostream>

using ::testing::Return;


class Bus1Test : public testing::Test 
{};

TEST_F(Bus1Test, basicOperationBus1BitIsZero) 
{
    Bus inputBus;
    Bus outputBus;
    Bus1 B1(&inputBus, &outputBus);
    
    // set bus value
    inputBus.set(0xAA); 
    outputBus.set(0xBB); 

    // the bits of the input bus pass through to the output bus unchanged
    B1.enable(0);

    // outputBus refreshed with the inputBus content 
    EXPECT_TRUE(outputBus.get() == 0xAA);
    EXPECT_TRUE(inputBus.get() == 0xAA);
}
