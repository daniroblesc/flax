#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Register.h"
#include "circuit/Bus.h"
#include <memory>

using ::testing::Return;

class RegisterTest : public testing::Test 
{
protected:    
    void SetUp() override 
    {
        inputBus_ = std::make_unique<Bus>("in");
        outputBus_ = std::make_unique<Bus>("out");
    }

    void TearDown() override 
    {
    } 

    // buses
    std::unique_ptr<Bus> inputBus_; 
    std::unique_ptr<Bus> outputBus_; 
};

TEST_F(RegisterTest, basicOperationSingleBus) 
{
    Register reg("reg", inputBus_.get());

    inputBus_->write(0xA0); // set bus value

    reg.set();    // reg content is refreshed with the bus content
    EXPECT_TRUE(inputBus_->read() == 0xA0); // bus still maintain its value

    inputBus_->write(0xA1); // someone refresh bus content
    reg.enable(); // register's content is written to the bus
    EXPECT_TRUE(inputBus_->read() == 0xA0); // check that bus content is refreshed with register's content
}

TEST_F(RegisterTest, basicOperationTwoBuses) 
{
    Register reg("reg", inputBus_.get(), outputBus_.get());

    // set bus value
    inputBus_->write(0xAA); 
    outputBus_->write(0xBB); 

    // reg content is refreshed with the inputBus content
    reg.set();    
    // outputBus still not refreshed
    EXPECT_TRUE(outputBus_->read() == 0xBB);

    // reg content is written to the outputBus
    reg.enable();
    // outputBus refreshed
    EXPECT_TRUE(outputBus_->read() == 0xAA);
    // inputBus does not change its value
    EXPECT_TRUE(inputBus_->read() == 0xAA);
}
