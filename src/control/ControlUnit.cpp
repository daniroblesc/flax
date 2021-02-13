#include "ControlUnit.h"
#include <iostream>

namespace control
{

//
// IControllableUnit implementation
//

IControllableUnit::IControllableUnit(const std::string& id) 
{
    id_ = id;
}

IControllableUnit::~IControllableUnit()
{}

std::string IControllableUnit::getId() const
{
    return  id_;
}

//
// ControlUnit implementation
//

ControlUnit::ControlUnit(const double clkFreq)
{
    clock_ = std::make_unique<control::Clock>(clkFreq);    
}

ControlUnit::~ControlUnit()
{}

void ControlUnit::start()
{
    clock_->subscribe(this);
    clock_->start();
}

void ControlUnit::shutdown()
{
    clock_->shutdown();
    clock_->unsubscribe(this);
}

void ControlUnit::connect(IControllableUnit* controllableUnit)
{
    std::string id = controllableUnit->getId();
    ControllableUnitCollection::iterator it = controllableUnits_.find(id);
    if (it == controllableUnits_.end())
    {
        controllableUnits_[id] = controllableUnit;
        allEnableGates_[id] = std::make_shared<ANDGate>();
        allSetGates_[id] = std::make_shared<ANDGate>();
    }
}

void ControlUnit::onClk(const bool clk)
{
    stepper_.update(clk);

    if (stepper_.output(STEP1))
    {
        std::cout << "ControlUnit::onClk( STEP1 )\n";
    }
    if (stepper_.output(STEP2))
    {
        std::cout << "ControlUnit::onClk( STEP2 )\n";
    }
    if (stepper_.output(STEP2))
    {
        std::cout << "ControlUnit::onClk( STEP3 )\n";
    }
    if (stepper_.output(STEP4))
    {
        std::cout << "ControlUnit::onClk( STEP4 )\n";
    }
    else if (stepper_.output(STEP5))
    {
        std::cout << "ControlUnit::onClk( STEP5 )\n";
    }
    else if (stepper_.output(STEP6))
    {
        std::cout << "ControlUnit::onClk( STEP6 )\n";
    }
    
}

void ControlUnit::onClkE(const bool clkE)
{
    allEnableGates_["R1"]->update(clkE, stepper_.output(STEP4));
    allEnableGates_["R0"]->update(clkE, stepper_.output(STEP5));
    allEnableGates_["ACC"]->update(clkE, stepper_.output(STEP6));

    sendSignal("R1",  SIG_ENABLE, allEnableGates_["R1"]->output());
    sendSignal("R0",  SIG_ENABLE, allEnableGates_["R0"]->output());
    sendSignal("ACC", SIG_ENABLE, allEnableGates_["ACC"]->output());
    
    if (stepper_.output(STEP5))
    {
        SignalCollection sigValue;
        // ADD = 110
        sigValue.push_back(0);
        sigValue.push_back(1);
        sigValue.push_back(1);
        sendSignal("ALU", SIG_OP, sigValue);
    }
}

void ControlUnit::onClkS(const bool clkS)
{
    allSetGates_["TMP"]->update(clkS, stepper_.output(STEP4));
    allSetGates_["ACC"]->update(clkS, stepper_.output(STEP5));
    allSetGates_["R0"]->update(clkS, stepper_.output(STEP6));

    sendSignal("TMP", SIG_SET, allSetGates_["TMP"]->output());
    sendSignal("ACC", SIG_SET, allSetGates_["ACC"]->output());
    sendSignal("R0",  SIG_SET, allSetGates_["R0"]->output());

    if (stepper_.output(STEP6))
    {
        std::cout << "ControlUnit::onClkS( STEP6 )\n";
       /// std::cout << "Bus content => " << bus_->get().toInt() << "\n";
    }
}

void ControlUnit::sendSignal(const std::string& id, const signalType type, const bool sigValue)
{
    SignalCollection signal;
    signal.push_back(sigValue);

    controllableUnits_[id]->signal(type, signal);
}

void ControlUnit::sendSignal(const std::string& id, const signalType type, const SignalCollection& sigValue)
{
    controllableUnits_[id]->signal(type, sigValue);
}


} // namespace