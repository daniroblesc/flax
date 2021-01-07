#ifndef REGISTER_H_
#define REGISTER_H_

#include "ByteEnabler.h"
#include "MemoryByte.h"

class Register
{
public:

    void write(const Byte& input);
    Byte read();

private:

    ByteEnabler enabler_;
    MemoryByte memoryByte_;
};

#endif // REGISTER_H_  