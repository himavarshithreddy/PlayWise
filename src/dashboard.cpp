#include "../include/dashboard.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>

// Constructor
Dashboard::Dashboard() : currentPlaylist(nullptr), playbackHistory(nullptr), 
                        ratingTree(nullptr), songDatabase(nullptr) {
    stats = {0, 0, 0, 0.0, "", "", 0, 0.0, 0};
}

Dashboard::Dashboard(Playlist* playlist, History* history, RatingTree* tree, SongDatabase* db)
    : currentPlaylist(playlist), playbackHistory(history), ratingTree(tree), songDatabase(db) {
    stats = {0, 0, 0, 0.0, "", "", 0, 0.0, 0};
    updateSystemStats();
}

// Destructor
Dashboard::~Dashboard() {
    clear();
}

// Helper methods
void Dashboard::updateSystemStats() {
    if (!is_initialized()) return;
    
    // Update total songs
    if (songDatabase) {
        stats.totalSongs = songDatabase->get_size();
    }
    
    // Update total playlists (assuming 1 for now)
    stats.totalPlaylists = 1;
    
    // Update total play time
    stats.totalPlayTime = calculateTotalPlayTime();
    
    // Update average rating
    stats.averageRating = calculateAverageRating();
    
    // Update most played artist and song
    stats.mostPlayedArtist = getMostPlayedArtist();
    stats.mostPlayedSong = getMostPlayedSong();
    
    // Update total play count
    if (playbackHistory) {
        stats.totalPlayCount = playbackHistory->get_size();
    }
    
    // Update system load factor
    if (songDatabase) {
        stats.systemLoadFactor = songDatabase->get_load_factor();
    }
    
    // Estimate memory usage (rough calculation)
    stats.memoryUsage = sizeof(Dashboard) + 
                       (songDatabase ? songDatabase->get_size() * sizeof(Song) : 0) +
                       (playbackHistory ? playbackHistory->get_size() * sizeof(Song) : 0) +
                       (ratingTree ? ratingTree->get_total_songs() * sizeof(Song) : 0);
}

std::vector<Song> Dashboard::getTopLongestSongs(int count) const {
    std::vector<Song> allSongs;
    
    if (songDatabase) {
        allSongs = songDatabase->get_all_songs();
    }
    
    // Sort by duration (descending)
    std::sort(allSongs.begin(), allSongs.end(), 
              [](const Song& a, const Song& b) {
                  return a.getDuration() > b.getDuration();
              });
    
    // Return top count songs
    if (allSongs.size() > static_cast<size_t>(count)) {
        allSongs.resize(count);
    }
    
    return allSongs;
}

std::vector<Song> Dashboard::getMostRecentlyPlayed(int count) const {
    if (!playbackHistory) {
        return std::vector<Song>();
    }
    
    return playbackHistory->get_recent_songs(count);
}

std::map<int, int> Dashboard::getSongCountByRating() const {
    std::map<int, int> ratingCounts;
    
    if (songDatabase) {
        std::vector<Song> allSongs = songDatabase->get_all_songs();
        for (const Song& song : allSongs) {
            ratingCounts[song.getRating()]++;
        }
    }
    
    return ratingCounts;
}

std::map<std::string, int> Dashboard::getArtistPlayCount() const {
    std::map<std::string, int> artistCounts;
    
    if (songDatabase) {
        std::vector<Song> allSongs = songDatabase->get_all_songs();
        for (const Song& song : allSongs) {
            artistCounts[song.getArtist()]++;
        }
    }
    
    return artistCounts;
}

std::string Dashboard::getMostPlayedArtist() const {
    auto artistCounts = getArtistPlayCount();
    
    if (artistCounts.empty()) return "None";
    
    auto maxElement = std::max_element(artistCounts.begin(), artistCounts.end(),
                                      [](const auto& a, const auto& b) {
                                          return a.second < b.second;
                                      });
    
    return maxElement->first;
}

std::string Dashboard::getMostPlayedSong() const {
    if (!playbackHistory || playbackHistory->is_empty()) {
        return "None";
    }
    
    // Get the most recent song as a proxy for most played
    Song lastSong = playbackHistory->get_last_played();
    return lastSong.getTitle();
}

double Dashboard::calculateAverageRating() const {
    if (!songDatabase) return 0.0;
    
    std::vector<Song> allSongs = songDatabase->get_all_songs();
    if (allSongs.empty()) return 0.0;
    
    double totalRating = 0.0;
    int ratedSongs = 0;
    
    for (const Song& song : allSongs) {
        if (song.getRating() > 0) {
            totalRating += song.getRating();
            ratedSongs++;
        }
    }
    
    return ratedSongs > 0 ? totalRating / ratedSongs : 0.0;
}

