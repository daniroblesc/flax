#include "Shifter.h"

void RShifter::update(const Byte& a, const bool shiftIn)
{
    a_ = a;
    shiftIn_ = shiftIn;
}

void RShifter::output(Byte &retval, bool &shiftOut)
{
    shiftOut = a_[0];
    retval.set(0, a_[1]);
    retval.set(1, a_[2]);
    retval.set(2, a_[3]);
    retval.set(3, a_[4]);
    retval.set(4, a_[5]);
    retval.set(5, a_[6]);
    retval.set(6, a_[7]);
    retval.set(7, shiftIn_);
}

void LShifter::update(const Byte& a, const bool shiftIn)
{
    a_ = a;
    shiftIn_ = shiftIn;
}

void LShifter::output(Byte &retval, bool &shiftOut)
{
    shiftOut = a_[7];
    retval.set(7, a_[6]);
    retval.set(6, a_[5]);
    retval.set(5, a_[4]);
    retval.set(4, a_[3]);
    retval.set(3, a_[2]);
    retval.set(2, a_[1]);
    retval.set(1, a_[0]);
    retval.set(0, shiftIn_);
}
