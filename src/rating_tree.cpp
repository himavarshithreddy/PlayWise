#include "../include/rating_tree.h"
#include <algorithm>
#include <numeric>
#include <unordered_map>

// Constructor
RatingTree::RatingTree() : root(nullptr), totalSongs(0) {}

// Destructor
RatingTree::~RatingTree() {
    clearTree(root);
}

// Copy constructor
RatingTree::RatingTree(const RatingTree& other) : root(nullptr), totalSongs(0) {
    if (other.root != nullptr) {
        std::vector<Song> allSongs = other.get_all_songs();
        for (const Song& song : allSongs) {
            insert_song(song, song.getRating());
        }
    }
}

// Assignment operator
RatingTree& RatingTree::operator=(const RatingTree& other) {
    if (this != &other) {
        clear();
        if (other.root != nullptr) {
            std::vector<Song> allSongs = other.get_all_songs();
            for (const Song& song : allSongs) {
                insert_song(song, song.getRating());
            }
        }
    }
    return *this;
}

// Helper methods
RatingNode* RatingTree::insertNode(RatingNode* node, int rating) {
    if (node == nullptr) {
        return new RatingNode(rating);
    }
    
    if (rating < node->rating) {
        node->left = insertNode(node->left, rating);
    } else if (rating > node->rating) {
        node->right = insertNode(node->right, rating);
    }
    // If rating == node->rating, the node already exists, so we don't create a new one
    
    return node;
}

RatingNode* RatingTree::findNode(RatingNode* node, int rating) const {
    if (node == nullptr || node->rating == rating) {
        return node;
    }
    
    if (rating < node->rating) {
        return findNode(node->left, rating);
    } else {
        return findNode(node->right, rating);
    }
}

