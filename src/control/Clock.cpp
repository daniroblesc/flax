#include "Clock.h"
#include <chrono>         // std::chrono::seconds
#include <math.h>         /* pow */

namespace control
{

Clock::Clock(const double freq)
{
    // freq ^ (-1) = periodo
    // 1000 ^ (-1) = 0,001 secs = 1 millisec

    cycleTime_ = static_cast<int64_t>(pow(freq, -1) * MILLISECS_PER_SEC);
    halfCycleTime_ = (cycleTime_* MICROSECS_PER_MILLISEC) / 2;
    quarterCycleTime_ = halfCycleTime_ / 2;
}

Clock::~Clock()
{
}

void Clock::start()
{
    clkThread_ =  new std::thread([this]() {clkThread();} );
}

void Clock::shutdown()
{
    shutdownClkThread_ = true;
    if (clkThread_ != nullptr)
    {
        clkThread_->join();
        delete clkThread_;
    }
}

void Clock::updateEnableAndSetClocks()
{
    if ((clk_ || clkd_) != clkE_)
    {
        clkE_ = (clk_ || clkd_);
        onClockChange(ClockEnable, clkE_);        
    }

    if ((clk_ && clkd_) != clkS_)
    {
        clkS_ = (clk_ && clkd_);
       onClockChange(ClockSet, clkS_);
    }
}

void Clock::clkThread()
{
    while (!shutdownClkThread_)
    {
        IClockSubscriber::ClockMessage msg;
        (clk_) ? clk_ = false : clk_ = true;

        onClockChange(ClockSystem, clk_); // clk_ cambia:
                                          //     1) notificar a los clientes 
                                          //     2) empieza el ciclo

        updateEnableAndSetClocks();       

        std::this_thread::sleep_for(std::chrono::microseconds(quarterCycleTime_));

        (clkd_) ? clkd_ = false : clkd_ = true; // actualizar clkd_        

        updateEnableAndSetClocks();       

        std::this_thread::sleep_for(std::chrono::microseconds(quarterCycleTime_));  
    }
}

void Clock::onClockChange(ClockType type, const bool value)
{
    mtxSubscribers_.lock();
    for (auto subscriber : subscribers_) 
    {
        switch (type)
        {
        case ClockSystem:
            subscriber->onClk(value);    
            break;
        case ClockEnable:
            subscriber->onClkE(value);  
            break;
        case ClockSet:
            subscriber->onClkS(value);  
            break;            
        default:
            break;
        }        
    }
    mtxSubscribers_.unlock();
}

void Clock::subscribe(IClockSubscriber* subscriber)
{
    mtxSubscribers_.lock();
    subscribers_.push_back(subscriber);
    mtxSubscribers_.unlock();
}

void Clock::unsubscribe(IClockSubscriber* subscriber)
{
    mtxSubscribers_.lock();
    subscribers_.remove(subscriber);
    mtxSubscribers_.unlock();
}

} // namespace