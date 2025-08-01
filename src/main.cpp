#include "../include/playwise_app.h"
#include <iostream>

int main() {
    std::cout << "PlayWise Music Playlist Management System" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Starting application..." << std::endl;
    std::cout << std::endl;
    
    try {
        // Create and run the main application
        PlayWiseApp app;
        app.run();
        
    } catch (const std::exception& e) {
        std::cout << "Error during execution: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 