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