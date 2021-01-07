#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

#include "Bit.h"

class MemoryBit
{
public:

    void write(const Bit& I);
    Bit read() const;

private:

    Bit O_; // output of the remembered bit
};


#endif // MEMORY_BIT_H_