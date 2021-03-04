#ifndef BYTE_GATES_H_
#define BYTE_GATES_H_

#include "misc/Byte.h"
#include "circuit/Wire.h"
#include "BitGates.h"
#include <vector>

/*! \class NOTter
 *  \brief This device connects two registers with 8 NOT gates.
 *  
 *  Each bit will be changed to its opossite. This operation is used for many 
 *  purposes, the first being in some arithmetic functions.
 *  Another name for a NOT gate is an "inverter", because it makes the opposite
 *  of what you give it, turns it up side down, or inverts it.
 */
class NOTter
{
public:

    NOTter();
    NOTter(const pWireCollection& inputs);
    ~NOTter() = default;

    /** Update device input
     *  @param [in] a value for device input
     */
    void update(const Byte& a);

    /** Generate device output
     *  @return output byte
     */ 
    Byte output();

private:

    Byte a_;    ///< input byte
    std::vector<NOTGate> not_;  ///< NOT gates

    pWireCollection inputs_;
    bool new_ = false;
};

/*! \class ANDer
 *  \brief The ANDer takes two input bytes,and ANDs each bit of those two into a third byte.
 * 
 *  With this, we can AND two bytes together to form a third byte.
 */ 
class ANDer
{
public:

    ANDer();
    ~ANDer();

    /** Update device input
     *  @param [in] a value for device input a
     *  @param [in] b value for device input b
     */
    void update(const Byte& a, const Byte& b);

    /** Generate device output
     *  @return output byte
     */  
    Byte output();

private:

    Byte a_;    ///< input byte a 
    Byte b_;    ///< input byte b
    std::vector<ANDGate> and_;  ///< AND gates
};

/*! \class ORer
 *  \brief The ORer takes two input bytes,and ORs each bit of those two into a third byte.
 * 
 *  With this, we can OR two bytes together to form a third byte.
 */ 
class ORer
{
public:

    ORer();
    ~ORer();

    /** Update device input
     *  @param [in] a value for device input a
     *  @param [in] b value for device input b
     */
    void update(const Byte& a, const Byte& b);

    /** Generate device output
     *  @return output byte
     */  
    Byte output();

private:

    Byte a_;    ///< input byte a 
    Byte b_;    ///< input byte b 
    std::vector<ORGate> or_;    ///< OR gates
};

/*! \class XORer
 *  \brief The XORer takes two input bytes,and XORs each bit of those two into a third byte.
 * 
 *  With this, we can XOR two bytes together to form a third byte.
 */ 
class XORer
{
public:

    XORer();
    ~XORer();

    /** Update device input
     *  @param [in] a value for device input a
     *  @param [in] b value for device input b
     */
    void update(const Byte& a, const Byte& b);

    /** Generate device output
     *  @return output byte
     */ 
    Byte output();

private:

    Byte a_;    ///< input byte a 
    Byte b_;    ///< input byte b 
    std::vector<XORGate> xor_;  ///< XOR gates
};


/*! \class Zero
 *  \brief The Zero takes one byte as input and returns one bit that tell us when 
 *         the content of the byte is all zeros.
 * 
 *  This is a gate combination that takes a whole byte as input, and generates 
 *  only one bit as output. The output bit turns on when all of the bits in the 
 *  byte are off. In other words, the output bit tell us when the content of
 *  the byte is all zeros.
 */
class Zero
{
public:    
    /** Update device input
     *  @param [in] a value for device input
     */
    void update(const Byte& a);

    /** Generate device output
     *  @return the output bit
     */  
    bool output();

private:
    Byte a_;    ///< input byte a
    ORGate or_[7];    ///< OR gates
    NOTGate not_;  ///< NOT gate
};

#endif // BYTE_GATES_H_