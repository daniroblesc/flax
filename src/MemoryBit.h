#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

#include "Bit.h"

class MemoryBit
{
public:

    void save(const Bit& I);
    Bit get() const;

private:

    Bit O_; // output of the remembered bit
};


#endif // MEMORY_BIT_H_