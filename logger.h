#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string.h>

///
/// \brief The Logger class
///
class Logger
{
public:
    static Logger& getInstance();
    void logMessage(std::string message);

private:
    Logger();

};

#endif
