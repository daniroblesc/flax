#include "BitGates.h"
#include <iostream>

//
// NANDGate implementation
//

void NANDGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool NANDGate::output()
{
    if ((a_.output()) && (b_.output()))
    {
        return false;          
    }

    return true;
}

//
// NOTGate implementation
//

void NOTGate::update(const bool a)
{
    a_.update(a);
}

bool NOTGate::output()
{
    if (a_.output())
    {
        return false;  
    }

    return true;
}

//
// ANDGate implementation
//

void ANDGate::update(const bool a, const bool b)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
}

void ANDGate::update(const bool a, const bool b, const bool c)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
    inputs_.push_back(c);
}

void ANDGate::update(const bool a, const bool b, const bool c, const bool d)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
    inputs_.push_back(c);
    inputs_.push_back(d);
}

void ANDGate::update(const std::vector<bool>& inputs)
{
    inputs_.clear();
    inputs_ = inputs;
}

bool ANDGate::output()
{
    size_t n = inputs_.size();
    for (int i = 0; i < n; ++i)
    {
        if (inputs_[i] == false)
        {
            return false;
        }
    }

    return true;
}

//
// ORGate implementation
//

void ORGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool ORGate::output()
{
   not_[0].update(a_.output());
   c_.update(not_[0].output());

   not_[1].update(b_.output());
   d_.update(not_[1].output());

   nand_.update(c_.output(), d_.output());
   return nand_.output();
}


//
// XORGate implementation
//

void XORGate::update(const bool a, const bool b)
{
    a_.update(a);
    b_.update(b);
}

bool XORGate::output()
{
    not_[0].update(a_.output());
    c_.update(not_[0].output());

    not_[1].update(b_.output());
    d_.update(not_[1].output());

    nand_[0].update(c_.output(), b_.output());
    e_.update(nand_[0].output());

    nand_[1].update(a_.output(), d_.output());
    f_.update(nand_[1].output());

    nand_[2].update(e_.output(), f_.output());
    return nand_[2].output();
}

//
// AddGate implementation
//

void AddGate::update(const bool a, const bool b, const bool carryIn)
{
    a_.update(a);
    b_.update(b);
    carryIn_.update(carryIn);
}

void AddGate::output(bool &sum, bool &carryOut)
{
    xor_[0].update(a_.output(), b_.output());

    and_[0].update(carryIn_.output(), xor_[0].output());
    and_[1].update(a_.output(), b_.output());

    xor_[1].update(xor_[0].output(), carryIn_.output());
    sum_.update(xor_[1].output());
    sum = sum_.output();

    or_.update(and_[0].output(), and_[1].output());
    carryOut_.update(or_.output());
    carryOut = carryOut_.output();
}
