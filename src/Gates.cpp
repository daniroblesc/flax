#include "Gates.h"

bool NANDGate::execute(const bool a, const bool b)
{
    if ((a == true) &&  (b == true))
    {
        return false;
    }

    return true;
}

bool NOTGate::execute(const bool a)
{
    if (a == true)
    {
        return false;
    }

    return true;
}

bool ANDGate::execute(const bool a, const bool b)
{
    if ((a == true) &&  (b == true))
    {
        return true;
    }

    return false;    
}