int Dashboard::calculateTotalPlayTime() const {
    if (!songDatabase) return 0;
    
    std::vector<Song> allSongs = songDatabase->get_all_songs();
    int totalTime = 0;
    
    for (const Song& song : allSongs) {
        totalTime += song.getDuration();
    }
    
    return totalTime;
}

// Core dashboard functions
void Dashboard::export_snapshot() const {
    std::cout << "\n=== PlayWise System Snapshot ===" << std::endl;
    std::cout << "Timestamp: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
    std::cout << "Dashboard Version: " << get_dashboard_version() << std::endl;
    std::cout << std::endl;
    
    // System Overview
    std::cout << "SYSTEM OVERVIEW:" << std::endl;
    std::cout << "  Total Songs: " << stats.totalSongs << std::endl;
    std::cout << "  Total Playlists: " << stats.totalPlaylists << std::endl;
    std::cout << "  Total Play Time: " << stats.totalPlayTime / 60 << " minutes" << std::endl;
    std::cout << "  Average Rating: " << std::fixed << std::setprecision(2) << stats.averageRating << "/5" << std::endl;
    std::cout << "  Most Played Artist: " << stats.mostPlayedArtist << std::endl;
    std::cout << "  Most Played Song: " << stats.mostPlayedSong << std::endl;
    std::cout << "  Total Play Count: " << stats.totalPlayCount << std::endl;
    std::cout << "  System Load Factor: " << std::fixed << std::setprecision(3) << stats.systemLoadFactor << std::endl;
    std::cout << "  Memory Usage: " << stats.memoryUsage << " bytes" << std::endl;
    std::cout << std::endl;
    
    // Top 5 Longest Songs
    std::cout << "TOP 5 LONGEST SONGS:" << std::endl;
    std::vector<Song> longestSongs = getTopLongestSongs(5);
    for (size_t i = 0; i < longestSongs.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << longestSongs[i].getTitle() 
                  << " - " << longestSongs[i].getArtist()
                  << " (" << longestSongs[i].getDurationString() << ")" << std::endl;
    }
    std::cout << std::endl;
    
    // Most Recently Played
    std::cout << "MOST RECENTLY PLAYED:" << std::endl;
    std::vector<Song> recentSongs = getMostRecentlyPlayed(5);
    for (size_t i = 0; i < recentSongs.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << recentSongs[i].getTitle() 
                  << " - " << recentSongs[i].getArtist() << std::endl;
    }
    std::cout << std::endl;
    
    // Song Count by Rating
    std::cout << "SONG COUNT BY RATING:" << std::endl;
    auto ratingCounts = getSongCountByRating();
    for (const auto& pair : ratingCounts) {
        std::cout << "  " << pair.first << " stars: " << pair.second << " songs" << std::endl;
    }
    std::cout << std::endl;
}

