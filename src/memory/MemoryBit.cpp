#include "MemoryBit.h"

void MemoryBit::update(const Bit& input)
{
    input_ = input;
}

void MemoryBit::set(const Bit& s)
{
    s_ = s;
}

Bit MemoryBit::output()
{
    G1_.update(input_, s_);
    Bit a = G1_.output();

    G2_.update(a, s_);
    Bit b = G2_.output();

    Bit o;
    G4_.update(b, o);
    Bit c = G4_.output();

    G3_.update(a, c);
    o = G3_.output();

    return o;
}
