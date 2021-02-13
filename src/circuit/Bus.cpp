#include "Bus.h"
#include <iostream>

IBusNode::IBusNode(const std::string& id)
{
    id_ = id;
}

std::string IBusNode::getId() const
{
    return id_;
}

Bus::Bus(const std::string& id, LogLevel logLevel)
{
    id_ = id;
    logLevel_ = logLevel;
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
    if (logLevel_ == VERBOSE)
    {
        std::cout << "Bus(" << id_ << ") write [" << busNode->getId()  << "] " <<  value_.toInt() << "\n";
    }
    mtxBusAccess_.unlock();       
}

void Bus::write(const Byte& value)
{
    mtxBusAccess_.lock();
    value_ = value;
    if (logLevel_ == VERBOSE)
    {
        std::cout << "Bus(" << id_ << ") write [?] " <<  value_.toInt() << "\n";
    }
    mtxBusAccess_.unlock();       
}

Byte Bus::read(IBusNode* busNode)
{
    mtxBusAccess_.lock();
    Byte value = value_;
    if (logLevel_ == VERBOSE)
    {
        std::cout << "Bus(" << id_ << ") read [" << busNode->getId()  << "] " <<  value_.toInt() << "\n";
    }    
    mtxBusAccess_.unlock();
    return value;
}

Byte Bus::read()
{
    mtxBusAccess_.lock();
    Byte value = value_;
    if (logLevel_ == VERBOSE)
    {
        std::cout << "Bus(" << id_ << ") read [?] " <<  value_.toInt() << "\n";
    }
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
