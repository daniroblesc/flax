#include "ALU.h"
#include <iostream>
#include <assert.h>     /* assert */

ALU::ALU(const std::shared_ptr<Bus>& inputBusA, const std::shared_ptr<Bus>& inputBusB, const std::shared_ptr<Bus>& outputBus) : 
    control::IControllableUnit("ALU"),
    IBusNode("ALU")
{
    inputBusA_ = inputBusA;
    inputBusB_ = inputBusB;
    outputBus_ = outputBus;    
    inputBusA_->subscribe(this);
    inputBusB_->subscribe(this);
    outputBus_->subscribe(this);
}

void ALU::signal(const control::signalType type, const control::SignalCollection& value)
{
    assert(value.size()==3);
    
    switch (type)
    {
    case control::SIG_OP:
    {
        bool carryIn = false;
        Byte b;
        b.set(0, value[0]);  
        b.set(1, value[1]);  
        b.set(2, value[2]);  
        OpCode op = static_cast<OpCode>(b.toInt());
        bool carryOut, equal, a_larger, zero;
        update(carryIn, op, carryOut, equal, a_larger, zero);
    }
    break;

    default:
        assert(0);
        break;
    };
}

void ALU::update(const bool carryIn, const OpCode op,bool &carryOut, bool& equal, bool& a_larger, bool& zero)
{
    update(carryIn, op);
    output(carryOut, equal, a_larger, zero);
}

void ALU::update(const bool carryIn, const OpCode op)
{
    a_ = inputBusA_->read(this);
    b_ = inputBusB_->read(this);
    carryIn_ = carryIn;
    op_ = op;    
}

void ALU::output(bool &carryOut, bool& equal, bool& a_larger, bool& zero)
{
    Byte c;

    // Update inputs to the devices
    XOR_.update(a_, b_);
    OR_.update(a_, b_);
    AND_.update(a_, b_);
    NOT_.update(a_);
    SHL_.update(a_, carryIn_);
    SHR_.update(a_, carryIn_);
    ADD_.update(a_,b_,carryIn_);

    // Devices generates its outputs and update Enablers inputs
    Byte XORResult;
    XOR_.output(XORResult, equal, a_larger);
    enabler_[OP_CODE_XOR].update(XORResult);

    enabler_[OP_CODE_OR].update(OR_.output());
    
    enabler_[OP_CODE_AND].update(AND_.output());
    
    enabler_[OP_CODE_NOT].update(NOT_.output());

    Byte SHLResult;
    bool SHLShiftOut;
    SHL_.output(SHLResult, SHLShiftOut);
    enabler_[OP_CODE_SHL].update(SHLResult);

    Byte SHRResult;
    bool SHRShiftOut;
    SHR_.output(SHRResult, SHRShiftOut);
    enabler_[OP_CODE_SHR].update(SHRResult);

    Byte sum;
    bool adderCarryOut;
    ADD_.output(sum, adderCarryOut);
    enabler_[OP_CODE_ADD].update(sum);


    // update decoder input
    switch (op_)
    {
        case OP_CODE_ADD: // 000
        decoder_.update(false, false, false);
        break;
        case OP_CODE_SHR: // 001
        decoder_.update(true, false, false);
        break;
        case OP_CODE_SHL: // 010
        decoder_.update(false, true, false);
        break;
        case OP_CODE_NOT: // 011
        decoder_.update(true, true, false);
        break;
        case OP_CODE_AND: // 100
        decoder_.update(false, false, true);
        break;
        case OP_CODE_OR: // 101
        decoder_.update(true, false, true);
        break;
        case OP_CODE_XOR: // 110
        case OP_CODE_CMP: // 111
        decoder_.update(false, true, true);
        break;
    }
    

    // get decoder output
    std::vector<bool> code = decoder_.output();

    // select operation & generate outputs
    for (int i = 0; i < code.size(); ++i)
    {
        enabler_[i].enable(code[i]);
        if (code[i])
        {            
            c = enabler_[i].output();
            z_.update(c);
            zero = z_.output();

            if (i == OP_CODE_SHL) // SHL_
            {
                and_[0].update(SHLShiftOut, code[i]);
                carryOut = and_[0].output();
            }
            if (i == OP_CODE_SHR) // SHR_
            {
                and_[1].update(SHRShiftOut, code[i]);
                carryOut = and_[1].output();
            }
            if (i == OP_CODE_ADD) // ADD_
            {
                and_[2].update(adderCarryOut, code[i]);
                carryOut = and_[2].output();
            }
        }
    }

    outputBus_->write(this, c);
}