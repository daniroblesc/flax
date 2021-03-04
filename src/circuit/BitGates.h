#ifndef BIT_GATES_H_
#define BIT_GATES_H_

#include "Wire.h"
#include <vector>

/*! \class NANDGate
 *  \brief NAND gate class.
 *
 *  NAND gate (NOT-AND) is a logic gate which produces an output which is false
 *  only if all its inputs are true:
 *
 *       a   b  |   c
 *       ---------------
 *       0   0  |   1  
 *       1   0  |   1  
 *       0   1  |   1    
 *       1   1  |   0   
 */
class NANDGate
{
public:
    /** Update gate's inputs
     *  @param [in] a value for input a
     *  @param [in] b value for input b
     */
    void update(const bool a, const bool b);

    /** Generate output value
     *  @return output value
     */  
    bool output();
    
private:
    Wire a_;    ///< input wire a
    Wire b_;    ///< input wire b
};

/*! \class NOTGate
 *  \brief NOT gate class.
 * 
 *  Inverter or NOT gate is a logic gate which implements logical negation:
 *
 *   a   |   not a
 *   -------------
 *   0   |    1  
 *   1   |    0  
 */
class NOTGate
{
public:

    NOTGate();
    NOTGate(const pWire& a);

    ~NOTGate() = default;

    /** Update gate's inputs
     *  @param [in] a value for input a
     */
    void update(const bool a);

    /** Generate output value
     *  @return output value
     */    
    bool output();

private:
    Wire a_;    ///< input wire a   
    bool new_ = false;

    pWire input_;
};

/*! \class ANDGate
 *  \brief AND gate class.
 * 
 *  The AND gate is a basic digital logic gate that implements logical 
 *  conjunction - it behaves according to the following truth table:
 *
 *   a   b  |   c
 *   ---------------
 *   0   0  |   0  
 *   1   0  |   0  
 *   0   1  |   0   
 *   1   1  |   1   
 */
class ANDGate
{
public:
    /** Update gate's inputs
     *  @param [in] a value for input a
     *  @param [in] b value for input b
     */
    void update(const bool a, const bool b);

    /** Update gate's inputs
     *  @param [in] a value for input a
     *  @param [in] b value for input b
     *  @param [in] c value for input c
     */
    void update(const bool a, const bool b, const bool c);

    /** Update gate's inputs
     *  @param [in] a value for input a
     *  @param [in] b value for input b
     *  @param [in] c value for input c
     *  @param [in] d value for input d
     */
    void update(const bool a, const bool b, const bool c, const bool d);

    /** Generate output value
     *  @return output value
     */  
    bool output();

private:
   Wire a_;    ///< input wire a 
   Wire b_;    ///< input wire b
   Wire c_;    ///< input wire c
   Wire d_;    ///< input wire d
   int numOfInputs_ = 2;
};

/*! \class ORGate
 *  \brief OR gate class.
 * 
 *  The OR gate is a digital logic gate that implements logical 
 *   disjunction – it behaves according to the following truth table:
 *
 *   a   b  |   c
 *   ---------------
 *   0   0  |   0  
 *   1   0  |   1  
 *   0   1  |   1   
 *   1   1  |   1   
 */
class ORGate
{
public:
    /** Update gate's inputs
     *  @param [in] a value for input a
     *  @param [in] b value for input b
     */
    void update(const bool a, const bool b);

    /** Generate output value
     *  @return output value
     */  
    bool output();
    
private:
    Wire a_;    ///< input wire a 
    Wire b_;    ///< input wire b
    Wire c_;    ///< internal wire c
    Wire d_;    ///< internal wire d

    NOTGate not_[2];    ///< NOT gates
    NANDGate nand_;     ///< NAND gate
};

/*! \class XORGate
 *  \brief XOR gate class.
 * 
 *  XOR represents the inequality function, i.e., the output is true if the 
 *  inputs are not alike otherwise the output is false. A way to remember 
 *  XOR is "must have one or the other but not both".
 *
 *   a   b  |   c
 *   ---------------
 *   0   0  |   0  
 *   1   0  |   1  
 *   0   1  |   1   
 *   1   1  |   0    
*/
class XORGate
{
public:
    /** Update gate's inputs
     *  @param [in] a value for input a
     *  @param [in] b value for input b
     */
    void update(const bool a, const bool b);

    /** Generate output value
     *  @return output value
     */       
    bool output();
    
private:
    Wire a_;    ///< input wire a     
    Wire b_;    ///< input wire b 
    Wire c_;    ///< input wire c 
    Wire d_;    ///< input wire d
    Wire e_;    ///< input wire e 
    Wire f_;    ///< input wire f 

    NOTGate not_[2];    ///< NOT gates
    NANDGate nand_[3];  ///< NAND gates
};


#endif // BIT_GATES_H_