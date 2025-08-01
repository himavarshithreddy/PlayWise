#include "../include/playwise_app.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Constructor
PlayWiseApp::PlayWiseApp() : currentPlaylist(nullptr), playbackHistory(nullptr),
                             ratingTree(nullptr), songDatabase(nullptr), dashboard(nullptr),
                             isRunning(false), currentUser("User") {
    initializeSystem();
}

// Destructor
PlayWiseApp::~PlayWiseApp() {
    shutdown();
}

// Helper methods
void PlayWiseApp::initializeSystem() {
    std::cout << "Initializing PlayWise Music Management System..." << std::endl;
    
    // Create system components
    currentPlaylist = new Playlist("My Playlist");
    playbackHistory = new History(50);
    ratingTree = new RatingTree();
    songDatabase = new SongDatabase();
    dashboard = new Dashboard(currentPlaylist, playbackHistory, ratingTree, songDatabase);
    
    // Load sample data
    loadSampleData();
    
    std::cout << "System initialized successfully!" << std::endl;
    std::cout << "Welcome to PlayWise v" << getVersion() << std::endl;
    std::cout << std::endl;
}

void PlayWiseApp::displayMainMenu() {
    clearScreen();
    std::cout << "+==============================================================+" << std::endl;
    std::cout << "|                    PlayWise Music System                    |" << std::endl;
    std::cout << "|                     Main Menu                               |" << std::endl;
    std::cout << "+==============================================================+" << std::endl;
    std::cout << "|  1. Playlist Operations (Doubly Linked List)               |" << std::endl;
    std::cout << "|  2. History Operations (Stack)                             |" << std::endl;
    std::cout << "|  3. Rating Operations (Binary Search Tree)                 |" << std::endl;
    std::cout << "|  4. Database Operations (HashMap)                          |" << std::endl;
    std::cout << "|  5. Sorting Operations (Merge/Quick/Heap Sort)             |" << std::endl;
    std::cout << "|  6. Dashboard & Analytics                                  |" << std::endl;
    std::cout << "|  7. System Operations                                      |" << std::endl;
    std::cout << "|  0. Exit                                                   |" << std::endl;
    std::cout << "+==============================================================+" << std::endl;
    std::cout << "Enter your choice: ";
}

void PlayWiseApp::handlePlaylistOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Playlist Operations (Doubly Linked List) ===" << std::endl;
        std::cout << "1. Display current playlist" << std::endl;
        std::cout << "2. Add song to playlist" << std::endl;
        std::cout << "3. Delete song from playlist" << std::endl;
        std::cout << "4. Move song in playlist" << std::endl;
        std::cout << "5. Reverse playlist" << std::endl;
        std::cout << "6. Shuffle playlist" << std::endl;
        std::cout << "7. Search song in playlist" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 7);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                currentPlaylist->display();
                pauseScreen();
                break;
            case 2: {
                std::string title = getValidString("Enter song title: ");
                std::string artist = getValidString("Enter artist name: ");
                int duration = getValidInt("Enter duration (in seconds): ", 1, 3600);
                currentPlaylist->add_song(title, artist, duration);
                std::cout << "Song added successfully!" << std::endl;
                pauseScreen();
                break;
            }
            case 3: {
                currentPlaylist->display();
                int index = getValidInt("Enter song index to delete: ", 1, currentPlaylist->getSize());
                if (currentPlaylist->delete_song(index - 1)) {
                    std::cout << "Song deleted successfully!" << std::endl;
                } else {
                    std::cout << "Failed to delete song!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                currentPlaylist->display();
                int fromIndex = getValidInt("Enter source index: ", 1, currentPlaylist->getSize());
                int toIndex = getValidInt("Enter destination index: ", 1, currentPlaylist->getSize());
                if (currentPlaylist->move_song(fromIndex - 1, toIndex - 1)) {
                    std::cout << "Song moved successfully!" << std::endl;
                } else {
                    std::cout << "Failed to move song!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 5:
                currentPlaylist->reverse_playlist();
                std::cout << "Playlist reversed successfully!" << std::endl;
                pauseScreen();
                break;
            case 6:
                currentPlaylist->shuffle();
                std::cout << "Playlist shuffled successfully!" << std::endl;
                pauseScreen();
                break;
            case 7: {
                std::string searchTerm = getValidString("Enter song title to search: ");
                Song* foundSong = currentPlaylist->find_song_by_title(searchTerm);
                if (foundSong) {
                    std::cout << "Song found: " << foundSong->getTitle() << " - " << foundSong->getArtist() << std::endl;
                } else {
                    std::cout << "Song not found!" << std::endl;
                }
                pauseScreen();
                break;
            }
        }
    }
}

