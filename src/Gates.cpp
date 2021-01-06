#include "Gates.h"

Bit NANDGate::execute(const Bit& a, const Bit& b)
{
    if ((a == 1) &&  (b == 1))
    {
        return Bit(0);  
    }

    return Bit(1);
}

Bit NOTGate::execute(const Bit& a)
{
    if (a == true)
    {
        return Bit(0);   
    }

    return Bit(1);
}

Bit ANDGate::execute(const Bit& a, const Bit& b)
{
    if ((a == 1) &&  (b == 1))
    {
        return Bit(1);
    }

    return Bit(0);    
}

