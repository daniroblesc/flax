#ifndef CLOCK_H_
#define CLOCK_H_

#include <list>
#include <map>
#include <thread>         // std::thread
#include <mutex>          // std::mutex

namespace control
{

typedef enum ClockType
{
    ClockSystem,
    ClockDelayed,
    ClockEnable,
    ClockSet
} ClockType;

/*! \class The IClockSubscriber interface
 *  \brief It is the interface for all those objects that wants
 *         to receive the clock signal.
 */
class IClockSubscriber
{
public:
    typedef std::map<ClockType, bool> ClockMessage;

    virtual void onClk(const bool clk) = 0;
    virtual void onClkE(const bool clkE) = 0;
    virtual void onClkS(const bool clkS) = 0;
};

/*! \class The Clock class
 *  \brief A clock generator is an oscillator that produces a clock signal for 
 *         use in synchronizing a circuit's operation.
 *
 *   A clock signal (historically also known as logic beat) oscillates between a 
 *   high and a low state and is used like a metronome to coordinate actions of 
 *   digital circuits.
 */
class Clock
{
public: 

    /* freq in Hz. 1kHz by default */
    explicit Clock(const double freq = 1000.0);
    ~Clock();

    /** Start object 
     *  internal clock signal generator thread is created
     */
    void start();
    
    /** Shutdown object 
     *  internal clock signal generator thread is terminated
     */
    void shutdown();

    /** Subscribe clients that wants to receive the clock signal
     *  @param [in] subscriber the client
     */
    void subscribe(IClockSubscriber* subscriber);

    /** Unsubscribe clients from receiving the clock signal
     *  @param [in] subscriber the client
     */
    void unsubscribe(IClockSubscriber* subscriber);

private:

    const int MICROSECS_PER_MILLISEC = 1000;
    const int MILLISECS_PER_SEC = 1000;

    std::mutex mtxSubscribers_;
    std::list<IClockSubscriber*>  subscribers_;

    // clock thread stuff
    std::thread* clkThread_ = nullptr;
    void clkThread();
    bool shutdownClkThread_ = false;
    void onClockChange(ClockType type, const bool value);

    int64_t cycleTime_ = 0; ///< in millisecs
    int64_t halfCycleTime_ = 0; ///< in microseconds
    int64_t quarterCycleTime_ = 0; ///< in microseconds

    bool clkd_ = false; ///< delayed clock signal
    bool clk_ = false; ///< clock signal
    bool clkE_ = false; ///< clock enable
    bool clkS_ = false; ///< clock set

    void updateEnableAndSetClocks();
};


} // namespace


#endif // CLOCK_H_