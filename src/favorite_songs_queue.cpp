#include "../include/favorite_songs_queue.h"
#include "../include/logger.h"
#include <iostream>
#include <algorithm>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <fstream> // For file operations
#include <unordered_map> // For unordered_map

// Constructor
FavoriteSongsQueue::FavoriteSongsQueue() {
    // Initialize empty queue
}

// Helper function to generate song key
std::string FavoriteSongsQueue::generateSongKey(const Song& song) const {
    return song.getTitle() + "|||" + song.getArtist();
}

// Add a song to favorites
void FavoriteSongsQueue::addSong(const Song& song) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::string key = generateSongKey(song);
    
    // If song is not already in favorites, add it
    if (songListeningTime.find(key) == songListeningTime.end()) {
        songListeningTime[key] = 0;
        songPlayCount[key] = 0;
        
        // Add to priority queue
        SongWithDuration songWithDuration(song, 0, 0);
        songQueue.push(songWithDuration);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::string details = "Added song: " + song.getTitle() + " by " + song.getArtist();
        LOG_QUEUE_OP("ADD_SONG", details, songQueue.size(), duration_us);
    } else {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::string details = "Song already exists: " + song.getTitle() + " by " + song.getArtist();
        LOG_QUEUE_OP("ADD_SONG_SKIP", details, songQueue.size(), duration_us);
    }
}

// Remove a song from favorites
void FavoriteSongsQueue::removeSong(const Song& song) {
    std::string key = generateSongKey(song);
    
    // Remove from tracking maps
    songListeningTime.erase(key);
    songPlayCount.erase(key);
    
    // Rebuild queue without the removed song
    std::priority_queue<SongWithDuration> newQueue;
    std::vector<SongWithDuration> tempSongs;
    
    // Extract all songs from current queue
    while (!songQueue.empty()) {
        SongWithDuration current = songQueue.top();
        songQueue.pop();
        
        std::string currentKey = generateSongKey(current.song);
        if (currentKey != key) {
            tempSongs.push_back(current);
        }
    }
    
    // Rebuild queue with remaining songs
    for (const SongWithDuration& songWithDuration : tempSongs) {
        songQueue.push(songWithDuration);
    }
}

// Update listening duration for a song
void FavoriteSongsQueue::updateListeningTime(const Song& song, int additionalSeconds) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::string key = generateSongKey(song);
    
    // Add song to favorites if not already present
    if (songListeningTime.find(key) == songListeningTime.end()) {
        addSong(song);
    }
    
    // Update listening time
    songListeningTime[key] += additionalSeconds;
    
    // Rebuild queue to maintain correct order
    rebuildQueue();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Updated listening time for: " + song.getTitle() + " (+" + std::to_string(additionalSeconds) + "s)";
    LOG_QUEUE_OP("UPDATE_LISTENING_TIME", details, songQueue.size(), duration_us);
}

// Update play count for a song
void FavoriteSongsQueue::incrementPlayCount(const Song& song) {
    std::string key = generateSongKey(song);
    
    // Add song to favorites if not already present
    if (songPlayCount.find(key) == songPlayCount.end()) {
        addSong(song);
    }
    
    // Increment play count
    songPlayCount[key]++;
    
    // Rebuild queue to maintain correct order
    rebuildQueue();
}

// Helper function to rebuild the priority queue
void FavoriteSongsQueue::rebuildQueue() {
    std::priority_queue<SongWithDuration> newQueue;
    
    // Create a temporary vector to hold all songs
    std::vector<SongWithDuration> tempSongs;
    
    // Extract all songs from current queue
    while (!songQueue.empty()) {
        tempSongs.push_back(songQueue.top());
        songQueue.pop();
    }
    
    // Rebuild queue with updated durations and counts
    for (const SongWithDuration& songWithDuration : tempSongs) {
        std::string key = generateSongKey(songWithDuration.song);
        
        int currentListeningTime = songListeningTime[key];
        int currentPlayCount = songPlayCount[key];
        
        SongWithDuration updatedSong(songWithDuration.song, currentListeningTime, currentPlayCount);
        newQueue.push(updatedSong);
    }
    
    songQueue = newQueue;
}

// Get the top favorite song (most listened)
Song FavoriteSongsQueue::getTopFavorite() const {
    if (songQueue.empty()) {
        // Return empty song if queue is empty
        return Song();
    }
    return songQueue.top().song;
}

// Get top N favorite songs
std::vector<Song> FavoriteSongsQueue::getTopFavorites(int count) const {
    std::vector<Song> topSongs;
    
    // Create a copy of the queue to avoid modifying the original
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    
    int songsToGet = std::min(count, static_cast<int>(songQueue.size()));
    
    for (int i = 0; i < songsToGet; i++) {
        if (!tempQueue.empty()) {
            topSongs.push_back(tempQueue.top().song);
            tempQueue.pop();
        }
    }
    
    return topSongs;
}

