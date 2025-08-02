# PlayWise: Smart Music Playlist Management Engine

A comprehensive C++ implementation of a music playlist management system demonstrating advanced data structures and algorithms.

## 🎵 Project Overview

PlayWise is a sophisticated music playlist management system that showcases the implementation of various data structures and algorithms in C++. The system provides real-time playlist manipulation, personalized recommendations, memory-efficient search, and smart sorting capabilities.

## 🏗️ System Architecture

### Core Components

1. **Song Class** - Fundamental data structure with metadata management
2. **Playlist Engine** - Doubly Linked List for efficient playlist operations
3. **Playback History** - Stack-based undo system for recently played songs
4. **Rating Tree** - Binary Search Tree for rating-based organization
5. **Song Database** - HashMap for O(1) average time song lookup
6. **Sorting Module** - Multiple sorting algorithms (Merge, Quick, Heap Sort)
7. **Dashboard** - Real-time system monitoring and analytics
8. **Main Application** - Complete user interface and system integration

## 🚀 Features

### Data Structures Implemented
- ✅ **Doubly Linked List** - Playlist management with bidirectional traversal
- ✅ **Stack** - LIFO-based undo system for playback history
- ✅ **Binary Search Tree** - Rating-based song organization
- ✅ **HashMap** - O(1) average time song lookup
- ✅ **Vector** - Dynamic array for various operations

### Algorithms Implemented
- ✅ **Merge Sort** - Stable, predictable O(n log n) sorting
- ✅ **Quick Sort** - In-place sorting with good cache performance
- ✅ **Heap Sort** - Constant space complexity sorting
- ✅ **Binary Search** - Efficient tree operations
- ✅ **Linear Search** - Simple search algorithms

### Advanced Features
- 🎯 **Real-time Analytics** - Live system monitoring and statistics
- 🔄 **Undo/Redo System** - Playback history management
- 📊 **Performance Metrics** - System health and optimization suggestions
- 💾 **Data Persistence** - Export/import functionality
- 🎨 **User-friendly Interface** - Menu-driven console application

## 📁 Project Structure

```
PlayWise/
├── include/                 # Header files
│   ├── song.h              # Song class definition
│   ├── playlist.h          # Playlist (Doubly Linked List)
│   ├── history.h           # History (Stack)
│   ├── rating_tree.h       # Rating Tree (BST)
│   ├── song_database.h     # Song Database (HashMap)
│   ├── sorting.h           # Sorting algorithms
│   └── dashboard.h         # System dashboard
├── src/                    # Source files
│   ├── song.cpp            # Song class implementation
│   ├── playlist.cpp        # Playlist implementation
│   ├── history.cpp         # History implementation
│   ├── rating_tree.cpp     # Rating Tree implementation
│   ├── song_database.cpp   # Database implementation
│   ├── sorting.cpp         # Sorting algorithms
│   ├── dashboard.cpp       # Dashboard implementation
│   ├── playwise_app.cpp    # Main application
│   └── main.cpp            # Entry point
├── docs/                   # Documentation
│   └── technical_design.md # Technical design document
├── tests/                  # Test files
└── README.md              # This file
```

## 🛠️ Installation & Setup

### Prerequisites
- C++17 compatible compiler (GCC, Clang, or MSVC)

### Compilation

