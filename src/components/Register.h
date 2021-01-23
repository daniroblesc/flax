#ifndef REGISTER_H_
#define REGISTER_H_

#include "Enabler.h"
#include "memory/MemoryByte.h"
#include "circuit/Bus.h"

/*! \class Register
 *  \brief A register is a quickly accessible location available to a computer's processor.
 */
class Register 
{
public:

    /** Constructor
     *  @param [in] bus the input/output bus
     */
    Register(Bus* bus);

    /** Constructor
     *  @param [in] inputBus  the input bus
     *  @param [in] outputBus the output bus
     */
    Register(Bus* inputBus, Bus* outputBus);

    /** Destructor
     */
    ~Register();

    /** This is the "enable" signal 
     *  Writes reg's content to the bus when 'e' bit is ON
     *  @param [in] e 'e' bit 
     */
    void enable(const bool e = true);   
    
    /** This is the "set" signal 
     *  Writes bus content to the reg when 's' bit is ON
     *  @param [in] s 's' bit 
     */
    void set(const bool s = true);  

private:

    Enabler enabler_; ///< The enabler
    MemoryByte memoryByte_; ///< the byte memory

    Bus* inputBus_;     ///< input bus
    Bus* outputBus_;    ///< output bus
};

#endif // REGISTER_H_  