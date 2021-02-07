#include "MemoryBit.h"

void MemoryBit::update(const bool input, const bool s)
{
    wireI_.update(input);
    wireS_.update(s);

    /*G1*/gates[0].update(wireI_.output(), wireS_.output());
    bool a = gates[0].output();

	/*G2*/gates[1].update(a, wireS_.output());
    bool b = gates[1].output();

    bool c = gates[3].output();
	/*G3*/gates[2].update(a, c);

    bool o = gates[2].output();
	/*G4*/gates[3].update(o, b );

    o = gates[2].output();
	wireO_.update(o);
}

bool MemoryBit::output()
{
    return wireO_.output();
}
