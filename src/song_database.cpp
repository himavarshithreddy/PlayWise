#include "../include/song_database.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <unordered_set>

// Constructor
SongDatabase::SongDatabase() {}

// Destructor
SongDatabase::~SongDatabase() {
    clear();
}

// Copy constructor
SongDatabase::SongDatabase(const SongDatabase& other) {
    songsById = other.songsById;
    titleArtistKeys = other.titleArtistKeys;
}

// Assignment operator
SongDatabase& SongDatabase::operator=(const SongDatabase& other) {
    if (this != &other) {
        songsById = other.songsById;
        titleArtistKeys = other.titleArtistKeys;
    }
    return *this;
}

// Helper methods
std::string SongDatabase::normalizeString(const std::string& str) const {
    std::string normalized = str;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}

bool SongDatabase::isValidSongId(const std::string& songId) const {
    return !songId.empty() && songId.length() > 0;
}

// Core operations
std::string SongDatabase::generateCompositeKey(const std::string& title, const std::string& artist) const {
    return normalizeString(title) + "|||" + normalizeString(artist);
}

bool SongDatabase::insert_song(const Song& song) {
    if (!song.isValid()) return false;
    
    std::string songId = song.getId();
    std::string title = song.getTitle();
    std::string artist = song.getArtist();
    
    if (!isValidSongId(songId)) return false;
    
    // Check if song already exists
    if (songsById.find(songId) != songsById.end()) {
        return false;  // Song already exists
    }
    
    // Check for duplicate title+artist (normalized)
    std::string compositeKey = generateCompositeKey(title, artist);
    if (titleArtistKeys.find(compositeKey) != titleArtistKeys.end()) {
        return false; // Duplicate title+artist
    }
    
    // Insert the song
    songsById[songId] = song;
    titleArtistKeys.insert(compositeKey);
    
    return true;
}

bool SongDatabase::delete_song(const std::string& songId) {
    auto it = songsById.find(songId);
    if (it == songsById.end()) {
        return false;  // Song not found
    }
    
    // Remove from composite key set
    std::string title = it->second.getTitle();
    std::string artist = it->second.getArtist();
    titleArtistKeys.erase(generateCompositeKey(title, artist));
    
    // Remove from songs mapping
    songsById.erase(it);
    
    return true;
}

bool SongDatabase::update_song(const Song& song) {
    if (!song.isValid()) return false;
    
    std::string songId = song.getId();
    auto it = songsById.find(songId);
    if (it == songsById.end()) {
        return false;  // Song not found
    }
    
    // Update the song
    std::string oldTitle = it->second.getTitle();
    std::string oldArtist = it->second.getArtist();
    std::string newTitle = song.getTitle();
    std::string newArtist = song.getArtist();
    
    // Update composite key if title or artist changed
    if (oldTitle != newTitle || oldArtist != newArtist) {
        titleArtistKeys.erase(generateCompositeKey(oldTitle, oldArtist));
        std::string newKey = generateCompositeKey(newTitle, newArtist);
        // Prevent update to a duplicate key
        auto existing = titleArtistKeys.find(newKey);
        if (existing != titleArtistKeys.end()) {
            return false;
        }
        titleArtistKeys.insert(newKey);
    }
    
    it->second = song;
    return true;
}

bool SongDatabase::update_song_rating(const std::string& songId, int newRating) {
    auto it = songsById.find(songId);
    if (it == songsById.end()) {
        return false;  // Song not found
    }
    
    // Validate rating
    if (newRating < 1 || newRating > 5) {
        return false;  // Invalid rating
    }
    
    // Update the song's rating
    it->second.setRating(newRating);
    return true;
}

// Search operations
Song* SongDatabase::search_by_id(const std::string& songId) {
    auto it = songsById.find(songId);
    if (it != songsById.end()) {
        return &(it->second);
    }
    return nullptr;
}

Song* SongDatabase::search_by_title(const std::string& title) {
    // Linear search by exact title (case-sensitive), for simplicity.
    for (auto& pair : songsById) {
        if (pair.second.getTitle() == title) {
            return &pair.second;
        }
    }
    return nullptr;
}

std::vector<Song> SongDatabase::search_by_artist(const std::string& artist) const {
    std::vector<Song> result;
    std::string normalizedArtist = normalizeString(artist);
    
    for (const auto& pair : songsById) {
        if (normalizeString(pair.second.getArtist()) == normalizedArtist) {
            result.push_back(pair.second);
        }
    }
    
    return result;
}

std::vector<Song> SongDatabase::search_by_album(const std::string& album) const {
    std::vector<Song> result;
    std::string normalizedAlbum = normalizeString(album);
    
    for (const auto& pair : songsById) {
        if (normalizeString(pair.second.getAlbum()) == normalizedAlbum) {
            result.push_back(pair.second);
        }
    }
    
    return result;
}

