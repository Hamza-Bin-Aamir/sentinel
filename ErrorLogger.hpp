#ifndef ERROR_LOGGER_HPP
#define ERROR_LOGGER_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

class ErrorLogger {
public:
    // Error severity levels
    enum class Level {
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };
};