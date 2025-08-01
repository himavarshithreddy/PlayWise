#ifndef RATING_TREE_H
#define RATING_TREE_H

#include "song.h"
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Node structure for Binary Search Tree implementation
 */
struct RatingNode {
    int rating;
    std::vector<Song> songs;  // Multiple songs can have the same rating
    RatingNode* left;
    RatingNode* right;
    
    RatingNode(int rating) : rating(rating), left(nullptr), right(nullptr) {}
};

/**
 * @brief RatingTree class implementing a Binary Search Tree for song rating management
 * 
 * This class organizes songs by their ratings (1-5 stars) in a BST structure.
 * Each node represents a rating bucket that can contain multiple songs with that rating.
 * This allows for efficient searching, insertion, and deletion by rating.
 * 
 * Time Complexity Analysis:
 * - insert_song: O(log n) average, O(n) worst case
 * - search_by_rating: O(log n) average, O(n) worst case
 * - delete_song: O(log n) average, O(n) worst case
 * - get_songs_by_rating: O(log n) average, O(n) worst case
 * 
 * Space Complexity: O(n) where n is the number of songs
 */
class RatingTree {
private:
    RatingNode* root;
    int totalSongs;
    
    // Helper methods
    RatingNode* insertNode(RatingNode* node, int rating);
    RatingNode* findNode(RatingNode* node, int rating) const;
    RatingNode* deleteNode(RatingNode* node, int rating);
    RatingNode* findMin(RatingNode* node) const;
    void clearTree(RatingNode* node);
    void inorderTraversal(RatingNode* node, std::vector<Song>& result) const;
    void getSongsByRatingHelper(RatingNode* node, int rating, std::vector<Song>& result) const;
    int getHeight(RatingNode* node) const;
    int getBalance(RatingNode* node) const;

public:
    // Constructors and Destructor
    RatingTree();
    ~RatingTree();
    
    // Copy constructor and assignment operator
    RatingTree(const RatingTree& other);
    RatingTree& operator=(const RatingTree& other);

    // Core operations
    void insert_song(const Song& song, int rating);
    bool delete_song(const std::string& songId, int rating);
    std::vector<Song> search_by_rating(int rating) const;
    std::vector<Song> get_songs_by_rating(int rating) const;
    
    // Utility operations
    void display_tree() const;
    void display_rating_stats() const;
    int get_total_songs() const;
    bool is_empty() const;
    int get_height() const;
    
    // Search and retrieval
    bool contains_song(const std::string& songId) const;
    Song* find_song(const std::string& songId) const;
    std::vector<Song> get_all_songs() const;
    std::vector<Song> get_songs_in_range(int minRating, int maxRating) const;
    
    // Tree management
    void clear();
    void balance_tree();
    std::vector<int> get_all_ratings() const;
    
    // Advanced features
    std::vector<Song> get_top_rated_songs(int count) const;
    double get_average_rating() const;
    int get_most_common_rating() const;
};

#endif // RATING_TREE_H 