#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <time.h>

class Logger
{
public:
    typedef enum LogLevel
    {
        VERBOSE,
        ERROR
    } LogLevel;

    Logger(const LogLevel logLevel);
    virtual ~Logger();

    void logVerbose(const char *fmt, ...);
    void logError(const char *fmt, ...);

private:

    LogLevel logLevel_ = ERROR;
    std::string timestamp();
};

#endif