#ifndef REGISTER_H_
#define REGISTER_H_

#include "Enabler.h"
#include "memory/MemoryByte.h"
#include "circuit/Bus.h"
#include "control/ControlUnit.h"


/*! \class Register
 *  \brief A register is a quickly accessible location available to a computer's processor.
 */
class Register : public control::IControllableUnit, public IBusNode
{
public:

    /** Constructor
     *  @param [in] id register's id
     *  @param [in] bus the input/output bus
     *  @param [in] defaultValue the default value 
     */
    Register(const std::string& id, Bus* bus, const Byte& defaultValue = 0);

    /** Constructor
     *  @param [in] id register's id
     *  @param [in] inputBus  the input bus
     *  @param [in] outputBus the output bus
     */
    Register(const std::string& id, Bus* inputBus, Bus* outputBus);

    /** Destructor
     */
    ~Register();

    /** Get register's output bus
     *  @return the output bus
     */ 
    Bus* getOutputBus();

    /** Update the "enable" bit 
     *  Writes reg's content to the bus when 'e' bit is ON
     *  @param [in] e 'e' bit 
     */
    void enable(const bool e = true);   
    
    /** Update the "set" bit 
     *  Writes bus content to the reg when 's' bit is ON
     *  @param [in] s 's' bit 
     */
    void set(const bool s = true);  

    /** implements control::IControllableUnit method
     *  Signal received from the Control Unit
     *  @param [in] type signal's type
     *  @param [in] value signal value
     */
    void signal(const control::signalType type, const control::SignalCollection& value) override;

    /** Get register output (for debugging purposes)
     *  @return the saved byte
     */ 
    Byte output();

private:

    Enabler enabler_; ///< The enabler
    MemoryByte memoryByte_; ///< the byte memory

    Bus* inputBus_;     ///< input bus
    Bus* outputBus_;    ///< output bus

    void setDefaultValue(const Byte& defaultValue);
};

#endif // REGISTER_H_  