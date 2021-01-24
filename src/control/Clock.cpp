#include "Clock.h"
#include <iostream>       // std::cout
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
    //std::cout << "cycleTime_: " << cycleTime_ << " halfCycleTime_: "<< halfCycleTime_ << " quarterCycleTime_: " << quarterCycleTime_ << std::endl;
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

void Clock::onClockChange(const IClockSubscriber::ClockMessage& msg)
{
    mtxSubscribers_.lock();
    for (auto subscriber : subscribers_) 
    {
        subscriber->onClkMessage(msg);
    }
    mtxSubscribers_.unlock();
}

void Clock::updateEnableAndSetClocks(IClockSubscriber::ClockMessage& msg)
{
    if ((clk_ || clkd_) != clkE_)
    {
        clkE_ = (clk_ || clkd_);
        //notifyClk(enable, clkE_);
        msg[ClockEnable] = clkE_;
    }

    if ((clk_ && clkd_) != clkS_)
    {
        clkS_ = (clk_ && clkd_);
       //notifyClk(set, clkS_);
       msg[ClockSet] = clkS_;
    }
}

void Clock::clkThread()
{
    while (!shutdownClkThread_)
    {
        IClockSubscriber::ClockMessage msg;
        (clk_) ? clk_ = false : clk_ = true;

        msg[ClockSystem] = clk_;

        //notifyClk(system, clk_); // clk_ cambia:
                                 //     1) notificar a los clientes 
                                 //     2) empieza el ciclo

        updateEnableAndSetClocks(msg);
        onClockChange(msg);

        std::this_thread::sleep_for(std::chrono::microseconds(quarterCycleTime_));

        (clkd_) ? clkd_ = false : clkd_ = true; // actualizar clkd_
        //notifyClk(delayed, clkd_);
        msg.clear();
        msg[ClockDelayed] = clkd_;

        updateEnableAndSetClocks(msg);
        onClockChange(msg);

        std::this_thread::sleep_for(std::chrono::microseconds(quarterCycleTime_));  
    }
}

void Clock::notifyClk(ClockType type, const bool value)
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
            subscriber->onClkD(value);  
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