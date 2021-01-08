#include "Gates.h"

Bit NANDGate::execute(const Bit& a, const Bit& b)
{
    if ((a == Bit::ONE) && (b == Bit::ONE))
    {
        return Bit(Bit::ZERO);  
    }

    return Bit(Bit::ONE);
}

Bit NOTGate::execute(const Bit& a)
{
    if (a == Bit::ONE)
    {
        return Bit(Bit::ZERO);   
    }

    return Bit(Bit::ONE);
}

Bit ANDGate::execute(const Bit& a, const Bit& b)
{
    if ((a == Bit::ONE) &&  (b == Bit::ONE))
    {
        return Bit(Bit::ONE);
    }

    return Bit(Bit::ZERO);
}

Bit ANDGate::execute(const Bit& a, const Bit& b, const Bit& c)
{
    if ((a == Bit::ONE) &&  (b == Bit::ONE) &&  (c == Bit::ONE))
    {
        return Bit(Bit::ONE);
    }

    return Bit(Bit::ZERO);
}

Bit ANDGate::execute(const Bit& a, const Bit& b, const Bit& c, const Bit& d)
{
    if ((a == Bit::ONE) &&  (b == Bit::ONE) &&  (c == Bit::ONE) &&  (d == Bit::ONE))
    {
        return Bit(Bit::ONE);
    }

    return Bit(Bit::ZERO);
}

Bit ANDGate::execute(const std::vector<Bit>& inputs)
{
    size_t n = inputs.size();
    for (int i = 0; i < n; ++i)
    {
        if (inputs[i].get() == Bit::ZERO)
        {
            return Bit(Bit::ZERO);
        }
    }

    return Bit(Bit::ONE);
}