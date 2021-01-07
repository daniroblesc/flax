#ifndef BYTE_ENABLER_H_
#define BYTE_ENABLER_H_

#include "Gates.h"
#include "Byte.h"
#include <vector>

class ByteEnabler
{
public:

    ByteEnabler();
    ~ByteEnabler();

    Byte execute(const Byte& I, const Bit& E = 1);

private:
    std::vector<ANDGate> gatesCollection_;
};

#endif // BYTE_ENABLER_H_  