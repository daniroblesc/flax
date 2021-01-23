
#ifndef ADDER_H_
#define ADDER_H_

#include "misc/Byte.h"
#include "circuit/Wire.h"
#include "circuit/BitGates.h"
#include <vector>

/*! \class AddGate
 *  \brief AddGate is a half adder.
 * 
 *  Half Adder:
 *
 *   a   b  |  sum   carry  
 *   ----------------------
 *   0   0  |   0      0     
 *   1   0  |   1      0     
 *   0   1  |   1      0     
 *   1   1  |   0      1     
 *
 *  'sum' is XOR(a,b)
 *  'carry' is AND(a,b)
 *
 *  A Full Adder adds binary numbers and accounts for values carried in as well
 *  as out.
 *   
 *  A one-bit Full Adder adds three one-bit numbers, often written as A, B and Cin. 
 *
 *  A and B are the operands, and Cin is a bit carried in from the previous 
 *  less-signficant stage.
*/
class AddGate
{
public:
    /** Update device input
     *  @param [in] a value for device input a
     *  @param [in] b value for device input b
     *  @param [in] carryIn bit carried in from the previous less-signficant stage
     */
    void update(const bool a, const bool b, const bool carryIn);

    /** Generate output value
     *  @param [out] sum sum of the two input bits 
     *  @param [out] carryOut bit of the leftmost column will turn on if the sum of the 
     *                        two bits is greater than 2
     */
    void output(bool &sum, bool &carryOut);

private:
    Wire a_;        ///< input wire a   
    Wire b_;        ///< input wire b 
    Wire carryIn_;  ///< bit carried in from the previous less-signficant stage 
    Wire sum_;      ///< sum of the two input bits 
    Wire carryOut_; ///< bit of the leftmost column will turn on if the sum of the two bits is greater than 2 

    XORGate xor_[2]; ///< XOR gates
    ANDGate and_[2]; ///< AND gates
    ORGate or_;      ///< OR gate
};


/*! \class Adder
 *  \brief An Adder adds two bytes together.
 * 
 */
class Adder
{
public:

    Adder();
    ~Adder();

    /** Update device input
     *  @param [in] a value for device input a
     *  @param [in] b value for device input b
     *  @param [in] carryIn bit carried in from the previous less-signficant stage
     */
    void update(const Byte& a, const Byte& b, const bool carryIn);

    /** Generate output value
     *  @param [out] sum sum of the two numbers 
     *  @param [out] carryOut bit of the leftmost column will turn on if the sum of the 
     *                        two numbers is greater than 255
     */
    void output(Byte &sum, bool &carryOut);

private:

    Byte a_;    ///< input byte a 
    Byte b_;    ///< input byte b 
    bool carryIn_;  ///< bit carried in from the previous less-signficant stage
    bool carryOut_; ///< bit of the leftmost column will turn on if the sum of the two numbers is greater than 255
    std::vector<AddGate> add_;  ///< ADD gates
};

#endif // ADDER_H_