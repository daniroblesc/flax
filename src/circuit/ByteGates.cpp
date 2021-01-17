#include "ByteGates.h"
#include <iostream>

//
// Notter
//

Notter::Notter()
{
    not_.resize(Byte::NUM_BITS);
}

Notter::~Notter()
{}


void Notter::update(const Byte& a)
{
    a_ = a;
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

//
// Ander
//

Ander::Ander()
{
    and_.resize(Byte::NUM_BITS);
}

Ander::~Ander()
{}


void Ander::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte Ander::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        and_[i].update(a_[i], b_[i]);
        output.set(i, and_[i].output());
    }

    return output;
}


//
// Orer
//

Orer::Orer()
{
    or_.resize(Byte::NUM_BITS);
}

Orer::~Orer()
{}


void Orer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte Orer::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        or_[i].update(a_[i], b_[i]);
        output.set(i, or_[i].output());
    }

    return output;
}


//
// XOrer
//

XOrer::XOrer()
{
    xor_.resize(Byte::NUM_BITS);
}

XOrer::~XOrer()
{}


void XOrer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte XOrer::output()
{
    Byte output;
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        xor_[i].update(a_[i], b_[i]);
        output.set(i, xor_[i].output());
    }

    return output;
}


//
// Z
//

void Z::update(const Byte& a)
{
    a_ = a;
}

bool Z::output()
{
    for ( int i = 0; i < Byte::NUM_BITS; ++i )
    {
        if (a_[i])
        {
            return false;
        }
    }

    return true;
}