RatingNode* RatingTree::findMin(RatingNode* node) const {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

RatingNode* RatingTree::deleteNode(RatingNode* node, int rating) {
    if (node == nullptr) return nullptr;
    
    if (rating < node->rating) {
        node->left = deleteNode(node->left, rating);
    } else if (rating > node->rating) {
        node->right = deleteNode(node->right, rating);
    } else {
        // Node with the rating found
        if (node->left == nullptr) {
            RatingNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            RatingNode* temp = node->left;
            delete node;
            return temp;
        }
        
        // Node with two children
        RatingNode* temp = findMin(node->right);
        node->rating = temp->rating;
        node->songs = temp->songs;
        node->right = deleteNode(node->right, temp->rating);
    }
    
    return node;
}

void RatingTree::clearTree(RatingNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

void RatingTree::inorderTraversal(RatingNode* node, std::vector<Song>& result) const {
    if (node != nullptr) {
        inorderTraversal(node->left, result);
        result.insert(result.end(), node->songs.begin(), node->songs.end());
        inorderTraversal(node->right, result);
    }
}

void RatingTree::getSongsByRatingHelper(RatingNode* node, int rating, std::vector<Song>& result) const {
    if (node != nullptr) {
        if (rating < node->rating) {
            getSongsByRatingHelper(node->left, rating, result);
        } else if (rating > node->rating) {
            getSongsByRatingHelper(node->right, rating, result);
        } else {
            result.insert(result.end(), node->songs.begin(), node->songs.end());
        }
    }
}

int RatingTree::getHeight(RatingNode* node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

int RatingTree::getBalance(RatingNode* node) const {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Core operations
void RatingTree::insert_song(const Song& song, int rating) {
    if (rating < 1 || rating > 5) return;  // Validate rating range
    
    // Find or create the rating node
    RatingNode* ratingNode = findNode(root, rating);
    if (ratingNode == nullptr) {
        // Create new rating node
        root = insertNode(root, rating);
        ratingNode = findNode(root, rating);
    }
    
    // Add song to the rating bucket
    ratingNode->songs.push_back(song);
    totalSongs++;
}

bool RatingTree::delete_song(const std::string& songId, int rating) {
    RatingNode* ratingNode = findNode(root, rating);
    if (ratingNode == nullptr) return false;
    
    // Find and remove the song from the rating bucket
    auto it = std::find_if(ratingNode->songs.begin(), ratingNode->songs.end(),
                          [&songId](const Song& song) { return song.getId() == songId; });
    
    if (it != ratingNode->songs.end()) {
        ratingNode->songs.erase(it);
        totalSongs--;
        
        // If the rating bucket is empty, remove the node
        if (ratingNode->songs.empty()) {
            root = deleteNode(root, rating);
        }
        
        return true;
    }
    
    return false;
}

std::vector<Song> RatingTree::search_by_rating(int rating) const {
    return get_songs_by_rating(rating);
}

std::vector<Song> RatingTree::get_songs_by_rating(int rating) const {
    std::vector<Song> result;
    getSongsByRatingHelper(root, rating, result);
    return result;
}

// Utility operations
void RatingTree::display_tree() const {
    std::cout << "\n=== Rating Tree Structure ===" << std::endl;
    if (is_empty()) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    
    std::vector<int> ratings = get_all_ratings();
    for (int rating : ratings) {
        std::vector<Song> songs = get_songs_by_rating(rating);
        std::cout << "Rating " << rating << "/5 (" << songs.size() << " songs):" << std::endl;
        for (const Song& song : songs) {
            std::cout << "  - " << song.getTitle() << " - " << song.getArtist() << std::endl;
        }
        std::cout << std::endl;
    }
}

void RatingTree::display_rating_stats() const {
    std::cout << "\n=== Rating Statistics ===" << std::endl;
    std::cout << "Total songs: " << totalSongs << std::endl;
    std::cout << "Tree height: " << get_height() << std::endl;
    std::cout << "Average rating: " << get_average_rating() << std::endl;
    std::cout << "Most common rating: " << get_most_common_rating() << "/5" << std::endl;
    
    std::vector<int> ratings = get_all_ratings();
    for (int rating : ratings) {
        std::vector<Song> songs = get_songs_by_rating(rating);
        std::cout << "Rating " << rating << "/5: " << songs.size() << " songs" << std::endl;
    }
    std::cout << std::endl;
}

int RatingTree::get_total_songs() const { return totalSongs; }
bool RatingTree::is_empty() const { return root == nullptr; }
int RatingTree::get_height() const { return getHeight(root); }

// Search and retrieval
bool RatingTree::contains_song(const std::string& songId) const {
    return find_song(songId) != nullptr;
}

Song* RatingTree::find_song(const std::string& songId) const {
    std::vector<Song> allSongs = get_all_songs();
    for (Song& song : allSongs) {
        if (song.getId() == songId) {
            return &song;
        }
    }
    return nullptr;
}

std::vector<Song> RatingTree::get_all_songs() const {
    std::vector<Song> result;
    inorderTraversal(root, result);
    return result;
}

std::vector<Song> RatingTree::get_songs_in_range(int minRating, int maxRating) const {
    std::vector<Song> result;
    for (int rating = minRating; rating <= maxRating; rating++) {
        std::vector<Song> songs = get_songs_by_rating(rating);
        result.insert(result.end(), songs.begin(), songs.end());
    }
    return result;
}

// Tree management
void RatingTree::clear() {
    clearTree(root);
    root = nullptr;
    totalSongs = 0;
}

void RatingTree::balance_tree() {
    // Simple balancing - rebuild the tree
    std::vector<Song> allSongs = get_all_songs();
    clear();
    for (const Song& song : allSongs) {
        insert_song(song, song.getRating());
    }
}

std::vector<int> RatingTree::get_all_ratings() const {
    std::vector<int> ratings;
    std::vector<Song> allSongs = get_all_songs();
    for (const Song& song : allSongs) {
        int rating = song.getRating();
        if (std::find(ratings.begin(), ratings.end(), rating) == ratings.end()) {
            ratings.push_back(rating);
        }
    }
    std::sort(ratings.begin(), ratings.end());
    return ratings;
}

// Advanced features
std::vector<Song> RatingTree::get_top_rated_songs(int count) const {
    std::vector<Song> result;
    std::vector<int> ratings = get_all_ratings();
    
    // Start from highest rating
    for (auto it = ratings.rbegin(); it != ratings.rend(); ++it) {
        std::vector<Song> songs = get_songs_by_rating(*it);
        for (const Song& song : songs) {
            if (result.size() < static_cast<size_t>(count)) {
                result.push_back(song);
            } else {
                break;
            }
        }
        if (result.size() >= static_cast<size_t>(count)) break;
    }
    
    return result;
}

double RatingTree::get_average_rating() const {
    if (totalSongs == 0) return 0.0;
    
    std::vector<Song> allSongs = get_all_songs();
    double sum = 0.0;
    for (const Song& song : allSongs) {
        sum += song.getRating();
    }
    return sum / totalSongs;
}

int RatingTree::get_most_common_rating() const {
    std::unordered_map<int, int> ratingCounts;
    std::vector<Song> allSongs = get_all_songs();
    
    for (const Song& song : allSongs) {
        ratingCounts[song.getRating()]++;
    }
    
    int mostCommonRating = 0;
    int maxCount = 0;
    
    for (const auto& pair : ratingCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonRating = pair.first;
        }
    }
    
    return mostCommonRating;
} 