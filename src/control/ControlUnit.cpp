#include "ControlUnit.h"
#include <iostream>
#include <assert.h>

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
/*
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
*/    
}

int ControlUnit::getCurrentStep()
{
    int n = 0;
    int retval = 0;
    for (size_t i = 0; i < 7; ++i)
    {
        if (stepper_.output(i))
        {
            ++n;
            retval = i;
        }
    }
    assert(n==1);
    return retval;
}


void ControlUnit::onClkE(const bool clkE)
{
    std::cout << "ControlUnit::onClkE( " << clkE << " step " << getCurrentStep() << ")\n";

    allEnableGates_["R1"]->update(clkE, stepper_.output(STEP4));
    sendSignal("R1",  SIG_ENABLE, allEnableGates_["R1"]->output());

    allEnableGates_["R0"]->update(clkE, stepper_.output(STEP5));
    allEnableGates_["TMP"]->update(clkE, stepper_.output(STEP5));
    sendSignal("R0",  SIG_ENABLE, allEnableGates_["R0"]->output());
    sendSignal("TMP",  SIG_ENABLE, allEnableGates_["TMP"]->output());
    if (stepper_.output(STEP5))
    {
        SignalCollection sigValue;
        // ADD = 110
        sigValue.push_back(0);
        sigValue.push_back(1);
        sigValue.push_back(1);
        sendSignal("ALU", SIG_OP, sigValue);
    }

    allEnableGates_["ACC"]->update(clkE, stepper_.output(STEP6));
    sendSignal("ACC", SIG_ENABLE, allEnableGates_["ACC"]->output());
}

void ControlUnit::onClkS(const bool clkS)
{
    std::cout << "ControlUnit::onClkS( " << clkS << " step " << getCurrentStep() << ")\n";

    allSetGates_["TMP"]->update(clkS, stepper_.output(STEP4));
    sendSignal("TMP", SIG_SET, allSetGates_["TMP"]->output());

    allSetGates_["ACC"]->update(clkS, stepper_.output(STEP5));
    sendSignal("ACC", SIG_SET, allSetGates_["ACC"]->output());

    allSetGates_["R0"]->update(clkS, stepper_.output(STEP6));
    sendSignal("R0",  SIG_SET, allSetGates_["R0"]->output());
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