void PlayWiseApp::handleHistoryOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== History Operations (Stack) ===" << std::endl;
        std::cout << "1. Display playback history" << std::endl;
        std::cout << "2. Display recent songs" << std::endl;
        std::cout << "3. Undo last played song" << std::endl;
        std::cout << "4. Clear history" << std::endl;
        std::cout << "5. Export history to file" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 5);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                playbackHistory->display_history();
                pauseScreen();
                break;
            case 2: {
                int count = getValidInt("Enter number of recent songs to display: ", 1, 20);
                playbackHistory->display_recent_songs(count);
                pauseScreen();
                break;
            }
            case 3: {
                if (!playbackHistory->is_empty()) {
                    Song undoneSong = playbackHistory->undo_last_play();
                    std::cout << "Undone: " << undoneSong.getTitle() << " - " << undoneSong.getArtist() << std::endl;
                    // Add back to playlist
                    currentPlaylist->add_song(undoneSong);
                    std::cout << "Song added back to playlist!" << std::endl;
                } else {
                    std::cout << "No songs in history to undo!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4:
                playbackHistory->clear_history();
                std::cout << "History cleared successfully!" << std::endl;
                pauseScreen();
                break;
            case 5:
                playbackHistory->export_history_to_file("playback_history.txt");
                pauseScreen();
                break;
        }
    }
}

void PlayWiseApp::handleRatingOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Rating Operations (Binary Search Tree) ===" << std::endl;
        std::cout << "1. Display rating tree structure" << std::endl;
        std::cout << "2. Display rating statistics" << std::endl;
        std::cout << "3. Search songs by rating" << std::endl;
        std::cout << "4. Get top rated songs" << std::endl;
        std::cout << "5. Add song with rating" << std::endl;
        std::cout << "6. Delete song from rating tree" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 6);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                ratingTree->display_tree();
                pauseScreen();
                break;
            case 2:
                ratingTree->display_rating_stats();
                pauseScreen();
                break;
            case 3: {
                int rating = getValidInt("Enter rating (1-5): ", 1, 5);
                std::vector<Song> songs = ratingTree->search_by_rating(rating);
                std::cout << "Songs with " << rating << " stars:" << std::endl;
                for (const Song& song : songs) {
                    std::cout << "  - " << song.getTitle() << " - " << song.getArtist() << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                int count = getValidInt("Enter number of top songs: ", 1, 10);
                std::vector<Song> topSongs = ratingTree->get_top_rated_songs(count);
                std::cout << "Top " << count << " rated songs:" << std::endl;
                for (const Song& song : topSongs) {
                    std::cout << "  - " << song.getTitle() << " - " << song.getArtist() 
                              << " (" << song.getRating() << " stars)" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 5: {
                std::string title = getValidString("Enter song title: ");
                std::string artist = getValidString("Enter artist name: ");
                int duration = getValidInt("Enter duration (in seconds): ", 1, 3600);
                int rating = getValidInt("Enter rating (1-5): ", 1, 5);
                
                Song song("", title, artist, duration, rating);
                ratingTree->insert_song(song, rating);
                std::cout << "Song added to rating tree successfully!" << std::endl;
                pauseScreen();
                break;
            }
            case 6: {
                std::string songId = getValidString("Enter song ID: ");
                int rating = getValidInt("Enter song rating: ", 1, 5);
                if (ratingTree->delete_song(songId, rating)) {
                    std::cout << "Song deleted from rating tree successfully!" << std::endl;
                } else {
                    std::cout << "Failed to delete song from rating tree!" << std::endl;
                }
                pauseScreen();
                break;
            }
        }
    }
}

