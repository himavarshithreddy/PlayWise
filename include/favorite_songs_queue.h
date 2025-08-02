#ifndef FAVORITE_SONGS_QUEUE_H
#define FAVORITE_SONGS_QUEUE_H

#include "song.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

/**
 * @brief Sorted Queue of Favorite Songs
 * 
 * This class implements a priority queue that maintains songs sorted by
 * total listening duration. It automatically keeps the most listened songs
 * at the top of the queue.
 * 
 * Time Complexity: O(log n) for insert/remove operations
 * Space Complexity: O(n) for storing songs and their listening counts
 */
class FavoriteSongsQueue {
private:
    // Structure to hold song with listening duration
    struct SongWithDuration {
        Song song;
        int totalListeningTime;  // in seconds
        int playCount;
        
        SongWithDuration(const Song& s, int duration = 0, int count = 0)
            : song(s), totalListeningTime(duration), playCount(count) {}
        
        // Comparison operator for priority queue (max heap)
        bool operator<(const SongWithDuration& other) const {
            // Primary sort by total listening time (descending)
            if (totalListeningTime != other.totalListeningTime) {
                return totalListeningTime < other.totalListeningTime;
            }
            // Secondary sort by play count (descending)
            if (playCount != other.playCount) {
                return playCount < other.playCount;
            }
            // Tertiary sort by song title (ascending)
            return song.getTitle() > other.song.getTitle();
        }
    };
    
    // Priority queue (max heap) to maintain sorted order
    std::priority_queue<SongWithDuration> songQueue;
    
    // Hash map to track listening duration for each song
    std::unordered_map<std::string, int> songListeningTime;
    
    // Hash map to track play count for each song
    std::unordered_map<std::string, int> songPlayCount;
    
    // Helper function to generate song key
    std::string generateSongKey(const Song& song) const;
    
    // Helper function to rebuild the priority queue
    void rebuildQueue();

public:
    // Constructor
    FavoriteSongsQueue();
    
    // Add a song to favorites
    void addSong(const Song& song);
    
    // Remove a song from favorites
    void removeSong(const Song& song);
    
    // Update listening duration for a song
    void updateListeningTime(const Song& song, int additionalSeconds);
    
    // Update play count for a song
    void incrementPlayCount(const Song& song);
    
    // Get the top favorite song (most listened)
    Song getTopFavorite() const;
    
    // Get top N favorite songs
    std::vector<Song> getTopFavorites(int count) const;
    
    // Get listening duration for a song
    int getListeningTime(const Song& song) const;
    
    // Get play count for a song
    int getPlayCount(const Song& song) const;
    
    // Check if a song is in favorites
    bool isInFavorites(const Song& song) const;
    
    // Get total number of favorite songs
    size_t getSize() const;
    
    // Check if queue is empty
    bool isEmpty() const;
    
    // Clear all favorites
    void clear();
    
    // Display all favorite songs with their stats
    void displayFavorites() const;
    
    // Get all favorite songs as a vector
    std::vector<Song> getAllFavorites() const;

    // Advanced features
    std::vector<Song> get_recent_songs(int count) const;
    void export_history_to_file(const std::string& filename) const;
    
    // Enhanced auto-sorting features
    void autoUpdateFromPlayback(const Song& song, int playbackDuration);
    void syncWithHistory(const std::vector<Song>& playedSongs);
    std::vector<Song> getFavoritesByTimeRange(int minSeconds, int maxSeconds) const;
    double getAverageListeningTime() const;
    int getTotalListeningTime() const;
    void optimizeQueue();  // Rebuild queue more efficiently
    void exportFavoritesToFile(const std::string& filename) const;
    void importFavoritesFromFile(const std::string& filename);
    
    // Statistics and analytics
    struct FavoriteStats {
        int totalSongs;
        int totalListeningTime;
        double averageListeningTime;
        Song mostListenedSong;
        int mostListenedTime;
    };
    
    FavoriteStats getStatistics() const;
    void displayDetailedStats() const;
};

#endif // FAVORITE_SONGS_QUEUE_H 