# PlayWise Data Structure Logging System

## Overview

The PlayWise logging system provides comprehensive tracking of all data structure operations in real-time. It logs every operation performed on stacks, queues, linked lists, binary search trees, and hash tables with detailed timing information and performance metrics.

## Features

### 🔍 **Comprehensive Operation Tracking**
- **Linked List Operations**: Add, delete, move, search, reverse
- **Stack Operations**: Push, pop, top, overflow handling
- **Priority Queue Operations**: Insert, update, rebuild, extract
- **BST Operations**: Insert, search, delete, range queries
- **Hash Table Operations**: Insert, search, delete, collision handling

### ⏱️ **Performance Metrics**
- **Microsecond precision timing** for all operations
- **Size tracking** before and after operations
- **Performance analysis** and bottleneck identification
- **Real-time performance monitoring**

### 📊 **Multiple Output Formats**
- **Console output** for real-time monitoring
- **File logging** for persistent records
- **Thread-safe logging** with mutex protection
- **Timestamped entries** with millisecond precision

### 🎯 **Smart Logging Categories**
- **Operation-specific logging** for each data structure
- **Success/failure tracking** with detailed error messages
- **Performance warnings** for slow operations
- **System health monitoring**

## Logging Categories

### 1. Linked List Operations (`[LINKED_LIST]`)
```
[LINKED_LIST] ADD_SONG | Size: 5 | Duration: 45 μs | Added song: Bohemian Rhapsody by Queen
[LINKED_LIST] MOVE_SONG | Size: 5 | Duration: 123 μs | Moved song: Hotel California from 1 to 3
[LINKED_LIST] DELETE_SONG | Size: 4 | Duration: 67 μs | Deleted song: Stairway to Heaven at index 2
```

### 2. Stack Operations (`[STACK]`)
```
[STACK] ADD_PLAYED_SONG | Size: 3 | Duration: 23 μs | Added song: Bohemian Rhapsody by Queen
[STACK] UNDO_LAST_PLAY | Size: 2 | Duration: 12 μs | Undid last play: Hotel California by Eagles
[STACK] ADD_PLAYED_SONG | Size: 5 | Duration: 89 μs | Stack overflow handled, oldest song removed
```

### 3. Priority Queue Operations (`[QUEUE]`)
```
[QUEUE] ADD_SONG | Size: 3 | Duration: 34 μs | Added song: Bohemian Rhapsody by Queen
[QUEUE] UPDATE_LISTENING_TIME | Size: 3 | Duration: 156 μs | Updated listening time for: Hotel California (+300s)
[QUEUE] REBUILD_QUEUE | Size: 3 | Duration: 234 μs | Queue rebuilt after listening time update
```

### 4. BST Operations (`[BST]`)
```
[BST] INSERT_SONG | Size: 4 | Duration: 45 μs | Inserted song: Bohemian Rhapsody with rating 5
[BST] SEARCH_BY_RATING | Size: 4 | Duration: 23 μs | Found 2 songs with rating 5
[BST] RANGE_QUERY | Size: 4 | Duration: 34 μs | Found 3 songs in range 4-5 stars
```

### 5. Hash Table Operations (`[HASH_TABLE]`)
```
[HASH_TABLE] INSERT_SONG | Size: 5 | Duration: 12 μs | Inserted song: Bohemian Rhapsody
[HASH_TABLE] SEARCH_BY_ID | Size: 5 | Duration: 8 μs | Found song by ID: 1
[HASH_TABLE] SEARCH_BY_TITLE | Size: 5 | Duration: 9 μs | Found song by title: Hotel California
```

## Usage Examples

### Basic Logging Setup
```cpp
#include "../include/logger.h"

// Configure logger
Logger* logger = Logger::getInstance();
logger->enableConsoleOutput(true);
logger->setLogFile("playwise_operations.log");
```

### Linked List Operation Logging
```cpp
void Playlist::add_song(const Song& song) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform operation
    PlaylistNode* newNode = new PlaylistNode(song);
    insertNode(newNode, tail);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Added song: " + song.getTitle() + " by " + song.getArtist();
    LOG_LL_OP("ADD_SONG", details, size, duration_us);
}
```

### Stack Operation Logging
```cpp
void History::add_played_song(const Song& song) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform operation
    playbackHistory.push(song);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Added song: " + song.getTitle() + " by " + song.getArtist();
    LOG_STACK_OP("ADD_PLAYED_SONG", details, playbackHistory.size(), duration_us);
}
```

### Priority Queue Operation Logging
```cpp
void FavoriteSongsQueue::updateListeningTime(const Song& song, int additionalSeconds) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform operation
    std::string key = generateSongKey(song);
    songListeningTime[key] += additionalSeconds;
    rebuildQueue();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::string details = "Updated listening time for: " + song.getTitle() + " (+" + std::to_string(additionalSeconds) + "s)";
    LOG_QUEUE_OP("UPDATE_LISTENING_TIME", details, songQueue.size(), duration_us);
}
```

## Log Format

### Standard Log Entry Format
```
[Timestamp] [Category] Operation | Size: N | Duration: X μs/ms/s | Details
```

