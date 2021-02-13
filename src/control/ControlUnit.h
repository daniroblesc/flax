#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include "control/Clock.h"
#include "control/Stepper.h"
#include "circuit/Bus.h"
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
class ControlUnit : public IClockSubscriber
{
public:

    ControlUnit(const double clkFreq = 1000.0);
    ~ControlUnit();

    void inject(Bus* bus)
    {
        bus_ = bus;
    }

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
    void connect(IControllableUnit* controllableUnit);

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

    std::unique_ptr<control::Clock> clock_; ///< The internal clock
    control::Stepper stepper_; ///< The stepper

    typedef std::map<std::string, IControllableUnit*> ControllableUnitCollection;
    ControllableUnitCollection controllableUnits_; ///< The collection of controllabe units

    std::map<std::string, std::shared_ptr<ANDGate>> allEnableGates_;
    std::map<std::string, std::shared_ptr<ANDGate>> allSetGates_;

    void sendSignal(const std::string& id, const signalType type, const bool sigValue);
    void sendSignal(const std::string& id, const signalType type, const SignalCollection& sigValue);    

    Bus* bus_;
};


} // namespace

#endif // CONTROL_UNIT_H