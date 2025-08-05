#include "test_framework.h"
#include "../include/playlist.h"
#include "../include/history.h"
#include "../include/rating_tree.h"
#include "../include/song_database.h"
#include "../include/favorite_songs_queue.h"
#include "../include/sorting.h"
#include <iostream>
#include <string>

// Global test framework instance
// TestFramework instance is defined in test_runner.cpp

// Integration test functions
bool testPlaylistToHistoryIntegration() {
    // Test integration between playlist and history
    Playlist playlist("Test Playlist");
    History history(10);
    
    // Add songs to playlist
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    // Simulate playing songs from playlist
    Song* song1 = playlist.get_song_at(0);
    Song* song2 = playlist.get_song_at(1);
    
    ASSERT_NOT_NULL(song1);
    ASSERT_NOT_NULL(song2);
    
    // Add to history
    history.add_played_song(*song1);
    history.add_played_song(*song2);
    
    ASSERT_EQUAL(2, history.get_size());
    
    // Verify history contains the songs
    Song lastPlayed = history.get_last_played();
    ASSERT_EQUAL("Song 2", lastPlayed.getTitle());
    
    return true;
}

bool testHistoryToFavoritesIntegration() {
    // Test integration between history and favorites
    History history(5);
    FavoriteSongsQueue favorites;
    
    // Add songs to history
    Song song1("1", "Song 1", "Artist 1", 180, 4);
    Song song2("2", "Song 2", "Artist 2", 200, 5);
    Song song3("3", "Song 3", "Artist 3", 160, 3);
    
    history.add_played_song(song1);
    history.add_played_song(song2);
    history.add_played_song(song3);
    history.add_played_song(song1); // Play song1 again
    
    // Sync favorites with history
    std::vector<Song> recentSongs = history.get_recent_songs(10);
    favorites.syncWithHistory(recentSongs);
    
    ASSERT_EQUAL(3, favorites.getSize()); // Should have 3 unique songs
    
    // Verify favorites are sorted by listening time
    Song topFavorite = favorites.getTopFavorite();
    ASSERT_EQUAL("Song 1", topFavorite.getTitle()); // Song1 played twice
    
    return true;
}

bool testDatabaseToPlaylistIntegration() {
    // Test integration between database and playlist
    SongDatabase database;
    Playlist playlist("Test");
    
    // Add songs to database
    Song song1("1", "Song 1", "Artist 1", 180, 4);
    Song song2("2", "Song 2", "Artist 2", 200, 5);
    
    database.insert_song(song1);
    database.insert_song(song2);
    
    // Search and add to playlist
    Song* found = database.search_by_title("Song 1");
    ASSERT_NOT_NULL(found);
    
    playlist.add_song(*found);
    ASSERT_EQUAL(1, playlist.getSize());
    
    // Add another song
    std::vector<Song> foundSongs = database.search_by_artist("Artist 2");
    ASSERT_NOT_EMPTY(foundSongs);
    
    playlist.add_song(foundSongs[0]);
    ASSERT_EQUAL(2, playlist.getSize());
    
    return true;
}

bool testRatingTreeToPlaylistIntegration() {
    // Test integration between rating tree and playlist
    RatingTree ratingTree;
    Playlist playlist("High Rated Songs");
    
    // Add songs with different ratings
    Song song1("1", "Song 1", "Artist 1", 180, 5);
    Song song2("2", "Song 2", "Artist 2", 200, 4);
    Song song3("3", "Song 3", "Artist 3", 160, 5);
    
    ratingTree.insert_song(song1, 5);
    ratingTree.insert_song(song2, 4);
    ratingTree.insert_song(song3, 5);
    
    // Get 5-star songs and add to playlist
    std::vector<Song> fiveStarSongs = ratingTree.search_by_rating(5);
    ASSERT_EQUAL(2, fiveStarSongs.size());
    
    for (const Song& song : fiveStarSongs) {
        playlist.add_song(song);
    }
    
    ASSERT_EQUAL(2, playlist.getSize());
    
    return true;
}

bool testSortingToPlaylistIntegration() {
    // Test integration between sorting and playlist
    Playlist playlist("Test");
    
    // Add songs in random order
    playlist.add_song("Zebra", "Artist C", 300);
    playlist.add_song("Apple", "Artist A", 180);
    playlist.add_song("Banana", "Artist B", 200);
    
    // Convert playlist to vector for sorting
    std::vector<Song> songs;
    PlaylistNode* current = playlist.getHead();
    while (current != nullptr) {
        songs.push_back(current->song);
        current = current->next;
    }
    
    // Sort by title
    Sorting::sortPlaylist(songs, Sorting::SortCriteria::TITLE_ASC, "merge");
    
    // Verify sorting
    ASSERT_EQUAL("Apple", songs[0].getTitle());
    ASSERT_EQUAL("Banana", songs[1].getTitle());
    ASSERT_EQUAL("Zebra", songs[2].getTitle());
    
    return true;
}

