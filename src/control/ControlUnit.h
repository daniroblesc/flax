#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "control/Clock.h"
#include "control/Stepper.h"
#include "circuit/Bus.h"
#include "circuit/Wire.h"
#include "misc/Logger.h"
#include "components/Decoder.h"
#include <map>
#include <memory>


namespace control
{

enum signalType
{
    SIG_ENABLE,
    SIG_SET,
    SIG_OP
};

typedef std::vector<bool> SignalCollection;

/*! \class The IControllableUnit interface
 *  \brief It is the interface for all those objects that needs to be 
 *         synchronized by the Control Unit
 */
class IControllableUnit
{
public:

    /** Constructor
     *  @param [in] id The controllabe unit identifier
     */
    IControllableUnit(const std::string& id);

    /** Destructor
     */
    virtual ~IControllableUnit();

    /** Signal to the controllable units
     */ 
    virtual void signal(const signalType type, const SignalCollection& value) = 0;

    /** Get the controllable unit identifier
     *  @return The identifier
     */
    std::string getId() const;

private:

    std::string id_;    ///< The identifier
};

typedef std::map< std::string, std::shared_ptr<IControllableUnit> > ControllableUnitCollection;

/*! \class The ControlGPRegisters class
 *  \brief  
 * 
 *
 */
class ControlGPRegisters
{
public:

    ControlGPRegisters(const std::shared_ptr<Wire>& RegA, 
                       const std::shared_ptr<Wire>& RegB);

    /** Connect a controllable unit (like a register) 
     *  The control unit will update controllable unit enable/set bits 
     *  @param [in] controllableUnit the controllable unit
     */
    void connect(const std::shared_ptr<IControllableUnit>& controllableUnit);

    /** Inject clock enable signal from ControlUnit
     *  @param [in] clkE the clock enable signal
     */
    void onClkE(const bool clkE);

    /** Inject clock set signal from ControlUnit
     *  @param [in] clkS the clock set signal
     */
    void onClkS(const bool clkS);

private:

    std::map<std::string, std::shared_ptr<ORGate>>  orGates_;
    std::map<std::string, std::shared_ptr<ANDGate>> setGates_;
    Decoder2X4 decoders2x4_[3];

    std::shared_ptr<Wire> RegA_;
    std::shared_ptr<Wire> RegB_;
    bool clkE_ = false;
    bool clkS_ = false;

    ControllableUnitCollection controllableUnits_; ///< The collection of general purposes registers
};


/*! \class The ControlUnit class
 *  \brief The control unit (CU) is a component of a computer's central processing 
 *         unit (CPU) that directs the operation of the processor. 
 * 
 *  It tells the computer's memory, arithmetic logic unit and input and output devices 
 *  how to respond to the instructions that have been sent to the processor.
 *  It directs the operation of the other units by providing timing and control signals. 
 *  It directs the flow of data between the CPU and the other devices.
 *
 */
class ControlUnit : public IClockSubscriber, public Logger
{
public:
    /** Constructor
     *  @param [in] inputBus  the input bus (from IR)
     */
    ControlUnit(const std::shared_ptr<Bus>& inputBus, Logger::LogLevel logLevel = ERROR);

    /** Destructor
     */
    ~ControlUnit();

    /** Inject an external clock (for debugging purposes)
     *  @param [in] clk the clock signal
     */
    void extClk(bool clk);
    
    /** Start object 
     *  subscribe the object to the internal clock (receive notifications)
     */
    void start();

    /** Shutdown object to receive notifications from the internal clock
     *  unsubscribe the object from the internal clock
     */
    void shutdown();

    /** Connect a controllable unit (like a register) 
     *  The control unit will update controllable unit enable/set bits 
     *  @param [in] controllableUnit the controllable unit
     */
    void connect(const std::shared_ptr<IControllableUnit>& controllableUnit);

    // IClockSubscriber methods
    void onClk(const bool clk);
    void onClkE(const bool clkE);
    void onClkS(const bool clkS);

private:

    enum step
    {
        STEP1 = 0,
        STEP2,
        STEP3,
        STEP4, 
        STEP5,
        STEP6
    };

    const char* className_;

    std::shared_ptr<Bus> inputBus_;     ///< input bus

    std::unique_ptr<control::Clock> clock_; ///< The internal clock
    control::Stepper stepper_; ///< The stepper
    
    ControllableUnitCollection controllableUnits_; ///< The collection of controllabe units

    std::map<std::string, std::shared_ptr<ANDGate>> allEnableGates_;
    std::map<std::string, std::shared_ptr<ANDGate>> allSetGates_;
    std::shared_ptr<Wire> RegA_;
    std::shared_ptr<Wire> RegB_;

    void sendSignal(const std::string& id, const signalType type, const bool sigValue);
    void sendSignal(const std::string& id, const signalType type, const SignalCollection& sigValue);    

    int getCurrentStep();
    bool isGPRegister(const std::string& id);

    std::unique_ptr<ControlGPRegisters> controlGPRegisters_;
};


} // namespace

#endif // CONTROL_UNIT_H