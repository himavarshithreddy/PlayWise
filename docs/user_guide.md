# PlayWise: Complete User Guide
## Comprehensive Documentation for All Operations and Options

---

## Table of Contents
1. [Getting Started](#getting-started)
2. [Main Menu Navigation](#main-menu-navigation)
3. [Playlist Operations](#playlist-operations)
4. [History Operations](#history-operations)
5. [Rating Operations](#rating-operations)
6. [Database Operations](#database-operations)
7. [Sorting Operations](#sorting-operations)
8. [Dashboard & Analytics](#dashboard--analytics)
9. [System Operations](#system-operations)
10. [Troubleshooting](#troubleshooting)

---

## Getting Started

### Launching PlayWise
1. **Compile the Application** (if not already done):
   ```bash
   g++ -std=c++17 -Wall -Wextra -Iinclude -o playwise.exe src/*.cpp
   ```

2. **Run the Application**:
   ```bash
   ./playwise.exe
   ```

3. **Initial Setup**: The system automatically loads sample data including:
   - 7 classic songs (Queen, Eagles, Beatles, etc.)
   - Pre-configured playlists
   - Sample ratings and history

### Understanding the Interface
- **Menu System**: Navigate using number keys (0-9)
- **Input Validation**: All inputs are validated for correctness
- **Error Handling**: Clear error messages guide you through issues
- **Screen Clearing**: Automatic screen clearing for better readability

---

## Main Menu Navigation

### Main Menu Options
```
╔══════════════════════════════════════════════════════════════╗
║                    PlayWise Music System                    ║
║                     Main Menu                               ║
╠══════════════════════════════════════════════════════════════╣
║  1. Playlist Operations (Doubly Linked List)               ║
║  2. History Operations (Stack)                             ║
║  3. Rating Operations (Binary Search Tree)                 ║
║  4. Database Operations (HashMap)                          ║
║  5. Sorting Operations (Merge/Quick/Heap Sort)             ║
║  6. Dashboard & Analytics                                  ║
║  7. System Operations                                      ║
║  0. Exit                                                   ║
╚══════════════════════════════════════════════════════════════╝
```

### Navigation Instructions
- **Enter a number** (0-7) to select an option
- **Press Enter** to confirm your selection
- **Invalid inputs** will prompt you to try again
- **Option 0** always returns to the previous menu or exits

---

## Playlist Operations (Doubly Linked List)

### Accessing Playlist Operations
1. From main menu, select **Option 1**
2. You'll see the playlist operations submenu

### Available Operations

#### 1. Display Current Playlist
- **Purpose**: View all songs in your current playlist
- **How to Use**:
  1. Select **Option 1** from playlist menu
  2. View the formatted list showing:
     - Song number
     - Title and artist
     - Duration in MM:SS format
  3. Press **Enter** to return to playlist menu

#### 2. Add Song to Playlist
- **Purpose**: Add a new song to your playlist
- **How to Use**:
  1. Select **Option 2** from playlist menu
  2. Enter **Song Title** (e.g., "Bohemian Rhapsody")
  3. Enter **Artist Name** (e.g., "Queen")
  4. Enter **Duration in seconds** (e.g., 354 for 5:54)
  5. System confirms: "Song added successfully!"
  6. Press **Enter** to continue

**Input Requirements**:
- Title: Any text string (required)
- Artist: Any text string (required)
- Duration: Integer between 1-3600 seconds (1 second to 1 hour)

#### 3. Delete Song from Playlist
- **Purpose**: Remove a song from your playlist by position
- **How to Use**:
  1. Select **Option 3** from playlist menu
  2. View the current playlist display
  3. Enter the **song number** (1, 2, 3, etc.) to delete
  4. System confirms: "Song deleted successfully!"
  5. Press **Enter** to continue

**Important Notes**:
- Song numbers are 1-indexed (first song is #1)
- Deletion is permanent
- Remaining songs are automatically renumbered

#### 4. Move Song in Playlist
- **Purpose**: Reorder songs within your playlist
- **How to Use**:
  1. Select **Option 4** from playlist menu
  2. View the current playlist display
  3. Enter **source position** (where song currently is)
  4. Enter **destination position** (where you want it)
  5. System confirms: "Song moved successfully!"
  6. Press **Enter** to continue

**Example**:
- Move song from position 3 to position 1
- Enter: Source = 3, Destination = 1
- Song moves to the top of the playlist

#### 5. Reverse Playlist
- **Purpose**: Reverse the entire order of your playlist
- **How to Use**:
  1. Select **Option 5** from playlist menu
  2. System confirms: "Playlist reversed successfully!"
  3. Press **Enter** to continue

**Result**: First song becomes last, last song becomes first

#### 6. Shuffle Playlist
- **Purpose**: Randomize the order of songs in your playlist
- **How to Use**:
  1. Select **Option 6** from playlist menu
  2. System confirms: "Playlist shuffled successfully!"
  3. Press **Enter** to continue

**Note**: Uses a pseudo-random algorithm for shuffling

#### 7. Search Song in Playlist
- **Purpose**: Find a specific song by title
- **How to Use**:
  1. Select **Option 7** from playlist menu
  2. Enter the **song title** to search for
  3. System displays results:
     - "Song found: [Title] - [Artist]" (if found)
     - "Song not found!" (if not found)
  4. Press **Enter** to continue

**Search Features**:
- Case-sensitive search
- Exact title match required
- Returns first match found

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from playlist menu
  2. Returns to main menu

---

## History Operations (Stack)

### Accessing History Operations
1. From main menu, select **Option 2**
2. You'll see the history operations submenu

### Available Operations

#### 1. Display Playback History
- **Purpose**: View all recently played songs
- **How to Use**:
  1. Select **Option 1** from history menu
  2. View the formatted history showing:
     - Song number (most recent first)
     - Title and artist
     - Duration and rating
  3. Press **Enter** to return to history menu

**Display Format**:
```
=== Playback History ===
Size: 5/10 songs

1. Bohemian Rhapsody - Queen (05:54) [Rating: 5/5]
2. Hotel California - Eagles (06:31) [Rating: 4/5]
...
```

#### 2. Display Recent Songs
- **Purpose**: View a specific number of most recent songs
- **How to Use**:
  1. Select **Option 2** from history menu
  2. Enter **number of songs** to display (1-20)
  3. View the recent songs list
  4. Press **Enter** to continue

**Example**: Enter "3" to see the 3 most recently played songs

#### 3. Undo Last Played Song
- **Purpose**: Remove the most recent song from history and add it back to playlist
- **How to Use**:
  1. Select **Option 3** from history menu
  2. System displays: "Undone: [Song Title] - [Artist]"
  3. System confirms: "Song added back to playlist!"
  4. Press **Enter** to continue

**What Happens**:
- Most recent song is removed from history
- Song is automatically added to the end of your playlist
- History size is reduced by 1

#### 4. Clear History
- **Purpose**: Remove all songs from playback history
- **How to Use**:
  1. Select **Option 4** from history menu
  2. System confirms: "History cleared successfully!"
  3. Press **Enter** to continue

**Warning**: This action is permanent and cannot be undone

#### 5. Export History to File
- **Purpose**: Save your playback history to a text file
- **How to Use**:
  1. Select **Option 5** from history menu
  2. System creates file: "playback_history.txt"
  3. System confirms: "History exported to file successfully!"
  4. Press **Enter** to continue

**File Location**: Created in the same directory as the executable

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from history menu
  2. Returns to main menu

---

## Rating Operations (Binary Search Tree)

### Accessing Rating Operations
1. From main menu, select **Option 3**
2. You'll see the rating operations submenu

### Available Operations

#### 1. Display Rating Tree Structure
- **Purpose**: View the hierarchical structure of songs organized by rating
- **How to Use**:
  1. Select **Option 1** from rating menu
  2. View the tree structure showing:
     - Rating levels (1-5 stars)
     - Songs grouped by rating
     - Tree organization
  3. Press **Enter** to continue

**Display Format**:
```
=== Rating Tree Structure ===
Rating 5 stars (4 songs):
  - Bohemian Rhapsody - Queen
  - Imagine - John Lennon
  - Stairway to Heaven - Led Zeppelin
  - Hey Jude - The Beatles

Rating 4 stars (2 songs):
  - Hotel California - Eagles
  - Yesterday - The Beatles
...
```

#### 2. Display Rating Statistics
- **Purpose**: View comprehensive statistics about song ratings
- **How to Use**:
  1. Select **Option 2** from rating menu
  2. View statistics including:
     - Total songs
     - Tree height
     - Average rating
     - Most common rating
     - Breakdown by rating level
  3. Press **Enter** to continue

**Statistics Shown**:
- Total songs in tree
- Tree height (complexity measure)
- Average rating across all songs
- Most frequently occurring rating
- Count of songs for each rating (1-5 stars)

#### 3. Search Songs by Rating
- **Purpose**: Find all songs with a specific rating
- **How to Use**:
  1. Select **Option 3** from rating menu
  2. Enter **rating** (1-5 stars)
  3. View all songs with that rating
  4. Press **Enter** to continue

**Example**: Enter "5" to see all 5-star rated songs

#### 4. Get Top Rated Songs
- **Purpose**: View the highest-rated songs in your collection
- **How to Use**:
  1. Select **Option 4** from rating menu
  2. Enter **number of songs** to display (1-10)
  3. View the top-rated songs list
  4. Press **Enter** to continue

**Sorting**: Songs are sorted by rating (highest first), then by title

#### 5. Add Song with Rating
- **Purpose**: Add a new song directly to the rating tree
- **How to Use**:
  1. Select **Option 5** from rating menu
  2. Enter **Song Title**
  3. Enter **Artist Name**
  4. Enter **Duration** (1-3600 seconds)
  5. Enter **Rating** (1-5 stars)
  6. System confirms: "Song added to rating tree successfully!"
  7. Press **Enter** to continue

**Note**: This adds the song to the rating tree but not to the main playlist

#### 6. Delete Song from Rating Tree
- **Purpose**: Remove a song from the rating tree
- **How to Use**:
  1. Select **Option 6** from rating menu
  2. Enter **Song ID** (e.g., "song_001")
  3. Enter **Song Rating** (1-5 stars)
  4. System confirms: "Song deleted from rating tree successfully!"
  5. Press **Enter** to continue

**Requirements**: Both song ID and rating must match exactly

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from rating menu
  2. Returns to main menu

---

## Database Operations (HashMap)

### Accessing Database Operations
1. From main menu, select **Option 4**
2. You'll see the database operations submenu

### Available Operations

#### 1. Display Database
- **Purpose**: View all songs in the database with detailed information
- **How to Use**:
  1. Select **Option 1** from database menu
  2. View the complete database showing:
     - Song ID
     - Title and artist
     - Duration and rating
     - Album and genre information
  3. Press **Enter** to continue

**Display Format**:
```
=== Song Database ===
Total songs: 5
Load factor: 0.384615
Bucket count: 13
Max bucket size: 2

1. Yesterday - The Beatles (ID: song_005) [02:05] Rating: 4/5
2. Stairway to Heaven - Led Zeppelin (ID: song_004) [08:02] Rating: 5/5
...
```

#### 2. Display Database Statistics
- **Purpose**: View performance and usage statistics
- **How to Use**:
  1. Select **Option 2** from database menu
  2. View comprehensive statistics including:
     - Total songs, unique artists, albums, genres
     - Performance metrics (load factor, bucket count)
     - Top artists by song count
  3. Press **Enter** to continue

**Statistics Include**:
- Total songs in database
- Number of unique artists
- Number of unique albums
- Number of unique genres
- Hash table load factor
- Number of hash buckets
- Maximum bucket size
- Top artists with song counts

#### 3. Search Song by ID
- **Purpose**: Find a song using its unique identifier
- **How to Use**:
  1. Select **Option 3** from database menu
  2. Enter **Song ID** (e.g., "song_001")
  3. View results:
     - "Found: [Title] - [Artist]" (if found)
     - "Song not found!" (if not found)
  4. Press **Enter** to continue

**ID Format**: Usually "song_XXX" where XXX is a number

#### 4. Search Song by Title
- **Purpose**: Find a song using its title
- **How to Use**:
  1. Select **Option 4** from database menu
  2. Enter **Song Title** (e.g., "Hotel California")
  3. View results:
     - "Found: [Title] - [Artist]" (if found)
     - "Song not found!" (if not found)
  4. Press **Enter** to continue

**Search Features**:
- Case-sensitive search
- Exact title match required

#### 5. Search Songs by Artist
- **Purpose**: Find all songs by a specific artist
- **How to Use**:
  1. Select **Option 5** from database menu
  2. Enter **Artist Name** (e.g., "Queen")
  3. View all songs by that artist
  4. Press **Enter** to continue

**Display**: Lists all song titles by the specified artist

#### 6. Search Songs by Genre
- **Purpose**: Find all songs in a specific genre
- **How to Use**:
  1. Select **Option 6** from database menu
  2. Enter **Genre** (e.g., "Rock")
  3. View all songs in that genre
  4. Press **Enter** to continue

**Display**: Lists all songs with title and artist in the specified genre

#### 7. Add Song to Database
- **Purpose**: Add a new song to the database with complete metadata
- **How to Use**:
  1. Select **Option 7** from database menu
  2. Enter **Song Title**
  3. Enter **Artist Name**
  4. Enter **Duration** (1-3600 seconds)
  5. Enter **Rating** (1-5 stars)
  6. Enter **Album Name**
  7. Enter **Genre**
  8. System confirms: "Song added to database successfully!"
  9. Press **Enter** to continue

**Complete Metadata**: All fields are stored for comprehensive search capabilities

#### 8. Delete Song from Database
- **Purpose**: Remove a song from the database
- **How to Use**:
  1. Select **Option 8** from database menu
  2. Enter **Song ID** (e.g., "song_001")
  3. System confirms: "Song deleted from database successfully!"
  4. Press **Enter** to continue

**Warning**: This action is permanent and removes the song from all database indexes

#### 9. Export Database to File
- **Purpose**: Save the entire database to a text file
- **How to Use**:
  1. Select **Option 9** from database menu
  2. System creates file: "song_database.txt"
  3. System confirms: "Database exported to file successfully!"
  4. Press **Enter** to continue

**File Contents**: Complete song information in formatted text

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from database menu
  2. Returns to main menu

---

## Sorting Operations

### Accessing Sorting Operations
1. From main menu, select **Option 5**
2. You'll see the sorting operations submenu

### Available Operations

#### 1. Sort Playlist by Title (A-Z)
- **Purpose**: Sort songs alphabetically by title in ascending order
- **How to Use**:
  1. Select **Option 1** from sorting menu
  2. System displays: "Sorting playlist by Title (A-Z) using merge sort..."
  3. System shows sorting time in microseconds
  4. System confirms: "Playlist sorted successfully!"
  5. Press **Enter** to continue

**Result**: Songs arranged alphabetically from A to Z

#### 2. Sort Playlist by Title (Z-A)
- **Purpose**: Sort songs alphabetically by title in descending order
- **How to Use**:
  1. Select **Option 2** from sorting menu
  2. System displays: "Sorting playlist by Title (Z-A) using merge sort..."
  3. System shows sorting time in microseconds
  4. System confirms: "Playlist sorted successfully!"
  5. Press **Enter** to continue

**Result**: Songs arranged alphabetically from Z to A

#### 3. Sort Playlist by Duration (Shortest First)
- **Purpose**: Sort songs by duration, shortest songs first
- **How to Use**:
  1. Select **Option 3** from sorting menu
  2. System displays: "Sorting playlist by Duration (Shortest First) using merge sort..."
  3. System shows sorting time in microseconds
  4. System confirms: "Playlist sorted successfully!"
  5. Press **Enter** to continue

**Result**: Songs arranged from shortest to longest duration

#### 4. Sort Playlist by Duration (Longest First)
- **Purpose**: Sort songs by duration, longest songs first
- **How to Use**:
  1. Select **Option 4** from sorting menu
  2. System displays: "Sorting playlist by Duration (Longest First) using merge sort..."
  3. System shows sorting time in microseconds
  4. System confirms: "Playlist sorted successfully!"
  5. Press **Enter** to continue

**Result**: Songs arranged from longest to shortest duration

#### 5. Sort Playlist by Rating (Highest First)
- **Purpose**: Sort songs by rating, highest-rated songs first
- **How to Use**:
  1. Select **Option 5** from sorting menu
  2. System displays: "Sorting playlist by Rating (Highest First) using merge sort..."
  3. System shows sorting time in microseconds
  4. System confirms: "Playlist sorted successfully!"
  5. Press **Enter** to continue

**Result**: Songs arranged from 5-star to 1-star ratings

#### 6. Sort Playlist by Artist (A-Z)
- **Purpose**: Sort songs alphabetically by artist name in ascending order
- **How to Use**:
  1. Select **Option 6** from sorting menu
  2. System displays: "Sorting playlist by Artist (A-Z) using merge sort..."
  3. System shows sorting time in microseconds
  4. System confirms: "Playlist sorted successfully!"
  5. Press **Enter** to continue

**Result**: Songs arranged by artist name from A to Z

#### 7. Benchmark Sorting Algorithms
- **Purpose**: Compare performance of different sorting algorithms
- **How to Use**:
  1. Select **Option 7** from sorting menu
  2. View benchmark results showing:
     - Algorithm names (Merge Sort, Quick Sort, Heap Sort)
     - Execution time in microseconds for each algorithm
     - Comparison across different sorting criteria
  3. Press **Enter** to continue

**Benchmark Results**:
```
=== Sorting Algorithm Benchmark ===
Testing with 7 songs
Algorithm           Time (μs)
-----------------------------------
Criterion: Title (A-Z)
Merge Sort              45
Quick Sort              38
Heap Sort               52

Criterion: Duration (Shortest First)
Merge Sort              42
Quick Sort              35
Heap Sort               48
...
```

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from sorting menu
  2. Returns to main menu

---

## Dashboard & Analytics

### Accessing Dashboard Operations
1. From main menu, select **Option 6**
2. You'll see the dashboard operations submenu

### Available Operations

#### 1. Display Live Dashboard
- **Purpose**: View real-time system statistics and status
- **How to Use**:
  1. Select **Option 1** from dashboard menu
  2. View the live dashboard showing:
     - System status with decorative borders
     - Total songs, playlists, play time
     - Average rating and system load
     - Memory usage
     - Top artists by song count
  3. Press **Enter** to continue

**Dashboard Display**:
```
╔══════════════════════════════════════════════════════════════╗
║                    SYSTEM STATUS                            ║
╠══════════════════════════════════════════════════════════════╣
║  Total Songs:        7                                    ║
║  Total Playlists:    1                                ║
║  Total Play Time:    25 min                          ║
║  Average Rating:     4.29/5                        ║
║  System Load:        0.385                              ║
║  Memory Usage:       2048 bytes                           ║
╚══════════════════════════════════════════════════════════╝
```

#### 2. Export System Snapshot
- **Purpose**: Generate a comprehensive system report
- **How to Use**:
  1. Select **Option 2** from dashboard menu
  2. View detailed snapshot including:
     - Timestamp and version information
     - System overview statistics
     - Top 5 longest songs
     - Most recently played songs
     - Song count by rating
  3. Press **Enter** to continue

**Snapshot Contents**:
- System overview with all key metrics
- Top 5 longest songs with durations
- Most recently played songs
- Distribution of songs by rating (1-5 stars)

#### 3. Display Performance Metrics
- **Purpose**: View detailed performance statistics
- **How to Use**:
  1. Select **Option 3** from dashboard menu
  2. View performance metrics including:
     - Database performance (load factor, bucket count)
     - Rating tree performance (height, total songs)
     - History performance (current size vs. maximum)
  3. Press **Enter** to continue

**Performance Data**:
- Database load factor and efficiency
- Tree height and balance information
- History utilization statistics

#### 4. Display User Activity
- **Purpose**: View user behavior and activity patterns
- **How to Use**:
  1. Select **Option 4** from dashboard menu
  2. View user activity including:
     - Most played artist and song
     - Total play count
     - Recent activity (last 3 songs played)
  3. Press **Enter** to continue

**Activity Information**:
- Most frequently played artist
- Most recently played song
- Total number of songs played
- Recent playback history

#### 5. Display System Health
- **Purpose**: View system health status and recommendations
- **How to Use**:
  1. Select **Option 5** from dashboard menu
  2. View health status including:
     - Database health with status indicators
     - Memory usage analysis
     - Overall system status
  3. Press **Enter** to continue

**Health Indicators**:
- 🟢 Excellent (load factor < 0.5)
- 🟡 Good (load factor < 0.8)
- 🔴 Needs attention (load factor >= 0.8)

#### 6. Generate Performance Report
- **Purpose**: Create a comprehensive performance analysis
- **How to Use**:
  1. Select **Option 6** from dashboard menu
  2. View detailed report including:
     - Performance metrics
     - Bottleneck analysis
     - Optimization suggestions
  3. Press **Enter** to continue

**Report Contents**:
- All performance metrics
- Identified bottlenecks
- Specific optimization recommendations

#### 7. Generate Usage Report
- **Purpose**: Create a detailed usage analysis
- **How to Use**:
  1. Select **Option 7** from dashboard menu
  2. View usage report including:
     - User activity summary
     - Genre distribution
     - Usage patterns
  3. Press **Enter** to continue

**Usage Analysis**:
- User activity patterns
- Genre preferences
- Playback behavior

#### 8. Export System Report to File
- **Purpose**: Save system report to a text file
- **How to Use**:
  1. Select **Option 8** from dashboard menu
  2. System creates file: "system_report.txt"
  3. System confirms: "System report exported to file successfully!"
  4. Press **Enter** to continue

**File Contents**: Complete system analysis and statistics

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from dashboard menu
  2. Returns to main menu

---

## System Operations

### Accessing System Operations
1. From main menu, select **Option 7**
2. You'll see the system operations submenu

### Available Operations

#### 1. Reset System
- **Purpose**: Clear all data and reload sample data
- **How to Use**:
  1. Select **Option 1** from system menu
  2. System asks: "Are you sure you want to reset the system? (y/n):"
  3. Enter **y** or **Y** to confirm, or **n** or **N** to cancel
  4. If confirmed:
     - All playlists are cleared
     - All history is cleared
     - All ratings are cleared
     - All database entries are cleared
     - Sample data is reloaded
     - System confirms: "System reset successfully!"
  5. Press **Enter** to continue

**Warning**: This action is permanent and removes all user data

#### 2. Export All System Data
- **Purpose**: Save all system data to separate files
- **How to Use**:
  1. Select **Option 2** from system menu
  2. System creates multiple files:
     - "export_song_database.txt" (database export)
     - "export_playback_history.txt" (history export)
     - "export_system_report.txt" (system report)
  3. System confirms: "System data exported successfully!"
  4. Press **Enter** to continue

**Files Created**:
- Complete database backup
- Playback history backup
- System analysis report

#### 3. Import System Data
- **Purpose**: Load system data from previously exported files
- **How to Use**:
  1. Select **Option 3** from system menu
  2. System attempts to import from "export_song_database.txt"
  3. System confirms: "System data imported successfully!" or "Failed to import system data!"
  4. Press **Enter** to continue

**Requirements**: Export files must exist in the same directory

#### 4. Display System Information
- **Purpose**: View system version and status information
- **How to Use**:
  1. Select **Option 4** from system menu
  2. View system information including:
     - System name and version
     - Initialization status
     - Current user information
  3. Press **Enter** to continue

**Information Displayed**:
- PlayWise Music Management System
- Version number (e.g., 1.0.0)
- System status (Initialized/Not Initialized)
- Current user name

#### 5. Memory Usage Analysis
- **Purpose**: View detailed memory usage statistics
- **How to Use**:
  1. Select **Option 5** from system menu
  2. View memory analysis including:
     - Total memory usage in bytes
     - Memory usage by component
     - Memory efficiency metrics
  3. Press **Enter** to continue

**Memory Analysis**:
- Total system memory usage
- Database memory usage
- History memory usage
- Memory usage in MB (if > 1MB)

#### 0. Back to Main Menu
- **Purpose**: Return to the main menu
- **How to Use**:
  1. Select **Option 0** from system menu
  2. Returns to main menu

---

## Troubleshooting

### Common Issues and Solutions

#### Application Won't Start
**Problem**: Application doesn't launch or shows error
**Solutions**:
1. Ensure all source files are compiled
2. Check that playwise.exe exists in the directory
3. Verify C++17 compatibility
4. Run from the correct directory

#### Invalid Input Errors
**Problem**: System rejects valid-looking input
**Solutions**:
1. Check input format requirements
2. Ensure numbers are within specified ranges
3. Verify text input doesn't contain special characters
4. Follow exact input prompts

#### File Export Issues
**Problem**: Export operations fail
**Solutions**:
1. Check write permissions in the directory
2. Ensure sufficient disk space
3. Verify no other programs are using the files
4. Check that the directory is not read-only

#### Memory Issues
**Problem**: System becomes slow or crashes
**Solutions**:
1. Check system memory usage
2. Restart the application
3. Use system reset if necessary
4. Monitor dashboard for memory warnings

#### Data Loss
**Problem**: Songs or data disappear
**Solutions**:
1. Check if system reset was accidentally triggered
2. Verify data wasn't deleted through menu operations
3. Use export/import to backup important data
4. Reload sample data if needed

### Performance Tips

#### For Large Playlists
1. Use sorting operations sparingly
2. Monitor dashboard for performance metrics
3. Consider using database operations for large datasets
4. Export data regularly as backup

#### For Optimal Performance
1. Keep playlist size manageable
2. Use appropriate sorting algorithms
3. Monitor system health regularly
4. Clear history periodically

#### For Data Management
1. Export important data regularly
2. Use descriptive song titles and artist names
3. Maintain consistent rating patterns
4. Backup system state before major operations

### Keyboard Shortcuts and Navigation

#### General Navigation
- **Number keys (0-9)**: Select menu options
- **Enter**: Confirm selections
- **Any key**: Continue after operations
- **Ctrl+C**: Force quit (if available)

#### Input Guidelines
- **Text input**: Type and press Enter
- **Numeric input**: Enter number and press Enter
- **Confirmation**: Type 'y' or 'n' and press Enter
- **Invalid input**: System will prompt for correction

### Best Practices

#### Data Entry
1. Use consistent naming conventions
2. Enter complete metadata when adding songs
3. Use appropriate ratings (1-5 stars)
4. Include album and genre information

#### System Management
1. Regular system health checks
2. Periodic data exports
3. Monitor performance metrics
4. Clear unnecessary data periodically

#### Playlist Management
1. Use descriptive playlist names
2. Organize songs logically
3. Use sorting features appropriately
4. Backup important playlists

---

## Conclusion

This comprehensive user guide covers every operation and option available in the PlayWise system. Each feature is designed to be intuitive and user-friendly, with clear feedback and error handling.

### Key Takeaways
- **Navigation**: Use number keys to navigate menus
- **Validation**: All inputs are validated for correctness
- **Feedback**: Clear confirmation messages for all operations
- **Safety**: Confirmation prompts for destructive operations
- **Performance**: Real-time performance monitoring available

### Getting Help
- Use the dashboard for system health monitoring
- Export data regularly as backup
- Monitor performance metrics for optimization
- Use the troubleshooting section for common issues

The PlayWise system is designed to be both powerful and user-friendly, providing comprehensive music management capabilities while maintaining simplicity of use. 