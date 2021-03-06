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

std::string IControllableUnit::getId() const
{
    return  id_;
}

void IControllableUnit::enable(const bool e)
{}
    
void IControllableUnit::set(const bool s)
{}

//
// ControlGPRegisters implementation
//

ControlGPRegisters::ControlGPRegisters(const std::shared_ptr<Bus>& inputBus, const std::shared_ptr<Wire>& RegA, const std::shared_ptr<Wire>& RegB)
{
    inputBus_ = inputBus;
    RegA_ = RegA;
    RegB_ = RegB;

    for (size_t i = 0; i < 3; ++i)
    {
        RegisterSelectionBlockControl block;
        block.andGates["R0"] = std::make_shared<ANDGate>();
        block.andGates["R1"] = std::make_shared<ANDGate>();
        block.andGates["R2"] = std::make_shared<ANDGate>();
        block.andGates["R3"] = std::make_shared<ANDGate>();
        block_[i] = block;
    }

    orGates_["R0"] = std::make_shared<ORGate>();
    orGates_["R1"] = std::make_shared<ORGate>();
    orGates_["R2"] = std::make_shared<ORGate>();
    orGates_["R3"] = std::make_shared<ORGate>();
}

void ControlGPRegisters::onClkE(const bool clkE)
{
    Byte IR = inputBus_->read();

    block_[1].decoders2x4.update(IR[6], IR[7]);    
    block_[1].andGates["R0"]->update(clkE, RegB_->output(), block_[1].decoders2x4.output(0));
    block_[1].andGates["R1"]->update(clkE, RegB_->output(), block_[1].decoders2x4.output(1));
    block_[1].andGates["R2"]->update(clkE, RegB_->output(), block_[1].decoders2x4.output(2));
    block_[1].andGates["R3"]->update(clkE, RegB_->output(), block_[1].decoders2x4.output(3));

    block_[2].decoders2x4.update(IR[4], IR[5]);    
    block_[2].andGates["R0"]->update(clkE, RegA_->output(), block_[2].decoders2x4.output(0));
    block_[2].andGates["R1"]->update(clkE, RegA_->output(), block_[2].decoders2x4.output(1));
    block_[2].andGates["R2"]->update(clkE, RegA_->output(), block_[2].decoders2x4.output(2));
    block_[2].andGates["R3"]->update(clkE, RegA_->output(), block_[2].decoders2x4.output(3));

    orGates_["R0"]->update( block_[1].andGates["R0"]->output(), block_[2].andGates["R0"]->output() );
    orGates_["R1"]->update( block_[1].andGates["R1"]->output(), block_[2].andGates["R1"]->output() );
    orGates_["R2"]->update( block_[1].andGates["R2"]->output(), block_[2].andGates["R2"]->output() );
    orGates_["R3"]->update( block_[1].andGates["R3"]->output(), block_[2].andGates["R3"]->output() );

    OnEnable.emit_for(controllableUnits_["R0"].e, orGates_["R0"]->output());
    OnEnable.emit_for(controllableUnits_["R1"].e, orGates_["R1"]->output());
    OnEnable.emit_for(controllableUnits_["R2"].e, orGates_["R2"]->output());
    OnEnable.emit_for(controllableUnits_["R3"].e, orGates_["R3"]->output());
}

void ControlGPRegisters::onClkS(const bool clkS)
{
    Byte IR = inputBus_->read();
    block_[0].decoders2x4.update(IR[6], IR[7]);

    block_[0].andGates["R0"]->update(clkS, RegB_->output(), block_[0].decoders2x4.output(0));
    block_[0].andGates["R1"]->update(clkS, RegB_->output(), block_[0].decoders2x4.output(1));
    block_[0].andGates["R2"]->update(clkS, RegB_->output(), block_[0].decoders2x4.output(2));
    block_[0].andGates["R3"]->update(clkS, RegB_->output(), block_[0].decoders2x4.output(3));
        
    OnSet.emit_for(controllableUnits_["R0"].s, block_[0].andGates["R0"]->output());
    OnSet.emit_for(controllableUnits_["R1"].s, block_[0].andGates["R1"]->output());
    OnSet.emit_for(controllableUnits_["R2"].s, block_[0].andGates["R2"]->output());
    OnSet.emit_for(controllableUnits_["R3"].s, block_[0].andGates["R3"]->output());
}

