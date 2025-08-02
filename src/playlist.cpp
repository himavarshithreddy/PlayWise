#include "../include/playlist.h"
#include "../include/logger.h"
#include <algorithm>
#include <random>
#include <chrono>

// Constructor
Playlist::Playlist() : head(nullptr), tail(nullptr), name("Untitled Playlist"), size(0) {}

Playlist::Playlist(const std::string& name) : head(nullptr), tail(nullptr), name(name), size(0) {}

// Destructor
Playlist::~Playlist() {
    clear();
}

// Copy constructor
Playlist::Playlist(const Playlist& other) : head(nullptr), tail(nullptr), name(other.name), size(0) {
    PlaylistNode* current = other.head;
    while (current != nullptr) {
        add_song(current->song);
        current = current->next;
    }
}

// Assignment operator
Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        clear();
        name = other.name;
        PlaylistNode* current = other.head;
        while (current != nullptr) {
            add_song(current->song);
            current = current->next;
        }
    }
    return *this;
}

// Helper methods
PlaylistNode* Playlist::getNodeAt(int index) const {
    if (index < 0 || index >= size) return nullptr;
    
    PlaylistNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

void Playlist::insertNode(PlaylistNode* newNode, PlaylistNode* afterNode) {
    if (afterNode == nullptr) {
        // Insert at beginning
        newNode->next = head;
        newNode->prev = nullptr;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
    } else {
        // Insert after afterNode
        newNode->next = afterNode->next;
        newNode->prev = afterNode;
        if (afterNode->next != nullptr) {
            afterNode->next->prev = newNode;
        }
        afterNode->next = newNode;
        if (afterNode == tail) {
            tail = newNode;
        }
    }
    size++;
}

void Playlist::removeNode(PlaylistNode* node) {
    if (node == nullptr) return;
    
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    
    delete node;
    size--;
}

// Core playlist operations
void Playlist::add_song(const std::string& title, const std::string& artist, int duration) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Song song("", title, artist, duration);
    add_song(song);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Added song: " + title + " by " + artist;
    LOG_LL_OP("ADD_SONG", details, size, duration_us);
}

void Playlist::add_song(const Song& song) {
    auto start = std::chrono::high_resolution_clock::now();
    
    PlaylistNode* newNode = new PlaylistNode(song);
    insertNode(newNode, tail);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Added song: " + song.getTitle() + " by " + song.getArtist();
    LOG_LL_OP("ADD_SONG_OBJECT", details, size, duration_us);
}

void Playlist::add_song_at(const Song& song, int position) {
    if (position < 0 || position > size) return;
    
    PlaylistNode* newNode = new PlaylistNode(song);
    if (position == 0) {
        insertNode(newNode, nullptr);
    } else {
        PlaylistNode* afterNode = getNodeAt(position - 1);
        insertNode(newNode, afterNode);
    }
}

bool Playlist::delete_song(int index) {
    auto start = std::chrono::high_resolution_clock::now();
    
    PlaylistNode* node = getNodeAt(index);
    if (node == nullptr) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        LOG_LL_OP("DELETE_SONG_FAILED", "Invalid index: " + std::to_string(index), size, duration_us);
        return false;
    }
    
    std::string songTitle = node->song.getTitle();
    removeNode(node);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Deleted song: " + songTitle + " at index " + std::to_string(index);
    LOG_LL_OP("DELETE_SONG", details, size, duration_us);
    return true;
}

bool Playlist::delete_song_by_id(const std::string& songId) {
    int index = find_song_index(songId);
    if (index == -1) return false;
    
    return delete_song(index);
}

bool Playlist::move_song(int from_index, int to_index) {
    auto start = std::chrono::high_resolution_clock::now();
    
    if (from_index < 0 || from_index >= size || to_index < 0 || to_index >= size) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        LOG_LL_OP("MOVE_SONG_FAILED", "Invalid indices: " + std::to_string(from_index) + " -> " + std::to_string(to_index), size, duration_us);
        return false;
    }
    
    if (from_index == to_index) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        LOG_LL_OP("MOVE_SONG_SKIP", "Same position: " + std::to_string(from_index), size, duration_us);
        return true;
    }
    
    PlaylistNode* fromNode = getNodeAt(from_index);
    if (fromNode == nullptr) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        LOG_LL_OP("MOVE_SONG_FAILED", "Node not found at index: " + std::to_string(from_index), size, duration_us);
        return false;
    }
    
    // Store the song data before removing the node
    Song songToMove = fromNode->song;
    
    // Remove the node from its current position
    removeNode(fromNode);
    
    // Create a new node with the song data and insert at new position
    PlaylistNode* newNode = new PlaylistNode(songToMove);
    if (to_index == 0) {
        insertNode(newNode, nullptr);
    } else {
        PlaylistNode* afterNode = getNodeAt(to_index - 1);
        insertNode(newNode, afterNode);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Moved song: " + songToMove.getTitle() + " from " + std::to_string(from_index) + " to " + std::to_string(to_index);
    LOG_LL_OP("MOVE_SONG", details, size, duration_us);
    return true;
}

