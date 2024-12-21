#ifndef ERROR_LOGGER_HPP
#define ERROR_LOGGER_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

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

    void log(Level level, const string& message) {
        // Only log if severity is high enough
        if (level < minLevel) return;

        try {
            ofstream logFile(logFilePath, ios::app);
            if (!file) {
                throw runtime_error("Unable to open file: " + logFilePath);
            }

            logFile << "[" << getCurrentTimestamp() << "] "
                   << "[" << levelToString(level) << "] "
                   << message << endl;
        } catch (...) {
                // If logging fails, not much we can do
             return "Unknown error occurred.";  
        }
    }

    // Convenience methods for different levels
    void info(const string& message) {
        log(Level::INFO, message);
    }

    void warning(const string& message) {
        log(Level::WARNING, message);
    }

    void error(const string& message) {
        log(Level::ERROR, message);
    }

    void critical(const string& message) {
        log(Level::CRITICAL, message);
    }

    // Set minimum logging level
    void setMinLevel(Level level) {
        minLevel = level;
    }

    // Clear log file
    void clearLog() {
        ofstream logFile(logFilePath, ios::trunc);
    }

};

#endif 