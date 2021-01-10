
#include "Byte.h"
#include <sstream>      // std::stringstream
#include <string.h>
#include <iostream>      

const int Byte::NUM_BITS = 8;

void Byte::initBitCollection()
{
    bitCollection_.reserve(NUM_BITS);
    for (int n = 0; n < NUM_BITS; ++n)
    {
        bitCollection_.push_back(Bit::ZERO);
    }
}

void Byte::setBitCollection(const int val)
{
    for (int i = 0; i < NUM_BITS; ++i )
    {
        int b = (val >> i) & 1U;
        bitCollection_[i] = static_cast<Bit::e_BitValue>(b);
    }
}

Byte::Byte()
{
    initBitCollection();
}

Byte::Byte(const int val)
{
    initBitCollection();
    setBitCollection(val); 
}

Byte::Byte(const Byte &that)
{
    initBitCollection();
    bitCollection_ = that.bitCollection_;
}
    
Byte& Byte::operator=(const Byte &that)
{
    bitCollection_ = that.bitCollection_;
    return *this;
}

Byte& Byte::operator=(const int &val)
{
    setBitCollection(val);
    return *this;
}
        
bool Byte::operator==(const Byte &that) const
{  
   return (toInt() == that.toInt());
}

bool Byte::operator==(const int &val) const
{
    return (val == toInt());
}

int Byte::toInt() const
{
    int retval = 0;
    for (int i = 0; i < NUM_BITS; ++i )
    {
        if (bitCollection_[i] == Bit::ONE)
        {
            retval |= 1UL << i;
        }
        else
        {
            retval &= ~(1UL << i);
        }    
    }
    
    return retval;
}

Bit Byte::get(const int position) const
{
    if (position >= NUM_BITS)
    {
        return Bit::ZERO;
    }

    return bitCollection_[position];
}

void Byte::set(const int position, Bit value)
{
    bitCollection_[position] = value.get();
}

std::string Byte::toString()
{
    std::stringstream ss;
    for (int i = NUM_BITS; i > 0; --i)
    {
        ss << bitCollection_[i - 1];
    }
    return ss.str();
}
