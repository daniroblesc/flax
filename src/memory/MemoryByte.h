#ifndef MEMORY_BYTE_H_
#define MEMORY_BYTE_H_

#include "MemoryBit.h"
#include "misc/Byte.h"
#include <vector>

class MemoryByte
{
public:
    
    MemoryByte();
    ~MemoryByte();

    // update the input
    void update(const Byte& input);

    // enable/disable 's' bit
    void set(const bool s = true);

    // get the output
    Byte output();

private:

    std::vector<MemoryBit> memoryBitCollection_;
};


#endif // MEMORY_BYTE_H_