void PlayWiseApp::handleDatabaseOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Database Operations (HashMap) ===" << std::endl;
        std::cout << "1. Display database" << std::endl;
        std::cout << "2. Display database statistics" << std::endl;
        std::cout << "3. Search song by ID" << std::endl;
        std::cout << "4. Search song by title" << std::endl;
        std::cout << "5. Search songs by artist" << std::endl;
        std::cout << "6. Search songs by genre" << std::endl;
        std::cout << "7. Add song to database" << std::endl;
        std::cout << "8. Delete song from database" << std::endl;
        std::cout << "9. Export database to file" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 9);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                songDatabase->display_database();
                pauseScreen();
                break;
            case 2:
                songDatabase->display_stats();
                pauseScreen();
                break;
            case 3: {
                std::string songId = getValidString("Enter song ID: ");
                Song* foundSong = songDatabase->search_by_id(songId);
                if (foundSong) {
                    std::cout << "Found: " << foundSong->getTitle() << " - " << foundSong->getArtist() << std::endl;
                } else {
                    std::cout << "Song not found!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                std::string title = getValidString("Enter song title: ");
                Song* foundSong = songDatabase->search_by_title(title);
                if (foundSong) {
                    std::cout << "Found: " << foundSong->getTitle() << " - " << foundSong->getArtist() << std::endl;
                } else {
                    std::cout << "Song not found!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 5: {
                std::string artist = getValidString("Enter artist name: ");
                std::vector<Song> songs = songDatabase->search_by_artist(artist);
                std::cout << "Songs by " << artist << ":" << std::endl;
                for (const Song& song : songs) {
                    std::cout << "  - " << song.getTitle() << std::endl;
                }
                pauseScreen();
                break;
            }
            case 6: {
                std::string genre = getValidString("Enter genre: ");
                std::vector<Song> songs = songDatabase->search_by_genre(genre);
                std::cout << "Songs in genre " << genre << ":" << std::endl;
                for (const Song& song : songs) {
                    std::cout << "  - " << song.getTitle() << " - " << song.getArtist() << std::endl;
                }
                pauseScreen();
                break;
            }
            case 7: {
                std::string title = getValidString("Enter song title: ");
                std::string artist = getValidString("Enter artist name: ");
                int duration = getValidInt("Enter duration (in seconds): ", 1, 3600);
                int rating = getValidInt("Enter rating (1-5): ", 1, 5);
                std::string album = getValidString("Enter album name: ");
                std::string genre = getValidString("Enter genre: ");
                
                Song song("", title, artist, duration, rating, album, genre);
                if (songDatabase->insert_song(song)) {
                    std::cout << "Song added to database successfully!" << std::endl;
                } else {
                    std::cout << "Failed to add song to database!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 8: {
                std::string songId = getValidString("Enter song ID: ");
                if (songDatabase->delete_song(songId)) {
                    std::cout << "Song deleted from database successfully!" << std::endl;
                } else {
                    std::cout << "Failed to delete song from database!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 9:
                songDatabase->export_to_file("song_database.txt");
                pauseScreen();
                break;
        }
    }
}

void PlayWiseApp::handleSortingOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Sorting Operations ===" << std::endl;
        std::cout << "1. Sort playlist by title (A-Z)" << std::endl;
        std::cout << "2. Sort playlist by title (Z-A)" << std::endl;
        std::cout << "3. Sort playlist by duration (shortest first)" << std::endl;
        std::cout << "4. Sort playlist by duration (longest first)" << std::endl;
        std::cout << "5. Sort playlist by rating (highest first)" << std::endl;
        std::cout << "6. Sort playlist by artist (A-Z)" << std::endl;
        std::cout << "7. Benchmark sorting algorithms" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 7);
        
        if (choice == 0) return;
        
        // Get songs from current playlist
        std::vector<Song> songs;
        PlaylistNode* current = currentPlaylist->getHead();
        while (current != nullptr) {
            songs.push_back(current->song);
            current = current->next;
        }
        
        if (songs.empty()) {
            std::cout << "No songs in playlist to sort!" << std::endl;
            pauseScreen();
            continue;
        }
        
        Sorting::SortCriteria criteria;
        std::string algorithm = "merge";
        
        switch (choice) {
            case 1:
                criteria = Sorting::SortCriteria::TITLE_ASC;
                break;
            case 2:
                criteria = Sorting::SortCriteria::TITLE_DESC;
                break;
            case 3:
                criteria = Sorting::SortCriteria::DURATION_ASC;
                break;
            case 4:
                criteria = Sorting::SortCriteria::DURATION_DESC;
                break;
            case 5:
                criteria = Sorting::SortCriteria::RATING_DESC;
                break;
            case 6:
                criteria = Sorting::SortCriteria::ARTIST_ASC;
                break;
            case 7:
                Sorting::benchmarkSorting(songs);
                pauseScreen();
                continue;
        }
        
        Sorting::sortPlaylist(songs, criteria, algorithm);
        
        // Update playlist with sorted songs
        currentPlaylist->clear();
        for (const Song& song : songs) {
            currentPlaylist->add_song(song);
        }
        
        std::cout << "Playlist sorted successfully!" << std::endl;
        pauseScreen();
    }
}

