#include "test_framework.h"
#include "../include/song.h"
#include <iostream>
#include <string>

// Global test framework instance
// TestFramework instance is defined in test_runner.cpp

// Test functions for Song class
bool testSongConstructor() {
    Song song("1", "Test Song", "Test Artist", 180, 4);
    
    ASSERT_EQUAL("1", song.getId());
    ASSERT_EQUAL("Test Song", song.getTitle());
    ASSERT_EQUAL("Test Artist", song.getArtist());
    ASSERT_EQUAL(180, song.getDuration());
    ASSERT_EQUAL(4, song.getRating());
    
    return true;
}

bool testSongDefaultConstructor() {
    Song song;
    
    ASSERT_EQUAL("", song.getId());
    ASSERT_EQUAL("", song.getTitle());
    ASSERT_EQUAL("", song.getArtist());
    ASSERT_EQUAL(0, song.getDuration());
    ASSERT_EQUAL(0, song.getRating());
    
    return true;
}

bool testSongSetters() {
    Song song;
    
    song.setId("123");
    song.setTitle("New Title");
    song.setArtist("New Artist");
    song.setDuration(300);
    song.setRating(5);
    
    ASSERT_EQUAL("123", song.getId());
    ASSERT_EQUAL("New Title", song.getTitle());
    ASSERT_EQUAL("New Artist", song.getArtist());
    ASSERT_EQUAL(300, song.getDuration());
    ASSERT_EQUAL(5, song.getRating());
    
    return true;
}

bool testSongDurationString() {
    Song song1("1", "Short", "Artist", 65, 3);
    Song song2("2", "Medium", "Artist", 125, 4);
    Song song3("3", "Long", "Artist", 3661, 5);
    
    ASSERT_EQUAL("1:05", song1.getDurationString());
    ASSERT_EQUAL("2:05", song2.getDurationString());
    ASSERT_EQUAL("1:01:01", song3.getDurationString());
    
    return true;
}

bool testSongEdgeCaseDuration() {
    Song song("1", "Edge", "Artist", 0, 3);
    
    ASSERT_EQUAL(0, song.getDuration());
    ASSERT_EQUAL("0:00", song.getDurationString());
    
    return true;
}

bool testSongRatingValidation() {
    Song song("1", "Test", "Artist", 180, 3);
    
    // Test valid ratings
    song.setRating(1);
    ASSERT_EQUAL(1, song.getRating());
    
    song.setRating(5);
    ASSERT_EQUAL(5, song.getRating());
    
    // Test edge cases
    song.setRating(0);
    ASSERT_EQUAL(0, song.getRating());
    
    song.setRating(6); // Should handle invalid rating gracefully
    ASSERT_EQUAL(6, song.getRating()); // Assuming no validation in setter
    
    return true;
}

bool testSongEmptyValues() {
    Song song("", "", "", 0, 0);
    
    ASSERT_EQUAL("", song.getId());
    ASSERT_EQUAL("", song.getTitle());
    ASSERT_EQUAL("", song.getArtist());
    ASSERT_EQUAL(0, song.getDuration());
    ASSERT_EQUAL(0, song.getRating());
    
    return true;
}

bool testSongCopyConstructor() {
    Song original("1", "Original", "Artist", 200, 4);
    Song copy(original);
    
    ASSERT_EQUAL(original.getId(), copy.getId());
    ASSERT_EQUAL(original.getTitle(), copy.getTitle());
    ASSERT_EQUAL(original.getArtist(), copy.getArtist());
    ASSERT_EQUAL(original.getDuration(), copy.getDuration());
    ASSERT_EQUAL(original.getRating(), copy.getRating());
    
    return true;
}

bool testSongAssignmentOperator() {
    Song original("1", "Original", "Artist", 200, 4);
    Song assigned;
    
    assigned = original;
    
    ASSERT_EQUAL(original.getId(), assigned.getId());
    ASSERT_EQUAL(original.getTitle(), assigned.getTitle());
    ASSERT_EQUAL(original.getArtist(), assigned.getArtist());
    ASSERT_EQUAL(original.getDuration(), assigned.getDuration());
    ASSERT_EQUAL(original.getRating(), assigned.getRating());
    
    return true;
}

