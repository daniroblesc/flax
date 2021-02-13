#ifndef BUS_H_
#define BUS_H_

#include "misc/Byte.h"
#include <mutex>          // std::mutex
#include <list>

class IBusNode
{
public:
    /** Constructor
     *  @param [in] id The bus node identifier
     */
    IBusNode(const std::string& id);

    /** Get the bus node identifier
     *  @return The identifier
     */
    std::string getId() const;

private:
    std::string id_;    ///< The identifier
};

class Bus
{
public:

    typedef enum LogLevel
    {
        VERBOSE,
        ERROR
    } LogLevel;

    Bus(const std::string& id, LogLevel logLevel = ERROR);

    void subscribe(IBusNode* busNode);
    void unsubscribe(IBusNode* busNode);

    void write(IBusNode* busNode, const Byte& value);
    void write(const Byte& value);

    Byte read(IBusNode* busNode);
    Byte read();

    std::string toString();

private:
    Byte value_;
    std::mutex mtxBusAccess_;

    std::list<IBusNode*>  subscribers_;

    std::string id_; ///< bus identifier
    LogLevel logLevel_ = ERROR;
};


#endif // BUS_H_