#include "../include/history.h"
#include <fstream>
#include <algorithm>
#include <unordered_map>

// Constructor
History::History() : maxSize(100) {}

History::History(int maxSize) : maxSize(maxSize) {
    if (maxSize <= 0) {
        this->maxSize = 100;  // Default value
    }
}

// Core operations
void History::add_played_song(const Song& song) {
    // Check if we need to remove oldest songs to maintain max size
    if (playbackHistory.size() >= static_cast<size_t>(maxSize)) {
        // Remove oldest songs by creating a temporary stack
        std::stack<Song> tempStack;
        size_t songsToKeep = static_cast<size_t>(maxSize) - 1;
        
        // Pop songs from original stack and push to temp (except the oldest)
        for (size_t i = 0; i < songsToKeep; i++) {
            tempStack.push(playbackHistory.top());
            playbackHistory.pop();
        }
        
        // Clear the original stack
        while (!playbackHistory.empty()) {
            playbackHistory.pop();
        }
        
        // Push back the songs we want to keep (in reverse order)
        while (!tempStack.empty()) {
            playbackHistory.push(tempStack.top());
            tempStack.pop();
        }
    }
    
    playbackHistory.push(song);
}

Song History::undo_last_play() {
    if (playbackHistory.empty()) {
        // Return an empty song if history is empty
        return Song();
    }
    
    Song lastSong = playbackHistory.top();
    playbackHistory.pop();
    return lastSong;
}

Song History::get_last_played() const {
    if (playbackHistory.empty()) {
        return Song();
    }
    return playbackHistory.top();
}

// Utility operations
void History::clear_history() {
    while (!playbackHistory.empty()) {
        playbackHistory.pop();
    }
}

int History::get_size() const {
    return playbackHistory.size();
}

bool History::is_empty() const {
    return playbackHistory.empty();
}

int History::get_max_size() const {
    return maxSize;
}

void History::set_max_size(int maxSize) {
    if (maxSize > 0) {
        this->maxSize = maxSize;
        
        // If current size exceeds new max size, remove oldest songs
        if (playbackHistory.size() > static_cast<size_t>(maxSize)) {
            remove_oldest_songs(static_cast<int>(playbackHistory.size() - static_cast<size_t>(maxSize)));
        }
    }
}

// Display operations
void History::display_history() const {
    std::cout << "\n=== Playback History ===" << std::endl;
    std::cout << "Size: " << get_size() << "/" << maxSize << " songs\n" << std::endl;
    
    if (is_empty()) {
        std::cout << "No playback history available!" << std::endl;
        return;
    }
    
    // Create a copy of the stack to display (since we can't iterate over stack directly)
    std::stack<Song> tempStack = playbackHistory;
    std::vector<Song> songs;
    
    // Pop all songs from temp stack and store in vector
    while (!tempStack.empty()) {
        songs.push_back(tempStack.top());
        tempStack.pop();
    }
    
    // Display songs in chronological order (oldest first)
    for (int i = songs.size() - 1; i >= 0; i--) {
        std::cout << songs.size() - i << ". ";
        std::cout << songs[i].getTitle() << " - " << songs[i].getArtist();
        std::cout << " (" << songs[i].getDurationString() << ")";
        if (songs[i].getRating() > 0) {
            std::cout << " [Rating: " << songs[i].getRating() << "/5]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void History::display_recent_songs(int count) const {
    if (count <= 0) return;
    
    std::cout << "\n=== Recent " << count << " Songs ===" << std::endl;
    
    if (is_empty()) {
        std::cout << "No recent songs available!" << std::endl;
        return;
    }
    
    // Create a copy of the stack
    std::stack<Song> tempStack = playbackHistory;
    std::vector<Song> recentSongs;
    
    // Get the most recent songs
    int actualCount = std::min(count, get_size());
    for (int i = 0; i < actualCount; i++) {
        if (!tempStack.empty()) {
            recentSongs.push_back(tempStack.top());
            tempStack.pop();
        }
    }
    
    // Display in reverse order (most recent first)
    for (size_t i = 0; i < recentSongs.size(); i++) {
        std::cout << i + 1 << ". ";
        std::cout << recentSongs[i].getTitle() << " - " << recentSongs[i].getArtist();
        std::cout << " (" << recentSongs[i].getDurationString() << ")";
        if (recentSongs[i].getRating() > 0) {
            std::cout << " [Rating: " << recentSongs[i].getRating() << "/5]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// History management
void History::remove_oldest_songs(int count) {
    if (count <= 0 || is_empty()) return;
    
    int songsToRemove = std::min(count, get_size());
    
    // Create a temporary stack
    std::stack<Song> tempStack;
    int songsToKeep = get_size() - songsToRemove;
    
    // Pop songs from original stack and push to temp (except the oldest ones)
    for (int i = 0; i < songsToKeep; i++) {
        tempStack.push(playbackHistory.top());
        playbackHistory.pop();
    }
    
    // Clear the original stack
    while (!playbackHistory.empty()) {
        playbackHistory.pop();
    }
    
    // Push back the songs we want to keep (in reverse order)
    while (!tempStack.empty()) {
        playbackHistory.push(tempStack.top());
        tempStack.pop();
    }
}

bool History::contains_song(const std::string& songId) const {
    std::stack<Song> tempStack = playbackHistory;
    
    while (!tempStack.empty()) {
        if (tempStack.top().getId() == songId) {
            return true;
        }
        tempStack.pop();
    }
    return false;
}

int History::get_song_play_count(const std::string& songId) const {
    std::stack<Song> tempStack = playbackHistory;
    int count = 0;
    
    while (!tempStack.empty()) {
        if (tempStack.top().getId() == songId) {
            count++;
        }
        tempStack.pop();
    }
    return count;
}

// Advanced features
std::vector<Song> History::get_recent_songs(int count) const {
    std::vector<Song> recentSongs;
    std::stack<Song> tempStack = playbackHistory;
    
    int actualCount = std::min(count, get_size());
    for (int i = 0; i < actualCount; i++) {
        if (!tempStack.empty()) {
            recentSongs.push_back(tempStack.top());
            tempStack.pop();
        }
    }
    
    return recentSongs;
}

void History::export_history_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    file << "Playback History Export" << std::endl;
    file << "=======================" << std::endl;
    file << "Total songs: " << get_size() << std::endl;
    file << "Max size: " << maxSize << std::endl;
    file << std::endl;
    
    if (is_empty()) {
        file << "No playback history available." << std::endl;
    } else {
        std::stack<Song> tempStack = playbackHistory;
        std::vector<Song> songs;
        
        while (!tempStack.empty()) {
            songs.push_back(tempStack.top());
            tempStack.pop();
        }
        
        for (int i = songs.size() - 1; i >= 0; i--) {
            file << songs.size() - i << ". ";
            file << songs[i].getTitle() << " - " << songs[i].getArtist();
            file << " (" << songs[i].getDurationString() << ")";
            if (songs[i].getRating() > 0) {
                file << " [Rating: " << songs[i].getRating() << "/5]";
            }
            file << std::endl;
        }
    }
    
    file.close();
    std::cout << "History exported to " << filename << std::endl;
} 