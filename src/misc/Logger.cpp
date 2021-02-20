#include "Logger.h"
#include <iostream>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

Logger::Logger(const LogLevel logLevel)
{
    logLevel_ = logLevel;
}

Logger::~Logger()
{
    
}

std::string Logger::timestamp()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "[%d-%m-%Y %H:%M:%S"); 
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count() << "]";

    return oss.str();
}
void Logger::logVerbose(const char *fmt, ...)
{
    if (logLevel_ == ERROR)
    {
        return;
    }

    std::cout << timestamp() << " ";

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void Logger::logError(const char *fmt, ...)
{
    std::cout << timestamp() << " ";

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}