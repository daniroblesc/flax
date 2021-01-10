#ifndef REGISTER_H_
#define REGISTER_H_

#include "ByteEnabler.h"
#include "MemoryByte.h"
#include "Bus.h"

class Register 
{
public:

    Register(Bus* bus);
    Register(Bus* inputBus, Bus* outputBus);
    ~Register();

    void enable(const Bit& e = Bit::ONE);  // register's content is written to the bus
    void set(const Bit& s = Bit::ONE);  // register content is refreshed with the bus content

private:

    ByteEnabler enabler_;
    MemoryByte memoryByte_;

    Bus* inputBus_;
    Bus* outputBus_;
};

#endif // REGISTER_H_  