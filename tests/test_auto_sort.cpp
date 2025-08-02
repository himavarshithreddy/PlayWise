#include "../include/favorite_songs_queue.h"
#include "../include/song.h"
#include <iostream>
#include <cassert>
#include <vector>

/**
 * @brief Test suite for Auto-Sorting Favorite Songs Queue
 * 
 * This test file verifies the core functionality of the priority queue
 * that automatically sorts songs by listening duration.
 */

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    FavoriteSongsQueue queue;
    
    // Test empty queue
    assert(queue.isEmpty());
    assert(queue.getSize() == 0);
    
    // Add songs
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    Song song2("2", "Hotel California", "Eagles", 391, 5);
    
    queue.addSong(song1);
    queue.addSong(song2);
    
    assert(!queue.isEmpty());
    assert(queue.getSize() == 2);
    assert(queue.isInFavorites(song1));
    assert(queue.isInFavorites(song2));
    
    std::cout << "✓ Basic operations test passed" << std::endl;
}

void testAutoSorting() {
    std::cout << "Testing auto-sorting functionality..." << std::endl;
    
    FavoriteSongsQueue queue;
    
    // Add songs with different listening times
    Song song1("1", "Song A", "Artist A", 180, 4);
    Song song2("2", "Song B", "Artist B", 240, 4);
    Song song3("3", "Song C", "Artist C", 120, 4);
    
    queue.addSong(song1);
    queue.addSong(song2);
    queue.addSong(song3);
    
    // Update listening times
    queue.updateListeningTime(song1, 300);  // Total: 300 seconds
    queue.updateListeningTime(song2, 150);  // Total: 150 seconds
    queue.updateListeningTime(song3, 400);  // Total: 400 seconds
    
    // Get top songs - should be sorted by listening time
    std::vector<Song> topSongs = queue.getTopFavorites(3);
    
    // Verify order: Song C (400s) > Song A (300s) > Song B (150s)
    assert(topSongs[0].getTitle() == "Song C");
    assert(topSongs[1].getTitle() == "Song A");
    assert(topSongs[2].getTitle() == "Song B");
    
    std::cout << "✓ Auto-sorting test passed" << std::endl;
}

void testMultiLevelSorting() {
    std::cout << "Testing multi-level sorting..." << std::endl;
    
    FavoriteSongsQueue queue;
    
    // Add songs with same listening time but different play counts
    Song song1("1", "Song A", "Artist A", 180, 4);
    Song song2("2", "Song B", "Artist B", 180, 4);
    Song song3("3", "Song C", "Artist C", 180, 4);
    
    queue.addSong(song1);
    queue.addSong(song2);
    queue.addSong(song3);
    
    // Set same listening time but different play counts
    queue.updateListeningTime(song1, 300);
    queue.updateListeningTime(song2, 300);
    queue.updateListeningTime(song3, 300);
    
    queue.incrementPlayCount(song1);  // Play count: 1
    queue.incrementPlayCount(song2);  // Play count: 1
    queue.incrementPlayCount(song2);  // Play count: 2
    queue.incrementPlayCount(song3);  // Play count: 1
    queue.incrementPlayCount(song3);  // Play count: 2
    queue.incrementPlayCount(song3);  // Play count: 3
    
    // Get top songs - should be sorted by play count when listening time is equal
    std::vector<Song> topSongs = queue.getTopFavorites(3);
    
    // Verify order: Song C (3 plays) > Song B (2 plays) > Song A (1 play)
    assert(topSongs[0].getTitle() == "Song C");
    assert(topSongs[1].getTitle() == "Song B");
    assert(topSongs[2].getTitle() == "Song A");
    
    std::cout << "✓ Multi-level sorting test passed" << std::endl;
}

void testAutoUpdateFromPlayback() {
    std::cout << "Testing auto-update from playback..." << std::endl;
    
    FavoriteSongsQueue queue;
    
    Song song("1", "Test Song", "Test Artist", 240, 4);
    
    // Auto-update should add song and update stats
    queue.autoUpdateFromPlayback(song, 180);
    
    assert(queue.isInFavorites(song));
    assert(queue.getListeningTime(song) == 180);
    assert(queue.getPlayCount(song) == 1);
    
    // Second playback should update existing stats
    queue.autoUpdateFromPlayback(song, 120);
    
    assert(queue.getListeningTime(song) == 300);
    assert(queue.getPlayCount(song) == 2);
    
    std::cout << "✓ Auto-update from playback test passed" << std::endl;
}

void testStatistics() {
    std::cout << "Testing statistics functionality..." << std::endl;
    
    FavoriteSongsQueue queue;
    
    Song song1("1", "Song A", "Artist A", 180, 4);
    Song song2("2", "Song B", "Artist B", 240, 4);
    
    queue.addSong(song1);
    queue.addSong(song2);
    
    queue.updateListeningTime(song1, 300);
    queue.updateListeningTime(song2, 150);
    
    // Test statistics
    assert(queue.getSize() == 2);
    assert(queue.getTotalListeningTime() == 450);
    assert(queue.getAverageListeningTime() == 225.0);
    
    // Test time range filtering
    std::vector<Song> filtered = queue.getFavoritesByTimeRange(200, 400);
    assert(filtered.size() == 1);
    assert(filtered[0].getTitle() == "Song A");
    
    std::cout << "✓ Statistics test passed" << std::endl;
}

void testQueueRebuilding() {
    std::cout << "Testing queue rebuilding..." << std::endl;
    
    FavoriteSongsQueue queue;
    
    Song song1("1", "Song A", "Artist A", 180, 4);
    Song song2("2", "Song B", "Artist B", 240, 4);
    Song song3("3", "Song C", "Artist C", 200, 4);
    
    queue.addSong(song1);
    queue.addSong(song2);
    queue.addSong(song3);
    
    // Initial order
    std::vector<Song> initial = queue.getTopFavorites(3);
    
    // Update listening times to change order
    queue.updateListeningTime(song1, 100);
    queue.updateListeningTime(song2, 300);
    queue.updateListeningTime(song3, 200);
    
    // Get new order
    std::vector<Song> updated = queue.getTopFavorites(3);
    
    // Verify order changed
    assert(updated[0].getTitle() == "Song B");  // 300 seconds
    assert(updated[1].getTitle() == "Song C");  // 200 seconds
    assert(updated[2].getTitle() == "Song A");  // 100 seconds
    
    std::cout << "✓ Queue rebuilding test passed" << std::endl;
}

int main() {
    std::cout << "🎵 PlayWise Auto-Sorting Queue Test Suite 🎵" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << std::endl;
    
    try {
        testBasicOperations();
        testAutoSorting();
        testMultiLevelSorting();
        testAutoUpdateFromPlayback();
        testStatistics();
        testQueueRebuilding();
        
        std::cout << std::endl;
        std::cout << "🎉 All tests passed successfully! 🎉" << std::endl;
        std::cout << "The auto-sorting favorite songs queue is working correctly." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 