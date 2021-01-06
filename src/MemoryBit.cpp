#include "MemoryBit.h"
#include "Gates.h"

void MemoryBit::save(const bool I)
{
    bool S = true; // set the memory

    NANDGate G1;
    NANDGate G2;
    NANDGate G3;
    NANDGate G4;

    bool a = G1.execute(I, S);
    bool b = G2.execute(a, S);
    bool c = G4.execute(b, O_);
    O_     = G3.execute(a, c);
}

bool MemoryBit::get()
{
    return O_;
}