#ifndef MEMORY_BYTE_H_
#define MEMORY_BYTE_H_

#include "MemoryBit.h"
#include "misc/Byte.h"
#include <vector>

/*! \class MemoryByte
 *  \brief This class implements one byte of computer memory.
 * 
 */ 
class MemoryByte
{
public:
    
    MemoryByte();
    ~MemoryByte();

    /** Update the input byte
     *  @param [in] input The input byte
     */
    void update(const Byte& input);

    /** Save the input byte into the device
     *  @param [in] s the 's' bit. When s=1 then the input byte is saved.
     */
    void set(const bool s = true);

    /** Get device output
     *  @return the saved byte
     */ 
    Byte output();

private:

    std::vector<MemoryBit> memoryBitCollection_; ///< collection of saved bits
};


#endif // MEMORY_BYTE_H_