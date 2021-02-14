#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "control/ControlUnit.h"
#include "circuit/Bus.h"
#include "components/Register.h"
#include "ALU/ALU.h"
#include "memory/RAM.h"

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
        buses_["CU_in"] = std::make_shared<Bus>("CU_in", Bus::VERBOSE);
        buses_["MAR_out"] = std::make_shared<Bus>("MAR_out", Bus::VERBOSE);

        // Create controllable items
        // 
        R0_  = std::make_unique<Register>("R0", buses_["system"].get(), 0x4);
        R1_  = std::make_unique<Register>("R1", buses_["system"].get(), 0x3);
        R2_  = std::make_unique<Register>("R2", buses_["system"].get());
        R3_  = std::make_unique<Register>("R3", buses_["system"].get());
        TMP_ = std::make_unique<Register>("TMP", buses_["system"].get(), buses_["ALU_in_b"].get());
        ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"].get(), buses_["system"].get());
        IAR_ = std::make_unique<Register>("IAR", buses_["system"].get());
        IR_  = std::make_unique<Register>("IR", buses_["system"].get(), buses_["CU_in"].get());
        MAR_ = std::make_unique<Register>("MAR", buses_["system"].get(), buses_["MAR_out"].get());

        ALU_ = std::make_unique<ALU>(buses_["system"].get(), buses_["ALU_in_b"].get(), buses_["ALU_out"].get());
        RAM_ = std::make_unique<RAM256>(buses_["system"].get(), MAR_.get());

        // Create the control unit
        //
        controlUnit_ = std::make_unique<control::ControlUnit>(buses_["CU_in"].get(), 10);    

        // Connect items to the Control Unit
        //
        controlUnit_->connect(R0_.get());
        controlUnit_->connect(R1_.get());
        controlUnit_->connect(R2_.get());
        controlUnit_->connect(R3_.get());
        controlUnit_->connect(TMP_.get());
        controlUnit_->connect(ACC_.get());
        controlUnit_->connect(IAR_.get());
        controlUnit_->connect(IR_.get());
        controlUnit_->connect(MAR_.get());

        controlUnit_->connect(ALU_.get());
        controlUnit_->connect(RAM_.get());
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
    std::unique_ptr<Register> R2_;
    std::unique_ptr<Register> R3_;
    std::unique_ptr<Register> TMP_;
    std::unique_ptr<Register> ACC_;
    std::unique_ptr<Register> IAR_;
    std::unique_ptr<Register> IR_;
    std::unique_ptr<Register> MAR_;

    std::unique_ptr<RAM256> RAM_;
    std::unique_ptr<ALU> ALU_;
};

TEST_F(ControlUnitTest, add) 
{
    controlUnit_->start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_TRUE(R0_->output() == 0x7);
}
