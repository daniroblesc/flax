#ifndef GATES_H_
#define GATES_H_

#include "Bit.h"
#include <vector>

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
    Bit execute(const Bit& a, const Bit& b, const Bit& c);
    Bit execute(const Bit& a, const Bit& b, const Bit& c, const Bit& d);
    Bit execute(const std::vector<Bit>& inputs);

};


#endif // GATES_H_