bool testFavoritesToSortingIntegration() {
    // Test integration between favorites and sorting
    FavoriteSongsQueue favorites;
    
    // Add songs with different listening times
    Song song1("1", "Song 1", "Artist 1", 180, 4);
    Song song2("2", "Song 2", "Artist 2", 200, 5);
    Song song3("3", "Song 3", "Artist 3", 160, 3);
    
    favorites.addSong(song1);
    favorites.addSong(song2);
    favorites.addSong(song3);
    
    // Update listening times
    favorites.updateListeningTime(song1, 300);
    favorites.updateListeningTime(song2, 150);
    favorites.updateListeningTime(song3, 450);
    
    // Get top favorites (should be auto-sorted)
    std::vector<Song> topSongs = favorites.getTopFavorites(3);
    
    // Verify auto-sorting by listening time
    ASSERT_EQUAL("Song 3", topSongs[0].getTitle()); // 450 seconds
    ASSERT_EQUAL("Song 1", topSongs[1].getTitle()); // 300 seconds
    ASSERT_EQUAL("Song 2", topSongs[2].getTitle()); // 150 seconds
    
    return true;
}

bool testCompleteWorkflowIntegration() {
    // Test complete workflow: Database -> Playlist -> History -> Favorites -> Sorting
    
    // 1. Initialize components
    SongDatabase database;
    Playlist playlist("Workflow Test");
    History history(10);
    FavoriteSongsQueue favorites;
    RatingTree ratingTree;
    
    // 2. Add songs to database
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    Song song2("2", "Hotel California", "Eagles", 391, 4);
    Song song3("3", "Stairway to Heaven", "Led Zeppelin", 482, 5);
    
    database.insert_song(song1);
    database.insert_song(song2);
    database.insert_song(song3);
    
    // 3. Add high-rated songs to playlist
    std::vector<Song> highRatedSongs = database.search_by_rating_range(5, 5);
    for (const Song& song : highRatedSongs) {
        playlist.add_song(song);
    }
    
    ASSERT_EQUAL(2, playlist.getSize()); // 2 songs with rating 5
    
    // 4. Simulate playing songs from playlist
    PlaylistNode* current = playlist.getHead();
    while (current != nullptr) {
        history.add_played_song(current->song);
        current = current->next;
    }
    
    ASSERT_EQUAL(2, history.get_size());
    
    // 5. Add to favorites based on play history
    std::vector<Song> playedSongs = history.get_recent_songs(10);
    favorites.syncWithHistory(playedSongs);
    
    ASSERT_EQUAL(2, favorites.getSize());
    
    // 6. Update listening times
    favorites.updateListeningTime(song1, 500);
    favorites.updateListeningTime(song3, 300);
    
    // 7. Get sorted favorites
    std::vector<Song> sortedFavorites = favorites.getTopFavorites(2);
    
    // Verify the complete workflow
    ASSERT_EQUAL("Bohemian Rhapsody", sortedFavorites[0].getTitle()); // Most listened
    ASSERT_EQUAL("Stairway to Heaven", sortedFavorites[1].getTitle()); // Less listened
    
    return true;
}

bool testErrorHandlingIntegration() {
    // Test error handling across components
    
    // 1. Try to delete non-existent song from playlist
    Playlist playlist("Error Test");
    bool deleteResult = playlist.delete_song(0);
    ASSERT_FALSE(deleteResult);
    
    // 2. Try to get song from empty history
    History history(5);
    Song lastSong = history.get_last_played();
    ASSERT_FALSE(lastSong.isValid());
    
    // 3. Try to search non-existent song in database
    SongDatabase database;
    Song* found = database.search_by_title("Non-existent Song");
    ASSERT_NULL(found);
    
    // 4. Try to get top favorite from empty favorites
    FavoriteSongsQueue favorites;
    Song topSong = favorites.getTopFavorite();
    ASSERT_FALSE(topSong.isValid());
    
    // 5. Try to search non-existent rating in rating tree
    RatingTree ratingTree;
    std::vector<Song> songs = ratingTree.search_by_rating(5);
    ASSERT_EMPTY(songs);
    
    return true;
}

