#include "../include/favorite_songs_queue.h"
#include "../include/song.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

/**
 * @brief Demonstration of Auto-Sorting Favorite Songs Queue
 * 
 * This program demonstrates the implementation of a priority queue that
 * automatically maintains songs sorted by total listening duration.
 * 
 * Features demonstrated:
 * - Priority Queue (Max Heap) implementation
 * - Auto-sorting by listening time
 * - Real-time updates and reordering
 * - Integration with playback simulation
 * - Statistics and analytics
 */

class AutoSortDemo {
private:
    FavoriteSongsQueue* favoriteQueue;
    
    // Sample songs for demonstration
    std::vector<Song> sampleSongs;
    
    void initializeSampleSongs() {
        sampleSongs = {
            Song("1", "Bohemian Rhapsody", "Queen", 354, 5),
            Song("2", "Hotel California", "Eagles", 391, 5),
            Song("3", "Stairway to Heaven", "Led Zeppelin", 482, 5),
            Song("4", "Imagine", "John Lennon", 183, 4),
            Song("5", "Yesterday", "The Beatles", 125, 4),
            Song("6", "Hey Jude", "The Beatles", 431, 5),
            Song("7", "Smells Like Teen Spirit", "Nirvana", 301, 4),
            Song("8", "Sweet Child O' Mine", "Guns N' Roses", 356, 4),
            Song("9", "Wonderwall", "Oasis", 258, 3),
            Song("10", "Creep", "Radiohead", 239, 4)
        };
    }
    
    void simulatePlayback(const Song& song, int playbackDuration) {
        std::cout << "🎵 Playing: " << song.getTitle() << " - " << song.getArtist() << std::endl;
        std::cout << "   Duration: " << playbackDuration << " seconds" << std::endl;
        
        // Simulate playback time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // Auto-update favorites
        favoriteQueue->autoUpdateFromPlayback(song, playbackDuration);
        
        std::cout << "✅ Added to favorites and queue re-sorted!" << std::endl;
        std::cout << std::endl;
    }

public:
    AutoSortDemo() {
        favoriteQueue = new FavoriteSongsQueue();
        initializeSampleSongs();
    }
    
    ~AutoSortDemo() {
        delete favoriteQueue;
    }
    
    void runDemo() {
        std::cout << "🎵 PlayWise Auto-Sorting Favorite Songs Queue Demo 🎵" << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << std::endl;
        
        std::cout << "This demo showcases a priority queue that automatically" << std::endl;
        std::cout << "maintains songs sorted by total listening duration." << std::endl;
        std::cout << std::endl;
        
        // Step 1: Add some songs to favorites
        std::cout << "Step 1: Adding songs to favorites..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        for (int i = 0; i < 5; i++) {
            favoriteQueue->addSong(sampleSongs[i]);
            std::cout << "Added: " << sampleSongs[i].getTitle() << " - " << sampleSongs[i].getArtist() << std::endl;
        }
        std::cout << std::endl;
        
        // Step 2: Display initial state
        std::cout << "Step 2: Initial favorites (no listening time yet)" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        favoriteQueue->displayFavorites();
        std::cout << std::endl;
        
        // Step 3: Simulate playback and auto-update
        std::cout << "Step 3: Simulating playback and auto-updating favorites..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        // Simulate different playback scenarios
        simulatePlayback(sampleSongs[0], 180);  // Bohemian Rhapsody - 3 minutes
        simulatePlayback(sampleSongs[1], 240);  // Hotel California - 4 minutes
        simulatePlayback(sampleSongs[2], 300);  // Stairway to Heaven - 5 minutes
        simulatePlayback(sampleSongs[0], 120);  // Bohemian Rhapsody again - 2 minutes
        simulatePlayback(sampleSongs[3], 150);  // Imagine - 2.5 minutes
        simulatePlayback(sampleSongs[1], 200);  // Hotel California again - 3.3 minutes
        
        // Step 4: Display updated favorites
        std::cout << "Step 4: Updated favorites (sorted by listening time)" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        favoriteQueue->displayFavorites();
        std::cout << std::endl;
        
        // Step 5: Show statistics
        std::cout << "Step 5: Detailed statistics" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        favoriteQueue->displayDetailedStats();
        std::cout << std::endl;
        
        // Step 6: Demonstrate top favorites
        std::cout << "Step 6: Top 3 favorite songs" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::vector<Song> topSongs = favoriteQueue->getTopFavorites(3);
        for (size_t i = 0; i < topSongs.size(); i++) {
            const Song& song = topSongs[i];
            std::cout << (i + 1) << ". " << song.getTitle() << " - " << song.getArtist() << std::endl;
            std::cout << "   Total listening time: " << favoriteQueue->getListeningTime(song) << " seconds" << std::endl;
            std::cout << "   Play count: " << favoriteQueue->getPlayCount(song) << std::endl;
        }
        std::cout << std::endl;
        
        // Step 7: Demonstrate time range filtering
        std::cout << "Step 7: Songs with listening time between 200-400 seconds" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::vector<Song> filteredSongs = favoriteQueue->getFavoritesByTimeRange(200, 400);
        if (filteredSongs.empty()) {
            std::cout << "No songs found in the specified time range." << std::endl;
        } else {
            for (size_t i = 0; i < filteredSongs.size(); i++) {
                const Song& song = filteredSongs[i];
                std::cout << (i + 1) << ". " << song.getTitle() << " - " << song.getArtist() << std::endl;
                std::cout << "   Listening time: " << favoriteQueue->getListeningTime(song) << " seconds" << std::endl;
            }
        }
        std::cout << std::endl;
        
        // Step 8: Demonstrate real-time updates
        std::cout << "Step 8: Real-time update demonstration" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        std::cout << "Current top song: " << favoriteQueue->getTopFavorite().getTitle() << std::endl;
        std::cout << "Adding more listening time to a different song..." << std::endl;
        
        // Add more listening time to a song that wasn't at the top
        favoriteQueue->updateListeningTime(sampleSongs[4], 400);  // Yesterday - 6.7 minutes
        
        std::cout << "New top song: " << favoriteQueue->getTopFavorite().getTitle() << std::endl;
        std::cout << std::endl;
        
        // Step 9: Final display
        std::cout << "Step 9: Final favorites list (auto-sorted)" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        favoriteQueue->displayFavorites();
        std::cout << std::endl;
        
        std::cout << "🎉 Demo completed! The priority queue automatically" << std::endl;
        std::cout << "maintained the correct order based on listening time." << std::endl;
        std::cout << std::endl;
        
        std::cout << "Key Features Demonstrated:" << std::endl;
        std::cout << "✓ Priority Queue (Max Heap) implementation" << std::endl;
        std::cout << "✓ Auto-sorting by total listening duration" << std::endl;
        std::cout << "✓ Real-time updates and reordering" << std::endl;
        std::cout << "✓ Secondary sorting by play count" << std::endl;
        std::cout << "✓ Time range filtering" << std::endl;
        std::cout << "✓ Statistics and analytics" << std::endl;
        std::cout << std::endl;
    }
};

int main() {
    AutoSortDemo demo;
    demo.runDemo();
    return 0;
} 