#include "ByteGates.h"

Notter::Notter()
{
    not_.resize(Byte::NUM_BITS);
}

Notter::~Notter()
{}


void Notter::update(const Byte& input)
{
    a_ = input;
}

Byte Notter::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        not_[i].update(a_[i]);
        output.set(i, not_[i].output());
    }

    return output;
}
