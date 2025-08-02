#ifndef SONG_CLEANER_H
#define SONG_CLEANER_H

#include <string>
#include <unordered_set>
#include <vector>
#include <functional>
#include <algorithm>
#include <cctype>
#include "song.h"

/**
 * @brief Auto-Cleaner for Duplicate Songs
 * 
 * This class provides functionality to detect and remove duplicate songs
 * based on composite keys (song name + artist combination).
 * 
 * Time Complexity: O(1) average for duplicate detection
 * Space Complexity: O(n) for storing unique song keys
 */
class SongCleaner {
private:
    // HashSet to store unique song keys (title + artist)
    std::unordered_set<std::string> uniqueSongKeys;
    
    // Helper function to generate composite key
    std::string generateCompositeKey(const std::string& title, const std::string& artist) const;
    
    // Helper function to normalize strings for comparison
    std::string normalizeString(const std::string& str) const;

public:
    // Constructor
    SongCleaner();
    
    // Check if a song is a duplicate
    bool isDuplicate(const Song& song) const;
    
    // Add a song to the cleaner (returns true if added, false if duplicate)
    bool addSong(const Song& song);
    
    // Remove a song from the cleaner
    void removeSong(const Song& song);
    
    // Clean a vector of songs, removing duplicates
    std::vector<Song> cleanDuplicates(const std::vector<Song>& songs);
    
    // Get statistics about the cleaner
    size_t getUniqueSongCount() const;
    
    // Clear all stored song keys
    void clear();
    
    // Check if cleaner is empty
    bool isEmpty() const;
};

#endif // SONG_CLEANER_H 