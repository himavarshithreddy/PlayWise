#include "test_framework.h"
#include "test_song.cpp"
#include "test_playlist.cpp"
#include "test_integration.cpp"
#include <iostream>
#include <string>

// Global test framework instance
TestFramework testFramework;

int main(int argc, char* argv[]) {
    std::cout << "PlayWise Test Suite" << std::endl;
    std::cout << "===================" << std::endl;
    
    // Register all test suites
    registerSongTests();
    registerPlaylistTests();
    registerIntegrationTests();
    
    if (argc > 1) {
        std::string testType = argv[1];
        
        if (testType == "unit") {
            std::cout << "Running Unit Tests Only..." << std::endl;
            testFramework.runUnitTests();
        } else if (testType == "integration") {
            std::cout << "Running Integration Tests Only..." << std::endl;
            testFramework.runIntegrationTests();
        } else if (testType == "all") {
            std::cout << "Running All Tests..." << std::endl;
            testFramework.runAllTests();
        } else {
            std::cout << "Usage: " << argv[0] << " [unit|integration|all]" << std::endl;
            std::cout << "  unit       - Run unit tests only" << std::endl;
            std::cout << "  integration - Run integration tests only" << std::endl;
            std::cout << "  all        - Run all tests (default)" << std::endl;
            std::cout << "\nPress Enter to continue..." << std::endl;
            std::cin.get();
            return 1;
        }
    } else {
        // Default: run all tests
        std::cout << "Running All Tests..." << std::endl;
        testFramework.runAllTests();
    }
    
    std::cout << "\nPress Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
} 