bool testSongSelfAssignment() {
    Song song("1", "Test", "Artist", 180, 3);
    
    // Self-assignment should not cause issues
    song = song;
    
    ASSERT_EQUAL("1", song.getId());
    ASSERT_EQUAL("Test", song.getTitle());
    ASSERT_EQUAL("Artist", song.getArtist());
    ASSERT_EQUAL(180, song.getDuration());
    ASSERT_EQUAL(3, song.getRating());
    
    return true;
}

bool testSongIsValid() {
    Song validSong("1", "Valid", "Artist", 180, 3);
    Song invalidSong; // Default constructor creates invalid song
    
    ASSERT_TRUE(validSong.isValid());
    ASSERT_FALSE(invalidSong.isValid());
    
    return true;
}

bool testSongLongStrings() {
    std::string longTitle(1000, 'A');
    std::string longArtist(1000, 'B');
    
    Song song("1", longTitle, longArtist, 180, 3);
    
    ASSERT_EQUAL(longTitle, song.getTitle());
    ASSERT_EQUAL(longArtist, song.getArtist());
    
    return true;
}

bool testSongSpecialCharacters() {
    Song song("1", "Song with spaces & symbols!@#", "Artist with 123 numbers", 180, 3);
    
    ASSERT_EQUAL("Song with spaces & symbols!@#", song.getTitle());
    ASSERT_EQUAL("Artist with 123 numbers", song.getArtist());
    
    return true;
}

bool testSongUnicodeCharacters() {
    Song song("1", "Sóng with unicode: ñáéíóú", "Artíst with unicode: ñáéíóú", 180, 3);
    
    ASSERT_EQUAL("Sóng with unicode: ñáéíóú", song.getTitle());
    ASSERT_EQUAL("Artíst with unicode: ñáéíóú", song.getArtist());
    
    return true;
}

bool testSongNegativeDuration() {
    Song song("1", "Test", "Artist", -100, 3);
    
    // Should handle negative duration gracefully
    ASSERT_EQUAL(-100, song.getDuration());
    
    return true;
}

bool testSongLargeDuration() {
    Song song("1", "Test", "Artist", 999999, 3);
    
    ASSERT_EQUAL(999999, song.getDuration());
    // Should handle large duration in getDurationString()
    std::string durationStr = song.getDurationString();
    ASSERT_NOT_EMPTY(durationStr);
    
    return true;
}

// Register all Song tests
void registerSongTests() {
    testFramework.addTest("Song Constructor", "Test basic constructor with all parameters", testSongConstructor);
    testFramework.addTest("Song Default Constructor", "Test default constructor creates empty song", testSongDefaultConstructor);
    testFramework.addTest("Song Setters", "Test all setter methods", testSongSetters);
    testFramework.addTest("Song Duration String", "Test duration string formatting", testSongDurationString);
    testFramework.addTest("Song Edge Case Duration", "Test zero duration handling", testSongEdgeCaseDuration);
    testFramework.addTest("Song Rating Validation", "Test rating setter with various values", testSongRatingValidation);
    testFramework.addTest("Song Empty Values", "Test song with empty strings", testSongEmptyValues);
    testFramework.addTest("Song Copy Constructor", "Test copy constructor functionality", testSongCopyConstructor);
    testFramework.addTest("Song Assignment Operator", "Test assignment operator", testSongAssignmentOperator);
    testFramework.addTest("Song Self Assignment", "Test self-assignment safety", testSongSelfAssignment);
    testFramework.addTest("Song Is Valid", "Test isValid() method", testSongIsValid);
    testFramework.addTest("Song Long Strings", "Test with very long title and artist", testSongLongStrings);
    testFramework.addTest("Song Special Characters", "Test with special characters in strings", testSongSpecialCharacters);
    testFramework.addTest("Song Unicode Characters", "Test with unicode characters", testSongUnicodeCharacters);
    testFramework.addTest("Song Negative Duration", "Test negative duration handling", testSongNegativeDuration);
    testFramework.addTest("Song Large Duration", "Test very large duration values", testSongLargeDuration);
} 