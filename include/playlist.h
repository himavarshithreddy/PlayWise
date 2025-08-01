#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include <string>
#include <iostream>

/**
 * @brief Node structure for doubly linked list implementation
 */
struct PlaylistNode {
    Song song;
    PlaylistNode* prev;
    PlaylistNode* next;
    
    PlaylistNode(const Song& song) : song(song), prev(nullptr), next(nullptr) {}
};

/**
 * @brief Playlist class implementing a doubly linked list for song management
 * 
 * This class provides all the core playlist operations including adding,
 * deleting, moving, and reversing songs. It uses a doubly linked list
 * for efficient insertion and deletion operations.
 * 
 * Time Complexity Analysis:
 * - add_song: O(1) at end, O(n) at specific position
 * - delete_song: O(n) to find, O(1) to delete
 * - move_song: O(n) to find both positions, O(1) to move
 * - reverse_playlist: O(n)
 * - display: O(n)
 * 
 * Space Complexity: O(n) where n is the number of songs
 */
class Playlist {
private:
    PlaylistNode* head;
    PlaylistNode* tail;
    std::string name;
    int size;
    
    // Helper methods
    PlaylistNode* getNodeAt(int index) const;
    void insertNode(PlaylistNode* newNode, PlaylistNode* afterNode);
    void removeNode(PlaylistNode* node);

public:
    // Constructors and Destructor
    Playlist();
    Playlist(const std::string& name);
    ~Playlist();
    
    // Copy constructor and assignment operator
    Playlist(const Playlist& other);
    Playlist& operator=(const Playlist& other);

    // Core playlist operations
    void add_song(const std::string& title, const std::string& artist, int duration);
    void add_song(const Song& song);
    void add_song_at(const Song& song, int position);
    
    bool delete_song(int index);
    bool delete_song_by_id(const std::string& songId);
    
    bool move_song(int from_index, int to_index);
    void reverse_playlist();
    
    // Utility operations
    void display() const;
    void display_reverse() const;
    int getSize() const;
    std::string getName() const;
    void setName(const std::string& name);
    bool isEmpty() const;
    
    // Search operations
    Song* find_song_by_id(const std::string& songId);
    Song* find_song_by_title(const std::string& title);
    int find_song_index(const std::string& songId);
    
    // Playlist management
    void clear();
    void shuffle();
    Song* get_song_at(int index);
    
    // Iterator-like functionality
    PlaylistNode* getHead() const;
    PlaylistNode* getTail() const;
};

#endif // PLAYLIST_H 