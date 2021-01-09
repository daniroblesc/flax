#include "MemoryByte.h"

MemoryByte::MemoryByte()
{
    memoryBitCollection_.reserve(Byte::NUM_BITS);
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        memoryBitCollection_.push_back(MemoryBit());
    }
}

MemoryByte::~MemoryByte()
{
}

void MemoryByte::update(const Byte& input)
{
    for ( int n = 0; n < Byte::NUM_BITS; ++n )
    {
        Bit inputBit = input.get(n);
        memoryBitCollection_[n].update(inputBit);
    }
}

void MemoryByte::set(const Bit& s)
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
        Bit outputBit = memoryBitCollection_[n].output();
        output.set(n, outputBit);
    }

    return output;    
}