void Playlist::reverse_playlist() {
    if (size <= 1) return;
    
    PlaylistNode* current = head;
    PlaylistNode* temp = nullptr;
    
    // Swap prev and next pointers for all nodes
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    // Swap head and tail
    temp = head;
    head = tail;
    tail = temp;
}

// Utility operations
void Playlist::display() const {
    std::cout << "\n=== Playlist: " << name << " ===" << std::endl;
    std::cout << "Size: " << size << " songs\n" << std::endl;
    
    if (isEmpty()) {
        std::cout << "Playlist is empty!" << std::endl;
        return;
    }
    
    PlaylistNode* current = head;
    int index = 1;
    while (current != nullptr) {
        std::cout << index << ". ";
        std::cout << current->song.getTitle() << " - " << current->song.getArtist();
        std::cout << " (" << current->song.getDurationString() << ")";
        if (current->song.getRating() > 0) {
            std::cout << " [Rating: " << current->song.getRating() << "/5]";
        }
        std::cout << std::endl;
        current = current->next;
        index++;
    }
    std::cout << std::endl;
}

void Playlist::display_reverse() const {
    std::cout << "\n=== Playlist: " << name << " (Reverse Order) ===" << std::endl;
    std::cout << "Size: " << size << " songs\n" << std::endl;
    
    if (isEmpty()) {
        std::cout << "Playlist is empty!" << std::endl;
        return;
    }
    
    PlaylistNode* current = tail;
    int index = size;
    while (current != nullptr) {
        std::cout << index << ". ";
        std::cout << current->song.getTitle() << " - " << current->song.getArtist();
        std::cout << " (" << current->song.getDurationString() << ")";
        if (current->song.getRating() > 0) {
            std::cout << " [Rating: " << current->song.getRating() << "/5]";
        }
        std::cout << std::endl;
        current = current->prev;
        index--;
    }
    std::cout << std::endl;
}

int Playlist::getSize() const { return size; }
std::string Playlist::getName() const { return name; }
void Playlist::setName(const std::string& name) { this->name = name; }
bool Playlist::isEmpty() const { return size == 0; }

// Search operations
Song* Playlist::find_song_by_id(const std::string& songId) {
    PlaylistNode* current = head;
    while (current != nullptr) {
        if (current->song.getId() == songId) {
            return &(current->song);
        }
        current = current->next;
    }
    return nullptr;
}

Song* Playlist::find_song_by_title(const std::string& title) {
    PlaylistNode* current = head;
    while (current != nullptr) {
        if (current->song.getTitle() == title) {
            return &(current->song);
        }
        current = current->next;
    }
    return nullptr;
}

int Playlist::find_song_index(const std::string& songId) {
    PlaylistNode* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->song.getId() == songId) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// Playlist management
void Playlist::clear() {
    while (head != nullptr) {
        PlaylistNode* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

void Playlist::shuffle() {
    if (size <= 1) return;
    
    // Convert to vector for shuffling
    std::vector<Song> songs;
    PlaylistNode* current = head;
    while (current != nullptr) {
        songs.push_back(current->song);
        current = current->next;
    }
    
    // Shuffle the vector
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(songs.begin(), songs.end(), std::default_random_engine(seed));
    
    // Rebuild the playlist
    clear();
    for (const Song& song : songs) {
        add_song(song);
    }
}

Song* Playlist::get_song_at(int index) {
    PlaylistNode* node = getNodeAt(index);
    return node ? &(node->song) : nullptr;
}

// Iterator-like functionality
PlaylistNode* Playlist::getHead() const { return head; }
PlaylistNode* Playlist::getTail() const { return tail; } 