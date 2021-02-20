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

ControlUnit::ControlUnit(Bus* inputBus, Logger::LogLevel logLevel) : Logger(logLevel)
{
    className_ = __func__;
    inputBus_ = inputBus;
    clock_ = std::make_unique<control::Clock>();    
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
}

void ControlUnit::extClk(bool clk)
{
    stepper_.update(clk); 
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

    retval++;
    return retval;
}

void ControlUnit::onClkE(const bool clkE)
{  
    logVerbose("%s::%s( clkE: %d STEP%d )\n", className_, __func__, clkE, getCurrentStep());

    if (stepper_.output(STEP1))
    {
        allEnableGates_["IAR"]->update(clkE, stepper_.output(STEP1));
        sendSignal("IAR", SIG_ENABLE, allEnableGates_["IAR"]->output());

        sendSignal("BUS1", SIG_ENABLE, stepper_.output(STEP1));

        SignalCollection sigValue;
        // ADD = 000
        sigValue.push_back(0);
        sigValue.push_back(0);
        sigValue.push_back(0);
        sendSignal("ALU", SIG_OP, sigValue);
    }
    else if (stepper_.output(STEP2))
    {
        allEnableGates_["RAM256"]->update(clkE, stepper_.output(STEP2));
        sendSignal("RAM256", SIG_ENABLE, allEnableGates_["RAM256"]->output());

    }
    else if (stepper_.output(STEP3))
    {
        allEnableGates_["ACC"]->update(clkE, stepper_.output(STEP3));
        sendSignal("ACC", SIG_ENABLE, allEnableGates_["ACC"]->output());
    } 
}

void ControlUnit::onClkS(const bool clkS)
{
    logVerbose("%s::%s( clkS: %d STEP%d )\n", className_, __func__, clkS, getCurrentStep());

    if (stepper_.output(STEP1))
    {
        allSetGates_["MAR"]->update(clkS, stepper_.output(STEP1));
        sendSignal("MAR", SIG_SET, allSetGates_["MAR"]->output());

        allSetGates_["ACC"]->update(clkS, stepper_.output(STEP1));
        sendSignal("ACC", SIG_SET, allSetGates_["ACC"]->output());
    }
    else if (stepper_.output(STEP2))
    {
        allSetGates_["IR"]->update(clkS, stepper_.output(STEP2));
        sendSignal("IR", SIG_SET, allSetGates_["IR"]->output());

    }
    else if (stepper_.output(STEP3))
    {
        allSetGates_["IAR"]->update(clkS, stepper_.output(STEP3));
        sendSignal("IAR", SIG_SET, allSetGates_["IAR"]->output());
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