void PlayWiseApp::handleDashboardOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Dashboard & Analytics ===" << std::endl;
        std::cout << "1. Display live dashboard" << std::endl;
        std::cout << "2. Export system snapshot" << std::endl;
        std::cout << "3. Display performance metrics" << std::endl;
        std::cout << "4. Display user activity" << std::endl;
        std::cout << "5. Display system health" << std::endl;
        std::cout << "6. Generate performance report" << std::endl;
        std::cout << "7. Generate usage report" << std::endl;
        std::cout << "8. Export system report to file" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 8);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                dashboard->display_live_dashboard();
                pauseScreen();
                break;
            case 2:
                dashboard->export_snapshot();
                pauseScreen();
                break;
            case 3:
                dashboard->display_performance_metrics();
                pauseScreen();
                break;
            case 4:
                dashboard->display_user_activity();
                pauseScreen();
                break;
            case 5:
                dashboard->display_system_health();
                pauseScreen();
                break;
            case 6:
                dashboard->generate_performance_report();
                pauseScreen();
                break;
            case 7:
                dashboard->generate_usage_report();
                pauseScreen();
                break;
            case 8:
                dashboard->export_to_file("system_report.txt");
                pauseScreen();
                break;
        }
    }
}

void PlayWiseApp::handleSystemOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== System Operations ===" << std::endl;
        std::cout << "1. Reset system" << std::endl;
        std::cout << "2. Export all system data" << std::endl;
        std::cout << "3. Import system data" << std::endl;
        std::cout << "4. Display system information" << std::endl;
        std::cout << "5. Memory usage analysis" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 5);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                resetSystem();
                break;
            case 2:
                exportSystemData();
                break;
            case 3:
                importSystemData();
                break;
            case 4:
                std::cout << "PlayWise Music Management System" << std::endl;
                std::cout << "Version: " << getVersion() << std::endl;
                std::cout << "Status: " << (isInitialized() ? "Initialized" : "Not Initialized") << std::endl;
                std::cout << "Current User: " << currentUser << std::endl;
                pauseScreen();
                break;
            case 5:
                dashboard->memory_usage_analysis();
                pauseScreen();
                break;
        }
    }
}