// Get listening duration for a song
int FavoriteSongsQueue::getListeningTime(const Song& song) const {
    std::string key = generateSongKey(song);
    auto it = songListeningTime.find(key);
    return (it != songListeningTime.end()) ? it->second : 0;
}

// Get play count for a song
int FavoriteSongsQueue::getPlayCount(const Song& song) const {
    std::string key = generateSongKey(song);
    auto it = songPlayCount.find(key);
    return (it != songPlayCount.end()) ? it->second : 0;
}

// Check if a song is in favorites
bool FavoriteSongsQueue::isInFavorites(const Song& song) const {
    std::string key = generateSongKey(song);
    return songListeningTime.find(key) != songListeningTime.end();
}

// Get total number of favorite songs
size_t FavoriteSongsQueue::getSize() const {
    return songQueue.size();
}

// Check if queue is empty
bool FavoriteSongsQueue::isEmpty() const {
    return songQueue.empty();
}

// Clear all favorites
void FavoriteSongsQueue::clear() {
    while (!songQueue.empty()) {
        songQueue.pop();
    }
    songListeningTime.clear();
    songPlayCount.clear();
}

// Display all favorite songs with their stats
void FavoriteSongsQueue::displayFavorites() const {
    if (songQueue.empty()) {
        std::cout << "No favorite songs found." << std::endl;
        return;
    }
    
    std::cout << "=== Favorite Songs (Sorted by Listening Time) ===" << std::endl;
    
    // Create a copy of the queue to display
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    int rank = 1;
    
    while (!tempQueue.empty()) {
        const SongWithDuration& songWithDuration = tempQueue.top();
        const Song& song = songWithDuration.song;
        
        std::cout << rank << ". " << song.getTitle() << " - " << song.getArtist() << std::endl;
        std::cout << "   Listening Time: " << songWithDuration.totalListeningTime / 60 
                  << " min " << songWithDuration.totalListeningTime % 60 << " sec" << std::endl;
        std::cout << "   Play Count: " << songWithDuration.playCount << std::endl;
        std::cout << "   Duration: " << song.getDurationString() << std::endl;
        std::cout << "   Rating: " << song.getRating() << "/5" << std::endl;
        std::cout << "   ------------------------" << std::endl;
        
        tempQueue.pop();
        rank++;
    }
}

// Get all favorite songs as a vector
std::vector<Song> FavoriteSongsQueue::getAllFavorites() const {
    std::vector<Song> allSongs;
    
    // Create a copy of the queue
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    
    while (!tempQueue.empty()) {
        allSongs.push_back(tempQueue.top().song);
        tempQueue.pop();
    }
    
    return allSongs;
}

// Enhanced auto-sorting features

// Auto-update from playback - automatically adds song and updates listening time
void FavoriteSongsQueue::autoUpdateFromPlayback(const Song& song, int playbackDuration) {
    std::string key = generateSongKey(song);
    
    // Add song to favorites if not already present
    if (songListeningTime.find(key) == songListeningTime.end()) {
        addSong(song);
    }
    
    // Update listening time and play count
    songListeningTime[key] += playbackDuration;
    songPlayCount[key]++;
    
    // Rebuild queue to maintain correct order
    rebuildQueue();
}

// Sync with history - update favorites based on played songs
void FavoriteSongsQueue::syncWithHistory(const std::vector<Song>& playedSongs) {
    // Count occurrences of each song in history
    std::unordered_map<std::string, int> songCounts;
    std::unordered_map<std::string, Song> songMap;
    
    for (const Song& song : playedSongs) {
        std::string key = generateSongKey(song);
        songCounts[key]++;
        songMap[key] = song;
    }
    
    // Update favorites based on play history
    for (const auto& pair : songCounts) {
        const std::string& key = pair.first;
        int count = pair.second;
        const Song& song = songMap[key];
        
        // Estimate listening time (assuming average song duration)
        int estimatedDuration = song.getDuration() * count;
        
        // Add to favorites if not present
        if (songListeningTime.find(key) == songListeningTime.end()) {
            addSong(song);
        }
        
        // Update listening time and play count
        songListeningTime[key] += estimatedDuration;
        songPlayCount[key] += count;
    }
    
    // Rebuild queue
    rebuildQueue();
}

// Get favorites by time range
std::vector<Song> FavoriteSongsQueue::getFavoritesByTimeRange(int minSeconds, int maxSeconds) const {
    std::vector<Song> filteredSongs;
    
    // Create a copy of the queue
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    
    while (!tempQueue.empty()) {
        const SongWithDuration& songWithDuration = tempQueue.top();
        
        if (songWithDuration.totalListeningTime >= minSeconds && 
            songWithDuration.totalListeningTime <= maxSeconds) {
            filteredSongs.push_back(songWithDuration.song);
        }
        
        tempQueue.pop();
    }
    
    return filteredSongs;
}

