#include "ByteEnabler.h"

ByteEnabler::ByteEnabler()
{
    gatesCollection_.reserve(Byte::NUM_BITS);
    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        gatesCollection_.push_back(ANDGate());
    }    
}

ByteEnabler::~ByteEnabler()
{}

Byte ByteEnabler::execute(const Byte& I, const Bit& E)
{
    Byte retval;

    for ( int position = 0; position < Byte::NUM_BITS; ++position )
    {
        Bit InputBit = I.get(position);
        Bit OutputBit = gatesCollection_[position].execute(InputBit, E);
        retval.set(OutputBit, position);
    }

    return retval;
}