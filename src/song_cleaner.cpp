#include "../include/song_cleaner.h"
#include <iostream>
#include <sstream>

// Constructor
SongCleaner::SongCleaner() {
    // Initialize empty cleaner
}

// Helper function to normalize strings for comparison
std::string SongCleaner::normalizeString(const std::string& str) const {
    std::string normalized = str;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    
    // Remove extra whitespace
    std::stringstream ss(normalized);
    std::string token, result;
    while (ss >> token) {
        if (!result.empty()) result += " ";
        result += token;
    }
    
    return result;
}

// Helper function to generate composite key
std::string SongCleaner::generateCompositeKey(const std::string& title, const std::string& artist) const {
    std::string normalizedTitle = normalizeString(title);
    std::string normalizedArtist = normalizeString(artist);
    return normalizedTitle + "|||" + normalizedArtist; // Using ||| as separator
}

// Check if a song is a duplicate
bool SongCleaner::isDuplicate(const Song& song) const {
    std::string key = generateCompositeKey(song.getTitle(), song.getArtist());
    return uniqueSongKeys.find(key) != uniqueSongKeys.end();
}

// Add a song to the cleaner (returns true if added, false if duplicate)
bool SongCleaner::addSong(const Song& song) {
    if (isDuplicate(song)) {
        return false; // Song is a duplicate
    }
    
    std::string key = generateCompositeKey(song.getTitle(), song.getArtist());
    uniqueSongKeys.insert(key);
    return true;
}

// Remove a song from the cleaner
void SongCleaner::removeSong(const Song& song) {
    std::string key = generateCompositeKey(song.getTitle(), song.getArtist());
    uniqueSongKeys.erase(key);
}

// Clean a vector of songs, removing duplicates
std::vector<Song> SongCleaner::cleanDuplicates(const std::vector<Song>& songs) {
    std::vector<Song> cleanedSongs;
    std::unordered_set<std::string> seenKeys;
    
    for (const Song& song : songs) {
        std::string key = generateCompositeKey(song.getTitle(), song.getArtist());
        
        if (seenKeys.find(key) == seenKeys.end()) {
            seenKeys.insert(key);
            cleanedSongs.push_back(song);
        }
    }
    
    return cleanedSongs;
}

// Get statistics about the cleaner
size_t SongCleaner::getUniqueSongCount() const {
    return uniqueSongKeys.size();
}

// Clear all stored song keys
void SongCleaner::clear() {
    uniqueSongKeys.clear();
}

// Check if cleaner is empty
bool SongCleaner::isEmpty() const {
    return uniqueSongKeys.empty();
} 