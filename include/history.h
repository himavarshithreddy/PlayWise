#ifndef HISTORY_H
#define HISTORY_H

#include "song.h"
#include <stack>
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief History class implementing a stack for playback history management
 * 
 * This class maintains a stack of recently played songs, allowing users
 * to undo their last played song and re-add it to the current playlist.
 * It uses the LIFO (Last In, First Out) principle which perfectly
 * matches the "undo" behavior.
 * 
 * Time Complexity Analysis:
 * - add_played_song: O(1) - push operation
 * - undo_last_play: O(1) - pop operation
 * - get_last_played: O(1) - top operation
 * - clear_history: O(n) - clear all elements
 * 
 * Space Complexity: O(n) where n is the number of songs in history
 */
class History {
private:
    std::stack<Song> playbackHistory;
    int maxSize;  // Maximum number of songs to keep in history

public:
    // Constructors
    History();
    History(int maxSize);
    
    // Core operations
    void add_played_song(const Song& song);
    Song undo_last_play();
    Song get_last_played() const;
    
    // Utility operations
    void clear_history();
    int get_size() const;
    bool is_empty() const;
    int get_max_size() const;
    void set_max_size(int maxSize);
    
    // Display operations
    void display_history() const;
    void display_recent_songs(int count) const;
    
    // History management
    void remove_oldest_songs(int count);
    bool contains_song(const std::string& songId) const;
    int get_song_play_count(const std::string& songId) const;
    
    // Advanced features
    std::vector<Song> get_recent_songs(int count) const;
    void export_history_to_file(const std::string& filename) const;
};

#endif // HISTORY_H 