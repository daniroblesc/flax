#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "control/ControlUnit.h"
#include "circuit/Bus.h"
#include "components/Register.h"
#include "ALU/ALU.h"
#include <memory>
#include <map>
#include <iostream>
#include <chrono>         // std::chrono::seconds

using ::testing::Return;

class ControlUnitTest : public testing::Test 
{
protected:    
    void SetUp() override 
    {
        // Create Buses
        //
        buses_["system"] = std::make_shared<Bus>("system", Bus::VERBOSE);
        buses_["ALU_out"] = std::make_shared<Bus>("ALU_out", Bus::VERBOSE);
        buses_["ALU_in_b"] = std::make_shared<Bus>("ALU_in_b", Bus::VERBOSE);

        // Create controllable items
        // 
        R1_  = std::make_unique<Register>("R1", buses_["system"].get());
        R0_  = std::make_unique<Register>("R0", buses_["system"].get());
        TMP_ = std::make_unique<Register>("TMP", buses_["system"].get());
        ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"].get(), buses_["system"].get());
        ALU_ = std::make_unique<ALU>(buses_["system"].get(), buses_["ALU_in_b"].get(), buses_["ALU_out"].get());

        controlUnit_ = std::make_unique<control::ControlUnit>(1);    

        // Connect items to the Control Unit
        //
        controlUnit_->connect(R1_.get());
        controlUnit_->connect(R0_.get());
        controlUnit_->connect(TMP_.get());
        controlUnit_->connect(ACC_.get());
        controlUnit_->connect(ALU_.get());
    }

    void TearDown() override 
    {
        controlUnit_->shutdown();
    }     

    // the code under test.
    std::unique_ptr<control::ControlUnit> controlUnit_;

    typedef std::map<std::string, std::shared_ptr<Bus>> BusCollection;
    BusCollection buses_;

    std::unique_ptr<Register> R1_;
    std::unique_ptr<Register> R0_;
    std::unique_ptr<Register> TMP_;
    std::unique_ptr<Register> ACC_;

    std::unique_ptr<ALU> ALU_;
};

TEST_F(ControlUnitTest, x) 
{
    controlUnit_->inject(buses_["system"].get());
    controlUnit_->start();


    std::this_thread::sleep_for(std::chrono::seconds(10));
    

}
