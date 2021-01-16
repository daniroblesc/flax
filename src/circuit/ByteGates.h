#ifndef BYTE_GATES_H_
#define BYTE_GATES_H_

#include "Byte.h"
#include "BitGates.h"
#include <vector>

class Notter
{
public:

    Notter();
    ~Notter();

    void update(const Byte& input);
    Byte output();

private:

    Byte a_;
    std::vector<NOTGate> not_;
};

#endif // BYTE_GATES_H_