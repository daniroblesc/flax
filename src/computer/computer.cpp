#include "computer.h"

Computer::Computer()
{
}

Computer::~Computer()
{
}

void Computer::initialize()
{
    // Create Buses
    //
    buses_["system"] = std::make_shared<Bus>("system");
    buses_["ALU_out"] = std::make_shared<Bus>("ALU_out");
    buses_["ALU_in_b"] = std::make_shared<Bus>("ALU_in_b");
    buses_["CU_in"] = std::make_shared<Bus>("CU_in");
    buses_["MAR_out"] = std::make_shared<Bus>("MAR_out");

    // Create the control unit
    //
    controlUnit_ = std::make_unique<control::ControlUnit>(buses_["CU_in"].get());

    // Create controllable items
    // 
    R0_  = std::make_unique<Register>("R0", buses_["system"].get());
    R1_  = std::make_unique<Register>("R1", buses_["system"].get());
    R2_  = std::make_unique<Register>("R2", buses_["system"].get());
    R3_  = std::make_unique<Register>("R3", buses_["system"].get());
    TMP_ = std::make_unique<Register>("TMP", buses_["system"].get(), buses_["ALU_in_b"].get());
    ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"].get(), buses_["system"].get());
    IAR_ = std::make_unique<Register>("IAR", buses_["system"].get());
    IR_  = std::make_unique<Register>("IR", buses_["system"].get(), buses_["CU_in"].get());
    MAR_ = std::make_unique<Register>("MAR", buses_["system"].get(), buses_["MAR_out"].get());

    ALU_ = std::make_unique<ALU>(buses_["system"].get(), buses_["ALU_in_b"].get(), buses_["ALU_out"].get());
    RAM_ = std::make_unique<RAM256>(buses_["system"].get(), MAR_.get());

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

void Computer::start()
{
    controlUnit_->start();
}

void Computer::shutdown()
{
    controlUnit_->shutdown();
}