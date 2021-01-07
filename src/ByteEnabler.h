#ifndef BYTE_ENABLER_H_
#define BYTE_ENABLER_H_

#include "Gates.h"
#include "Byte.h"

class ByteEnabler
{
public:
    void load(const Byte& input);
    Byte enable();
    
private:
    ANDGate gatesCollection_[8];
    Byte input_;
};

#endif // BYTE_ENABLER_H_  