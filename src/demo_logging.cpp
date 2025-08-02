#include "../include/playwise_app.h"
#include "../include/logger.h"
#include <iostream>
#include <chrono>
#include <thread>

/**
 * @brief Demo program to showcase comprehensive logging of all data structure operations
 * 
 * This program demonstrates logging for:
 * - Linked List operations (Playlist)
 * - Stack operations (History)
 * - Priority Queue operations (Favorites)
 * - BST operations (Rating Tree)
 * - Hash Table operations (Song Database)
 */

void demoLinkedListLogging() {
    std::cout << "\n=== LINKED LIST LOGGING DEMO ===" << std::endl;
    LOG_INFO("Starting Linked List (Playlist) logging demonstration");
    
    Playlist playlist("Demo Playlist");
    
    // Add songs with logging
    playlist.add_song("Bohemian Rhapsody", "Queen", 354);
    playlist.add_song("Hotel California", "Eagles", 391);
    playlist.add_song("Stairway to Heaven", "Led Zeppelin", 482);
    playlist.add_song("Imagine", "John Lennon", 183);
    playlist.add_song("Hey Jude", "The Beatles", 431);
    
    // Display playlist
    playlist.display();
    
    // Move songs with logging
    playlist.move_song(0, 2);  // Move first song to third position
    playlist.move_song(3, 1);  // Move fourth song to second position
    
    // Delete songs with logging
    playlist.delete_song(2);   // Delete third song
    playlist.delete_song(0);   // Delete first song
    
    // Display final state
    playlist.display();
    
    LOG_INFO("Linked List logging demonstration completed");
}

void demoStackLogging() {
    std::cout << "\n=== STACK LOGGING DEMO ===" << std::endl;
    LOG_INFO("Starting Stack (History) logging demonstration");
    
    History history(5);  // Max 5 songs
    
    // Add songs to history (stack)
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    Song song2("2", "Hotel California", "Eagles", 391, 5);
    Song song3("3", "Stairway to Heaven", "Led Zeppelin", 482, 5);
    Song song4("4", "Imagine", "John Lennon", 183, 5);
    Song song5("5", "Hey Jude", "The Beatles", 431, 5);
    Song song6("6", "Yesterday", "The Beatles", 125, 4);
    
    history.add_played_song(song1);
    history.add_played_song(song2);
    history.add_played_song(song3);
    history.add_played_song(song4);
    history.add_played_song(song5);
    
    // This will trigger stack overflow handling
    history.add_played_song(song6);
    
    // Display history
    history.display_history();
    
    // Undo operations
    Song undone = history.undo_last_play();
    std::cout << "Undid: " << undone.getTitle() << std::endl;
    
    undone = history.undo_last_play();
    std::cout << "Undid: " << undone.getTitle() << std::endl;
    
    // Display final state
    history.display_history();
    
    LOG_INFO("Stack logging demonstration completed");
}

void demoQueueLogging() {
    std::cout << "\n=== PRIORITY QUEUE LOGGING DEMO ===" << std::endl;
    LOG_INFO("Starting Priority Queue (Favorites) logging demonstration");
    
    FavoriteSongsQueue favorites;
    
    // Add songs to favorites
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    Song song2("2", "Hotel California", "Eagles", 391, 5);
    Song song3("3", "Stairway to Heaven", "Led Zeppelin", 482, 5);
    Song song4("4", "Imagine", "John Lennon", 183, 5);
    Song song5("5", "Hey Jude", "The Beatles", 431, 5);
    
    favorites.addSong(song1);
    favorites.addSong(song2);
    favorites.addSong(song3);
    favorites.addSong(song4);
    favorites.addSong(song5);
    
    // Update listening times (this triggers queue rebuilding)
    favorites.updateListeningTime(song1, 300);  // 5 minutes
    favorites.updateListeningTime(song2, 600);  // 10 minutes
    favorites.updateListeningTime(song3, 150);  // 2.5 minutes
    favorites.updateListeningTime(song4, 900);  // 15 minutes
    favorites.updateListeningTime(song5, 450);  // 7.5 minutes
    
    // Get top favorites
    std::vector<Song> topSongs = favorites.getTopFavorites(3);
    std::cout << "\nTop 3 Favorite Songs:" << std::endl;
    for (size_t i = 0; i < topSongs.size(); i++) {
        std::cout << (i + 1) << ". " << topSongs[i].getTitle() << " by " << topSongs[i].getArtist() << std::endl;
    }
    
    // Display all favorites
    favorites.displayFavorites();
    
    LOG_INFO("Priority Queue logging demonstration completed");
}