std::vector<Song> SongDatabase::search_by_genre(const std::string& genre) const {
    std::vector<Song> result;
    std::string normalizedGenre = normalizeString(genre);
    
    for (const auto& pair : songsById) {
        if (normalizeString(pair.second.getGenre()) == normalizedGenre) {
            result.push_back(pair.second);
        }
    }
    
    return result;
}

// Utility operations
void SongDatabase::display_database() const {
    std::cout << "\n=== Song Database ===" << std::endl;
    std::cout << "Total songs: " << get_size() << std::endl;
    std::cout << "Load factor: " << get_load_factor() << std::endl;
    std::cout << "Bucket count: " << get_bucket_count() << std::endl;
    std::cout << "Max bucket size: " << get_max_bucket_size() << std::endl;
    std::cout << std::endl;
    
    if (is_empty()) {
        std::cout << "Database is empty!" << std::endl;
        return;
    }
    
    int index = 1;
    for (const auto& pair : songsById) {
        std::cout << index << ". ";
        std::cout << pair.second.getTitle() << " - " << pair.second.getArtist();
        std::cout << " (ID: " << pair.first << ")";
        std::cout << " [" << pair.second.getDurationString() << "]";
        if (pair.second.getRating() > 0) {
            std::cout << " Rating: " << pair.second.getRating() << "/5";
        }
        std::cout << std::endl;
        index++;
    }
    std::cout << std::endl;
}

void SongDatabase::display_stats() const {
    std::cout << "\n=== Database Statistics ===" << std::endl;
    std::cout << "Total songs: " << get_size() << std::endl;
    std::cout << "Unique artists: " << get_all_artists().size() << std::endl;
    std::cout << "Unique albums: " << get_all_albums().size() << std::endl;
    std::cout << "Unique genres: " << get_all_genres().size() << std::endl;
    std::cout << "Load factor: " << get_load_factor() << std::endl;
    std::cout << "Bucket count: " << get_bucket_count() << std::endl;
    std::cout << "Max bucket size: " << get_max_bucket_size() << std::endl;
    
    // Display top artists
    std::vector<std::string> artists = get_all_artists();
    std::cout << "\nTop artists:" << std::endl;
    for (const std::string& artist : artists) {
        std::vector<Song> artistSongs = search_by_artist(artist);
        std::cout << "  " << artist << ": " << artistSongs.size() << " songs" << std::endl;
    }
    std::cout << std::endl;
}

int SongDatabase::get_size() const { return songsById.size(); }
bool SongDatabase::is_empty() const { return songsById.empty(); }

void SongDatabase::clear() {
    songsById.clear();
    titleArtistKeys.clear();
}

// Batch operations
bool SongDatabase::insert_songs(const std::vector<Song>& songs) {
    bool allInserted = true;
    for (const Song& song : songs) {
        if (!insert_song(song)) {
            allInserted = false;
        }
    }
    return allInserted;
}

