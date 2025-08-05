#include "../include/song.h"
#include <iomanip>
#include <sstream>
#include <ctime>

// Default constructor
Song::Song() : id(""), title(""), artist(""), duration(0), rating(0) {
    std::time_t now = std::time(nullptr);
    addedDate = std::to_string(now);
}

// Parameterized constructor
Song::Song(const std::string& id, const std::string& title, const std::string& artist, 
           int duration, int rating) 
    : id(id), title(title), artist(artist), duration(duration), rating(rating) {
    std::time_t now = std::time(nullptr);
    addedDate = std::to_string(now);
}

// Full parameterized constructor
Song::Song(const std::string& id, const std::string& title, const std::string& artist, 
           int duration, int rating, const std::string& album, const std::string& genre)
    : id(id), title(title), artist(artist), duration(duration), rating(rating), 
      album(album), genre(genre) {
    std::time_t now = std::time(nullptr);
    addedDate = std::to_string(now);
}

// Getters
std::string Song::getId() const { return id; }
std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
int Song::getDuration() const { return duration; }
int Song::getRating() const { return rating; }
std::string Song::getAlbum() const { return album; }
std::string Song::getGenre() const { return genre; }
std::string Song::getAddedDate() const { return addedDate; }

// Setters
void Song::setId(const std::string& id) { this->id = id; }
void Song::setTitle(const std::string& title) { this->title = title; }
void Song::setArtist(const std::string& artist) { this->artist = artist; }
void Song::setDuration(int duration) { this->duration = duration; }
void Song::setRating(int rating) { 
    if (rating >= 0 && rating <= 6) {
        this->rating = rating; 
    }
}
void Song::setAlbum(const std::string& album) { this->album = album; }
void Song::setGenre(const std::string& genre) { this->genre = genre; }
void Song::setAddedDate(const std::string& date) { this->addedDate = date; }

// Utility methods
std::string Song::getDurationString() const {
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;
    
    std::stringstream ss;
    if (hours > 0) {
        ss << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" 
           << std::setfill('0') << std::setw(2) << seconds;
    } else {
        ss << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
    }
    return ss.str();
}

void Song::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Duration: " << getDurationString() << std::endl;
    std::cout << "Rating: " << rating << "/5" << std::endl;
    if (!album.empty()) std::cout << "Album: " << album << std::endl;
    if (!genre.empty()) std::cout << "Genre: " << genre << std::endl;
    std::cout << "Added: " << addedDate << std::endl;
    std::cout << "------------------------" << std::endl;
}

bool Song::isValid() const {
    return !id.empty() && !title.empty() && !artist.empty() && duration > 0;
}

// Comparison operators
bool Song::operator<(const Song& other) const {
    // Compare by title first, then by artist
    if (title != other.title) {
        return title < other.title;
    }
    return artist < other.artist;
}

bool Song::operator==(const Song& other) const {
    return id == other.id;
}

bool Song::operator!=(const Song& other) const {
    return !(*this == other);
} 