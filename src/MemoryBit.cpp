#include "MemoryBit.h"
#include "Gates.h"

void MemoryBit::save(const Bit& I)
{
    Bit S(1); // set the memory

    NANDGate G1;
    NANDGate G2;
    NANDGate G3;
    NANDGate G4;

    Bit a = G1.execute(I, S);
    Bit b = G2.execute(a, S);
    Bit c = G4.execute(b, O_);
    O_     = G3.execute(a, c);
}

Bit MemoryBit::get() const
{
    return O_;
}