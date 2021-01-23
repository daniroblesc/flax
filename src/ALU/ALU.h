#ifndef ALU_H_
#define ALU_H_

#include "circuit/ByteGates.h"
#include "circuit/Wire.h"
#include "components/Decoder.h"
#include "components/Shifter.h"
#include "components/Enabler.h"
#include "components/Comparator.h"
#include "components/Adder.h"

class ALU
{
public:

    ALU();
    ~ALU();

    void update(const Byte& a, const Byte& b, const bool carryIn, const Wire* op);
    void output(Byte &c, bool &carryOut, bool& equal, bool& a_larger, bool& zero);

private:
    Comparator XOR_;
    ORer OR_; 
    ANDer AND_;
    NOTter NOT_;
    LShifter SHL_;
    RShifter SHR_;
    Adder ADD_;
    Enabler enabler_[7];
    ANDGate and_[3];
    Zero z_;
    Decoder3X8 decoder_;

    // inputs
    //
    Byte a_;
    Byte b_;
    bool carryIn_;
    Wire op_[3];
};

#endif // ALU_H_