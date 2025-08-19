#ifndef SORTING_H
#define SORTING_H

#include "song.h"
#include <vector>
#include <string>
#include <functional>

/**
 * @brief Sorting class implementing various sorting algorithms for playlist management
 * 
 * This class provides multiple sorting algorithms to sort playlists by different criteria:
 * - Song title (alphabetical)
 * - Duration (ascending/descending)
 * - Recently added
 * - Rating (ascending/descending)
 * - Artist name
 * 
 * Time Complexity Analysis:
 * - Merge Sort: O(n log n) time, O(n) space
 * - Quick Sort: O(n log n) average, O(n²) worst case, O(log n) space
 * 
 * Space Complexity: Varies by algorithm
 */
class Sorting {
public:
    // Sorting criteria enum
    enum class SortCriteria {
        TITLE_ASC,
        TITLE_DESC,
        DURATION_ASC,
        DURATION_DESC,
        RATING_ASC,
        RATING_DESC,
        ARTIST_ASC,
        ARTIST_DESC,
        DATE_ADDED_ASC,
        DATE_ADDED_DESC
    };

    // Sorting algorithms
    static void mergeSort(std::vector<Song>& songs, SortCriteria criteria);
    static void quickSort(std::vector<Song>& songs, SortCriteria criteria);
    
    // Utility functions
    static std::string getCriteriaName(SortCriteria criteria);
    static void sortPlaylist(std::vector<Song>& songs, SortCriteria criteria, const std::string& algorithm = "merge");
    static void benchmarkSorting(std::vector<Song>& songs);
    
    // Comparison functions
    static bool compareByTitle(const Song& a, const Song& b, bool ascending = true);
    static bool compareByDuration(const Song& a, const Song& b, bool ascending = true);
    static bool compareByRating(const Song& a, const Song& b, bool ascending = true);
    static bool compareByArtist(const Song& a, const Song& b, bool ascending = true);
    static bool compareByDateAdded(const Song& a, const Song& b, bool ascending = true);

private:
    // Helper functions for merge sort
    static void mergeSortHelper(std::vector<Song>& songs, int left, int right, 
                               std::function<bool(const Song&, const Song&)> compare);
    static void merge(std::vector<Song>& songs, int left, int mid, int right,
                     std::function<bool(const Song&, const Song&)> compare);
    
    // Helper functions for quick sort
    static void quickSortHelper(std::vector<Song>& songs, int low, int high,
                               std::function<bool(const Song&, const Song&)> compare);
    static int partition(std::vector<Song>& songs, int low, int high,
                        std::function<bool(const Song&, const Song&)> compare);
    

    
    // Utility functions
    static std::function<bool(const Song&, const Song&)> getComparator(SortCriteria criteria);
    static void swap(Song& a, Song& b);
};

#endif // SORTING_H 