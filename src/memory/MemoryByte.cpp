#include "MemoryByte.h"

MemoryByte::MemoryByte()
{
    memoryBitCollection_.resize(Byte::NUM_BITS);
}

MemoryByte::~MemoryByte()
{
}

void MemoryByte::update(const Byte& input)
{
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        bool inputBit = input[n];
        memoryBitCollection_[n].update(inputBit);
    }
}

void MemoryByte::set(const bool s)
{
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        memoryBitCollection_[n].set(s);
    }
}

Byte MemoryByte::output()
{
    Byte output;

    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        bool outputBit = memoryBitCollection_[n].output();
        output.set(n, outputBit);
    }

    return output;    
}
