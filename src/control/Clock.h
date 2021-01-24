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

class IClockSubscriber
{
public:
    typedef std::map<ClockType, bool> ClockMessage;

    virtual void onClk(const bool clk) = 0;
    virtual void onClkE(const bool clkE) = 0;
    virtual void onClkS(const bool clkS) = 0;
    virtual void onClkD(const bool clkD) = 0;

    virtual void onClkMessage(const ClockMessage msg) = 0;
};

/*! \class Clock
 *  \brief 
 *
 */
class Clock
{
public: 

    /* freq in Hz. 1kHz by default */
    explicit Clock(const double freq = 1000.0);
    ~Clock();

    void start();
    void shutdown();

    void subscribe(IClockSubscriber* subscriber);
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
    void notifyClk(ClockType type, const bool value);
    void onClockChange(const IClockSubscriber::ClockMessage& msg);

    int64_t cycleTime_ = 0; ///< in millisecs
    int64_t halfCycleTime_ = 0; ///< in microseconds
    int64_t quarterCycleTime_ = 0; ///< in microseconds

    bool clkd_ = false; ///< delayed clock signal
    bool clk_ = false; ///< clock signal
    bool clkE_ = false; ///< clock enable
    bool clkS_ = false; ///< clock set

    void updateEnableAndSetClocks(IClockSubscriber::ClockMessage& msg);
};


} // namespace


#endif // CLOCK_H_