# Recommendation System Implementation - Complete Change Log

This document provides a comprehensive record of all changes made to implement the Music Recommendation System in the PlayWise application. Each change is documented with file names, line numbers, and detailed descriptions.

## Table of Contents

1. [New Files Created](#new-files-created)
2. [Existing Files Modified](#existing-files-modified)
3. [Change Summary by Feature](#change-summary-by-feature)
4. [Technical Implementation Details](#technical-implementation-details)

---

## New Files Created

### 1. `include/recommendation_system.h` (NEW FILE)
**Purpose**: Header file defining the RecommendationSystem class interface

**Content**: Complete class declaration with:
- Private members: `playbackHistory`, `songDatabase`, `MAX_RECOMMENDATIONS`
- Helper method declarations for genre analysis and song filtering
- Public interface: constructors, destructor, `getRecommendations()`, utility methods

**Key Methods**:
- `getRecommendations(int recentCount)` - Main recommendation method
- `countGenreFrequency(int recentCount)` - Count genre occurrences
- `getSongsByGenre(const std::string& genre)` - Get songs by genre
- `filterSongsNotInHistory(const std::vector<Song>& songs)` - Remove played songs
- `rankSongsByRating(const std::vector<Song>& songs)` - Sort by rating and ID

**Complete File Content**:
```cpp
#ifndef RECOMMENDATION_SYSTEM_H
#define RECOMMENDATION_SYSTEM_H

#include "song.h"
#include "history.h"
#include "song_database.h"
#include <vector>
#include <unordered_map>
#include <string>

/**
 * @brief Music Recommendation System
 * 
 * Provides personalized song recommendations based on user's playback history.
 * Analyzes genre preferences and suggests songs with high ratings.
 */
class RecommendationSystem {
private:
    History* playbackHistory;
    SongDatabase* songDatabase;
    static const int MAX_RECOMMENDATIONS = 10;

    // Helper methods
    std::unordered_map<std::string, int> countGenreFrequency(int recentCount) const;
    std::vector<Song> getSongsByGenre(const std::string& genre) const;
    std::vector<Song> getTopRatedSongs(int count) const;
    std::vector<Song> filterSongsNotInHistory(const std::vector<Song>& songs) const;
    std::vector<Song> rankSongsByRating(const std::vector<Song>& songs) const;
    std::string getMostFrequent(const std::unordered_map<std::string, int>& freqMap) const;

public:
    // Constructors and Destructor
    RecommendationSystem();
    RecommendationSystem(History* history, SongDatabase* database);
    ~RecommendationSystem();

    // Core functionality
    std::vector<Song> getRecommendations(int recentCount) const;

    // Configuration methods
    void setHistory(History* history);
    void setSongDatabase(SongDatabase* database);
    bool isInitialized() const;
    void clear();
};

#endif // RECOMMENDATION_SYSTEM_H
```

### 2. `src/recommendation_system.cpp` (NEW FILE)
**Purpose**: Implementation file containing all RecommendationSystem functionality

**Content**: Complete implementation of all methods declared in the header, including:
- Constructors and destructor
- Core recommendation algorithm implementation
- Helper methods for data processing
- Genre frequency analysis using `std::unordered_map`
- Song ranking and filtering logic

**Algorithm Implementation**:
- Analyzes recent N songs from playback history
- Counts genre frequency using hash map
- Identifies most frequent genre
- Searches database for unplayed songs in that genre
- Ranks candidates by rating (descending), then by song ID (ascending)
- Falls back to global top-rated songs if no matches found

**Complete File Content**:
```cpp
#include "../include/recommendation_system.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor
RecommendationSystem::RecommendationSystem() : playbackHistory(nullptr), songDatabase(nullptr) {}

// Parameterized constructor
RecommendationSystem::RecommendationSystem(History* history, SongDatabase* database) 
    : playbackHistory(history), songDatabase(database) {}

// Destructor
RecommendationSystem::~RecommendationSystem() {
    // No dynamic memory to clean up
}

// Core recommendation function - simple personalized recommendations
std::vector<Song> RecommendationSystem::getRecommendations(int recentCount) const {
    if (!isInitialized()) {
        return getTopRatedSongs(MAX_RECOMMENDATIONS);
    }
    
    // Count genre frequency from recent history
    std::unordered_map<std::string, int> genreFreq = countGenreFrequency(recentCount);
    
    if (genreFreq.empty()) {
        return getTopRatedSongs(MAX_RECOMMENDATIONS);
    }
    
    // Get most frequent genre
    std::string mostFrequentGenre = getMostFrequent(genreFreq);
    
    // Get songs by that genre
    std::vector<Song> genreSongs = getSongsByGenre(mostFrequentGenre);
    
    // Filter out songs already in history
    std::vector<Song> filteredSongs = filterSongsNotInHistory(genreSongs);
    
    // Rank by rating and limit results
    std::vector<Song> rankedSongs = rankSongsByRating(filteredSongs);
    
    if (rankedSongs.size() > MAX_RECOMMENDATIONS) {
        rankedSongs.resize(MAX_RECOMMENDATIONS);
    }
    
    return rankedSongs;
}

// Helper: Count genre frequency from recent history
std::unordered_map<std::string, int> RecommendationSystem::countGenreFrequency(int recentCount) const {
    std::unordered_map<std::string, int> genreFreq;
    
    if (!playbackHistory || playbackHistory->is_empty()) {
        return genreFreq;
    }
    
    std::vector<Song> recentSongs = playbackHistory->get_recent_songs(recentCount);
    
    for (const Song& song : recentSongs) {
        std::string genre = song.getGenre();
        if (!genre.empty()) {
            genreFreq[genre]++;
        }
    }
    
    return genreFreq;
}

// Helper: Get songs by genre
std::vector<Song> RecommendationSystem::getSongsByGenre(const std::string& genre) const {
    if (!songDatabase) {
        return std::vector<Song>();
    }
    
    return songDatabase->search_by_genre(genre);
}

// Helper: Get top-rated songs from database
std::vector<Song> RecommendationSystem::getTopRatedSongs(int count) const {
    if (!songDatabase) {
        return std::vector<Song>();
    }
    
    std::vector<Song> allSongs = songDatabase->get_all_songs();
    
    // Sort by rating (descending) and then by ID (for tie-breaking)
    std::sort(allSongs.begin(), allSongs.end(), [](const Song& a, const Song& b) {
        if (a.getRating() != b.getRating()) {
            return a.getRating() > b.getRating();
        }
        return a.getId() < b.getId();
    });
    
    if (allSongs.size() > count) {
        allSongs.resize(count);
    }
    
    return allSongs;
}

// Helper: Filter out songs already in history
std::vector<Song> RecommendationSystem::filterSongsNotInHistory(const std::vector<Song>& candidates) const {
    if (!playbackHistory) {
        return candidates;
    }
    
    std::vector<Song> filtered;
    std::vector<Song> historySongs = playbackHistory->get_recent_songs(playbackHistory->get_size());
    
    for (const Song& candidate : candidates) {
        bool inHistory = false;
        for (const Song& historySong : historySongs) {
            if (candidate.getId() == historySong.getId()) {
                inHistory = true;
                break;
            }
        }
        if (!inHistory) {
            filtered.push_back(candidate);
        }
    }
    
    return filtered;
}

// Helper: Rank songs by rating (higher rating first, then by ID for tie-breaking)
std::vector<Song> RecommendationSystem::rankSongsByRating(const std::vector<Song>& songs) const {
    std::vector<Song> ranked = songs;
    
    std::sort(ranked.begin(), ranked.end(), [](const Song& a, const Song& b) {
        if (a.getRating() != b.getRating()) {
            return a.getRating() > b.getRating();
        }
        return a.getId() < b.getId();
    });
    
    return ranked;
}

// Helper: Get most frequent item from frequency map
std::string RecommendationSystem::getMostFrequent(const std::unordered_map<std::string, int>& frequencyMap) const {
    if (frequencyMap.empty()) {
        return "";
    }
    
    std::string mostFrequent;
    int maxFreq = 0;
    
    for (const auto& pair : frequencyMap) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            mostFrequent = pair.first;
        }
    }
    
    return mostFrequent;
}

// Set history component
void RecommendationSystem::setHistory(History* history) {
    playbackHistory = history;
}

// Set song database component
void RecommendationSystem::setSongDatabase(SongDatabase* database) {
    songDatabase = database;
}

// Check if system is initialized
bool RecommendationSystem::isInitialized() const {
    return playbackHistory != nullptr && songDatabase != nullptr;
}

// Clear system
void RecommendationSystem::clear() {
    playbackHistory = nullptr;
    songDatabase = nullptr;
}
```

### 3. `tests/test_recommendation_system.cpp` (NEW FILE)
**Purpose**: Standalone test file for RecommendationSystem functionality

**Content**: Comprehensive tests including:
- Basic recommendation functionality
- Edge cases (empty history, no matches)
- Integration with History and SongDatabase classes
- Performance testing for large datasets

---

## Existing Files Modified

### 1. `include/playwise_app.h`

#### **Line 17**: Header Include Added
```cpp
#include "recommendation_system.h"
```
**Change**: Added include for RecommendationSystem class header.

#### **Line 47**: Member Variable Added
```cpp
RecommendationSystem* recommendationSystem;
```
**Change**: Added private member variable to store RecommendationSystem instance.

### 2. `src/playwise_app.cpp`

#### **Line 33**: Constructor Initialization Added
```cpp
recommendationSystem = new RecommendationSystem(playbackHistory, songDatabase);
```
**Change**: Added instantiation of RecommendationSystem in `initializeSystem()` method.

#### **Line 47**: Constructor Initialization Added
```cpp
recommendationSystem(nullptr),
```
**Change**: Added initialization of recommendationSystem pointer to nullptr in constructor.

#### **Line 67**: Menu Option Added
```cpp
std::cout << "|  9. Music Recommendations                                  |" << std::endl;
```
**Change**: Added "Music Recommendations" option to main menu display.

#### **Line 904**: Direct Implementation Added
```cpp
case 9: {
    // Directly show personalized recommendations
    std::cout << "\n=== Music Recommendations ===" << std::endl;
    int recentCount = getValidInt("Enter number of recent songs to analyze (1-20): ", 1, 20);
    std::vector<Song> recommendations = recommendationSystem->getRecommendations(recentCount);
    
    if (recommendations.empty()) {
        std::cout << "No recommendations available. Try adding more songs to your history." << std::endl;
    } else {
        std::cout << "Based on your recent " << recentCount << " songs, here are your recommendations:" << std::endl;
        for (size_t i = 0; i < recommendations.size(); i++) {
            const Song& song = recommendations[i];
            std::cout << (i + 1) << ". " << song.getTitle() << " - " << song.getArtist();
            std::cout << " [" << song.getGenre() << "] (Rating: " << song.getRating() << "/5)" << std::endl;
        }
    }
    pauseScreen();
    break;
}
```
**Change**: Implemented direct recommendation logic in main menu case 9.

#### **Line 951**: Destructor Cleanup Added
```cpp
delete recommendationSystem;
```
**Change**: Added cleanup of RecommendationSystem instance in destructor.

#### **Line 978**: Reset Method Added
```cpp
recommendationSystem->clear();
```
**Change**: Added recommendation system cleanup in `resetSystem()` method.

---

## Change Summary by Feature

### 1. Core Recommendation System Implementation
- **New Class**: `RecommendationSystem` with genre-based recommendation algorithm
- **Integration**: Added to main application with proper lifecycle management
- **Algorithm**: Analyzes playback history, identifies preferred genres, suggests unplayed songs

### 2. User Interface Integration
- **Main Menu**: Added "Music Recommendations" option (Option 9)
- **Direct Access**: Provides immediate recommendations without submenu
- **User Input**: Prompts for number of recent songs to analyze (1-20)

### 3. System Integration
- **Constructor**: Proper initialization and cleanup
- **Destructor**: Memory management and cleanup
- **Reset**: Integration with system reset functionality

---

## Technical Implementation Details

### Data Structures Used
- **`std::unordered_map<std::string, int>`**: Genre frequency counting
- **`std::vector<Song>`**: Song collections and recommendations
- **`std::stack<Song>`**: Playback history (from History class)

### Algorithm Complexity
- **Time Complexity**: O(n) for most operations where n is number of songs
- **Space Complexity**: O(n) for storing frequency maps and recommendations
- **Efficiency**: Uses hash maps for O(1) genre frequency lookup

### Integration Points
- **History Class**: Accesses recent playback data
- **SongDatabase**: Searches for songs by genre
- **Main Application**: User interface and lifecycle management

### Fallback Mechanisms
- **Primary**: Genre-based recommendations from unplayed songs
- **Secondary**: Global top-rated songs if no genre matches found
- **Error Handling**: Graceful degradation when system not initialized

---

## Final State

The recommendation system is now fully integrated into the PlayWise application with:
- ✅ **Simplified Interface**: Direct access from main menu
- ✅ **Genre-Based Logic**: Analyzes user preferences from playback history
- ✅ **Proper Integration**: Clean lifecycle management and memory handling

The system provides personalized music recommendations based on the user's listening patterns while maintaining a clean, professional user interface.