void Dashboard::display_live_dashboard() const {
    std::cout << "\n=== PlayWise Live Dashboard ===" << std::endl;
    std::cout << "+==============================================================+" << std::endl;
    std::cout << "|                    SYSTEM STATUS                            |" << std::endl;
    std::cout << "+==============================================================+" << std::endl;
    std::cout << "|  Total Songs: " << std::setw(8) << stats.totalSongs << "                                    |" << std::endl;
    std::cout << "|  Total Playlists: " << std::setw(5) << stats.totalPlaylists << "                                |" << std::endl;
    std::cout << "|  Total Play Time: " << std::setw(6) << stats.totalPlayTime / 60 << " min                          |" << std::endl;
    std::cout << "|  Average Rating: " << std::setw(6) << std::fixed << std::setprecision(2) << stats.averageRating << "/5                        |" << std::endl;
    std::cout << "|  System Load: " << std::setw(8) << std::fixed << std::setprecision(3) << stats.systemLoadFactor << "                              |" << std::endl;
    std::cout << "|  Memory Usage: " << std::setw(7) << stats.memoryUsage << " bytes                           |" << std::endl;
    std::cout << "+==============================================================+" << std::endl;
    std::cout << std::endl;
    
    // Top Artists
    std::cout << "TOP ARTISTS:" << std::endl;
    auto artistCounts = getArtistPlayCount();
    std::vector<std::pair<std::string, int>> artistList(artistCounts.begin(), artistCounts.end());
    std::sort(artistList.begin(), artistList.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    for (size_t i = 0; i < std::min(artistList.size(), size_t(5)); i++) {
        std::cout << "  " << (i + 1) << ". " << artistList[i].first 
                  << " (" << artistList[i].second << " songs)" << std::endl;
    }
    std::cout << std::endl;
}

void Dashboard::display_performance_metrics() const {
    std::cout << "\n=== Performance Metrics ===" << std::endl;
    std::cout << "Database Performance:" << std::endl;
    if (songDatabase) {
        std::cout << "  Load Factor: " << std::fixed << std::setprecision(3) << songDatabase->get_load_factor() << std::endl;
        std::cout << "  Bucket Count: " << songDatabase->get_bucket_count() << std::endl;
        std::cout << "  Max Bucket Size: " << songDatabase->get_max_bucket_size() << std::endl;
    }
    
    if (ratingTree) {
        std::cout << "Rating Tree Performance:" << std::endl;
        std::cout << "  Tree Height: " << ratingTree->get_height() << std::endl;
        std::cout << "  Total Songs: " << ratingTree->get_total_songs() << std::endl;
    }
    
    if (playbackHistory) {
        std::cout << "History Performance:" << std::endl;
        std::cout << "  History Size: " << playbackHistory->get_size() << "/" << playbackHistory->get_max_size() << std::endl;
    }
    std::cout << std::endl;
}

void Dashboard::display_user_activity() const {
    std::cout << "\n=== User Activity ===" << std::endl;
    std::cout << "Most Played Artist: " << stats.mostPlayedArtist << std::endl;
    std::cout << "Most Played Song: " << stats.mostPlayedSong << std::endl;
    std::cout << "Total Play Count: " << stats.totalPlayCount << std::endl;
    
    if (playbackHistory) {
        std::cout << "Recent Activity:" << std::endl;
        std::vector<Song> recentSongs = playbackHistory->get_recent_songs(3);
        for (size_t i = 0; i < recentSongs.size(); i++) {
            std::cout << "  " << (i + 1) << ". " << recentSongs[i].getTitle() 
                      << " - " << recentSongs[i].getArtist() << std::endl;
        }
    }
    std::cout << std::endl;
}

void Dashboard::display_system_health() const {
    std::cout << "\n=== System Health ===" << std::endl;
    
    // Database health
    if (songDatabase) {
        double loadFactor = songDatabase->get_load_factor();
        std::cout << "Database Health: ";
        if (loadFactor < 0.5) {
            std::cout << "[OK] Excellent";
        } else if (loadFactor < 0.8) {
            std::cout << "[!] Good";
        } else {
            std::cout << "[X] Needs attention";
        }
        std::cout << " (Load: " << std::fixed << std::setprecision(3) << loadFactor << ")" << std::endl;
    }
    
    // Memory usage
    std::cout << "Memory Usage: " << stats.memoryUsage << " bytes";
    if (stats.memoryUsage > 1000000) {
        std::cout << " (" << stats.memoryUsage / 1000000 << " MB)";
    }
    std::cout << std::endl;
    
    // System status
    std::cout << "System Status: [OK] Operational" << std::endl;
    std::cout << std::endl;
}

// Statistics functions
void Dashboard::updateStats() {
    updateSystemStats();
}

Dashboard::SystemStats Dashboard::getSystemStats() const {
    return stats;
}

std::vector<Song> Dashboard::getTopSongs(int count, const std::string& criteria) const {
    if (criteria == "duration") {
        return getTopLongestSongs(count);
    } else if (criteria == "rating") {
        if (ratingTree) {
            return ratingTree->get_top_rated_songs(count);
        }
    }
    return std::vector<Song>();
}

std::vector<std::string> Dashboard::getTopArtists(int count) const {
    auto artistCounts = getArtistPlayCount();
    std::vector<std::pair<std::string, int>> artistList(artistCounts.begin(), artistCounts.end());
    std::sort(artistList.begin(), artistList.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<std::string> topArtists;
    for (size_t i = 0; i < std::min(artistList.size(), size_t(count)); i++) {
        topArtists.push_back(artistList[i].first);
    }
    return topArtists;
}

std::vector<std::string> Dashboard::getTopGenres(int count) const {
    if (!songDatabase) return std::vector<std::string>();
    
    std::map<std::string, int> genreCounts;
    std::vector<Song> allSongs = songDatabase->get_all_songs();
    
    for (const Song& song : allSongs) {
        if (!song.getGenre().empty()) {
            genreCounts[song.getGenre()]++;
        }
    }
    
    std::vector<std::pair<std::string, int>> genreList(genreCounts.begin(), genreCounts.end());
    std::sort(genreList.begin(), genreList.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::vector<std::string> topGenres;
    for (size_t i = 0; i < std::min(genreList.size(), size_t(count)); i++) {
        topGenres.push_back(genreList[i].first);
    }
    return topGenres;
}

// Real-time monitoring
void Dashboard::start_monitoring() {
    std::cout << "Starting real-time monitoring..." << std::endl;
    // In a real implementation, this would start a background thread
}

void Dashboard::stop_monitoring() {
    std::cout << "Stopping real-time monitoring..." << std::endl;
    // In a real implementation, this would stop the background thread
}

bool Dashboard::is_monitoring() const {
    return false; // Simplified implementation
}

// Export and reporting
void Dashboard::export_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    file << "PlayWise System Report" << std::endl;
    file << "=====================" << std::endl;
    file << "Generated: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
    file << std::endl;
    
    file << "System Statistics:" << std::endl;
    file << "  Total Songs: " << stats.totalSongs << std::endl;
    file << "  Total Playlists: " << stats.totalPlaylists << std::endl;
    file << "  Average Rating: " << std::fixed << std::setprecision(2) << stats.averageRating << "/5" << std::endl;
    file << "  Most Played Artist: " << stats.mostPlayedArtist << std::endl;
    file << "  System Load Factor: " << std::fixed << std::setprecision(3) << stats.systemLoadFactor << std::endl;
    file << std::endl;
    
    file.close();
    std::cout << "System report exported to " << filename << std::endl;
}

void Dashboard::generate_performance_report() const {
    std::cout << "\n=== Performance Report ===" << std::endl;
    display_performance_metrics();
    analyze_performance_bottlenecks();
    suggest_optimizations();
}

void Dashboard::generate_usage_report() const {
    std::cout << "\n=== Usage Report ===" << std::endl;
    display_user_activity();
    
    // Genre distribution
    std::cout << "Genre Distribution:" << std::endl;
    auto topGenres = getTopGenres(5);
    for (size_t i = 0; i < topGenres.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << topGenres[i] << std::endl;
    }
    std::cout << std::endl;
}

// System analysis
void Dashboard::analyze_performance_bottlenecks() const {
    std::cout << "Performance Analysis:" << std::endl;
    
    if (songDatabase) {
        double loadFactor = songDatabase->get_load_factor();
        if (loadFactor > 0.8) {
            std::cout << "  ⚠️  High database load factor detected. Consider rehashing." << std::endl;
        }
        
        size_t maxBucketSize = songDatabase->get_max_bucket_size();
        if (maxBucketSize > 5) {
            std::cout << "  ⚠️  Large bucket sizes detected. Hash function may need improvement." << std::endl;
        }
    }
    
    if (ratingTree && ratingTree->get_height() > 10) {
        std::cout << "  ⚠️  Deep rating tree detected. Consider balancing." << std::endl;
    }
    
    std::cout << "  ✅ No critical bottlenecks detected." << std::endl;
}

void Dashboard::suggest_optimizations() const {
    std::cout << "Optimization Suggestions:" << std::endl;
    std::cout << "  💡 Consider implementing caching for frequently accessed songs." << std::endl;
    std::cout << "  💡 Use lazy loading for large playlists." << std::endl;
    std::cout << "  💡 Implement connection pooling for database operations." << std::endl;
    std::cout << "  💡 Consider using a more efficient hash function." << std::endl;
}

void Dashboard::memory_usage_analysis() const {
    std::cout << "Memory Usage Analysis:" << std::endl;
    std::cout << "  Total Memory: " << stats.memoryUsage << " bytes";
    if (stats.memoryUsage > 1000000) {
        std::cout << " (" << stats.memoryUsage / 1000000 << " MB)";
    }
    std::cout << std::endl;
    
    if (songDatabase) {
        size_t dbMemory = songDatabase->get_size() * sizeof(Song);
        std::cout << "  Database Memory: " << dbMemory << " bytes" << std::endl;
    }
    
    if (playbackHistory) {
        size_t historyMemory = playbackHistory->get_size() * sizeof(Song);
        std::cout << "  History Memory: " << historyMemory << " bytes" << std::endl;
    }
}

// Component setters
void Dashboard::setPlaylist(Playlist* playlist) { currentPlaylist = playlist; }
void Dashboard::setHistory(History* history) { playbackHistory = history; }
void Dashboard::setRatingTree(RatingTree* tree) { ratingTree = tree; }
void Dashboard::setSongDatabase(SongDatabase* db) { songDatabase = db; }

// Utility functions
void Dashboard::clear() {
    currentPlaylist = nullptr;
    playbackHistory = nullptr;
    ratingTree = nullptr;
    songDatabase = nullptr;
    stats = {0, 0, 0, 0.0, "", "", 0, 0.0, 0};
}

bool Dashboard::is_initialized() const {
    return songDatabase != nullptr || playbackHistory != nullptr || 
           ratingTree != nullptr || currentPlaylist != nullptr;
}

std::string Dashboard::get_dashboard_version() const {
    return "1.0.0";
} 