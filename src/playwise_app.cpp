#include "../include/playwise_app.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Constructor
PlayWiseApp::PlayWiseApp() : currentPlaylist(nullptr), playbackHistory(nullptr),
                             ratingTree(nullptr), songDatabase(nullptr), dashboard(nullptr),
                             songCleaner(nullptr), favoriteSongsQueue(nullptr),
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
    songCleaner = new SongCleaner();
    favoriteSongsQueue = new FavoriteSongsQueue();
    
    // Load sample data
    loadSampleData();
    
    // Update dashboard stats after loading sample data
    dashboard->updateStats();
    
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
    std::cout << "|  7. Song Cleaner (Duplicate Removal)                       |" << std::endl;
    std::cout << "|  8. Favorite Songs Queue                                   |" << std::endl;
    std::cout << "|  9. System Operations                                      |" << std::endl;
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
                dashboard->updateStats();
                std::cout << "Song added successfully!" << std::endl;
                pauseScreen();
                break;
            }
            case 3: {
                currentPlaylist->display();
                int index = getValidInt("Enter song index to delete: ", 1, currentPlaylist->getSize());
                if (currentPlaylist->delete_song(index - 1)) {
                    dashboard->updateStats();
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
                Song* selectedSong = selectSongFromPlaylist("Select song to search");
                if (selectedSong) {
                    std::cout << "Selected song: " << selectedSong->getTitle() << " - " << selectedSong->getArtist() << std::endl;
                } else {
                    std::cout << "No song selected." << std::endl;
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
                dashboard->updateStats();
                std::cout << "Song added back to playlist!" << std::endl;
                } else {
                    std::cout << "No songs in history to undo!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4:
                playbackHistory->clear_history();
                dashboard->updateStats();
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
        std::cout << "6. Rate existing song" << std::endl;
        std::cout << "7. Delete song from rating tree" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 7);
        
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
                Song* selectedSong = selectSongFromDatabase("Select song to add with rating");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                int rating = getValidInt("Enter rating (1-5): ", 1, 5);
                
                // Check if song already has a rating
                int oldRating = selectedSong->getRating();
                if (oldRating > 0) {
                    ratingTree->delete_song(selectedSong->getId(), oldRating);
                }
                
                // Add new rating
                selectedSong->setRating(rating);
                ratingTree->insert_song(*selectedSong, rating);
                songDatabase->update_song_rating(selectedSong->getId(), rating);
                
                dashboard->updateStats();
                std::cout << "Song added to rating tree successfully! " << selectedSong->getTitle() 
                          << " now has " << rating << " stars." << std::endl;
                pauseScreen();
                break;
            }
            case 6: {
                // Rate existing song
                std::cout << "Available songs in database:" << std::endl;
                std::vector<Song> allSongs = songDatabase->get_all_songs();
                if (allSongs.empty()) {
                    std::cout << "No songs in database to rate!" << std::endl;
                    pauseScreen();
                    break;
                }
                
                // Display available songs
                for (size_t i = 0; i < allSongs.size(); i++) {
                    std::cout << (i + 1) << ". " << allSongs[i].getTitle() 
                              << " - " << allSongs[i].getArtist() 
                              << " (Current rating: " << allSongs[i].getRating() << ")" << std::endl;
                }
                
                int songChoice = getValidInt("Select song number: ", 1, allSongs.size());
                int newRating = getValidInt("Enter new rating (1-5): ", 1, 5);
                
                Song selectedSong = allSongs[songChoice - 1];
                std::string songId = selectedSong.getId();
                
                // Remove old rating if exists
                int oldRating = selectedSong.getRating();
                if (oldRating > 0) {
                    ratingTree->delete_song(songId, oldRating);
                }
                
                // Add new rating
                selectedSong.setRating(newRating);
                ratingTree->insert_song(selectedSong, newRating);
                
                // Update song in database
                songDatabase->update_song_rating(songId, newRating);
                
                dashboard->updateStats();
                std::cout << "Song rated successfully! " << selectedSong.getTitle() 
                          << " now has " << newRating << " stars." << std::endl;
                pauseScreen();
                break;
            }
            case 7: {
                Song* selectedSong = selectSongFromDatabase("Select song to delete from rating tree");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                int rating = selectedSong->getRating();
                if (rating <= 0) {
                    std::cout << "This song has no rating to delete." << std::endl;
                    pauseScreen();
                    break;
                }
                
                if (ratingTree->delete_song(selectedSong->getId(), rating)) {
                    selectedSong->setRating(0);
                    songDatabase->update_song_rating(selectedSong->getId(), 0);
                    dashboard->updateStats();
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
                Song* selectedSong = selectSongFromDatabase("Select song to search by ID");
                if (selectedSong) {
                    std::cout << "Found: " << selectedSong->getTitle() << " - " << selectedSong->getArtist() << std::endl;
                } else {
                    std::cout << "No song selected." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                Song* selectedSong = selectSongFromDatabase("Select song to search by title");
                if (selectedSong) {
                    std::cout << "Found: " << selectedSong->getTitle() << " - " << selectedSong->getArtist() << std::endl;
                } else {
                    std::cout << "No song selected." << std::endl;
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
                    dashboard->updateStats();
                    std::cout << "Song added to database successfully!" << std::endl;
                } else {
                    std::cout << "Failed to add song to database!" << std::endl;
                }
                pauseScreen();
                break;
            }
            case 8: {
                Song* selectedSong = selectSongFromDatabase("Select song to delete from database");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                std::string songId = selectedSong->getId();
                if (songDatabase->delete_song(songId)) {
                    dashboard->updateStats();
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

// Song selection helper methods
void PlayWiseApp::displaySongsWithIndices(const std::vector<Song>& songs, const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
    if (songs.empty()) {
        std::cout << "No songs available." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < songs.size(); i++) {
        std::cout << (i + 1) << ". " << songs[i].getTitle() 
                  << " - " << songs[i].getArtist();
        
        // Show additional info if available
        if (songs[i].getRating() > 0) {
            std::cout << " (Rating: " << songs[i].getRating() << "★)";
        }
        if (songs[i].getDuration() > 0) {
            std::cout << " [" << songs[i].getDurationString() << "]";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int PlayWiseApp::selectSongFromList(const std::vector<Song>& songs, const std::string& prompt) {
    if (songs.empty()) {
        std::cout << "No songs available for selection." << std::endl;
        return -1;
    }
    
    displaySongsWithIndices(songs);
    return getValidInt(prompt + " (1-" + std::to_string(songs.size()) + "): ", 1, songs.size());
}

Song* PlayWiseApp::selectSongFromDatabase(const std::string& prompt) {
    std::vector<Song> allSongs = songDatabase->get_all_songs();
    if (allSongs.empty()) {
        std::cout << "No songs in database." << std::endl;
        return nullptr;
    }
    
    int choice = selectSongFromList(allSongs, prompt);
    if (choice == -1) return nullptr;
    
    Song selectedSong = allSongs[choice - 1];
    return songDatabase->search_by_id(selectedSong.getId());
}

Song* PlayWiseApp::selectSongFromPlaylist(const std::string& prompt) {
    std::vector<Song> playlistSongs;
    PlaylistNode* current = currentPlaylist->getHead();
    while (current != nullptr) {
        playlistSongs.push_back(current->song);
        current = current->next;
    }
    
    if (playlistSongs.empty()) {
        std::cout << "No songs in current playlist." << std::endl;
        return nullptr;
    }
    
    int choice = selectSongFromList(playlistSongs, prompt);
    if (choice == -1) return nullptr;
    
    Song selectedSong = playlistSongs[choice - 1];
    return songDatabase->search_by_id(selectedSong.getId());
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
        int choice = getValidChoice(0, 9);
        
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
                handleSongCleanerOperations();
                break;
            case 8:
                handleFavoriteSongsOperations();
                break;
            case 9:
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
    delete songCleaner;
    delete favoriteSongsQueue;
    
    dashboard = nullptr;
    songDatabase = nullptr;
    ratingTree = nullptr;
    playbackHistory = nullptr;
    currentPlaylist = nullptr;
    songCleaner = nullptr;
    favoriteSongsQueue = nullptr;
    
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
        songCleaner->clear();
        favoriteSongsQueue->clear();
        
        // Reload sample data
        loadSampleData();
        
        // Update dashboard stats after reset
        dashboard->updateStats();
        
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
        dashboard->updateStats();
        std::cout << "System data imported successfully!" << std::endl;
    } else {
        std::cout << "Failed to import system data!" << std::endl;
    }
    pauseScreen();
}

// Utility methods
bool PlayWiseApp::isInitialized() const {
    return currentPlaylist != nullptr && playbackHistory != nullptr && 
           ratingTree != nullptr && songDatabase != nullptr && dashboard != nullptr &&
           songCleaner != nullptr && favoriteSongsQueue != nullptr;
}

std::string PlayWiseApp::getVersion() const {
    return "1.0.0";
}

// Song Cleaner Operations
void PlayWiseApp::handleSongCleanerOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Song Cleaner (Duplicate Removal) ===" << std::endl;
        std::cout << "1. Check for duplicates in current playlist" << std::endl;
        std::cout << "2. Remove duplicates from current playlist" << std::endl;
        std::cout << "3. Check if a song is a duplicate" << std::endl;
        std::cout << "4. Add song to cleaner (test)" << std::endl;
        std::cout << "5. Display cleaner statistics" << std::endl;
        std::cout << "6. Clean duplicates from database" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 6);
        
        switch (choice) {
            case 0:
                return;
            case 1: {
                std::cout << "Checking for duplicates in current playlist..." << std::endl;
                std::vector<Song> playlistSongs;
                // Get songs from current playlist
                PlaylistNode* current = currentPlaylist->getHead();
                while (current != nullptr) {
                    playlistSongs.push_back(current->song);
                    current = current->next;
                }
                
                std::vector<Song> cleanedSongs = songCleaner->cleanDuplicates(playlistSongs);
                int duplicates = playlistSongs.size() - cleanedSongs.size();
                
                std::cout << "Found " << duplicates << " duplicate(s) in playlist." << std::endl;
                std::cout << "Original: " << playlistSongs.size() << " songs" << std::endl;
                std::cout << "After cleaning: " << cleanedSongs.size() << " songs" << std::endl;
                pauseScreen();
                break;
            }
            case 2: {
                std::cout << "Removing duplicates from current playlist..." << std::endl;
                std::vector<Song> playlistSongs;
                // Get songs from current playlist
                PlaylistNode* current = currentPlaylist->getHead();
                while (current != nullptr) {
                    playlistSongs.push_back(current->song);
                    current = current->next;
                }
                
                std::vector<Song> cleanedSongs = songCleaner->cleanDuplicates(playlistSongs);
                int duplicates = playlistSongs.size() - cleanedSongs.size();
                
                if (duplicates > 0) {
                    // Clear current playlist and add cleaned songs
                    currentPlaylist->clear();
                    for (const Song& song : cleanedSongs) {
                        currentPlaylist->add_song(song);
                    }
                    dashboard->updateStats();
                    std::cout << "Removed " << duplicates << " duplicate(s) from playlist." << std::endl;
                } else {
                    std::cout << "No duplicates found in playlist." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 3: {
                Song* selectedSong = selectSongFromDatabase("Select song to check for duplicates");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                if (songCleaner->isDuplicate(*selectedSong)) {
                    std::cout << "This song is a duplicate!" << std::endl;
                } else {
                    std::cout << "This song is not a duplicate." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                Song* selectedSong = selectSongFromDatabase("Select song to add to cleaner");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                if (songCleaner->addSong(*selectedSong)) {
                    std::cout << "Song added to cleaner successfully!" << std::endl;
                } else {
                    std::cout << "Song is a duplicate and was not added." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 5: {
                std::cout << "=== Song Cleaner Statistics ===" << std::endl;
                std::cout << "Unique songs tracked: " << songCleaner->getUniqueSongCount() << std::endl;
                std::cout << "Cleaner is empty: " << (songCleaner->isEmpty() ? "Yes" : "No") << std::endl;
                pauseScreen();
                break;
            }
            case 6: {
                std::cout << "Cleaning duplicates from database..." << std::endl;
                std::vector<Song> dbSongs = songDatabase->get_all_songs();
                std::vector<Song> cleanedSongs = songCleaner->cleanDuplicates(dbSongs);
                int duplicates = dbSongs.size() - cleanedSongs.size();
                
                std::cout << "Found " << duplicates << " duplicate(s) in database." << std::endl;
                std::cout << "Original: " << dbSongs.size() << " songs" << std::endl;
                std::cout << "After cleaning: " << cleanedSongs.size() << " songs" << std::endl;
                pauseScreen();
                break;
            }
        }
    }
}

// Favorite Songs Queue Operations
void PlayWiseApp::handleFavoriteSongsOperations() {
    while (true) {
        clearScreen();
        std::cout << "=== Favorite Songs Queue (Auto-Sorted by Listening Time) ===" << std::endl;
        std::cout << "1. Display favorite songs (sorted by listening time)" << std::endl;
        std::cout << "2. Add song to favorites" << std::endl;
        std::cout << "3. Remove song from favorites" << std::endl;
        std::cout << "4. Update listening time for a song" << std::endl;
        std::cout << "5. Increment play count for a song" << std::endl;
        std::cout << "6. Get top favorite song" << std::endl;
        std::cout << "7. Get top N favorite songs" << std::endl;
        std::cout << "8. Check if song is in favorites" << std::endl;
        std::cout << "9. Clear all favorites" << std::endl;
        std::cout << "10. Auto-update from playback simulation" << std::endl;
        std::cout << "11. Sync with playback history" << std::endl;
        std::cout << "12. Get favorites by time range" << std::endl;
        std::cout << "13. Display detailed statistics" << std::endl;
        std::cout << "14. Export favorites to file" << std::endl;
        std::cout << "15. Import favorites from file" << std::endl;
        std::cout << "0. Back to main menu" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice = getValidChoice(0, 15);
        
        switch (choice) {
            case 0:
                return;
            case 1:
                favoriteSongsQueue->displayFavorites();
                pauseScreen();
                break;
            case 2: {
                Song* selectedSong = selectSongFromDatabase("Select song to add to favorites");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                favoriteSongsQueue->addSong(*selectedSong);
                std::cout << "Song added to favorites!" << std::endl;
                pauseScreen();
                break;
            }
            case 3: {
                Song* selectedSong = selectSongFromDatabase("Select song to remove from favorites");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                if (favoriteSongsQueue->isInFavorites(*selectedSong)) {
                    favoriteSongsQueue->removeSong(*selectedSong);
                    std::cout << "Song removed from favorites!" << std::endl;
                } else {
                    std::cout << "Song not found in favorites." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                Song* selectedSong = selectSongFromDatabase("Select song to update listening time");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                int additionalTime = getValidInt("Enter additional listening time (in seconds): ", 1, 3600);
                favoriteSongsQueue->updateListeningTime(*selectedSong, additionalTime);
                std::cout << "Listening time updated! Queue automatically re-sorted." << std::endl;
                pauseScreen();
                break;
            }
            case 5: {
                Song* selectedSong = selectSongFromDatabase("Select song to increment play count");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                favoriteSongsQueue->incrementPlayCount(*selectedSong);
                std::cout << "Play count incremented! Queue automatically re-sorted." << std::endl;
                pauseScreen();
                break;
            }
            case 6: {
                Song topSong = favoriteSongsQueue->getTopFavorite();
                if (topSong.isValid()) {
                    std::cout << "Top favorite song: " << topSong.getTitle() << " - " << topSong.getArtist() << std::endl;
                    std::cout << "Listening time: " << favoriteSongsQueue->getListeningTime(topSong) << " seconds" << std::endl;
                    std::cout << "Play count: " << favoriteSongsQueue->getPlayCount(topSong) << std::endl;
                } else {
                    std::cout << "No favorite songs found." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 7: {
                int count = getValidInt("Enter number of top songs to display: ", 1, 10);
                std::vector<Song> topSongs = favoriteSongsQueue->getTopFavorites(count);
                
                if (topSongs.empty()) {
                    std::cout << "No favorite songs found." << std::endl;
                } else {
                    std::cout << "Top " << count << " favorite songs (sorted by listening time):" << std::endl;
                    for (size_t i = 0; i < topSongs.size(); i++) {
                        const Song& song = topSongs[i];
                        std::cout << (i + 1) << ". " << song.getTitle() << " - " << song.getArtist() << std::endl;
                        std::cout << "   Listening time: " << favoriteSongsQueue->getListeningTime(song) << " seconds" << std::endl;
                        std::cout << "   Play count: " << favoriteSongsQueue->getPlayCount(song) << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 8: {
                Song* selectedSong = selectSongFromDatabase("Select song to check if in favorites");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                if (favoriteSongsQueue->isInFavorites(*selectedSong)) {
                    std::cout << "Song is in favorites!" << std::endl;
                    std::cout << "Listening time: " << favoriteSongsQueue->getListeningTime(*selectedSong) << " seconds" << std::endl;
                    std::cout << "Play count: " << favoriteSongsQueue->getPlayCount(*selectedSong) << std::endl;
                } else {
                    std::cout << "Song is not in favorites." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 9: {
                std::cout << "Are you sure you want to clear all favorites? (y/n): ";
                std::string confirm = getValidString("");
                
                if (confirm == "y" || confirm == "Y") {
                    favoriteSongsQueue->clear();
                    std::cout << "All favorites cleared!" << std::endl;
                } else {
                    std::cout << "Operation cancelled." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 10: {
                // Simulate auto-update from playback
                std::cout << "=== Auto-Update from Playback Simulation ===" << std::endl;
                Song* selectedSong = selectSongFromDatabase("Select song for playback simulation");
                if (!selectedSong) {
                    std::cout << "No song selected." << std::endl;
                    pauseScreen();
                    break;
                }
                
                int playbackTime = getValidInt("Enter playback time (in seconds): ", 1, selectedSong->getDuration());
                favoriteSongsQueue->autoUpdateFromPlayback(*selectedSong, playbackTime);
                
                std::cout << "Song automatically added/updated in favorites!" << std::endl;
                std::cout << "Queue automatically re-sorted by listening time." << std::endl;
                pauseScreen();
                break;
            }
            case 11: {
                // Sync with playback history
                std::cout << "=== Sync with Playback History ===" << std::endl;
                
                // Get recent songs from history
                std::vector<Song> recentSongs = playbackHistory->get_recent_songs(10);
                
                if (recentSongs.empty()) {
                    std::cout << "No recent playback history found." << std::endl;
                } else {
                    favoriteSongsQueue->syncWithHistory(recentSongs);
                    std::cout << "Favorites synchronized with playback history!" << std::endl;
                    std::cout << "Queue automatically re-sorted by listening time." << std::endl;
                }
                pauseScreen();
                break;
            }
            case 12: {
                std::cout << "=== Get Favorites by Time Range ===" << std::endl;
                int minTime = getValidInt("Enter minimum listening time (in seconds): ", 0, 3600);
                int maxTime = getValidInt("Enter maximum listening time (in seconds): ", minTime, 3600);
                
                std::vector<Song> filteredSongs = favoriteSongsQueue->getFavoritesByTimeRange(minTime, maxTime);
                
                if (filteredSongs.empty()) {
                    std::cout << "No songs found in the specified time range." << std::endl;
                } else {
                    std::cout << "Songs with listening time between " << minTime << " and " << maxTime << " seconds:" << std::endl;
                    for (size_t i = 0; i < filteredSongs.size(); i++) {
                        const Song& song = filteredSongs[i];
                        std::cout << (i + 1) << ". " << song.getTitle() << " - " << song.getArtist() << std::endl;
                        std::cout << "   Listening time: " << favoriteSongsQueue->getListeningTime(song) << " seconds" << std::endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 13: {
                favoriteSongsQueue->displayDetailedStats();
                pauseScreen();
                break;
            }
            case 14: {
                std::string filename = getValidString("Enter filename to export to: ");
                favoriteSongsQueue->exportFavoritesToFile(filename);
                pauseScreen();
                break;
            }
            case 15: {
                std::string filename = getValidString("Enter filename to import from: ");
                favoriteSongsQueue->importFavoritesFromFile(filename);
                pauseScreen();
                break;
            }
        }
    }
} 