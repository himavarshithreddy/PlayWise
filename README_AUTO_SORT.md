# Auto-Sorting Favorite Songs Queue

## 🎵 Overview

This implementation provides a **Priority Queue (Max Heap)** that automatically maintains favorite songs sorted by total listening duration. The system ensures that your most-listened songs always appear at the top of your favorites list.

## 🎯 Scenario Solved

**Problem**: Users want to auto-sort their favorite playlist by total time listened.

**Solution**: A sorted queue structure that always maintains top songs in order of listening duration.

## 🏗️ Data Structures Used

### 1. Priority Queue (Max Heap)
- **Implementation**: `std::priority_queue<SongWithDuration>`
- **Purpose**: Automatic sorting by listening duration
- **Time Complexity**: O(log n) for insert/remove
- **Space Complexity**: O(n)

### 2. Hash Maps for Tracking
- **Listening Time**: `std::unordered_map<std::string, int>`
- **Play Count**: `std::unordered_map<std::string, int>`
- **Purpose**: O(1) lookup and updates
- **Key**: `title + "|||" + artist`

### 3. Custom Comparator
```cpp
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
```

## 🚀 Key Features

### ✅ Auto-Sorting
- Songs automatically sorted by listening duration
- Real-time reordering when data changes
- Multi-level sorting (time → play count → title)

### ✅ Smart Integration
- Auto-update from playback simulation
- Sync with playback history
- Time range filtering
- Comprehensive statistics

### ✅ User Experience
- Intuitive menu interface
- Immediate feedback on changes
- Export/import functionality
- Detailed analytics

## 📁 Files Structure

```
Playwise/
├── include/
│   ├── favorite_songs_queue.h    # Header with enhanced features
│   └── song.h                    # Song class definition
├── src/
│   ├── favorite_songs_queue.cpp  # Implementation with new methods
│   ├── demo_auto_sort.cpp        # Interactive demonstration
│   └── playwise_app.cpp          # Enhanced main application
├── tests/
│   └── test_auto_sort.cpp        # Comprehensive test suite
├── docs/
│   └── auto_sorting_favorites.md # Technical documentation
└── Makefile                      # Build system with demo/test targets
```

## 🛠️ Building and Running

### Prerequisites
- C++17 compatible compiler (GCC, Clang, MSVC)
- Make utility

### Build Commands
```bash
# Build everything (main app + demo + tests)
make

# Build and run main application
make run

# Build and run auto-sorting demo
make demo

# Build and run test suite
make test

# Clean build files
make clean

# Show help
make help
```

## 🎮 Usage Examples

### 1. Main Application
```bash
make run
# Navigate to "Favorite Songs Queue" menu
# Choose from 15 different operations
```

### 2. Interactive Demo
```bash
make demo
# Watch real-time auto-sorting in action
# See priority queue behavior
# View statistics and analytics
```

### 3. Test Suite
```bash
make test
# Verify all functionality works correctly
# Test auto-sorting, multi-level sorting, etc.
```

## 📊 Menu Options

The enhanced favorite songs queue provides 15 menu options:

1. **Display favorites** - Shows auto-sorted list
2. **Add song** - Manual addition
3. **Remove song** - Manual removal
4. **Update listening time** - Manual updates with auto-sorting
5. **Increment play count** - Update play statistics
6. **Get top favorite** - Most listened song
7. **Get top N favorites** - Top songs by listening time
8. **Check if in favorites** - Search functionality
9. **Clear all** - Reset favorites
10. **Auto-update from playback** - Simulate real playback
11. **Sync with history** - Update from playback history
12. **Time range filtering** - Filter by listening duration
13. **Statistics** - Detailed analytics
14. **Export to file** - Save favorites
15. **Import from file** - Load favorites

## 🔬 Technical Details

### Time Complexity
- **Insertion**: O(log n)
- **Deletion**: O(n) - requires queue rebuild
- **Update**: O(n) - requires queue rebuild
- **Top access**: O(1)
- **Top N**: O(n log n)

### Space Complexity
- **Storage**: O(n)
- **Auxiliary**: O(n) during rebuilds

### Sorting Algorithm
1. **Primary**: Total listening time (descending)
2. **Secondary**: Play count (descending)
3. **Tertiary**: Song title (ascending)

## 🧪 Testing

The test suite covers:

- ✅ Basic operations (add, remove, check)
- ✅ Auto-sorting functionality
- ✅ Multi-level sorting (time + play count + title)
- ✅ Auto-update from playback
- ✅ Statistics and analytics
- ✅ Queue rebuilding
- ✅ Time range filtering

## 📈 Learning Outcomes

### Data Structures Mastered
- **Priority Queue (Max Heap)**: Automatic sorting
- **Hash Maps**: Efficient key-value storage
- **Custom Comparators**: Multi-level sorting
- **Vectors**: Data manipulation

### Algorithms Learned
- **Heap Operations**: Insert, delete, extract max
- **Queue Rebuilding**: Efficient maintenance
- **Multi-level Sorting**: Complex comparison logic
- **Hash-based Lookup**: O(1) access patterns

### Design Patterns
- **Observer Pattern**: Auto-update on changes
- **Strategy Pattern**: Different sorting strategies
- **Factory Pattern**: Object creation
- **Singleton-like**: Centralized management

## 🎯 Scenario Requirements Met

✅ **Auto-sorting**: Songs automatically sorted by listening duration  
✅ **Priority Queue**: Uses max heap for efficient ordering  
✅ **Real-time Updates**: Queue reorders immediately when data changes  
✅ **Multi-level Sorting**: Comprehensive ordering criteria  
✅ **Integration**: Seamless integration with playback system  
✅ **User Experience**: Intuitive interface with immediate feedback  

## 🚀 Future Enhancements

1. **Lazy Rebuilding**: Only rebuild when necessary
2. **Incremental Updates**: Update heap without full rebuild
3. **Caching**: Cache frequently accessed elements
4. **Persistent Storage**: Database integration
5. **Real-time Sync**: Live updates from music players

## 📚 Documentation

- **Technical Design**: `docs/auto_sorting_favorites.md`
- **User Guide**: Main application help system
- **API Reference**: Header file documentation
- **Examples**: Demo program and test suite

---

**🎉 The auto-sorting favorite songs queue successfully demonstrates mastery of priority queues, comparators, and sorting algorithms while providing a practical, user-friendly system for managing favorite songs based on listening behavior.** 