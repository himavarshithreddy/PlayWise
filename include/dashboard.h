#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "song.h"
#include "playlist.h"
#include "history.h"
#include "rating_tree.h"
#include "song_database.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

/**
 * @brief Dashboard class implementing a live system dashboard for PlayWise
 * 
 * This class provides real-time monitoring and statistics for the music
 * playlist management system. It aggregates data from all components and
 * provides insights into system performance and usage patterns.
 * 
 * Features:
 * - Top 5 longest songs
 * - Most recently played songs
 * - Song count by rating
 * - System performance metrics
 * - User activity statistics
 * - Memory usage analysis
 * 
 * Time Complexity: O(n) for most operations where n is the number of songs
 * Space Complexity: O(n) for storing aggregated data
 */
class Dashboard {
private:
    // System components
    Playlist* currentPlaylist;
    History* playbackHistory;
    RatingTree* ratingTree;
    SongDatabase* songDatabase;
    
    // Dashboard data
    struct SystemStats {
        int totalSongs;
        int totalPlaylists;
        int totalPlayTime;
        double averageRating;
        std::string mostPlayedArtist;
        std::string mostPlayedSong;
        int totalPlayCount;
        double systemLoadFactor;
        size_t memoryUsage;
    };
    
    SystemStats stats;
    
    // Helper methods
    void updateSystemStats();
    std::vector<Song> getTopLongestSongs(int count) const;
    std::vector<Song> getMostRecentlyPlayed(int count) const;
    std::map<int, int> getSongCountByRating() const;
    std::map<std::string, int> getArtistPlayCount() const;
    std::string getMostPlayedArtist() const;
    std::string getMostPlayedSong() const;
    double calculateAverageRating() const;
    int calculateTotalPlayTime() const;

public:
    // Constructors and Destructor
    Dashboard();
    Dashboard(Playlist* playlist, History* history, RatingTree* tree, SongDatabase* db);
    ~Dashboard();
    
    // Core dashboard functions
    void export_snapshot() const;
    void display_live_dashboard() const;
    void display_performance_metrics() const;
    void display_user_activity() const;
    void display_system_health() const;
    
    // Statistics functions
    void updateStats();
    SystemStats getSystemStats() const;
    std::vector<Song> getTopSongs(int count, const std::string& criteria) const;
    std::vector<std::string> getTopArtists(int count) const;
    std::vector<std::string> getTopGenres(int count) const;
    
    // Real-time monitoring
    void start_monitoring();
    void stop_monitoring();
    bool is_monitoring() const;
    
    // Export and reporting
    void export_to_file(const std::string& filename) const;
    void generate_performance_report() const;
    void generate_usage_report() const;
    
    // System analysis
    void analyze_performance_bottlenecks() const;
    void suggest_optimizations() const;
    void memory_usage_analysis() const;
    
    // Component setters
    void setPlaylist(Playlist* playlist);
    void setHistory(History* history);
    void setRatingTree(RatingTree* tree);
    void setSongDatabase(SongDatabase* db);
    
    // Utility functions
    void clear();
    bool is_initialized() const;
    std::string get_dashboard_version() const;
};

#endif // DASHBOARD_H 