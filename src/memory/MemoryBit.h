#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

#include "circuit/BitGates.h"

/*! \class MemoryBit
 *  \brief This class implements one bit of computer memory.
 * 
 *  The bit data cell consists of a D-Type Flip-Flop circuit that is built using four NAND logic gates
 * 
 *  A D-Type Flip-Flop Circuit is used to store 1 bit of information. It has two input pins 
 *  called I (Input) and S (Set) and two output pins (Q and ~Q = NOT Q).
 * 
 *  The truth table of a D-Type Flip-Flop circuit is as follows:
 * 
 *   I   S  |   Q   ~Q
 *   -----------------
 *   0   1  |   0    1
 *   1   1  |   1    0
 *   0   0  |   Q   ~Q  
 *   1   0  |   Q   ~Q    
 */ 
class MemoryBit
{
public:

    /** Update the input bit
     *  @param [in] input The input bit
     *  @param [in] s the 's' bit. When s=1 then the input bit is saved.
     */
    void update(const bool input, const bool s = true);

    /** Get device output
     *  @return the saved bit
     */ 
    bool output();

private:

    Wire wireI_; ///< input bit
    Wire wireS_; ///< S bit
    Wire wireO_; ///< output bit

    /// NAND gates
    NANDGate gates[4];
};


#endif // MEMORY_BIT_H_