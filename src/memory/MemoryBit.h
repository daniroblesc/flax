#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

#include "circuit/Gates.h"

class MemoryBit
{
public:

    // update the input
    void update(const bool input);

    // enable/disable 's' bit
    void set(const bool s = true);

    // get the output
    bool output();

private:

    Wire input_;
    Wire s_;

    NANDGate G1_;
    NANDGate G2_;
    NANDGate G3_;
    NANDGate G4_;
};


#endif // MEMORY_BIT_H_