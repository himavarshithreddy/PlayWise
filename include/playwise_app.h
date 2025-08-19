#ifndef PLAYWISE_APP_H
#define PLAYWISE_APP_H

#include "song.h"
#include "playlist.h"
#include "history.h"
#include "rating_tree.h"
#include "song_database.h"
#include "sorting.h"
#include "dashboard.h"
#include "song_cleaner.h"
#include "favorite_songs_queue.h"
#include <string>
#include <vector>

/**
 * @brief PlayWise Application - Main application class
 * 
 * This class provides a complete user interface for the PlayWise music
 * playlist management system. It integrates all components and provides
 * a menu-driven interface for users to interact with the system.
 */
class PlayWiseApp {
private:
    // Core system components
    Playlist* currentPlaylist;
    History* playbackHistory;
    RatingTree* ratingTree;
    SongDatabase* songDatabase;
    Dashboard* dashboard;
    SongCleaner* songCleaner;
    FavoriteSongsQueue* favoriteSongsQueue;
    
    // Application state
    bool isRunning;
    std::string currentUser;
    
    // Helper methods
    void initializeSystem();
    void displayMainMenu();
    void handlePlaylistOperations();
    void handleHistoryOperations();
    void handleRatingOperations();
    void handleDatabaseOperations();
    void handleSortingOperations();
    void handleDashboardOperations();
    void handleSystemOperations();
    void handleSongCleanerOperations();
    void handleFavoriteSongsOperations();
    
    // Utility methods
    void clearScreen();
    void pauseScreen();
    int getValidChoice(int min, int max);
    std::string getValidString(const std::string& prompt);
    int getValidInt(const std::string& prompt, int min, int max);
    
    // Song selection helpers
    void displaySongsWithIndices(const std::vector<Song>& songs, const std::string& title = "Available Songs");
    int selectSongFromList(const std::vector<Song>& songs, const std::string& prompt = "Select song number");
    Song* selectSongFromDatabase(const std::string& prompt = "Select song from database");
    Song* selectSongFromPlaylist(const std::string& prompt = "Select song from playlist");
    Song* selectSongFromDatabaseNotInPlaylist(const std::string& prompt = "Select song from database (not already in playlist)");
    
    // Data management
    void loadSampleData();
    void saveSystemState();
    void loadSystemState();

public:
    // Constructor and Destructor
    PlayWiseApp();
    ~PlayWiseApp();
    
    // Main application methods
    void run();
    void shutdown();
    
    // System management
    void resetSystem();
    void exportSystemData();
    void importSystemData();
    
    // Utility methods
    bool isInitialized() const;
    std::string getVersion() const;
};

#endif // PLAYWISE_APP_H 