#include "Register.h"
#include <assert.h>     /* assert */
#include <iostream>

Register::Register(const std::string& id, const std::shared_ptr<Bus>& bus, const Byte& defaultValue, const Logger::LogLevel logLevel) : 
    control::IControllableUnit(id),
    IBusNode(id),
    Logger(logLevel)
{
    className_ = __func__;
    inputBus_ = outputBus_ = bus;
    bus->subscribe(this);
    setDefaultValue(defaultValue);
}

Register::Register(const std::string& id, const std::shared_ptr<Bus>& inputBus, const std::shared_ptr<Bus>& outputBus, const Byte& defaultValue, const Logger::LogLevel logLevel) : 
    control::IControllableUnit(id),
    IBusNode(id),
    Logger(logLevel)
{
    className_ = __func__;
    inputBus_ = inputBus;
    outputBus_ = outputBus;
    inputBus_->subscribe(this);
    outputBus_->subscribe(this);
    setDefaultValue(defaultValue);
}

const std::shared_ptr<Bus>& Register::getOutputBus()
{
    return outputBus_;
}

void Register::setDefaultValue(const Byte& defaultValue)
{
    if (defaultValue == 0)
    {
        return;
    }
    memoryByte_.update(defaultValue);
    enabler_.update(memoryByte_.output());
}

void Register::enable(const bool e)
{
    logVerbose("%s::%s( e = %d )\n", IControllableUnit::getId().c_str() , __func__, e);

    if (e == false) 
    {
        return;
    }

    // the E's inputs go to the outputs
    enabler_.enable();
    // get the E's outputs
    Byte output = enabler_.output();
    // save E's outputs to the bus
    outputBus_->write(this, output);
}

void Register::set(const bool s)
{
    logVerbose("%s::%s( s = %d )\n", IControllableUnit::getId().c_str(), __func__, s);

    if (s == false) 
    {
        return;
    }

    // get bus content
    Byte input = inputBus_->read(this);

    // update B's inputs with bus content & save B content
    memoryByte_.update(input, s);

    // update E's input with B's output
    enabler_.update(memoryByte_.output());
}

Byte Register::output()
{
    return memoryByte_.output();
}