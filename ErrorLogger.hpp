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

private:
    string logFilePath;
    Level minLevel;  // Minimum level to log

    // Convert Level to string
    string levelToString(Level level) {
        switch (level) {
            case Level::INFO: 
                return "INFO";
            case Level::WARNING:
                return "WARNING";
            case Level::ERROR: 
                return "ERROR";
            case Level::CRITICAL:
                return "CRITICAL";
            default:    
                return "UNKNOWN";
        }
    }

     // Get current timestamp as string
    string getCurrentTimestamp() {
        auto now = time(nullptr);
        auto* timeinfo = localtime(&now);
        
        stringstream ss;
        ss << put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
public:
    // Constructor
    ErrorLogger(const string& filePath = "error_log.txt", 
                Level minimumLevel = Level::INFO) 
        : logFilePath(filePath), minLevel(minimumLevel) {}

};