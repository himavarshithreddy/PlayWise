#include "../include/sorting.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iomanip>

// Comparison functions
bool Sorting::compareByTitle(const Song& a, const Song& b, bool ascending) {
    if (ascending) {
        return a.getTitle() < b.getTitle();
    } else {
        return a.getTitle() > b.getTitle();
    }
}

bool Sorting::compareByDuration(const Song& a, const Song& b, bool ascending) {
    if (ascending) {
        return a.getDuration() < b.getDuration();
    } else {
        return a.getDuration() > b.getDuration();
    }
}

bool Sorting::compareByRating(const Song& a, const Song& b, bool ascending) {
    if (ascending) {
        return a.getRating() < b.getRating();
    } else {
        return a.getRating() > b.getRating();
    }
}

bool Sorting::compareByArtist(const Song& a, const Song& b, bool ascending) {
    if (ascending) {
        return a.getArtist() < b.getArtist();
    } else {
        return a.getArtist() > b.getArtist();
    }
}

bool Sorting::compareByDateAdded(const Song& a, const Song& b, bool ascending) {
    if (ascending) {
        return a.getAddedDate() < b.getAddedDate();
    } else {
        return a.getAddedDate() > b.getAddedDate();
    }
}

// Utility functions
std::function<bool(const Song&, const Song&)> Sorting::getComparator(SortCriteria criteria) {
    switch (criteria) {
        case SortCriteria::TITLE_ASC:
            return [](const Song& a, const Song& b) { return compareByTitle(a, b, true); };
        case SortCriteria::TITLE_DESC:
            return [](const Song& a, const Song& b) { return compareByTitle(a, b, false); };
        case SortCriteria::DURATION_ASC:
            return [](const Song& a, const Song& b) { return compareByDuration(a, b, true); };
        case SortCriteria::DURATION_DESC:
            return [](const Song& a, const Song& b) { return compareByDuration(a, b, false); };
        case SortCriteria::RATING_ASC:
            return [](const Song& a, const Song& b) { return compareByRating(a, b, true); };
        case SortCriteria::RATING_DESC:
            return [](const Song& a, const Song& b) { return compareByRating(a, b, false); };
        case SortCriteria::ARTIST_ASC:
            return [](const Song& a, const Song& b) { return compareByArtist(a, b, true); };
        case SortCriteria::ARTIST_DESC:
            return [](const Song& a, const Song& b) { return compareByArtist(a, b, false); };
        case SortCriteria::DATE_ADDED_ASC:
            return [](const Song& a, const Song& b) { return compareByDateAdded(a, b, true); };
        case SortCriteria::DATE_ADDED_DESC:
            return [](const Song& a, const Song& b) { return compareByDateAdded(a, b, false); };
        default:
            return [](const Song& a, const Song& b) { return compareByTitle(a, b, true); };
    }
}

std::string Sorting::getCriteriaName(SortCriteria criteria) {
    switch (criteria) {
        case SortCriteria::TITLE_ASC: return "Title (A-Z)";
        case SortCriteria::TITLE_DESC: return "Title (Z-A)";
        case SortCriteria::DURATION_ASC: return "Duration (Shortest First)";
        case SortCriteria::DURATION_DESC: return "Duration (Longest First)";
        case SortCriteria::RATING_ASC: return "Rating (Lowest First)";
        case SortCriteria::RATING_DESC: return "Rating (Highest First)";
        case SortCriteria::ARTIST_ASC: return "Artist (A-Z)";
        case SortCriteria::ARTIST_DESC: return "Artist (Z-A)";
        case SortCriteria::DATE_ADDED_ASC: return "Date Added (Oldest First)";
        case SortCriteria::DATE_ADDED_DESC: return "Date Added (Newest First)";
        default: return "Unknown";
    }
}

void Sorting::swap(Song& a, Song& b) {
    Song temp = a;
    a = b;
    b = temp;
}

// Merge Sort Implementation
void Sorting::mergeSort(std::vector<Song>& songs, SortCriteria criteria) {
    if (songs.size() <= 1) return;
    
    auto compare = getComparator(criteria);
    mergeSortHelper(songs, 0, static_cast<int>(songs.size()) - 1, compare);
}

