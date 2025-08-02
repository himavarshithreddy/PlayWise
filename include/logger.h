#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>

/**
 * @brief Comprehensive logging system for tracking data structure operations
 * 
 * This logger provides detailed tracking of all stack, queue, and linked list operations
 * with timestamps, operation details, and performance metrics.
 */
class Logger {
private:
    static Logger* instance;
    std::ofstream logFile;
    std::mutex logMutex;
    bool consoleOutput;
    bool fileOutput;
    
    Logger();
    ~Logger();
    
    std::string getTimestamp();
    std::string formatDuration(std::chrono::microseconds duration);

public:
    // Singleton pattern
    static Logger* getInstance();
    
    // Configuration
    void enableConsoleOutput(bool enable = true);
    void enableFileOutput(bool enable = true);
    void setLogFile(const std::string& filename);
    
    // Logging methods for different data structures
    void logLinkedListOperation(const std::string& operation, const std::string& details, 
                               int size, std::chrono::microseconds duration);
    
    void logStackOperation(const std::string& operation, const std::string& details, 
                          int size, std::chrono::microseconds duration);
    
    void logQueueOperation(const std::string& operation, const std::string& details, 
                          int size, std::chrono::microseconds duration);
    
    void logBSTOperation(const std::string& operation, const std::string& details, 
                        int size, std::chrono::microseconds duration);
    
    void logHashTableOperation(const std::string& operation, const std::string& details, 
                              int size, std::chrono::microseconds duration);
    
    // Generic logging
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);
    void logPerformance(const std::string& operation, std::chrono::microseconds duration);
    
    // Utility methods
    void logSeparator();
    void logHeader(const std::string& header);
    void logFooter(const std::string& footer);
    
    // Close and cleanup
    void close();
};

// Convenience macros for easy logging
#define LOG_LL_OP(operation, details, size, duration) \
    Logger::getInstance()->logLinkedListOperation(operation, details, size, duration)

#define LOG_STACK_OP(operation, details, size, duration) \
    Logger::getInstance()->logStackOperation(operation, details, size, duration)

#define LOG_QUEUE_OP(operation, details, size, duration) \
    Logger::getInstance()->logQueueOperation(operation, details, size, duration)

#define LOG_BST_OP(operation, details, size, duration) \
    Logger::getInstance()->logBSTOperation(operation, details, size, duration)

#define LOG_HASH_OP(operation, details, size, duration) \
    Logger::getInstance()->logHashTableOperation(operation, details, size, duration)

#define LOG_INFO(msg) Logger::getInstance()->logInfo(msg)
#define LOG_WARNING(msg) Logger::getInstance()->logWarning(msg)
#define LOG_ERROR(msg) Logger::getInstance()->logError(msg)
#define LOG_PERF(operation, duration) Logger::getInstance()->logPerformance(operation, duration)

#endif // LOGGER_H 