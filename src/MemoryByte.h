#ifndef MEMORY_BYTE_H_
#define MEMORY_BYTE_H_

#include "MemoryBit.h"
#include "Byte.h"

class MemoryByte
{
public:
    void write(const Byte& I);
    Byte read() const;

private:
    MemoryBit memoryBitCollection_[8];
};


#endif // MEMORY_BYTE_H_