#include "Gates.h"

//
// NANDGate implementation
//

void NANDGate::update(const Bit& a, const Bit& b)
{
    a_ = a;
    b_ = b;
}

Bit NANDGate::output()
{
    if ((a_ == Bit::ONE) && (b_ == Bit::ONE))
    {
        return Bit::ZERO;          
    }

    return Bit::ONE;
}

//
// NOTGate implementation
//

void NOTGate::update(const Bit& a)
{
    a_ = a;
}

Bit NOTGate::output()
{
    if (a_ == Bit::ONE)
    {
        return Bit::ZERO;  
    }

    return  Bit::ONE;
}

//
// ANDGate implementation
//

void ANDGate::update(const Bit& a, const Bit& b)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
}

void ANDGate::update(const Bit& a, const Bit& b, const Bit& c)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
    inputs_.push_back(c);
}

void ANDGate::update(const Bit& a, const Bit& b, const Bit& c, const Bit& d)
{
    inputs_.clear();
    inputs_.push_back(a);
    inputs_.push_back(b);
    inputs_.push_back(c);
    inputs_.push_back(d);
}

void ANDGate::update(const std::vector<Bit>& inputs)
{
    inputs_.clear();
    inputs_ = inputs;
}

Bit ANDGate::output()
{
    size_t n = inputs_.size();
    for (int i = 0; i < n; ++i)
    {
        if (inputs_[i].get() == Bit::ZERO)
        {
            return Bit(Bit::ZERO);
        }
    }

    return Bit(Bit::ONE);
}