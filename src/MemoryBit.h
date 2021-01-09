#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

#include "Bit.h"
#include "Gates.h"

class MemoryBit
{
public:

    // update the input
    void update(const Bit& input);

    // enable/disable 's' bit
    void set(const Bit& s = Bit::ONE);

    // get the output
    Bit output();

private:

    Bit input_;
    Bit s_;

    NANDGate G1_;
    NANDGate G2_;
    NANDGate G3_;
    NANDGate G4_;
};


#endif // MEMORY_BIT_H_