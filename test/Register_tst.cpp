#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Register.h"
#include "Bus.h"

using ::testing::Return;

class RegisterTest : public testing::Test 
{};

TEST_F(RegisterTest, basicOperationSingleBus) 
{
    Bus bus_;
    Register reg(&bus_);

    bus_.set(0xA0); // set bus value

    reg.set();    // reg content is refreshed with the bus content
    EXPECT_TRUE(bus_.get() == 0xA0); // bus still maintain its value

    bus_.set(0xA1); // someone refresh bus content
    reg.enable(); // register's content is written to the bus
    EXPECT_TRUE(bus_.get() == 0xA0); // check that bus content is refreshed with register's content
}

TEST_F(RegisterTest, basicOperationTwoBuses) 
{
    Bus inputBus;
    Bus outputBus;
    Register reg(&inputBus, &outputBus);

    // set bus value
    inputBus.set(0xAA); 
    outputBus.set(0xBB); 

    // reg content is refreshed with the inputBus content
    reg.set();    
    // outputBus still not refreshed
    EXPECT_TRUE(outputBus.get() == 0xBB);

    // reg content is written to the outputBus
    reg.enable();
    // outputBus refreshed
    EXPECT_TRUE(outputBus.get() == 0xAA);
    // inputBus does not change its value
    EXPECT_TRUE(inputBus.get() == 0xAA);
}