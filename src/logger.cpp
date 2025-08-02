#include "../include/logger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>

// Static instance
Logger* Logger::instance = nullptr;

// Constructor
Logger::Logger() : consoleOutput(true), fileOutput(false) {
    // Initialize with console output enabled by default
}

// Destructor
Logger::~Logger() {
    close();
}

// Singleton getInstance
Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

// Configuration methods
void Logger::enableConsoleOutput(bool enable) {
    consoleOutput = enable;
}

void Logger::enableFileOutput(bool enable) {
    fileOutput = enable;
}

void Logger::setLogFile(const std::string& filename) {
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
    fileOutput = logFile.is_open();
}

// Utility methods
std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Logger::formatDuration(std::chrono::microseconds duration) {
    std::stringstream ss;
    if (duration.count() < 1000) {
        ss << duration.count() << " μs";
    } else if (duration.count() < 1000000) {
        ss << std::fixed << std::setprecision(2) 
           << duration.count() / 1000.0 << " ms";
    } else {
        ss << std::fixed << std::setprecision(2) 
           << duration.count() / 1000000.0 << " s";
    }
    return ss.str();
}

// Logging methods for different data structures
void Logger::logLinkedListOperation(const std::string& operation, const std::string& details, 
                                   int size, std::chrono::microseconds duration) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::stringstream ss;
    ss << "[LINKED_LIST] " << operation << " | Size: " << size 
       << " | Duration: " << formatDuration(duration) << " | " << details;
    
    std::string message = ss.str();
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << message << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << message << std::endl;
        logFile.flush();
    }
}

void Logger::logStackOperation(const std::string& operation, const std::string& details, 
                              int size, std::chrono::microseconds duration) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::stringstream ss;
    ss << "[STACK] " << operation << " | Size: " << size 
       << " | Duration: " << formatDuration(duration) << " | " << details;
    
    std::string message = ss.str();
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << message << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << message << std::endl;
        logFile.flush();
    }
}

void Logger::logQueueOperation(const std::string& operation, const std::string& details, 
                              int size, std::chrono::microseconds duration) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::stringstream ss;
    ss << "[QUEUE] " << operation << " | Size: " << size 
       << " | Duration: " << formatDuration(duration) << " | " << details;
    
    std::string message = ss.str();
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << message << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << message << std::endl;
        logFile.flush();
    }
}

void Logger::logBSTOperation(const std::string& operation, const std::string& details, 
                            int size, std::chrono::microseconds duration) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::stringstream ss;
    ss << "[BST] " << operation << " | Size: " << size 
       << " | Duration: " << formatDuration(duration) << " | " << details;
    
    std::string message = ss.str();
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << message << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << message << std::endl;
        logFile.flush();
    }
}

void Logger::logHashTableOperation(const std::string& operation, const std::string& details, 
                                  int size, std::chrono::microseconds duration) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::stringstream ss;
    ss << "[HASH_TABLE] " << operation << " | Size: " << size 
       << " | Duration: " << formatDuration(duration) << " | " << details;
    
    std::string message = ss.str();
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << message << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << message << std::endl;
        logFile.flush();
    }
}

// Generic logging methods
void Logger::logInfo(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string formattedMessage = "[INFO] " + message;
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << formattedMessage << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << formattedMessage << std::endl;
        logFile.flush();
    }
}

void Logger::logWarning(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string formattedMessage = "[WARNING] " + message;
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << formattedMessage << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << formattedMessage << std::endl;
        logFile.flush();
    }
}

void Logger::logError(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string formattedMessage = "[ERROR] " + message;
    
    if (consoleOutput) {
        std::cerr << getTimestamp() << " " << formattedMessage << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << formattedMessage << std::endl;
        logFile.flush();
    }
}

void Logger::logPerformance(const std::string& operation, std::chrono::microseconds duration) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::stringstream ss;
    ss << "[PERFORMANCE] " << operation << " | Duration: " << formatDuration(duration);
    
    std::string message = ss.str();
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << message << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << message << std::endl;
        logFile.flush();
    }
}

// Utility methods
void Logger::logSeparator() {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string separator(80, '=');
    
    if (consoleOutput) {
        std::cout << separator << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << separator << std::endl;
        logFile.flush();
    }
}

void Logger::logHeader(const std::string& header) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string formattedHeader = "[HEADER] " + header;
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << formattedHeader << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << formattedHeader << std::endl;
        logFile.flush();
    }
}

void Logger::logFooter(const std::string& footer) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    std::string formattedFooter = "[FOOTER] " + footer;
    
    if (consoleOutput) {
        std::cout << getTimestamp() << " " << formattedFooter << std::endl;
    }
    
    if (fileOutput && logFile.is_open()) {
        logFile << getTimestamp() << " " << formattedFooter << std::endl;
        logFile.flush();
    }
}

// Close and cleanup
void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
} 