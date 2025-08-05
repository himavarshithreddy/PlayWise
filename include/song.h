#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>

/**
 * @brief Song class representing a music track in the PlayWise system
 * 
 * This class contains all metadata for a song including ID, title, artist,
 * duration, and rating. It serves as the fundamental data unit for the
 * playlist management system.
 * 
 * Time Complexity: O(1) for all operations
 * Space Complexity: O(1) per song object
 */
class Song {
private:
    std::string id;
    std::string title;
    std::string artist;
    int duration;  // in seconds
    int rating;    // 1-5 stars
    std::string album;
    std::string genre;
    std::string addedDate;

public:
    // Constructors
    Song();
    Song(const std::string& id, const std::string& title, const std::string& artist, 
         int duration, int rating = 0);
    Song(const std::string& id, const std::string& title, const std::string& artist, 
         int duration, int rating, const std::string& album, const std::string& genre);

    // Getters
    std::string getId() const;
    std::string getTitle() const;
    std::string getArtist() const;
    int getDuration() const;
    int getRating() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    std::string getAddedDate() const;

    // Setters
    void setId(const std::string& id);
    void setTitle(const std::string& title);
    void setArtist(const std::string& artist);
    void setDuration(int duration);
    void setRating(int rating);
    void setAlbum(const std::string& album);
    void setGenre(const std::string& genre);
    void setAddedDate(const std::string& date);

    // Utility methods
    std::string getDurationString() const;  
    void display() const;                   // Display song information
    bool isValid() const;                   // Check if song data is valid

    // Comparison operators for sorting
    bool operator<(const Song& other) const;
    bool operator==(const Song& other) const;
    bool operator!=(const Song& other) const;
};

#endif // SONG_H 