#ifndef GATES_H_
#define GATES_H_

#include "Bit.h"
#include <vector>

class NANDGate
{
public:
    void update(const Bit& a, const Bit& b);
    Bit output();
    
private:
    Bit a_;    
    Bit b_;    
};

class NOTGate
{
public:
    void update(const Bit& a);
    Bit output();

private:
    Bit a_;    
};

class ANDGate
{
public:
    void update(const Bit& a, const Bit& b);
    void update(const Bit& a, const Bit& b, const Bit& c);
    void update(const Bit& a, const Bit& b, const Bit& c, const Bit& d);
    void update(const std::vector<Bit>& inputs);

    Bit output();

private:
    std::vector<Bit> inputs_;
};


#endif // GATES_H_