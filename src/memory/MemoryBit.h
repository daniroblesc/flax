#ifndef MEMORY_BIT_H_
#define MEMORY_BIT_H_

#include "circuit/BitGates.h"

/*! \class MemoryBit
 *  \brief This class implements one bit of computer memory.
 * 
 */ 
class MemoryBit
{
public:

    /** Update the input bit
     *  @param [in] input The input bit
     */
    void update(const bool input);

    /** Save the input bit into the device
     *  @param [in] s the 's' bit. When s=1 then the input bit is saved.
     */
    void set(const bool s = true);

    /** Get device output
     *  @return the saved bit
     */ 
    bool output();

private:

    Wire input_; ///< input bit
    Wire s_;    ///< set bit

    /// NAND gates
    NANDGate G1_;
    NANDGate G2_;
    NANDGate G3_;
    NANDGate G4_;
};


#endif // MEMORY_BIT_H_