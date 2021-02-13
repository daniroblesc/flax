#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "components/Bus1.h"
#include "circuit/Bus.h"
#include <memory>
#include <iostream>

using ::testing::Return;


class Bus1Test : public testing::Test 
{
protected:    
    void SetUp() override 
    {
        inputBus_ = std::make_unique<Bus>("in");
        outputBus_ = std::make_unique<Bus>("out");

        B1_ = std::make_unique<Bus1>("BUS1",inputBus_.get(), outputBus_.get());    
    }

    void TearDown() override 
    {
    }    

    // the code under test.
    std::unique_ptr<Bus1> B1_;

    // buses
    std::unique_ptr<Bus> inputBus_;
    std::unique_ptr<Bus> outputBus_;
};

TEST_F(Bus1Test, basicOperationBus1BitIsZero) 
{
    // set bus value
    inputBus_->write(0xAA);   // 1010 1010
    outputBus_->write(0xBB);  

    // the bits of the input bus pass through to the output bus unchanged
    B1_->enable(0);

    // outputBus refreshed with the inputBus content 
    EXPECT_TRUE(outputBus_->read() == 0xAA);
    EXPECT_TRUE(inputBus_->read() == 0xAA);
}

TEST_F(Bus1Test, basicOperationBus1BitIsOne) 
{
    // set bus value
    inputBus_->write(0xAA);   // 1010 1010
    outputBus_->write(0xBB);  

    // the input byte is ignored and the output byte will be 1
    B1_->enable(1);

    // outputBus refreshed with the inputBus content 
    EXPECT_TRUE(outputBus_->read() == 1);
    EXPECT_TRUE(inputBus_->read() == 0xAA);
}