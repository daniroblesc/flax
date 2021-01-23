#include "ALU.h"
#include <iostream>

ALU::ALU()
{}

ALU::~ALU()
{}

void ALU::update(const Byte& a, const Byte& b, const bool carryIn, const Wire* op)
{
    a_ = a;
    b_ = b;
    carryIn_ = carryIn;
    op_[0] = op[0];    
    op_[1] = op[1];    
    op_[2] = op[2];    
}

void ALU::output(Byte &c, bool &carryOut, bool& equal, bool& a_larger, bool& zero)
{
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
    enabler_[0].update(XORResult);

    enabler_[1].update(OR_.output());
    
    enabler_[2].update(AND_.output());
    
    enabler_[3].update(NOT_.output());

    Byte SHLResult;
    bool SHLShiftOut;
    SHL_.output(SHLResult, SHLShiftOut);
    enabler_[4].update(SHLResult);

    Byte SHRResult;
    bool SHRShiftOut;
    SHR_.output(SHRResult, SHRShiftOut);
    enabler_[5].update(SHRResult);

    Byte sum;
    bool adderCarryOut;
    ADD_.output(sum, adderCarryOut);
    enabler_[6].update(sum);


    // update decoder input
    decoder_.update(op_[0].output(), op_[1].output(), op_[2].output());

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

            if (i == 4) // SHL_
            {
                and_[0].update(SHLShiftOut, code[i]);
                carryOut = and_[0].output();
            }
            if (i == 5) // SHR_
            {
                and_[1].update(SHRShiftOut, code[i]);
                carryOut = and_[1].output();
            }
            if (i == 6) // ADD_
            {
                and_[2].update(adderCarryOut, code[i]);
                carryOut = and_[2].output();
            }
        }
    }
}