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
        R0_  = std::make_unique<Register>("R0",  buses_["system"], defaultValues_["R0"]);
        R1_  = std::make_unique<Register>("R1",  buses_["system"], defaultValues_["R1"]);
        R2_  = std::make_unique<Register>("R2",  buses_["system"], defaultValues_["R2"]);
        R3_  = std::make_unique<Register>("R3",  buses_["system"], defaultValues_["R3"]);
        TMP_ = std::make_unique<Register>("TMP", buses_["system"], buses_["TMP_out"], defaultValues_["TMP"]);
        ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"], buses_["system"], defaultValues_["ACC"]);
        IAR_ = std::make_unique<Register>("IAR", buses_["system"], defaultValues_["IAR"]);
        IR_  = std::make_unique<Register>("IR",  buses_["system"], buses_["CU_in"], defaultValues_["IR"]);
        MAR_ = std::make_unique<Register>("MAR", buses_["system"], buses_["MAR_out"], defaultValues_["MAR"]);

        controlUnit_->connect(R0_);
        controlUnit_->connect(R1_);
        controlUnit_->connect(R2_);
        controlUnit_->connect(R3_);
        controlUnit_->connect(TMP_);
        controlUnit_->connect(ACC_);
        controlUnit_->connect(IAR_);
        controlUnit_->connect(IR_);
        controlUnit_->connect(MAR_);
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
        buses_["system"] = std::make_unique<Bus>("system", Bus::VERBOSE);
        buses_["ALU_out"] = std::make_unique<Bus>("ALU_out", Bus::VERBOSE);
        buses_["ALU_in_b"] = std::make_unique<Bus>("ALU_in_b", Bus::VERBOSE);
        buses_["CU_in"] = std::make_unique<Bus>("CU_in", Bus::VERBOSE);
        buses_["MAR_out"] = std::make_unique<Bus>("MAR_out", Bus::VERBOSE);
        buses_["TMP_out"] = std::make_unique<Bus>("TMP_out", Bus::VERBOSE);
    }

    void initializeControlUnit()
    {        
        createBuses();

        // Create ALU
        ALU_ = std::make_unique<ALU>(buses_["system"], buses_["ALU_in_b"], buses_["ALU_out"]);

        // Create the control unit
        controlUnit_ = std::make_unique<control::ControlUnit>(buses_["CU_in"], ALU_, Logger::VERBOSE);  

        initializeRegisters();

        // Initialize other controllable items:
        RAM_ = std::make_unique<RAM256>(buses_["system"], MAR_, defaultValues_["RAM256"]);
        BUS1_ = std::make_unique<Bus1>("BUS1",buses_["TMP_out"],buses_["ALU_in_b"]);

        controlUnit_->connect(RAM_);
        controlUnit_->connect(BUS1_);
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

    std::shared_ptr<Register> R1_;
    std::shared_ptr<Register> R0_;
    std::shared_ptr<Register> R2_;
    std::shared_ptr<Register> R3_;
    std::shared_ptr<Register> TMP_;
    std::shared_ptr<Register> ACC_;
    std::shared_ptr<Register> IAR_;
    std::shared_ptr<Register> IR_;
    std::shared_ptr<Register> MAR_;

    std::shared_ptr<RAM256> RAM_;
    std::shared_ptr<ALU> ALU_;
    std::shared_ptr<Bus1> BUS1_;
};

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

/* we need to finish updating IAR: we added 1 to it in step1, but
the answer is still in ACC. It needs to be moved to IAR before the
beginning of the next instruction cycle.  */
TEST_F(ControlUnitTest, step3) 
{
    // Arrange
    defaultValues_["IAR"] = 3;
    initializeControlUnit();

    // Act
    int cycles = 3;
    cycleControlUnit(cycles);

    // Assert
    EXPECT_TRUE(IAR_->output() == 4);
}
