#ifndef BYTE_ENABLER_H_
#define BYTE_ENABLER_H_

#include "circuit/Gates.h"
#include "circuit/Byte.h"
#include <vector>

class ByteEnabler
{
public:
    
    ByteEnabler();
    ~ByteEnabler();


    // update the input
    void update(const Byte& input);
    
    // enable/disable 'e' bit
    void enable(const Bit& e = Bit::ONE);

    // get the output
    Byte output();
    
private:
    std::vector< ANDGate > gatesCollection_;
    Byte input_;
    Bit e_;
};

#endif // BYTE_ENABLER_H_  