// Utility methods
void PlayWiseApp::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void PlayWiseApp::pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int PlayWiseApp::getValidChoice(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

std::string PlayWiseApp::getValidString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int PlayWiseApp::getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Data management
void PlayWiseApp::loadSampleData() {
    // Add sample songs to the system
    std::vector<Song> sampleSongs = {
        Song("song_001", "Bohemian Rhapsody", "Queen", 354, 5, "A Night at the Opera", "Rock"),
        Song("song_002", "Hotel California", "Eagles", 391, 4, "Hotel California", "Rock"),
        Song("song_003", "Imagine", "John Lennon", 183, 5, "Imagine", "Pop"),
        Song("song_004", "Stairway to Heaven", "Led Zeppelin", 482, 5, "Led Zeppelin IV", "Rock"),
        Song("song_005", "Yesterday", "The Beatles", 125, 4, "Help!", "Pop"),
        Song("song_006", "Hey Jude", "The Beatles", 431, 5, "The Beatles 1967-1970", "Pop"),
        Song("song_007", "Sweet Child O' Mine", "Guns N' Roses", 356, 3, "Appetite for Destruction", "Rock")
    };
    
    // Add to database
    for (const Song& song : sampleSongs) {
        songDatabase->insert_song(song);
        ratingTree->insert_song(song, song.getRating());
        currentPlaylist->add_song(song);
    }
    
    // Add some to history
    playbackHistory->add_played_song(sampleSongs[0]);
    playbackHistory->add_played_song(sampleSongs[1]);
    playbackHistory->add_played_song(sampleSongs[2]);
    
    std::cout << "Loaded " << sampleSongs.size() << " sample songs." << std::endl;
}

void PlayWiseApp::saveSystemState() {
    // In a real implementation, this would save to files
    std::cout << "System state saved." << std::endl;
}

void PlayWiseApp::loadSystemState() {
    // In a real implementation, this would load from files
    std::cout << "System state loaded." << std::endl;
}

// Main application methods
void PlayWiseApp::run() {
    isRunning = true;
    
    while (isRunning) {
        displayMainMenu();
        int choice = getValidChoice(0, 7);
        
        switch (choice) {
            case 0:
                shutdown();
                break;
            case 1:
                handlePlaylistOperations();
                break;
            case 2:
                handleHistoryOperations();
                break;
            case 3:
                handleRatingOperations();
                break;
            case 4:
                handleDatabaseOperations();
                break;
            case 5:
                handleSortingOperations();
                break;
            case 6:
                handleDashboardOperations();
                break;
            case 7:
                handleSystemOperations();
                break;
        }
    }
}

void PlayWiseApp::shutdown() {
    std::cout << "Saving system state..." << std::endl;
    saveSystemState();
    
    std::cout << "Shutting down PlayWise..." << std::endl;
    isRunning = false;
    
    // Clean up resources
    delete dashboard;
    delete songDatabase;
    delete ratingTree;
    delete playbackHistory;
    delete currentPlaylist;
    
    dashboard = nullptr;
    songDatabase = nullptr;
    ratingTree = nullptr;
    playbackHistory = nullptr;
    currentPlaylist = nullptr;
    
    std::cout << "Goodbye!" << std::endl;
}

// System management
void PlayWiseApp::resetSystem() {
    std::cout << "Are you sure you want to reset the system? (y/n): ";
    std::string confirm = getValidString("");
    
    if (confirm == "y" || confirm == "Y") {
        // Clear all data
        currentPlaylist->clear();
        playbackHistory->clear_history();
        ratingTree->clear();
        songDatabase->clear();
        
        // Reload sample data
        loadSampleData();
        
        std::cout << "System reset successfully!" << std::endl;
    } else {
        std::cout << "Reset cancelled." << std::endl;
    }
    pauseScreen();
}

void PlayWiseApp::exportSystemData() {
    std::cout << "Exporting system data..." << std::endl;
    songDatabase->export_to_file("export_song_database.txt");
    playbackHistory->export_history_to_file("export_playback_history.txt");
    dashboard->export_to_file("export_system_report.txt");
    std::cout << "System data exported successfully!" << std::endl;
    pauseScreen();
}

void PlayWiseApp::importSystemData() {
    std::cout << "Importing system data..." << std::endl;
    if (songDatabase->import_from_file("export_song_database.txt")) {
        std::cout << "System data imported successfully!" << std::endl;
    } else {
        std::cout << "Failed to import system data!" << std::endl;
    }
    pauseScreen();
}

// Utility methods
bool PlayWiseApp::isInitialized() const {
    return currentPlaylist != nullptr && playbackHistory != nullptr && 
           ratingTree != nullptr && songDatabase != nullptr && dashboard != nullptr;
}

std::string PlayWiseApp::getVersion() const {
    return "1.0.0";
} 