// Get average listening time
double FavoriteSongsQueue::getAverageListeningTime() const {
    if (songQueue.empty()) {
        return 0.0;
    }
    
    int totalTime = 0;
    int songCount = 0;
    
    // Create a copy of the queue
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    
    while (!tempQueue.empty()) {
        totalTime += tempQueue.top().totalListeningTime;
        songCount++;
        tempQueue.pop();
    }
    
    return static_cast<double>(totalTime) / songCount;
}

// Get total listening time
int FavoriteSongsQueue::getTotalListeningTime() const {
    int totalTime = 0;
    
    // Create a copy of the queue
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    
    while (!tempQueue.empty()) {
        totalTime += tempQueue.top().totalListeningTime;
        tempQueue.pop();
    }
    
    return totalTime;
}

// Optimize queue - more efficient rebuild
void FavoriteSongsQueue::optimizeQueue() {
    // Only rebuild if there are significant changes
    // This is a placeholder for future optimization
    rebuildQueue();
}

// Export favorites to file
void FavoriteSongsQueue::exportFavoritesToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file for writing." << std::endl;
        return;
    }
    
    file << "Favorite Songs Export" << std::endl;
    file << "=====================" << std::endl;
    file << "Total Songs: " << songQueue.size() << std::endl;
    file << "Total Listening Time: " << getTotalListeningTime() << " seconds" << std::endl;
    file << "Average Listening Time: " << getAverageListeningTime() << " seconds" << std::endl;
    file << std::endl;
    
    // Create a copy of the queue
    std::priority_queue<SongWithDuration> tempQueue = songQueue;
    int rank = 1;
    
    while (!tempQueue.empty()) {
        const SongWithDuration& songWithDuration = tempQueue.top();
        const Song& song = songWithDuration.song;
        
        file << rank << ". " << song.getTitle() << " - " << song.getArtist() << std::endl;
        file << "   Listening Time: " << songWithDuration.totalListeningTime << " seconds" << std::endl;
        file << "   Play Count: " << songWithDuration.playCount << std::endl;
        file << "   Duration: " << song.getDuration() << " seconds" << std::endl;
        file << "   Rating: " << song.getRating() << "/5" << std::endl;
        file << std::endl;
        
        tempQueue.pop();
        rank++;
    }
    
    file.close();
    std::cout << "Favorites exported to " << filename << std::endl;
}

// Import favorites from file (basic implementation)
void FavoriteSongsQueue::importFavoritesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file for reading." << std::endl;
        return;
    }
    
    // Clear current favorites
    clear();
    
    std::string line;
    // Skip header lines
    for (int i = 0; i < 6; i++) {
        std::getline(file, line);
    }
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // Parse song data (simplified parsing)
        // This is a basic implementation - could be enhanced
        if (line.find(". ") != std::string::npos) {
            size_t pos = line.find(". ");
            std::string songInfo = line.substr(pos + 2);
            
            size_t dashPos = songInfo.find(" - ");
            if (dashPos != std::string::npos) {
                std::string title = songInfo.substr(0, dashPos);
                std::string artist = songInfo.substr(dashPos + 3);
                
                // Create a basic song object
                Song newSong("", title, artist, 180, 3);
                addSong(newSong);
            }
        }
    }
    
    file.close();
    std::cout << "Favorites imported from " << filename << std::endl;
}

// Get comprehensive statistics
FavoriteSongsQueue::FavoriteStats FavoriteSongsQueue::getStatistics() const {
    FavoriteStats stats;
    stats.totalSongs = static_cast<int>(songQueue.size());
    stats.totalListeningTime = getTotalListeningTime();
    stats.averageListeningTime = getAverageListeningTime();
    
    if (!songQueue.empty()) {
        stats.mostListenedSong = songQueue.top().song;
        stats.mostListenedTime = songQueue.top().totalListeningTime;
    }
    
    return stats;
}

// Display detailed statistics
void FavoriteSongsQueue::displayDetailedStats() const {
    FavoriteStats stats = getStatistics();
    
    std::cout << "=== Favorite Songs Statistics ===" << std::endl;
    std::cout << "Total Songs: " << stats.totalSongs << std::endl;
    std::cout << "Total Listening Time: " << stats.totalListeningTime / 60 
              << " min " << stats.totalListeningTime % 60 << " sec" << std::endl;
    std::cout << "Average Listening Time: " << static_cast<int>(stats.averageListeningTime / 60)
              << " min " << static_cast<int>(stats.averageListeningTime) % 60 << " sec" << std::endl;
    
    if (stats.totalSongs > 0) {
        std::cout << "Most Listened Song: " << stats.mostListenedSong.getTitle() 
                  << " - " << stats.mostListenedSong.getArtist() << std::endl;
        std::cout << "Most Listened Time: " << stats.mostListenedTime / 60 
                  << " min " << stats.mostListenedTime % 60 << " sec" << std::endl;
    }
    
    std::cout << "================================" << std::endl;
} 