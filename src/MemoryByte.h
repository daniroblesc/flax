#ifndef MEMORY_BYTE_H_
#define MEMORY_BYTE_H_

#include "MemoryBit.h"
#include "Byte.h"
#include <vector>

class MemoryByte
{
public:

    MemoryByte();
    ~MemoryByte();

    void save(const Byte& I);
    Byte get() const;

private:
    std::vector<MemoryBit> memoryBitCollection_;
};


#endif // MEMORY_BYTE_H_