std::vector<Song> SongDatabase::get_all_songs() const {
    std::vector<Song> result;
    result.reserve(songsById.size());
    for (const auto& pair : songsById) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<std::string> SongDatabase::get_all_artists() const {
    std::vector<std::string> artists;
    for (const auto& pair : songsById) {
        std::string artist = pair.second.getArtist();
        if (std::find(artists.begin(), artists.end(), artist) == artists.end()) {
            artists.push_back(artist);
        }
    }
    return artists;
}

std::vector<std::string> SongDatabase::get_all_albums() const {
    std::vector<std::string> albums;
    for (const auto& pair : songsById) {
        std::string album = pair.second.getAlbum();
        if (!album.empty() && std::find(albums.begin(), albums.end(), album) == albums.end()) {
            albums.push_back(album);
        }
    }
    return albums;
}

std::vector<std::string> SongDatabase::get_all_genres() const {
    std::vector<std::string> genres;
    for (const auto& pair : songsById) {
        std::string genre = pair.second.getGenre();
        if (!genre.empty() && std::find(genres.begin(), genres.end(), genre) == genres.end()) {
            genres.push_back(genre);
        }
    }
    return genres;
}

// Advanced search
std::vector<Song> SongDatabase::search_by_duration_range(int minDuration, int maxDuration) const {
    std::vector<Song> result;
    for (const auto& pair : songsById) {
        int duration = pair.second.getDuration();
        if (duration >= minDuration && duration <= maxDuration) {
            result.push_back(pair.second);
        }
    }
    return result;
}

std::vector<Song> SongDatabase::search_by_rating_range(int minRating, int maxRating) const {
    std::vector<Song> result;
    for (const auto& pair : songsById) {
        int rating = pair.second.getRating();
        if (rating >= minRating && rating <= maxRating) {
            result.push_back(pair.second);
        }
    }
    return result;
}

std::vector<Song> SongDatabase::search_by_keyword(const std::string& keyword) const {
    std::vector<Song> result;
    std::string normalizedKeyword = normalizeString(keyword);
    
    for (const auto& pair : songsById) {
        const Song& song = pair.second;
        std::string title = normalizeString(song.getTitle());
        std::string artist = normalizeString(song.getArtist());
        std::string album = normalizeString(song.getAlbum());
        std::string genre = normalizeString(song.getGenre());
        
        if (title.find(normalizedKeyword) != std::string::npos ||
            artist.find(normalizedKeyword) != std::string::npos ||
            album.find(normalizedKeyword) != std::string::npos ||
            genre.find(normalizedKeyword) != std::string::npos) {
            result.push_back(song);
        }
    }
    
    return result;
}

// Database management
bool SongDatabase::contains_song(const std::string& songId) const {
    return songsById.find(songId) != songsById.end();
}

// contains_title removed in favor of composite key enforcement

void SongDatabase::sync_with_playlist(const std::vector<Song>& playlistSongs) {
    // Add any songs from playlist that aren't in database
    for (const Song& song : playlistSongs) {
        if (!contains_song(song.getId())) {
            insert_song(song);
        }
    }
}

void SongDatabase::export_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    file << "Song Database Export" << std::endl;
    file << "====================" << std::endl;
    file << "Total songs: " << get_size() << std::endl;
    file << std::endl;
    
    for (const auto& pair : songsById) {
        const Song& song = pair.second;
        file << "ID: " << song.getId() << std::endl;
        file << "Title: " << song.getTitle() << std::endl;
        file << "Artist: " << song.getArtist() << std::endl;
        file << "Duration: " << song.getDurationString() << std::endl;
        file << "Rating: " << song.getRating() << "/5" << std::endl;
        file << "Album: " << song.getAlbum() << std::endl;
        file << "Genre: " << song.getGenre() << std::endl;
        file << "Added: " << song.getAddedDate() << std::endl;
        file << "---" << std::endl;
    }
    
    file.close();
    std::cout << "Database exported to " << filename << std::endl;
}

bool SongDatabase::import_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for reading." << std::endl;
        return false;
    }
    
    std::string line;
    std::string id, title, artist, album, genre, addedDate;
    int duration = 0, rating = 0;
    bool readingSong = false;
    int songsImported = 0;
    
    while (std::getline(file, line)) {
        if (line.find("ID: ") == 0) {
            if (readingSong) {
                // Create and insert the previous song
                Song song(id, title, artist, duration, rating, album, genre);
                song.setAddedDate(addedDate);
                if (insert_song(song)) {
                    songsImported++;
                }
            }
            id = line.substr(4);
            readingSong = true;
        } else if (line.find("Title: ") == 0) {
            title = line.substr(7);
        } else if (line.find("Artist: ") == 0) {
            artist = line.substr(8);
        } else if (line.find("Duration: ") == 0) {
            std::string durationStr = line.substr(10);
            // Parse MM:SS format
            size_t colonPos = durationStr.find(':');
            if (colonPos != std::string::npos) {
                int minutes = std::stoi(durationStr.substr(0, colonPos));
                int seconds = std::stoi(durationStr.substr(colonPos + 1));
                duration = minutes * 60 + seconds;
            }
        } else if (line.find("Rating: ") == 0) {
            std::string ratingStr = line.substr(8);
            rating = std::stoi(ratingStr.substr(0, ratingStr.find('/')));
        } else if (line.find("Album: ") == 0) {
            album = line.substr(7);
        } else if (line.find("Genre: ") == 0) {
            genre = line.substr(7);
        } else if (line.find("Added: ") == 0) {
            addedDate = line.substr(7);
        }
    }
    
    // Insert the last song
    if (readingSong) {
        Song song(id, title, artist, duration, rating, album, genre);
        song.setAddedDate(addedDate);
        if (insert_song(song)) {
            songsImported++;
        }
    }
    
    file.close();
    std::cout << "Imported " << songsImported << " songs from " << filename << std::endl;
    return songsImported > 0;
}

// Performance and statistics
double SongDatabase::get_load_factor() const {
    if (songsById.bucket_count() == 0) return 0.0;
    return static_cast<double>(songsById.size()) / songsById.bucket_count();
}

size_t SongDatabase::get_bucket_count() const {
    return songsById.bucket_count();
}

size_t SongDatabase::get_max_bucket_size() const {
    size_t maxSize = 0;
    for (size_t i = 0; i < songsById.bucket_count(); ++i) {
        maxSize = std::max(maxSize, songsById.bucket_size(i));
    }
    return maxSize;
}

void SongDatabase::rehash(size_t bucketCount) {
    songsById.rehash(bucketCount);
} 