void Sorting::mergeSortHelper(std::vector<Song>& songs, int left, int right, 
                             std::function<bool(const Song&, const Song&)> compare) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(songs, left, mid, compare);
        mergeSortHelper(songs, mid + 1, right, compare);
        merge(songs, left, mid, right, compare);
    }
}

void Sorting::merge(std::vector<Song>& songs, int left, int mid, int right,
                   std::function<bool(const Song&, const Song&)> compare) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<Song> leftArray(n1);
    std::vector<Song> rightArray(n2);
    
    for (int i = 0; i < n1; i++) {
        leftArray[i] = songs[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = songs[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (compare(leftArray[i], rightArray[j])) {
            songs[k] = leftArray[i];
            i++;
        } else {
            songs[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        songs[k] = leftArray[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        songs[k] = rightArray[j];
        j++;
        k++;
    }
}

// Quick Sort Implementation
void Sorting::quickSort(std::vector<Song>& songs, SortCriteria criteria) {
    if (songs.size() <= 1) return;
    
    auto compare = getComparator(criteria);
    quickSortHelper(songs, 0, static_cast<int>(songs.size()) - 1, compare);
}

void Sorting::quickSortHelper(std::vector<Song>& songs, int low, int high,
                             std::function<bool(const Song&, const Song&)> compare) {
    if (low < high) {
        int pi = partition(songs, low, high, compare);
        quickSortHelper(songs, low, pi - 1, compare);
        quickSortHelper(songs, pi + 1, high, compare);
    }
}

int Sorting::partition(std::vector<Song>& songs, int low, int high,
                      std::function<bool(const Song&, const Song&)> compare) {
    Song pivot = songs[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (compare(songs[j], pivot)) {
            i++;
            swap(songs[i], songs[j]);
        }
    }
    
    swap(songs[i + 1], songs[high]);
    return i + 1;
}



// Main sorting interface
void Sorting::sortPlaylist(std::vector<Song>& songs, SortCriteria criteria, const std::string& algorithm) {
    if (songs.empty()) return;
    
    std::cout << "Sorting playlist by " << getCriteriaName(criteria) 
              << " using " << algorithm << " sort..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    if (algorithm == "merge") {
        mergeSort(songs, criteria);
    } else if (algorithm == "quick") {
        quickSort(songs, criteria);
    } else {
        std::cout << "Unknown algorithm, using merge sort as default." << std::endl;
        mergeSort(songs, criteria);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Sorting completed in " << duration.count() << " microseconds." << std::endl;
}

// Benchmarking function
void Sorting::benchmarkSorting(std::vector<Song>& songs) {
    if (songs.empty()) {
        std::cout << "No songs to benchmark!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Sorting Algorithm Benchmark ===" << std::endl;
    std::cout << "Testing with " << songs.size() << " songs" << std::endl;
    std::cout << std::setw(20) << "Algorithm" << std::setw(15) << "Time (μs)" << std::endl;
    std::cout << std::string(35, '-') << std::endl;
    
    std::vector<SortCriteria> criteria = {
        SortCriteria::TITLE_ASC,
        SortCriteria::DURATION_ASC,
        SortCriteria::RATING_DESC
    };
    
    for (auto criterion : criteria) {
        std::vector<Song> testSongs = songs; // Copy for testing
        
        // Test Merge Sort
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(testSongs, criterion);
        auto end = std::chrono::high_resolution_clock::now();
        auto mergeTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Test Quick Sort
        testSongs = songs; // Reset
        start = std::chrono::high_resolution_clock::now();
        quickSort(testSongs, criterion);
        end = std::chrono::high_resolution_clock::now();
        auto quickTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Criterion: " << getCriteriaName(criterion) << std::endl;
        std::cout << std::setw(20) << "Merge Sort" << std::setw(15) << mergeTime.count() << std::endl;
        std::cout << std::setw(20) << "Quick Sort" << std::setw(15) << quickTime.count() << std::endl;
        std::cout << std::endl;
    }
} 