void demoBSTLogging() {
    std::cout << "\n=== BINARY SEARCH TREE LOGGING DEMO ===" << std::endl;
    LOG_INFO("Starting BST (Rating Tree) logging demonstration");
    
    RatingTree ratingTree;
    
    // Add songs with different ratings
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    Song song2("2", "Hotel California", "Eagles", 391, 4);
    Song song3("3", "Stairway to Heaven", "Led Zeppelin", 482, 5);
    Song song4("4", "Imagine", "John Lennon", 183, 3);
    Song song5("5", "Hey Jude", "The Beatles", 431, 4);
    
    ratingTree.insert_song(song1, 5);
    ratingTree.insert_song(song2, 4);
    ratingTree.insert_song(song3, 5);
    ratingTree.insert_song(song4, 3);
    ratingTree.insert_song(song5, 4);
    
    // Search by rating
    std::vector<Song> fiveStarSongs = ratingTree.search_by_rating(5);
    std::cout << "\n5-Star Songs:" << std::endl;
    for (const Song& song : fiveStarSongs) {
        std::cout << "- " << song.getTitle() << " by " << song.getArtist() << std::endl;
    }
    
    // Get songs in range
    std::vector<Song> fourToFiveStarSongs = ratingTree.get_songs_in_range(4, 5);
    std::cout << "\n4-5 Star Songs:" << std::endl;
    for (const Song& song : fourToFiveStarSongs) {
        std::cout << "- " << song.getTitle() << " by " << song.getArtist() << " (Rating: " << song.getRating() << ")" << std::endl;
    }
    
    // Display tree stats
    ratingTree.display_rating_stats();
    
    LOG_INFO("BST logging demonstration completed");
}

void demoHashTableLogging() {
    std::cout << "\n=== HASH TABLE LOGGING DEMO ===" << std::endl;
    LOG_INFO("Starting Hash Table (Song Database) logging demonstration");
    
    SongDatabase database;
    
    // Add songs to database
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    Song song2("2", "Hotel California", "Eagles", 391, 4);
    Song song3("3", "Stairway to Heaven", "Led Zeppelin", 482, 5);
    Song song4("4", "Imagine", "John Lennon", 183, 3);
    Song song5("5", "Hey Jude", "The Beatles", 431, 4);
    
    database.insert_song(song1);
    database.insert_song(song2);
    database.insert_song(song3);
    database.insert_song(song4);
    database.insert_song(song5);
    
    // Search by ID
    Song* found = database.search_by_id("1");
    if (found) {
        std::cout << "Found by ID: " << found->getTitle() << std::endl;
    }
    
    // Search by title
    found = database.search_by_title("Hotel California");
    if (found) {
        std::cout << "Found by title: " << found->getTitle() << " by " << found->getArtist() << std::endl;
    }
    
    // Search by artist
    std::vector<Song> queenSongs = database.search_by_artist("Queen");
    std::cout << "\nQueen songs in database:" << std::endl;
    for (const Song& song : queenSongs) {
        std::cout << "- " << song.getTitle() << std::endl;
    }
    
    // Display database stats
    database.display_stats();
    
    LOG_INFO("Hash Table logging demonstration completed");
}

void demoPerformanceLogging() {
    std::cout << "\n=== PERFORMANCE LOGGING DEMO ===" << std::endl;
    LOG_INFO("Starting performance logging demonstration");
    
    // Simulate some operations with timing
    auto start = std::chrono::high_resolution_clock::now();
    
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    LOG_PERF("Simulated Operation", duration);
    
    // Simulate more operations
    for (int i = 0; i < 5; i++) {
        start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        LOG_PERF("Operation " + std::to_string(i + 1), duration);
    }
    
    LOG_INFO("Performance logging demonstration completed");
}

int main() {
    std::cout << "PlayWise Data Structure Logging Demo" << std::endl;
    std::cout << "====================================" << std::endl;
    
    // Configure logger
    Logger* logger = Logger::getInstance();
    logger->enableConsoleOutput(true);
    logger->setLogFile("playwise_operations.log");
    
    LOG_HEADER("Starting PlayWise Data Structure Logging Demonstration");
    
    try {
        // Run all demos
        demoLinkedListLogging();
        demoStackLogging();
        demoQueueLogging();
        demoBSTLogging();
        demoHashTableLogging();
        demoPerformanceLogging();
        
        LOG_FOOTER("All demonstrations completed successfully");
        
        std::cout << "\n=== LOGGING SUMMARY ===" << std::endl;
        std::cout << "All data structure operations have been logged to:" << std::endl;
        std::cout << "1. Console output (above)" << std::endl;
        std::cout << "2. File: playwise_operations.log" << std::endl;
        std::cout << "\nThe log file contains detailed information about:" << std::endl;
        std::cout << "- All linked list operations (add, delete, move)" << std::endl;
        std::cout << "- All stack operations (push, pop, top)" << std::endl;
        std::cout << "- All priority queue operations (insert, update, rebuild)" << std::endl;
        std::cout << "- All BST operations (insert, search, range queries)" << std::endl;
        std::cout << "- All hash table operations (insert, search, lookup)" << std::endl;
        std::cout << "- Performance metrics and timing information" << std::endl;
        
    } catch (const std::exception& e) {
        LOG_ERROR("Demo failed with exception: " + std::string(e.what()));
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    // Cleanup
    logger->close();
    
    return 0;
} 