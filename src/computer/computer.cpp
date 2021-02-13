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

    // Create controllable items
    // 
    R1_  = std::make_unique<Register>("R1", buses_["system"].get());
    R0_  = std::make_unique<Register>("R0", buses_["system"].get());
    TMP_ = std::make_unique<Register>("TMP", buses_["system"].get());
    ACC_ = std::make_unique<Register>("ACC", buses_["ALU_out"].get(), buses_["system"].get());
    ALU_ = std::make_unique<ALU>(buses_["system"].get(), buses_["ALU_in_b"].get(), buses_["ALU_out"].get());

    // Connect items to the bus

    // Connect items to the Control Unit
    //
    controlUnit_.connect(R1_.get());
    controlUnit_.connect(R0_.get());
    controlUnit_.connect(TMP_.get());
    controlUnit_.connect(ACC_.get());
    controlUnit_.connect(ALU_.get());
}

void Computer::start()
{
    controlUnit_.start();
}

void Computer::shutdown()
{
    controlUnit_.shutdown();
}