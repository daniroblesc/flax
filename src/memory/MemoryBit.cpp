#include "MemoryBit.h"

void MemoryBit::update(const bool input)
{
    input_.update(input);
}

void MemoryBit::set(const bool s)
{
    s_.update(s);
}

bool MemoryBit::output()
{
    G1_.update(input_.output(), s_.output());
    bool a = G1_.output();

    G2_.update(a, s_.output());
    bool b = G2_.output();

    bool o;
    G4_.update(b, o);
    bool c = G4_.output();

    G3_.update(a, c);
    o = G3_.output();

    return o;
}
