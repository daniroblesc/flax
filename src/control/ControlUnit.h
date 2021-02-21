#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "control/Clock.h"
#include "control/Stepper.h"
#include "circuit/Bus.h"
#include "circuit/Wire.h"
#include "misc/Logger.h"
#include "misc/Signal.h"
#include "components/Decoder.h"
#include "ALU/ALU.h"

#include <map>
#include <memory>

namespace control
{

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
    virtual ~IControllableUnit() = default;

    /** Update the "enable" bit 
     *  @param [in] e 'e' bit 
     */
    virtual void enable(const bool e = true);
    
    /** Update the "set" bit 
     *  @param [in] s 's' bit 
     */
    virtual void set(const bool s = true);

    /** Get the controllable unit identifier
     *  @return The identifier
     */
    std::string getId() const;

private:

    std::string id_;    ///< The identifier
};


/** @struct ControllableUnitInfo
 *  This is a struct to save information for those clients connected
 *  to the Control Unit
 *
 *  @var ControllableUnitInfo::e
 *    identifier for the connection between the signal and enable slot
 *  @var ControllableUnitInfo::s
 *    identifier for the connection between the signal and set slot
 *  @var ControllableUnitInfo::o
 *    (unused field)
 *  @var ControllableUnitInfo::ptr
 *    pointer to the controllable unit
 */
typedef struct 	
{ 
    int e; 
    int s; 
    std::shared_ptr<IControllableUnit> ptr;
} ControllableUnitInfo;	

typedef std::map<std::string, ControllableUnitInfo> ControllableUnitCollection;

/*! \class The ControlGPRegisters class
 *  \brief  
 * 
 *
 */
class ControlGPRegisters
{
public:

    /** Constructor
     *  @param [in] inputBus  the input bus (from IR)
     *  @param [in] RegA
     *  @param [in] RegB
     */
    ControlGPRegisters(const std::shared_ptr<Bus>& inputBus,
                       const std::shared_ptr<Wire>& RegA, 
                       const std::shared_ptr<Wire>& RegB);

    ~ControlGPRegisters() = default;

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
    
    typedef struct 	
    {
        Decoder2X4 decoders2x4;
        std::map<std::string, std::shared_ptr<ANDGate>> andGates;
    } RegisterSelectionBlockControl;	
    std::map<int, RegisterSelectionBlockControl> block_;


    Signal<const bool> OnEnable; ///< object to trigger the enable signal
    Signal<const bool> OnSet;    ///< object to trigger the set signal

    std::shared_ptr<Bus> inputBus_;     ///< input bus
    std::shared_ptr<Wire> RegA_;
    std::shared_ptr<Wire> RegB_;

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
    ControlUnit(const std::shared_ptr<Bus>& inputBus, 
                const std::shared_ptr<ALU>& ALU,
                Logger::LogLevel logLevel = ERROR);

    /** Destructor
     */
    ~ControlUnit() = default;

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

    /** Receives clk notification from Clock
     *  IClockSubscriber callback
     *  @param [in] clk the clk signal
     */
    void onClk(const bool clk);

    /** Receives clkE notification from Clock
     *  IClockSubscriber callback
     *  @param [in] clkE the clkE signal
     */
    void onClkE(const bool clkE);

    /** Receives clkS notification from Clock
     *  IClockSubscriber callback
     *  @param [in] clkS the clkS signal
     */
    void onClkS(const bool clkS);

private:

    //! steps from Stepper
    enum step
    {
        STEP1 = 0,
        STEP2,
        STEP3,
        STEP4, 
        STEP5,
        STEP6
    };

    ControllableUnitCollection controllableUnits_; ///< the collection of controllable units

    const char* className_; ///< the class name (for logging messages)
    std::shared_ptr<Bus> inputBus_; ///< the input bus
    std::shared_ptr<ALU> ALU_; ///< the ALU
    std::unique_ptr<control::Clock> clock_; ///< the internal clock
    control::Stepper stepper_; ///< the stepper
    
    Signal<const bool> OnEnable; ///< object to trigger the enable signal
    Signal<const bool> OnSet;    ///< object to trigger the set signal
    Signal<const bool> OnClkE;  ///< object to trigger the clkE signal
    Signal<const bool> OnClkS;  ///< object to trigger the clkS signal

    std::map<std::string, std::shared_ptr<ANDGate>> allEnableGates_;
    std::map<std::string, std::shared_ptr<ANDGate>> allSetGates_;
    std::shared_ptr<Wire> RegA_;
    std::shared_ptr<Wire> RegB_;
    std::unique_ptr<ControlGPRegisters> controlGPRegisters_;

    int getCurrentStep();
    bool isGPRegister(const std::string& id);

};


} // namespace

#endif // CONTROL_UNIT_H