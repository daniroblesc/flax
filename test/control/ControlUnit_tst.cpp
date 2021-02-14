#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "control/ControlUnit.h"
#include "circuit/Bus.h"
#include "components/Register.h"
#include "ALU/ALU.h"
#include "memory/RAM.h"
#include "components/Bus1.h"

#include <memory>
#include <map>
#include <iostream>
#include <chrono>         // std::chrono::seconds

using ::testing::Return;

class ControlUnitTest : public testing::Test 
{
protected:   

    void initializeRegisters()
    {
        R0_  = std::make_unique<Register>("R0",  buses_["system"].get(), defaultValues_["R0"]);
        R1_  = std::make_unique<Register>("R1",  buses_["system"].get(), defaultValues_["R1"]);
        R2_  = std::make_unique<Register>("R2",  buses_["system"].get(), defaultValues_["R2"]);
        R3_  = std::make_unique<Register>("R3",  buses_["system"].get(), defaultValues_["R3"]);
        TMP_ = std::make_unique<Register>("TMP", buses_["system"].get(), buses_["TMP_out"].get(), defaultValues_["TMP"]);
        ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"].get(), buses_["system"].get(), defaultValues_["ACC"]);
        IAR_ = std::make_unique<Register>("IAR", buses_["system"].get(), defaultValues_["IAR"]);
        IR_  = std::make_unique<Register>("IR",  buses_["system"].get(), buses_["CU_in"].get(), defaultValues_["IR"]);
        MAR_ = std::make_unique<Register>("MAR", buses_["system"].get(), buses_["MAR_out"].get(), defaultValues_["MAR"]);

        controlUnit_->connect(R0_.get());
        controlUnit_->connect(R1_.get());
        controlUnit_->connect(R2_.get());
        controlUnit_->connect(R3_.get());
        controlUnit_->connect(TMP_.get());
        controlUnit_->connect(ACC_.get());
        controlUnit_->connect(IAR_.get());
        controlUnit_->connect(IR_.get());
        controlUnit_->connect(MAR_.get());
    }

    void initializeDefaultValues()
    {
        defaultValues_["R0"] = 0;
        defaultValues_["R1"] = 0;
        defaultValues_["R2"] = 0;
        defaultValues_["R3"] = 0;
        defaultValues_["TMP"] = 0;
        defaultValues_["ACC"] = 0;
        defaultValues_["IAR"] = 0;
        defaultValues_["IR"] = 0;
        defaultValues_["MAR"] = 0;
        defaultValues_["RAM256"] = 0;
    }

    void createBuses()
    {
        buses_["system"] = std::make_shared<Bus>("system", Bus::VERBOSE);
        buses_["ALU_out"] = std::make_shared<Bus>("ALU_out", Bus::VERBOSE);
        buses_["ALU_in_b"] = std::make_shared<Bus>("ALU_in_b", Bus::VERBOSE);
        buses_["CU_in"] = std::make_shared<Bus>("CU_in", Bus::VERBOSE);
        buses_["MAR_out"] = std::make_shared<Bus>("MAR_out", Bus::VERBOSE);
        buses_["TMP_out"] = std::make_shared<Bus>("TMP_out", Bus::VERBOSE);
    }

    void initializeControlUnit()
    {        
        createBuses();

        // Create the control unit
        controlUnit_ = std::make_unique<control::ControlUnit>(buses_["CU_in"].get());  

        initializeRegisters();

        // Initialize other controllable items:
        ALU_ = std::make_unique<ALU>(buses_["system"].get(), buses_["ALU_in_b"].get(), buses_["ALU_out"].get());
        RAM_ = std::make_unique<RAM256>(buses_["system"].get(), MAR_.get(), defaultValues_["RAM256"]);
        BUS1_ = std::make_unique<Bus1>("BUS1",buses_["TMP_out"].get(),buses_["ALU_in_b"].get());

        controlUnit_->connect(ALU_.get());
        controlUnit_->connect(RAM_.get());
        controlUnit_->connect(BUS1_.get());
    }

    void SetUp() override 
    {
        initializeDefaultValues();                
    }

    void TearDown() override 
    {}     

    void cycleControlUnit(const int cycles)
    {
        for (int cycle=0; cycle < cycles; ++cycle)
        {
            controlUnit_->extClk(true);
            controlUnit_->extClk(false);
            /*step*/
            controlUnit_->onClkE(true);
            controlUnit_->onClkS(true);
            controlUnit_->onClkS(false);
            controlUnit_->onClkE(false);
        }
    }

    // the code under test.
    std::unique_ptr<control::ControlUnit> controlUnit_;

    typedef std::map<std::string, std::shared_ptr<Bus>> BusCollection;
    BusCollection buses_;

    typedef std::map<std::string, Byte> DefaultValuesCollection;
    DefaultValuesCollection defaultValues_;

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
    std::unique_ptr<Bus1> BUS1_;
};
/*
TEST_F(ControlUnitTest, add) 
{
    controlUnit_->start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_TRUE(R0_->output() == 0x7);
}
*/

/* get the @ in IAR over to MAR */
TEST_F(ControlUnitTest, step1) 
{
    // Arrange
    defaultValues_["IAR"] = 3;
    initializeControlUnit();

    // Act
    int cycles = 1;
    cycleControlUnit(cycles);

    // Assert
    EXPECT_TRUE(MAR_->output() == 3);
    EXPECT_TRUE(ACC_->output() == 4);
}

/* enables the currently selected byte in RAM onto the bus,
   and sets it into IR */
TEST_F(ControlUnitTest, step2) 
{
    // Arrange
    defaultValues_["IAR"] = 3;
    defaultValues_["RAM256"] = 69;
    initializeControlUnit();

    // Act
    int cycles = 2;
    cycleControlUnit(cycles);

    // Assert
    EXPECT_TRUE(IR_->output() == 69);
}