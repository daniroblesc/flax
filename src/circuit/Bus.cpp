#include "Bus.h"
#include <iostream>
#include <typeinfo>

IBusNode::IBusNode(const std::string& id)
{
    id_ = id;
}

std::string IBusNode::getId() const
{
    return id_;
}

Bus::Bus(const std::string& id, Logger::LogLevel logLevel) : Logger(logLevel)
{
    className_ = __func__;
    id_ = id;
}

void Bus::subscribe(IBusNode* subscriber)
{
    mtxBusAccess_.lock();
    subscribers_.push_back(subscriber);
    mtxBusAccess_.unlock();
}

void Bus::unsubscribe(IBusNode* subscriber)
{
    mtxBusAccess_.lock();
    subscribers_.remove(subscriber);
    mtxBusAccess_.unlock();
}

void Bus::write(IBusNode* busNode, const Byte& value)
{
    mtxBusAccess_.lock();
    value_ = value;
    logVerbose("%s::%s( %s writes %x in *%s*)\n", className_, __func__,
        busNode->getId().c_str(), value_.toInt(), id_.c_str() );
    mtxBusAccess_.unlock();       
}

void Bus::write(const Byte& value)
{
    mtxBusAccess_.lock();
    value_ = value;
    logVerbose("%s::%s( ? writes %x in *%s*)\n", className_,__func__,
        value_.toInt(), id_.c_str());
    mtxBusAccess_.unlock();       
}

Byte Bus::read(IBusNode* busNode)
{
    mtxBusAccess_.lock();
    Byte value = value_;
    logVerbose("%s::%s( %s reads %x in *%s*)\n",className_,__func__,
        busNode->getId().c_str(), value_.toInt(), id_.c_str());
    mtxBusAccess_.unlock();
    return value;
}

Byte Bus::read()
{
    mtxBusAccess_.lock();
    Byte value = value_;
    logVerbose("%s::%s( ? reads %x in *%s*)\n",className_,__func__,
        value_.toInt(), id_.c_str());
    mtxBusAccess_.unlock();
    return value;
}

std::string Bus::toString()
{
    mtxBusAccess_.lock();
    std::string value = value_.toString();
    mtxBusAccess_.unlock();
    return value;
}
