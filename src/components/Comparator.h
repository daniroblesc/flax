#ifndef COMPARATOR_H_
#define COMPARATOR_H_

#include "circuit/Wire.h"
#include "circuit/BitGates.h"
#include "misc/Byte.h"

/*! \class CompGate
 *  \brief Bit comparator gate class.
 *
 *  What the comparator gate does is to find out whether the two bits on the 
 *  input are exactly equal, and if not, whether the one on the 'a' bus is 
 *  larger according to the binary number system.
 */
class CompGate
{
public:
    /** Update gate's inputs
     *  @param [in] a value for input 'a'
     *  @param [in] b value for input 'b'
     *  @param [in] equal equal bit carried in from the previous less-signficant stage
     *  @param [in] a_larger a_larger bit carried in from the previous less-signficant stage
     */
    void update(const bool a, const bool b, const bool equal, const bool a_larger);

    /** Generate gate outputs
     *  @param [out] c is set to true if inputs bit are not equal, otherwise is set to false
     *  @param [out] equal is set to true if inputs bit are equal, otherwise is set to false
     *  @param [out] a_larger is set to true if 'a' bit is larger than 'b' bit
     */ 
    void output(bool& c, bool& equal, bool& a_larger);

private:

    Wire a_;    ///< input wire a
    Wire b_;    ///< input wire b
    Wire c_;    ///< output wire c
    Wire allBitsAboveAreEqual_; ///< equal bit carried in from the previous less-signficant stage
    Wire aAboveIsLarger_; ///< a_larger bit carried in from the previous less-signficant stage

    XORGate xor_;   ///< XOR gate
    NOTGate not_;   ///< NOT gate
    ANDGate and_[2];    ///< AND gates
    ORGate or_; ///< OR gate
};


/*! \class Comparator
 *  \brief The Comparator class compares two bytes.
 */
class Comparator
{
public:

    Comparator();
    ~Comparator();

    /** Update device inputs
     *  @param [in] a value for input 'a'
     *  @param [in] b value for input 'b'
     */
    void update(const Byte& a, const Byte& b);

    /** Generate device outputs
     *  @param [out] c a bit is set to true if inputs bit are not equal, otherwise is set to false
     *  @param [out] equal is set to true if inputs bit are equal, otherwise is set to false
     *  @param [out] a_larger is set to true if 'a' is larger than 'b' 
     */    
    void output(Byte& c, bool& equal, bool& a_larger);

private:
    std::vector<CompGate> cmp_; ///< CompGate gates

    Byte a_;    ///< input byte
    Byte b_;    ///< input byte
    bool equal_ = true; ///< true if input bytes are equal, otherwise is set to false
    bool a_larger_ = false; ///< is set to true if 'a' byte is larger than 'b' byte
};




#endif // COMPARATOR_H