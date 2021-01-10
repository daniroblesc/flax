#include "Bit.h"
#include <sstream>      // std::stringstream

Bit::Bit()
{}


Bit::Bit(const e_BitValue val)
{
    value_ = val;
}

Bit::Bit(const Bit &b)
{
    value_ = b.value_;
}

Bit::~Bit()
{}


Bit::e_BitValue Bit::get() const
{
    return value_;
}
    
void Bit::set(const e_BitValue val)
{
    value_ = val;
}

Bit& Bit::operator=(const Bit &a) 
{
    this->value_ = a.value_;
    return *this;  // Return a reference to myself.
}

Bit& Bit::operator=(const e_BitValue &val)
{
    this->value_ = val;
    return *this;  // Return a reference to myself.
}

bool Bit::operator==(const Bit &that) const
{
    return (this->value_ == that.value_);
}

bool Bit::operator==(const e_BitValue &val) const
{
    return (this->value_ == val);
}

std::string Bit::toString() const
{
    std::stringstream ss;
    ss << value_;
    return ss.str();
}