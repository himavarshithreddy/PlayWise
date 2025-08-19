#ifndef SONG_DATABASE_H
#define SONG_DATABASE_H

#include "song.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <iostream>

/**
 * @brief SongDatabase class implementing a HashMap for instant song lookup
 * 
 * This class provides O(1) average time complexity for song lookups by ID or title.
 * It maintains synchronization with other data structures and provides efficient
 * search and retrieval operations.
 * 
 * Time Complexity Analysis:
 * - insert_song: O(1) average
 * - search_by_id: O(1) average
 * - search_by_title: O(1) average
 * - delete_song: O(1) average
 * - update_song: O(1) average
 * 
 * Space Complexity: O(n) where n is the number of songs
 */
class SongDatabase {
private:
    std::unordered_map<std::string, Song> songsById;      // song_id -> Song
    // Track unique composite keys (normalized title + artist) to prevent duplicates
    std::unordered_set<std::string> titleArtistKeys; 
    
    // Helper methods
    std::string normalizeString(const std::string& str) const;
    bool isValidSongId(const std::string& songId) const;
    std::string generateCompositeKey(const std::string& title, const std::string& artist) const;

public:
    // Constructors and Destructor
    SongDatabase();
    ~SongDatabase();
    
    // Copy constructor and assignment operator
    SongDatabase(const SongDatabase& other);
    SongDatabase& operator=(const SongDatabase& other);

    // Core operations
    bool insert_song(const Song& song);
    bool delete_song(const std::string& songId);
    bool update_song(const Song& song);
    bool update_song_rating(const std::string& songId, int newRating);
    
    // Search operations
    Song* search_by_id(const std::string& songId);
    Song* search_by_title(const std::string& title);
    std::vector<Song> search_by_artist(const std::string& artist) const;
    std::vector<Song> search_by_album(const std::string& album) const;
    std::vector<Song> search_by_genre(const std::string& genre) const;
    
    // Utility operations
    void display_database() const;
    void display_stats() const;
    int get_size() const;
    bool is_empty() const;
    void clear();
    
    // Batch operations
    bool insert_songs(const std::vector<Song>& songs);
    std::vector<Song> get_all_songs() const;
    std::vector<std::string> get_all_artists() const;
    std::vector<std::string> get_all_albums() const;
    std::vector<std::string> get_all_genres() const;
    
    // Advanced search
    std::vector<Song> search_by_duration_range(int minDuration, int maxDuration) const;
    std::vector<Song> search_by_rating_range(int minRating, int maxRating) const;
    std::vector<Song> search_by_keyword(const std::string& keyword) const;
    
    // Database management
    bool contains_song(const std::string& songId) const;
    void sync_with_playlist(const std::vector<Song>& playlistSongs);
    void export_to_file(const std::string& filename) const;
    bool import_from_file(const std::string& filename);
    
    // Performance and statistics
    double get_load_factor() const;
    size_t get_bucket_count() const;
    size_t get_max_bucket_size() const;
    void rehash(size_t bucketCount);
};

#endif // SONG_DATABASE_H 