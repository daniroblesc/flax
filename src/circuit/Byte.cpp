
#include "Byte.h"
#include <sstream>      // std::stringstream
#include <string.h>
#include <iostream>      

const int Byte::NUM_BITS = 8;

void Byte::initBitCollection()
{
    bitCollection_.resize(NUM_BITS, false);
}

void Byte::setBitCollection(const int val)
{
    for (int i = 0; i < NUM_BITS; ++i )
    {
        int b = (val >> i) & 1U;
        bitCollection_[i] = static_cast<bool>(b);
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
        if (bitCollection_[i] == true)
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

bool Byte::get(const int position) const
{
    if (position >= NUM_BITS)
    {
        return false;
    }

    return bitCollection_[position];
}

void Byte::set(const int position, const bool value)
{
    bitCollection_[position] = value;
}

std::string Byte::toString() const
{
    std::stringstream ss;
    for (int i = NUM_BITS; i > 0; --i)
    {
        ss << bitCollection_[i - 1];
    }
    return ss.str();
}
