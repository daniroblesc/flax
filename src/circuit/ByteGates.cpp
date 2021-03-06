#include "ByteGates.h"
#include <iostream>

//
// NOTter
//

NOTter::NOTter()
{
    not_.resize(Byte::NUM_BITS);
}

void NOTter::update(const Byte& a)
{
    a_ = a;
}

Byte NOTter::output()
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
// ANDer
//

ANDer::ANDer()
{
    and_.resize(Byte::NUM_BITS);
}

ANDer::~ANDer()
{}


void ANDer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte ANDer::output()
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
// ORer
//

ORer::ORer()
{
    or_.resize(Byte::NUM_BITS);
}

ORer::~ORer()
{}


void ORer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte ORer::output()
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
// XORer
//

XORer::XORer()
{
    xor_.resize(Byte::NUM_BITS);
}

XORer::~XORer()
{}


void XORer::update(const Byte& a, const Byte& b)
{
    a_ = a;
    b_ = b;
}

Byte XORer::output()
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
// Zero
//

void Zero::update(const Byte& a)
{
    a_ = a;
}

bool Zero::output()
{
    or_[0].update(a_[0], a_[1]);
    or_[1].update(a_[2], a_[3]);
    or_[2].update(a_[4], a_[5]);
    or_[3].update(a_[6], a_[7]);

    or_[4].update(or_[0].output(), or_[1].output());
    or_[5].update(or_[2].output(), or_[3].output());

    or_[6].update(or_[4].output(), or_[5].output());

    not_.update(or_[6].output());

    return not_.output();
}