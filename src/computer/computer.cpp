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
    buses_["system"] = std::make_unique<Bus>("system");
    buses_["ALU_out"] = std::make_unique<Bus>("ALU_out");
    buses_["ALU_in_b"] = std::make_unique<Bus>("ALU_in_b");
    buses_["CU_in"] = std::make_unique<Bus>("CU_in");
    buses_["MAR_out"] = std::make_unique<Bus>("MAR_out");

    // Create the control unit
    //
    controlUnit_ = std::make_unique<control::ControlUnit>(buses_["CU_in"]);

    // Create controllable items
    // 
    R0_  = std::make_unique<Register>("R0", buses_["system"]);
    R1_  = std::make_unique<Register>("R1", buses_["system"]);
    R2_  = std::make_unique<Register>("R2", buses_["system"]);
    R3_  = std::make_unique<Register>("R3", buses_["system"]);
    TMP_ = std::make_unique<Register>("TMP", buses_["system"], buses_["ALU_in_b"]);
    ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"], buses_["system"]);
    IAR_ = std::make_unique<Register>("IAR", buses_["system"]);
    IR_  = std::make_unique<Register>("IR", buses_["system"], buses_["CU_in"]);
    MAR_ = std::make_unique<Register>("MAR", buses_["system"], buses_["MAR_out"]);

    ALU_ = std::make_unique<ALU>(buses_["system"], buses_["ALU_in_b"], buses_["ALU_out"]);
    RAM_ = std::make_unique<RAM256>(buses_["system"], MAR_);

    // Connect items to the Control Unit
    //
    controlUnit_->connect(R0_);
    controlUnit_->connect(R1_);
    controlUnit_->connect(R2_);
    controlUnit_->connect(R3_);    
    controlUnit_->connect(TMP_);
    controlUnit_->connect(ACC_);
    controlUnit_->connect(IAR_);
    controlUnit_->connect(IR_);
    controlUnit_->connect(MAR_);

    controlUnit_->connect(ALU_);
    controlUnit_->connect(RAM_);
}

void Computer::start()
{
    controlUnit_->start();
}

void Computer::shutdown()
{
    controlUnit_->shutdown();
}