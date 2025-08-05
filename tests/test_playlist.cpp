#include "test_framework.h"
#include "../include/playlist.h"
#include "../include/song.h"
#include <iostream>
#include <string>

// Global test framework instance
// TestFramework instance is defined in test_runner.cpp

// Test functions for Playlist class
bool testPlaylistConstructor() {
    Playlist playlist("Test Playlist");
    
    ASSERT_EQUAL("Test Playlist", playlist.getName());
    ASSERT_EQUAL(0, playlist.getSize());
    ASSERT_TRUE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistDefaultConstructor() {
    Playlist playlist;
    
    ASSERT_EQUAL("Untitled Playlist", playlist.getName());
    ASSERT_EQUAL(0, playlist.getSize());
    ASSERT_TRUE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistAddSong() {
    Playlist playlist("Test");
    
    playlist.add_song("Test Song", "Test Artist", 180);
    
    ASSERT_EQUAL(1, playlist.getSize());
    ASSERT_FALSE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistAddMultipleSongs() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    playlist.add_song("Song 3", "Artist 3", 160);
    
    ASSERT_EQUAL(3, playlist.getSize());
    
    return true;
}

bool testPlaylistDeleteSong() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    bool result = playlist.delete_song(0);
    
    ASSERT_TRUE(result);
    ASSERT_EQUAL(1, playlist.getSize());
    
    return true;
}

bool testPlaylistDeleteInvalidIndex() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    bool result = playlist.delete_song(5); // Invalid index
    
    ASSERT_FALSE(result);
    ASSERT_EQUAL(1, playlist.getSize()); // Size should remain unchanged
    
    return true;
}

bool testPlaylistDeleteFromEmpty() {
    Playlist playlist("Test");
    
    bool result = playlist.delete_song(0);
    
    ASSERT_FALSE(result);
    ASSERT_EQUAL(0, playlist.getSize());
    
    return true;
}

bool testPlaylistMoveSong() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    playlist.add_song("Song 3", "Artist 3", 160);
    
    bool result = playlist.move_song(0, 2);
    
    ASSERT_TRUE(result);
    ASSERT_EQUAL(3, playlist.getSize());
    
    return true;
}

bool testPlaylistMoveInvalidIndices() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    bool result = playlist.move_song(0, 5); // Invalid target index
    
    ASSERT_FALSE(result);
    
    return true;
}

bool testPlaylistMoveSamePosition() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    bool result = playlist.move_song(0, 0); // Same position
    
    ASSERT_TRUE(result); // Should succeed even if no actual move
    
    return true;
}

bool testPlaylistReverse() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    playlist.add_song("Song 3", "Artist 3", 160);
    
    playlist.reverse_playlist();
    
    ASSERT_EQUAL(3, playlist.getSize());
    
    return true;
}

bool testPlaylistReverseEmpty() {
    Playlist playlist("Test");
    
    playlist.reverse_playlist();
    
    ASSERT_EQUAL(0, playlist.getSize());
    ASSERT_TRUE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistReverseSingle() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.reverse_playlist();
    
    ASSERT_EQUAL(1, playlist.getSize());
    
    return true;
}

bool testPlaylistShuffle() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    playlist.add_song("Song 3", "Artist 3", 160);
    
    playlist.shuffle();
    
    ASSERT_EQUAL(3, playlist.getSize());
    
    return true;
}

bool testPlaylistShuffleEmpty() {
    Playlist playlist("Test");
    
    playlist.shuffle();
    
    ASSERT_EQUAL(0, playlist.getSize());
    ASSERT_TRUE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistShuffleSingle() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.shuffle();
    
    ASSERT_EQUAL(1, playlist.getSize());
    
    return true;
}

bool testPlaylistClear() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    playlist.clear();
    
    ASSERT_EQUAL(0, playlist.getSize());
    ASSERT_TRUE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistClearEmpty() {
    Playlist playlist("Test");
    
    playlist.clear();
    
    ASSERT_EQUAL(0, playlist.getSize());
    ASSERT_TRUE(playlist.isEmpty());
    
    return true;
}

