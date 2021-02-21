#ifndef REGISTER_H_
#define REGISTER_H_

#include "Enabler.h"
#include "memory/MemoryByte.h"
#include "circuit/Bus.h"
#include "control/ControlUnit.h"
#include "misc/Logger.h"


/*! \class Register
 *  \brief A register is a quickly accessible location available to a computer's processor.
 */
class Register : public control::IControllableUnit, public IBusNode, public Logger
{
public:

    /** Constructor
     *  @param [in] id register's id
     *  @param [in] bus the input/output bus
     *  @param [in] defaultValue the default value 
     *  @param [in] logLevel log level for log messages
     */
    Register(const std::string& id, const std::shared_ptr<Bus>& bus, const Byte& defaultValue = 0, const Logger::LogLevel logLevel = ERROR);

    /** Constructor
     *  @param [in] id register's id
     *  @param [in] inputBus  the input bus
     *  @param [in] outputBus the output bus
     *  @param [in] defaultValue the default value 
     *  @param [in] logLevel log level for log messages
     */
    Register(const std::string& id, const std::shared_ptr<Bus>& inputBus, const std::shared_ptr<Bus>& outputBus, const Byte& defaultValue = 0, const Logger::LogLevel logLevel = ERROR);

    /** Destructor
     */
    ~Register() = default;

    /** Get register's output bus
     *  @return the output bus
     */ 
    const std::shared_ptr<Bus>& getOutputBus();

    /** Update the "enable" bit 
     *  Writes reg's content to the bus when 'e' bit is ON
     *  @param [in] e 'e' bit 
     */
    void enable(const bool e = true) override;   
    
    /** Update the "set" bit 
     *  Writes bus content to the reg when 's' bit is ON
     *  @param [in] s 's' bit 
     */
    void set(const bool s = true) override;  

    /** Get register output (for debugging purposes)
     *  @return the saved byte
     */ 
    Byte output();

private:

    const char* className_;

    Enabler enabler_; ///< The enabler
    MemoryByte memoryByte_; ///< the byte memory

    std::shared_ptr<Bus> inputBus_;     ///< input bus
    std::shared_ptr<Bus> outputBus_;    ///< output bus

    void setDefaultValue(const Byte& defaultValue);
};

#endif // REGISTER_H_  