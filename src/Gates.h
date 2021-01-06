#ifndef GATES_H_
#define GATES_H_

#include "Bit.h"

class NANDGate
{
public:
    Bit execute(const Bit& a, const Bit& b);
};

class NOTGate
{
public:
    Bit execute(const Bit& a);
};

class ANDGate
{
public:
    Bit execute(const Bit& a, const Bit& b);
};


#endif // GATES_H_