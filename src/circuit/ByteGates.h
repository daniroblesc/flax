#ifndef BYTE_GATES_H_
#define BYTE_GATES_H_

#include "Byte.h"
#include "BitGates.h"
#include <vector>

//
// Notter
//
class Notter
{
public:

    Notter();
    ~Notter();

    void update(const Byte& a);
    Byte output();

private:

    Byte a_;
    std::vector<NOTGate> not_;
};

//
// Ander
//
class Ander
{
public:

    Ander();
    ~Ander();

    void update(const Byte& a, const Byte& b);
    Byte output();

private:

    Byte a_;
    Byte b_;
    std::vector<ANDGate> and_;
};

//
// Orer
//
class Orer
{
public:

    Orer();
    ~Orer();

    void update(const Byte& a, const Byte& b);
    Byte output();

private:

    Byte a_;
    Byte b_;
    std::vector<ORGate> or_;
};

//
// XOrer
//
class XOrer
{
public:

    XOrer();
    ~XOrer();

    void update(const Byte& a, const Byte& b);
    Byte output();

private:

    Byte a_;
    Byte b_;
    std::vector<XORGate> xor_;
};

//
// Adder
//
class Adder
{
public:

    Adder();
    ~Adder();

    void update(const Byte& a, const Byte& b, const bool carryIn);
    void output(Byte &sum, bool &carryOut);

private:

    Byte a_;
    Byte b_;
    bool carryIn_; 
    bool carryOut_; 
    std::vector<AddGate> add_;
};

//
// Comparator
//   we have two bits that pass down from the highest bit position to the lowest

class Comparator
{
public:

    Comparator();
    ~Comparator();

    void update(const Byte& a, const Byte& b);
    void output(Byte& c, bool& equal, bool& a_larger);

private:
    std::vector<CompGate> cmp_;

    Byte a_;
    Byte b_;
    bool equal_ = true;
    bool a_larger_ = false;
};

//
// Z: The output bit turns on when all of the bits in the byte are off
//

class Z
{
public:    
    void update(const Byte& a);
    bool output();

private:
    Byte a_;
};

#endif // BYTE_GATES_H_