#ifndef COMPARATOR_H_
#define COMPARATOR_H_

#include "circuit/Wire.h"
#include "circuit/BitGates.h"
#include "circuit/Byte.h"


/* What the comparator gate does is to find out whether the two bits on the 
   input are exactly equal, and if not, whether the one on the 'a' bus is 
   larger according to the binary number system.
 */
class CompGate
{
public:
    void update(const bool a, const bool b, const bool equal, const bool a_larger);
    void output(bool& c, bool& equal, bool& a_larger);

private:

    Wire a_;    
    Wire b_; 
    Wire c_;
    Wire allBitsAboveAreEqual_;
    Wire aAboveIsLarger_;

    XORGate xor_;
    NOTGate not_;
    ANDGate and_[2];
    ORGate or_;
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




#endif // COMPARATOR_H