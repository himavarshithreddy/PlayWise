# Auto-Sorting Favorite Songs Queue Implementation

## Scenario Overview

**Problem**: Users want to auto-sort their favorite playlist by total time listened.

**Solution**: Create a sorted queue structure that always maintains top songs in order of listening duration.

## Data Structures Used

### 1. Priority Queue (Max Heap)
- **Implementation**: `std::priority_queue<SongWithDuration>`
- **Purpose**: Automatically maintains songs sorted by listening duration
- **Time Complexity**: O(log n) for insert/remove operations
- **Space Complexity**: O(n) for storing songs

### 2. Hash Maps for Tracking
- **Listening Time Map**: `std::unordered_map<std::string, int> songListeningTime`
- **Play Count Map**: `std::unordered_map<std::string, int> songPlayCount`
- **Purpose**: Efficient O(1) lookup and updates for song statistics
- **Key Generation**: `title + "|||" + artist` for unique identification

### 3. SongWithDuration Structure
```cpp
struct SongWithDuration {
    Song song;
    int totalListeningTime;  // in seconds
    int playCount;
    
    // Custom comparator for priority queue
    bool operator<(const SongWithDuration& other) const {
        // Primary: total listening time (descending)
        if (totalListeningTime != other.totalListeningTime) {
            return totalListeningTime < other.totalListeningTime;
        }
        // Secondary: play count (descending)
        if (playCount != other.playCount) {
            return playCount < other.playCount;
        }
        // Tertiary: song title (ascending)
        return song.getTitle() > other.song.getTitle();
    }
};
```

## Core Algorithms

### 1. Auto-Sorting Algorithm
The priority queue automatically maintains the correct order using the custom comparator:

1. **Primary Sort**: Total listening time (descending)
2. **Secondary Sort**: Play count (descending) 
3. **Tertiary Sort**: Song title (ascending)

### 2. Queue Rebuilding Algorithm
When listening time or play count changes, the queue is rebuilt:

```cpp
void rebuildQueue() {
    std::priority_queue<SongWithDuration> newQueue;
    std::vector<SongWithDuration> tempSongs;
    
    // Extract all songs from current queue
    while (!songQueue.empty()) {
        tempSongs.push_back(songQueue.top());
        songQueue.pop();
    }
    
    // Rebuild with updated durations and counts
    for (const SongWithDuration& songWithDuration : tempSongs) {
        std::string key = generateSongKey(songWithDuration.song);
        int currentListeningTime = songListeningTime[key];
        int currentPlayCount = songPlayCount[key];
        
        SongWithDuration updatedSong(songWithDuration.song, 
                                   currentListeningTime, currentPlayCount);
        newQueue.push(updatedSong);
    }
    
    songQueue = newQueue;
}
```

### 3. Auto-Update from Playback
```cpp
void autoUpdateFromPlayback(const Song& song, int playbackDuration) {
    std::string key = generateSongKey(song);
    
    // Add song to favorites if not already present
    if (songListeningTime.find(key) == songListeningTime.end()) {
        addSong(song);
    }
    
    // Update listening time and play count
    songListeningTime[key] += playbackDuration;
    songPlayCount[key]++;
    
    // Rebuild queue to maintain correct order
    rebuildQueue();
}
```

## Key Features Implemented

### 1. Auto-Sorting
- Songs are automatically sorted by total listening duration
- Queue maintains correct order after any update
- Real-time reordering when listening time changes

### 2. Multi-Level Sorting
- **Primary**: Total listening time (descending)
- **Secondary**: Play count (descending)
- **Tertiary**: Song title (ascending)

### 3. Efficient Operations
- **Add Song**: O(log n)
- **Remove Song**: O(n) - requires queue rebuild
- **Update Listening Time**: O(n) - requires queue rebuild
- **Get Top Song**: O(1)
- **Get Top N Songs**: O(n log n)

### 4. Integration Features
- **Auto-update from playback**: Automatically adds songs and updates stats
- **Sync with history**: Updates favorites based on playback history
- **Time range filtering**: Get songs within specific listening time ranges
- **Statistics and analytics**: Comprehensive stats about favorites

### 5. File Operations
- **Export favorites**: Save favorites to file with detailed statistics
- **Import favorites**: Load favorites from file

## User Interface Integration

The system integrates seamlessly with the main PlayWise application:

### Menu Options
1. **Display favorites** - Shows auto-sorted list
2. **Add/Remove songs** - Manual management
3. **Update listening time** - Manual updates with auto-sorting
4. **Auto-update from playback** - Simulate real playback
5. **Sync with history** - Update from actual playback history
6. **Time range filtering** - Filter by listening duration
7. **Statistics** - Detailed analytics
8. **Export/Import** - File operations

### Real-time Updates
- Queue automatically re-sorts when listening time changes
- Immediate feedback to users about reordering
- Visual confirmation of auto-sorting behavior

## Performance Analysis

### Time Complexity
- **Insertion**: O(log n) - standard heap insertion
- **Deletion**: O(n) - requires full queue rebuild
- **Update**: O(n) - requires full queue rebuild
- **Top element access**: O(1) - heap root access
- **Top N elements**: O(n log n) - extract and rebuild

### Space Complexity
- **Storage**: O(n) - one entry per favorite song
- **Auxiliary**: O(n) - temporary storage during rebuilds

### Optimization Opportunities
1. **Lazy Rebuilding**: Only rebuild when necessary
2. **Incremental Updates**: Update heap without full rebuild
3. **Caching**: Cache frequently accessed elements

## Learning Outcomes

### Data Structures Mastered
1. **Priority Queue (Max Heap)**: Automatic sorting and ordering
2. **Hash Maps**: Efficient key-value storage and lookup
3. **Custom Comparators**: Multi-level sorting criteria
4. **Vectors**: Temporary storage and data manipulation

### Algorithms Learned
1. **Heap Operations**: Insert, delete, extract max
2. **Queue Rebuilding**: Efficient data structure maintenance
3. **Multi-level Sorting**: Complex comparison logic
4. **Hash-based Lookup**: O(1) access patterns

### Design Patterns
1. **Observer Pattern**: Auto-update on data changes
2. **Strategy Pattern**: Different sorting strategies
3. **Factory Pattern**: Song object creation
4. **Singleton-like**: Centralized favorites management

## Demonstration

The system includes a comprehensive demo (`demo_auto_sort.cpp`) that showcases:

1. **Initial Setup**: Adding songs to favorites
2. **Playback Simulation**: Real-time updates during playback
3. **Auto-Sorting**: Visual demonstration of reordering
4. **Statistics**: Detailed analytics display
5. **Filtering**: Time range queries
6. **Real-time Updates**: Dynamic reordering demonstration

## Conclusion

This implementation successfully addresses the scenario requirements by:

✅ **Auto-sorting**: Songs are automatically sorted by listening duration  
✅ **Priority Queue**: Uses max heap for efficient ordering  
✅ **Real-time Updates**: Queue reorders immediately when data changes  
✅ **Multi-level Sorting**: Comprehensive ordering criteria  
✅ **Integration**: Seamless integration with playback system  
✅ **User Experience**: Intuitive interface with immediate feedback  

The solution demonstrates mastery of priority queues, comparators, and sorting algorithms while providing a practical, user-friendly system for managing favorite songs based on listening behavior. 