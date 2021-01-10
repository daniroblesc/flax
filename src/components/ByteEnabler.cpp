#include "ByteEnabler.h"

ByteEnabler::ByteEnabler()
{
    gatesCollection_.reserve(Byte::NUM_BITS);
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        gatesCollection_.push_back(ANDGate());
    }
}

ByteEnabler::~ByteEnabler()
{}

void ByteEnabler::update(const Byte& input)
{
    input_ = input;
}

void ByteEnabler::enable(const Bit& e)
{
    e_ = e;
}

Byte ByteEnabler::output()
{
    Byte retval;
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        Bit InputBit = input_.get(n);
        gatesCollection_[n].update(InputBit, e_);
        Bit OutputBit = gatesCollection_[n].output();
        retval.set(n, OutputBit);
    }
    return retval;
}