bool testPerformanceIntegration() {
    // Test performance with larger datasets
    
    // 1. Large playlist operations
    Playlist playlist("Performance Test");
    for (int i = 0; i < 100; i++) {
        playlist.add_song("Song " + std::to_string(i), "Artist " + std::to_string(i), 180 + i);
    }
    
    ASSERT_EQUAL(100, playlist.getSize());
    
    // 2. Large history operations
    History history(50);
    for (int i = 0; i < 100; i++) {
        Song song(std::to_string(i), "Song " + std::to_string(i), "Artist " + std::to_string(i), 180, 3);
        history.add_played_song(song);
    }
    
    ASSERT_EQUAL(50, history.get_size()); // Should respect max size
    
    // 3. Large database operations
    SongDatabase database;
    for (int i = 0; i < 100; i++) {
        Song song(std::to_string(i), "Song " + std::to_string(i), "Artist " + std::to_string(i), 180, 3);
        database.insert_song(song);
    }
    
    // 4. Large favorites operations
    FavoriteSongsQueue favorites;
    for (int i = 0; i < 100; i++) {
        Song song(std::to_string(i), "Song " + std::to_string(i), "Artist " + std::to_string(i), 180, 3);
        favorites.addSong(song);
        favorites.updateListeningTime(song, i * 10); // Different listening times
    }
    
    ASSERT_EQUAL(100, favorites.getSize());
    
    // 5. Test sorting performance
    std::vector<Song> songs;
    PlaylistNode* current = playlist.getHead();
    while (current != nullptr) {
        songs.push_back(current->song);
        current = current->next;
    }
    
    Sorting::sortPlaylist(songs, Sorting::SortCriteria::TITLE_ASC, "merge");
    ASSERT_EQUAL(100, songs.size());
    
    return true;
}

bool testDataConsistencyIntegration() {
    // Test data consistency across components
    
    SongDatabase database;
    Playlist playlist("Consistency Test");
    History history(10);
    FavoriteSongsQueue favorites;
    
    // Add same song to all components
    Song song("1", "Test Song", "Test Artist", 180, 4);
    
    database.insert_song(song);
    playlist.add_song(song);
    history.add_played_song(song);
    favorites.addSong(song);
    
    // Verify consistency
    Song* dbSong = database.search_by_id("1");
    Song* plSong = playlist.find_song_by_id("1");
    
    ASSERT_NOT_NULL(dbSong);
    ASSERT_NOT_NULL(plSong);
    
    // Verify same data
    ASSERT_EQUAL(dbSong->getTitle(), plSong->getTitle());
    ASSERT_EQUAL(dbSong->getArtist(), plSong->getArtist());
    ASSERT_EQUAL(dbSong->getDuration(), plSong->getDuration());
    ASSERT_EQUAL(dbSong->getRating(), plSong->getRating());
    
    // Verify history consistency
    Song histSong = history.get_last_played();
    ASSERT_EQUAL(song.getTitle(), histSong.getTitle());
    
    // Verify favorites consistency
    ASSERT_TRUE(favorites.isInFavorites(song));
    
    return true;
}

// Register all integration tests
void registerIntegrationTests() {
    testFramework.addTest("Playlist to History Integration", "Test integration between playlist and history", testPlaylistToHistoryIntegration, true);
    testFramework.addTest("History to Favorites Integration", "Test integration between history and favorites", testHistoryToFavoritesIntegration, true);
    testFramework.addTest("Database to Playlist Integration", "Test integration between database and playlist", testDatabaseToPlaylistIntegration, true);
    testFramework.addTest("Rating Tree to Playlist Integration", "Test integration between rating tree and playlist", testRatingTreeToPlaylistIntegration, true);
    testFramework.addTest("Sorting to Playlist Integration", "Test integration between sorting and playlist", testSortingToPlaylistIntegration, true);
    testFramework.addTest("Favorites to Sorting Integration", "Test integration between favorites and sorting", testFavoritesToSortingIntegration, true);
    testFramework.addTest("Complete Workflow Integration", "Test complete workflow across all components", testCompleteWorkflowIntegration, true);
    testFramework.addTest("Error Handling Integration", "Test error handling across components", testErrorHandlingIntegration, true);
    testFramework.addTest("Performance Integration", "Test performance with larger datasets", testPerformanceIntegration, true);
    testFramework.addTest("Data Consistency Integration", "Test data consistency across components", testDataConsistencyIntegration, true);
} 