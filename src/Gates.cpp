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