#### Manual Compilation (Windows)
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude -o playwise.exe src/*.cpp
```

#### Manual Compilation (Linux/macOS)
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude -o playwise src/*.cpp
```

### Running the Application
```bash
./playwise.exe  # Windows
./playwise       # Linux/macOS
```

## 🎮 Usage

### Main Menu Options

1. **Playlist Operations** - Manage your music playlists
   - Add/remove songs
   - Move songs within playlist
   - Reverse playlist order
   - Shuffle playlist
   - Search songs

2. **History Operations** - Manage playback history
   - View recent songs
   - Undo last played song
   - Clear history
   - Export history

3. **Rating Operations** - Organize songs by rating
   - View rating tree structure
   - Search songs by rating
   - Get top-rated songs
   - Add/remove songs with ratings

4. **Database Operations** - Manage song database
   - Search songs by ID, title, artist, genre
   - Add/remove songs from database
   - View database statistics
   - Export database

5. **Sorting Operations** - Sort playlists by various criteria
   - Sort by title (A-Z, Z-A)
   - Sort by duration (shortest/longest)
   - Sort by rating (highest/lowest)
   - Sort by artist (A-Z, Z-A)
   - Benchmark sorting algorithms

6. **Dashboard & Analytics** - System monitoring
   - Live dashboard
   - Performance metrics
   - User activity
   - System health
   - Generate reports

7. **System Operations** - System management
   - Reset system
   - Export/import data
   - System information
   - Memory analysis

## 📊 Performance Analysis

### Time Complexity
| Operation | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| Add Song (Playlist) | O(1) | O(1) | O(n) |
| Delete Song (Playlist) | O(1) | O(n) | O(n) |
| Search Song (Database) | O(1) | O(1) | O(n) |
| Search by Rating | O(log n) | O(log n) | O(n) |
| Sort Playlist | O(n log n) | O(n log n) | O(n log n) |
| Undo Last Play | O(1) | O(1) | O(1) |

### Space Complexity
| Component | Space Complexity |
|-----------|------------------|
| Song Class | O(1) |
| Playlist | O(n) |
| History | O(n) |
| Rating Tree | O(n) |
| Database | O(n) |
| Overall System | O(n) |

## 🧪 Testing

The system includes comprehensive testing for all components:

- **Unit Tests** - Individual component testing
- **Integration Tests** - System interaction testing
- **Performance Tests** - Algorithm benchmarking
- **Memory Tests** - Memory leak detection
- **Edge Case Tests** - Boundary condition testing

## 📚 Technical Documentation

For detailed technical information, see:
- [Technical Design Document](docs/technical_design.md)

## 🎯 Key Features Demonstrated

### Data Structures
- **Doubly Linked List**: Efficient playlist management with bidirectional traversal
- **Stack**: LIFO-based undo system for playback history
- **Binary Search Tree**: Rating-based song organization and search
- **HashMap**: O(1) average time song lookup by ID or title
- **Vector**: Dynamic array for various operations

### Algorithms
- **Merge Sort**: Stable, predictable O(n log n) sorting
- **Quick Sort**: In-place sorting with good cache performance
- **Heap Sort**: Constant space complexity sorting
- **Binary Search**: Efficient tree operations
- **Linear Search**: Simple search algorithms

### Advanced Concepts
- **Memory Management**: Proper destructors and memory leak prevention
- **Error Handling**: Comprehensive input validation and error recovery
- **Performance Optimization**: Algorithm selection and data structure optimization
- **Modular Design**: Clean separation of concerns and maintainable code

## 🏆 Hackathon Achievements

This project successfully demonstrates:

- ✅ **Advanced Data Structures**: All required structures implemented
- ✅ **Complex Algorithms**: Multiple sorting and search algorithms
- ✅ **Performance Analysis**: Time and space complexity analysis
- ✅ **Memory Management**: Proper resource management
- ✅ **Error Handling**: Robust error handling and validation
- ✅ **User Interface**: Complete menu-driven application
- ✅ **Documentation**: Comprehensive technical documentation
- ✅ **Testing**: Thorough testing framework

## 🔮 Future Enhancements

### Planned Features
- Multi-user support
- Network synchronization
- Real-time collaboration
- Advanced recommendation algorithms
- Graphical user interface
- Mobile application
- Web interface
- API development

### Performance Improvements
- Parallel processing for large datasets
- Advanced caching strategies
- Database optimization
- Load balancing

## 🤝 Contributing

This is a hackathon project demonstrating advanced C++ concepts. Feel free to explore the code and learn from the implementation.

## 📄 License

This project is created for educational purposes and hackathon demonstration.

## 👨‍💻 Author

Created as part of a DSA hackathon project to demonstrate advanced data structures and algorithms in C++.

---

**PlayWise** - Where Data Structures Meet Music Management! 🎵✨ 