bool testPlaylistFindSongById() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    Song* found = playlist.find_song_by_id("1");
    
    ASSERT_NOT_NULL(found);
    ASSERT_EQUAL("Song 1", found->getTitle());
    
    return true;
}

bool testPlaylistFindSongByIdNotFound() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    Song* found = playlist.find_song_by_id("999");
    
    ASSERT_NULL(found);
    
    return true;
}

bool testPlaylistFindSongByTitle() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    Song* found = playlist.find_song_by_title("Song 2");
    
    ASSERT_NOT_NULL(found);
    ASSERT_EQUAL("Artist 2", found->getArtist());
    
    return true;
}

bool testPlaylistFindSongByTitleNotFound() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    Song* found = playlist.find_song_by_title("Nonexistent Song");
    
    ASSERT_NULL(found);
    
    return true;
}

bool testPlaylistFindSongIndex() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    int index = playlist.find_song_index("2");
    
    ASSERT_EQUAL(1, index);
    
    return true;
}

bool testPlaylistFindSongIndexNotFound() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    int index = playlist.find_song_index("999");
    
    ASSERT_EQUAL(-1, index);
    
    return true;
}

bool testPlaylistGetSongAt() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    Song* song = playlist.get_song_at(1);
    
    ASSERT_NOT_NULL(song);
    ASSERT_EQUAL("Song 2", song->getTitle());
    
    return true;
}

bool testPlaylistGetSongAtInvalidIndex() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    Song* song = playlist.get_song_at(5);
    
    ASSERT_NULL(song);
    
    return true;
}

bool testPlaylistCopyConstructor() {
    Playlist original("Original");
    original.add_song("Song 1", "Artist 1", 180);
    original.add_song("Song 2", "Artist 2", 200);
    
    Playlist copy(original);
    
    ASSERT_EQUAL(original.getName(), copy.getName());
    ASSERT_EQUAL(original.getSize(), copy.getSize());
    
    return true;
}

bool testPlaylistAssignmentOperator() {
    Playlist original("Original");
    original.add_song("Song 1", "Artist 1", 180);
    
    Playlist assigned("Assigned");
    assigned = original;
    
    ASSERT_EQUAL(original.getName(), assigned.getName());
    ASSERT_EQUAL(original.getSize(), assigned.getSize());
    
    return true;
}

bool testPlaylistSelfAssignment() {
    Playlist playlist("Test");
    playlist.add_song("Song 1", "Artist 1", 180);
    
    playlist = playlist; // Self-assignment
    
    ASSERT_EQUAL(1, playlist.getSize());
    ASSERT_EQUAL("Test", playlist.getName());
    
    return true;
}

bool testPlaylistLargeNumberOfSongs() {
    Playlist playlist("Large Test");
    
    // Add many songs
    for (int i = 0; i < 1000; i++) {
        playlist.add_song("Song " + std::to_string(i), "Artist " + std::to_string(i), 180 + i);
    }
    
    ASSERT_EQUAL(1000, playlist.getSize());
    
    // Test operations on large playlist
    bool moveResult = playlist.move_song(0, 500);
    ASSERT_TRUE(moveResult);
    
    bool deleteResult = playlist.delete_song(250);
    ASSERT_TRUE(deleteResult);
    ASSERT_EQUAL(999, playlist.getSize());
    
    return true;
}

bool testPlaylistEdgeCaseNames() {
    Playlist playlist(""); // Empty name
    
    ASSERT_EQUAL("", playlist.getName());
    
    playlist.setName("Very Long Playlist Name That Exceeds Normal Length");
    ASSERT_EQUAL("Very Long Playlist Name That Exceeds Normal Length", playlist.getName());
    
    return true;
}

bool testPlaylistDeleteBySongId() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    playlist.add_song("Song 2", "Artist 2", 200);
    
    bool result = playlist.delete_song_by_id("1");
    
    ASSERT_TRUE(result);
    ASSERT_EQUAL(1, playlist.getSize());
    
    return true;
}

bool testPlaylistDeleteBySongIdNotFound() {
    Playlist playlist("Test");
    
    playlist.add_song("Song 1", "Artist 1", 180);
    
    bool result = playlist.delete_song_by_id("999");
    
    ASSERT_FALSE(result);
    ASSERT_EQUAL(1, playlist.getSize());
    
    return true;
}

