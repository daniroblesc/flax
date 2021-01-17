#ifndef SHIFTER_H_
#define SHIFTER_H_

#include "circuit/Byte.h"
 
/*
    0100 0010 -> 0010 0001
*/
class RShifter
{
public:


    void update(const Byte& a, const bool shiftIn);
    void output(Byte &retval, bool &shiftOut);

private:
    Byte a_;
    bool shiftIn_;
};

/*
    0100 0010 -> 1000 0100
*/
class LShifter
{
public:


    void update(const Byte& a, const bool shiftIn);
    void output(Byte &retval, bool &shiftOut);

private:
    Byte a_;
    bool shiftIn_;
};

#endif // SHIFTER_H_