### Example Log Entries
```
2024-01-15 14:30:25.123 [LINKED_LIST] ADD_SONG | Size: 5 | Duration: 45 μs | Added song: Bohemian Rhapsody by Queen
2024-01-15 14:30:25.124 [STACK] ADD_PLAYED_SONG | Size: 3 | Duration: 23 μs | Added song: Hotel California by Eagles
2024-01-15 14:30:25.125 [QUEUE] UPDATE_LISTENING_TIME | Size: 3 | Duration: 156 μs | Updated listening time for: Stairway to Heaven (+300s)
2024-01-15 14:30:25.126 [BST] SEARCH_BY_RATING | Size: 4 | Duration: 23 μs | Found 2 songs with rating 5
2024-01-15 14:30:25.127 [HASH_TABLE] SEARCH_BY_TITLE | Size: 5 | Duration: 9 μs | Found song by title: Imagine
```

## Performance Analysis

### Timing Categories
- **μs (microseconds)**: Fast operations (< 1ms)
- **ms (milliseconds)**: Medium operations (1ms - 1s)
- **s (seconds)**: Slow operations (> 1s)

### Performance Thresholds
- **Excellent**: < 100 μs
- **Good**: 100 μs - 1 ms
- **Acceptable**: 1 ms - 10 ms
- **Slow**: 10 ms - 100 ms
- **Very Slow**: > 100 ms

### Performance Warnings
The system automatically logs warnings for operations that exceed performance thresholds:
```
[WARNING] Operation ADD_SONG took 2.3 ms, exceeding threshold of 1 ms
[WARNING] Queue rebuild operation took 15.2 ms, consider optimization
```

## Demo Program

### Running the Logging Demo
```bash
# Build the logging demo
make logging-demo

# Run the demo
./bin/logging_demo
```

### Demo Features
1. **Linked List Demo**: Add, move, delete songs with logging
2. **Stack Demo**: Push, pop operations with overflow handling
3. **Priority Queue Demo**: Auto-sorting with real-time updates
4. **BST Demo**: Insert, search, range queries
5. **Hash Table Demo**: Insert, search operations
6. **Performance Demo**: Simulated operations with timing

### Sample Demo Output
```
=== LINKED LIST LOGGING DEMO ===
2024-01-15 14:30:25.123 [INFO] Starting Linked List (Playlist) logging demonstration
2024-01-15 14:30:25.124 [LINKED_LIST] ADD_SONG | Size: 1 | Duration: 45 μs | Added song: Bohemian Rhapsody by Queen
2024-01-15 14:30:25.125 [LINKED_LIST] ADD_SONG | Size: 2 | Duration: 34 μs | Added song: Hotel California by Eagles
2024-01-15 14:30:25.126 [LINKED_LIST] MOVE_SONG | Size: 2 | Duration: 123 μs | Moved song: Bohemian Rhapsody from 0 to 1
2024-01-15 14:30:25.127 [LINKED_LIST] DELETE_SONG | Size: 1 | Duration: 67 μs | Deleted song: Hotel California at index 0
```

## Configuration Options

### Logger Configuration
```cpp
// Enable/disable console output
logger->enableConsoleOutput(true);  // Default: true

// Enable/disable file output
logger->enableFileOutput(true);     // Default: false

// Set log file path
logger->setLogFile("custom_log.log");

// Close logger
logger->close();
```

### Log File Management
- **Append mode**: New logs are appended to existing files
- **Automatic flushing**: Logs are written immediately
- **Thread safety**: Concurrent logging is handled safely
- **Error handling**: Failed writes are reported

## Integration with Main Application

### Automatic Logging
The logging system is automatically integrated into all data structure operations:

1. **Playlist Operations**: All linked list operations are logged
2. **History Operations**: All stack operations are logged
3. **Favorites Operations**: All priority queue operations are logged
4. **Rating Operations**: All BST operations are logged
5. **Database Operations**: All hash table operations are logged

### Performance Monitoring
The system provides real-time performance monitoring:
- **Operation timing** for all data structure operations
- **Size tracking** to monitor memory usage
- **Performance trends** over time
- **Bottleneck identification** for optimization

## Benefits

### 🎯 **Debugging and Troubleshooting**
- **Detailed operation tracking** for debugging
- **Performance bottleneck identification**
- **Error tracking** with context
- **Operation sequence analysis**

### 📈 **Performance Optimization**
- **Real-time performance monitoring**
- **Operation timing analysis**
- **Memory usage tracking**
- **Optimization opportunity identification**

### 🔍 **System Analysis**
- **Usage pattern analysis**
- **Data structure efficiency evaluation**
- **System health monitoring**
- **Capacity planning**

### 📚 **Educational Value**
- **Data structure operation visualization**
- **Algorithm performance comparison**
- **Real-world usage examples**
- **Performance characteristics demonstration**

## Conclusion

The PlayWise logging system provides comprehensive visibility into all data structure operations, enabling:

- **Real-time monitoring** of system performance
- **Detailed debugging** of complex operations
- **Performance optimization** through bottleneck identification
- **Educational insights** into data structure behavior

The system is designed to be:
- **Non-intrusive**: Minimal performance impact
- **Comprehensive**: Covers all data structure operations
- **Flexible**: Configurable output and formatting
- **Thread-safe**: Safe for concurrent operations

This logging system serves as a powerful tool for understanding, optimizing, and maintaining the PlayWise music playlist management system. 