// Register all Playlist tests
void registerPlaylistTests() {
    testFramework.addTest("Playlist Constructor", "Test constructor with name", testPlaylistConstructor);
    testFramework.addTest("Playlist Default Constructor", "Test default constructor", testPlaylistDefaultConstructor);
    testFramework.addTest("Playlist Add Song", "Test adding a single song", testPlaylistAddSong);
    testFramework.addTest("Playlist Add Multiple Songs", "Test adding multiple songs", testPlaylistAddMultipleSongs);
    testFramework.addTest("Playlist Delete Song", "Test deleting a song by index", testPlaylistDeleteSong);
    testFramework.addTest("Playlist Delete Invalid Index", "Test deleting with invalid index", testPlaylistDeleteInvalidIndex);
    testFramework.addTest("Playlist Delete From Empty", "Test deleting from empty playlist", testPlaylistDeleteFromEmpty);
    testFramework.addTest("Playlist Move Song", "Test moving a song", testPlaylistMoveSong);
    testFramework.addTest("Playlist Move Invalid Indices", "Test moving with invalid indices", testPlaylistMoveInvalidIndices);
    testFramework.addTest("Playlist Move Same Position", "Test moving to same position", testPlaylistMoveSamePosition);
    testFramework.addTest("Playlist Reverse", "Test reversing playlist", testPlaylistReverse);
    testFramework.addTest("Playlist Reverse Empty", "Test reversing empty playlist", testPlaylistReverseEmpty);
    testFramework.addTest("Playlist Reverse Single", "Test reversing single song playlist", testPlaylistReverseSingle);
    testFramework.addTest("Playlist Shuffle", "Test shuffling playlist", testPlaylistShuffle);
    testFramework.addTest("Playlist Shuffle Empty", "Test shuffling empty playlist", testPlaylistShuffleEmpty);
    testFramework.addTest("Playlist Shuffle Single", "Test shuffling single song playlist", testPlaylistShuffleSingle);
    testFramework.addTest("Playlist Clear", "Test clearing playlist", testPlaylistClear);
    testFramework.addTest("Playlist Clear Empty", "Test clearing empty playlist", testPlaylistClearEmpty);
    testFramework.addTest("Playlist Find Song By ID", "Test finding song by ID", testPlaylistFindSongById);
    testFramework.addTest("Playlist Find Song By ID Not Found", "Test finding non-existent song by ID", testPlaylistFindSongByIdNotFound);
    testFramework.addTest("Playlist Find Song By Title", "Test finding song by title", testPlaylistFindSongByTitle);
    testFramework.addTest("Playlist Find Song By Title Not Found", "Test finding non-existent song by title", testPlaylistFindSongByTitleNotFound);
    testFramework.addTest("Playlist Find Song Index", "Test finding song index", testPlaylistFindSongIndex);
    testFramework.addTest("Playlist Find Song Index Not Found", "Test finding index of non-existent song", testPlaylistFindSongIndexNotFound);
    testFramework.addTest("Playlist Get Song At", "Test getting song at index", testPlaylistGetSongAt);
    testFramework.addTest("Playlist Get Song At Invalid Index", "Test getting song at invalid index", testPlaylistGetSongAtInvalidIndex);
    testFramework.addTest("Playlist Copy Constructor", "Test copy constructor", testPlaylistCopyConstructor);
    testFramework.addTest("Playlist Assignment Operator", "Test assignment operator", testPlaylistAssignmentOperator);
    testFramework.addTest("Playlist Self Assignment", "Test self-assignment", testPlaylistSelfAssignment);
    testFramework.addTest("Playlist Large Number of Songs", "Test with 1000 songs", testPlaylistLargeNumberOfSongs);
    testFramework.addTest("Playlist Edge Case Names", "Test with edge case playlist names", testPlaylistEdgeCaseNames);
    testFramework.addTest("Playlist Delete By Song ID", "Test deleting song by ID", testPlaylistDeleteBySongId);
    testFramework.addTest("Playlist Delete By Song ID Not Found", "Test deleting non-existent song by ID", testPlaylistDeleteBySongIdNotFound);
} 