void ControlGPRegisters::connect(const std::shared_ptr<IControllableUnit>& controllableUnit)
{
    std::string id = controllableUnit->getId();
    ControllableUnitCollection::iterator it = controllableUnits_.find(id);
    if (it == controllableUnits_.end())
    {
        ControllableUnitInfo cuInfo;
        cuInfo.ptr = controllableUnit;
        cuInfo.e = OnEnable.connect_member(controllableUnit.get(), &IControllableUnit::enable);
        cuInfo.s = OnSet.connect_member(controllableUnit.get(), &IControllableUnit::set);
        controllableUnits_[id] = cuInfo;

        
    }
}

//
// ControlUnit implementation
//

ControlUnit::ControlUnit(const std::shared_ptr<Bus>& inputBus, const std::shared_ptr<ALU>& ALU, Logger::LogLevel logLevel) : Logger(logLevel)
{
    className_ = __func__;
    inputBus_ = inputBus;
    ALU_ = ALU;
    clock_ = std::make_unique<control::Clock>();    

    RegA_ = std::make_shared<Wire>();
    RegB_ = std::make_shared<Wire>();

    controlGPRegisters_ = std::make_unique<ControlGPRegisters>(inputBus, RegA_, RegB_);    
    OnClkE.connect_member(controlGPRegisters_.get(), &ControlGPRegisters::onClkE);
    OnClkS.connect_member(controlGPRegisters_.get(), &ControlGPRegisters::onClkS);
}

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

bool ControlUnit::isGPRegister(const std::string& id)
{
    bool result = (id == "R0" || id == "R1" || id == "R2" || id == "R3");
    return result;
}

void ControlUnit::connect(const std::shared_ptr<IControllableUnit>& controllableUnit)
{
    std::string id = controllableUnit->getId();
    ControllableUnitCollection::iterator it = controllableUnits_.find(id);
    if (it == controllableUnits_.end())
    {
        ControllableUnitInfo cuInfo;
        cuInfo.ptr = controllableUnit;
        cuInfo.e = OnEnable.connect_member(controllableUnit.get(), &IControllableUnit::enable);
        cuInfo.s = OnSet.connect_member(controllableUnit.get(), &IControllableUnit::set);

        controllableUnits_[id] = cuInfo;
        if (isGPRegister(id))
        {
            controlGPRegisters_->connect(controllableUnit);
        }
        else
        {
            allEnableGates_[id] = std::make_shared<ANDGate>();
            allSetGates_[id] = std::make_shared<ANDGate>();
        }
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
    OnClkE.emit(clkE);

    if (stepper_.output(STEP1))
    {
        allEnableGates_["IAR"]->update(clkE, stepper_.output(STEP1));
        OnEnable.emit_for(controllableUnits_["IAR"].e, allEnableGates_["IAR"]->output());

        OnEnable.emit_for(controllableUnits_["BUS1"].e, stepper_.output(STEP1));

        ALU_->operation(ALU::OP_CODE_ADD);
    }
    else if (stepper_.output(STEP2))
    {
        allEnableGates_["RAM256"]->update(clkE, stepper_.output(STEP2));
        OnEnable.emit_for(controllableUnits_["RAM256"].e, allEnableGates_["RAM256"]->output());

    }
    else if (stepper_.output(STEP3))
    {
        allEnableGates_["ACC"]->update(clkE, stepper_.output(STEP3));
        OnEnable.emit_for(controllableUnits_["ACC"].e, allEnableGates_["ACC"]->output());
    } 
}

void ControlUnit::onClkS(const bool clkS)
{
    logVerbose("%s::%s( clkS: %d STEP%d )\n", className_, __func__, clkS, getCurrentStep());
    OnClkS.emit(clkS);

    if (stepper_.output(STEP1))
    {
        allSetGates_["MAR"]->update(clkS, stepper_.output(STEP1));
        OnSet.emit_for(controllableUnits_["MAR"].s, allSetGates_["MAR"]->output());

        allSetGates_["ACC"]->update(clkS, stepper_.output(STEP1));
        OnSet.emit_for(controllableUnits_["ACC"].s, allSetGates_["ACC"]->output());
    }
    else if (stepper_.output(STEP2))
    {
        allSetGates_["IR"]->update(clkS, stepper_.output(STEP2));
        OnSet.emit_for(controllableUnits_["IR"].s, allSetGates_["IR"]->output());
    }
    else if (stepper_.output(STEP3))
    {
        allSetGates_["IAR"]->update(clkS, stepper_.output(STEP3));
        OnSet.emit_for(controllableUnits_["IAR"].s, allSetGates_["IAR"]->output());
    } 
}

} // namespace