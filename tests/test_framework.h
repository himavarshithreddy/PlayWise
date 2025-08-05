#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <chrono>

/**
 * @brief Simple test framework for PlayWise project
 * 
 * Provides basic testing functionality including:
 * - Test case registration and execution
 * - Assertion macros
 * - Test result reporting
 * - Performance timing
 */

class TestFramework {
private:
    struct TestCase {
        std::string name;
        std::string description;
        std::function<bool()> testFunction;
        bool isIntegration;
    };
    
    std::vector<TestCase> testCases;
    int passedTests;
    int failedTests;
    int totalTests;
    
public:
    TestFramework() : passedTests(0), failedTests(0), totalTests(0) {}
    
    // Register a test case
    void addTest(const std::string& name, const std::string& description, 
                 std::function<bool()> testFunc, bool isIntegration = false) {
        testCases.push_back({name, description, testFunc, isIntegration});
    }
    
    // Run all tests
    void runAllTests() {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "           PLAYWISE TEST SUITE" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (const auto& test : testCases) {
            runTest(test);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        printSummary(duration);
    }
    
    // Run only unit tests
    void runUnitTests() {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "           UNIT TESTS" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        for (const auto& test : testCases) {
            if (!test.isIntegration) {
                runTest(test);
            }
        }
    }
    
    // Run only integration tests
    void runIntegrationTests() {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "         INTEGRATION TESTS" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        for (const auto& test : testCases) {
            if (test.isIntegration) {
                runTest(test);
            }
        }
    }
    
private:
    void runTest(const TestCase& test) {
        totalTests++;
        std::cout << "\n[" << totalTests << "] " << test.name << std::endl;
        std::cout << "Description: " << test.description << std::endl;
        std::cout << "Type: " << (test.isIntegration ? "Integration" : "Unit") << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        try {
            bool result = test.testFunction();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            if (result) {
                std::cout << "[PASSED] (" << duration.count() << " us)" << std::endl;
                passedTests++;
            } else {
                std::cout << "[FAILED] (" << duration.count() << " us)" << std::endl;
                failedTests++;
            }
        } catch (const std::exception& e) {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "[FAILED] with exception: " << e.what() << " (" << duration.count() << " us)" << std::endl;
            failedTests++;
        }
    }
    
    void printSummary(const std::chrono::milliseconds& totalDuration) {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "           TEST SUMMARY" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << failedTests << std::endl;
        std::cout << "Success Rate: " << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%" << std::endl;
        std::cout << "Total Time: " << totalDuration.count() << " ms" << std::endl;
        
        if (failedTests == 0) {
            std::cout << "\n*** ALL TESTS PASSED! ***" << std::endl;
        } else {
            std::cout << "\n*** " << failedTests << " TESTS FAILED ***" << std::endl;
        }
    }
};

// Global test framework instance
extern TestFramework testFramework;

// Assertion macros
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        std::cout << "    Assertion failed: " << #condition << std::endl; \
        return false; \
    }

#define ASSERT_FALSE(condition) \
    if (condition) { \
        std::cout << "    Assertion failed: " << #condition << " should be false" << std::endl; \
        return false; \
    }

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cout << "    Assertion failed: Expected " << (expected) << ", got " << (actual) << std::endl; \
        return false; \
    }

#define ASSERT_NOT_EQUAL(expected, actual) \
    if ((expected) == (actual)) { \
        std::cout << "    Assertion failed: Expected not " << (expected) << ", got " << (actual) << std::endl; \
        return false; \
    }

#define ASSERT_NULL(ptr) \
    if ((ptr) != nullptr) { \
        std::cout << "    Assertion failed: Pointer should be null" << std::endl; \
        return false; \
    }

#define ASSERT_NOT_NULL(ptr) \
    if ((ptr) == nullptr) { \
        std::cout << "    Assertion failed: Pointer should not be null" << std::endl; \
        return false; \
    }

#define ASSERT_EMPTY(container) \
    if (!(container).empty()) { \
        std::cout << "    Assertion failed: Container should be empty" << std::endl; \
        return false; \
    }

#define ASSERT_NOT_EMPTY(container) \
    if ((container).empty()) { \
        std::cout << "    Assertion failed: Container should not be empty" << std::endl; \
        return false; \
    }

#define ASSERT_THROWS(expression, exception_type) \
    try { \
        expression; \
        std::cout << "    Assertion failed: Expected " << #exception_type << " to be thrown" << std::endl; \
        return false; \
    } catch (const exception_type&) { \
        /* Expected exception caught */ \
    } catch (...) { \
        std::cout << "    Assertion failed: Expected " << #exception_type << " but different exception was thrown" << std::endl; \
        return false; \
    }

#endif // TEST_FRAMEWORK_H 