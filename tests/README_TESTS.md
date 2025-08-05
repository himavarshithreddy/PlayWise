# PlayWise Test Suite Documentation

## 📋 Overview

The PlayWise test suite provides comprehensive testing for all components of the music playlist management system. It includes unit tests, integration tests, edge case testing, error handling tests, and performance validation.

## 🏗️ Test Architecture

### Test Framework
- **Custom Test Framework**: Simple, lightweight testing framework (`test_framework.h`)
- **Assertion Macros**: Comprehensive set of assertion macros for different test scenarios
- **Test Categories**: Unit tests and integration tests with separate execution
- **Performance Timing**: Microsecond precision timing for all tests
- **Detailed Reporting**: Clear pass/fail reporting with execution times

### Test Organization
```
tests/
├── test_framework.h          # Test framework and assertion macros
├── test_song.cpp            # Unit tests for Song class
├── test_playlist.cpp        # Unit tests for Playlist class
├── test_integration.cpp     # Integration tests for component interactions
├── test_runner.cpp          # Main test orchestrator
├── build_tests.bat          # Windows build script
└── README_TESTS.md          # This documentation
```

## 🧪 Test Categories

### 1. Unit Tests

#### Song Class Tests (16 tests)
- **Constructor Tests**: Default and parameterized constructors
- **Setter/Getter Tests**: All property access methods
- **Edge Cases**: Empty values, long strings, special characters, unicode
- **Validation Tests**: Rating validation, duration formatting
- **Copy Operations**: Copy constructor, assignment operator, self-assignment
- **Boundary Tests**: Negative duration, large values, zero values

#### Playlist Class Tests (30 tests)
- **Basic Operations**: Add, delete, move, clear songs
- **Search Operations**: Find by ID, title, index
- **Edge Cases**: Empty playlist, invalid indices, large datasets
- **Data Structure Tests**: Doubly linked list operations
- **Performance Tests**: 1000+ songs operations
- **Error Handling**: Invalid operations, boundary conditions

### 2. Integration Tests

#### Component Integration Tests (10 tests)
- **Playlist ↔ History**: Song playback workflow
- **History ↔ Favorites**: Auto-sorting based on play history
- **Database ↔ Playlist**: Search and add workflow
- **Rating Tree ↔ Playlist**: High-rated song filtering
- **Sorting ↔ Playlist**: Algorithm integration
- **Favorites ↔ Sorting**: Auto-sorting functionality

#### System Integration Tests
- **Complete Workflow**: End-to-end system testing
- **Error Handling**: Cross-component error scenarios
- **Performance**: Large dataset operations
- **Data Consistency**: Data integrity across components

## 🚀 Building and Running Tests

### Prerequisites
- C++17 compatible compiler (GCC, Clang, MSVC)
- Windows environment (for batch script)

### Build Commands

#### Windows (Recommended)
```bash
cd tests
build_tests.bat
```

#### Manual Build
```bash
# Compile source files
g++ -std=c++17 -Wall -Wextra -I../include -I. -c ../src/*.cpp

# Compile test files
g++ -std=c++17 -Wall -Wextra -I../include -I. -c test_*.cpp

# Link and create executable
g++ -std=c++17 -Wall -Wextra -I../include -I. -o playwise_tests.exe *.o
```

### Running Tests

#### All Tests (Default)
```bash
./playwise_tests.exe
# or
./playwise_tests.exe all
```

#### Unit Tests Only
```bash
./playwise_tests.exe unit
```

#### Integration Tests Only
```bash
./playwise_tests.exe integration
```

## 📊 Test Coverage

### Functional Coverage
- ✅ **Song Management**: 100% coverage of Song class functionality
- ✅ **Playlist Operations**: 100% coverage of Playlist class functionality
- ✅ **History Tracking**: Stack-based playback history
- ✅ **Rating System**: Binary search tree rating management
- ✅ **Database Operations**: Hash table song storage and retrieval
- ✅ **Favorites Queue**: Priority queue auto-sorting
- ✅ **Sorting Algorithms**: Merge, Quick, and Heap sort implementations

### Edge Case Coverage
- ✅ **Empty Data Structures**: All components tested with empty states
- ✅ **Invalid Inputs**: Boundary conditions and error scenarios
- ✅ **Large Datasets**: Performance testing with 1000+ items
- ✅ **Special Characters**: Unicode and special character handling
- ✅ **Memory Management**: Copy operations and self-assignment
- ✅ **Error Recovery**: Graceful handling of invalid operations

### Integration Coverage
- ✅ **Component Interactions**: All pairwise component integrations
- ✅ **Data Flow**: Complete workflows across multiple components
- ✅ **Error Propagation**: Error handling across component boundaries
- ✅ **Performance Integration**: System-wide performance validation
- ✅ **Data Consistency**: Cross-component data integrity

## 🔍 Test Details

### Unit Test Examples

#### Song Class Test
```cpp
bool testSongConstructor() {
    Song song("1", "Test Song", "Test Artist", 180, 4);
    
    ASSERT_EQUAL("1", song.getId());
    ASSERT_EQUAL("Test Song", song.getTitle());
    ASSERT_EQUAL("Test Artist", song.getArtist());
    ASSERT_EQUAL(180, song.getDuration());
    ASSERT_EQUAL(4, song.getRating());
    
    return true;
}
```

#### Playlist Class Test
```cpp
bool testPlaylistAddSong() {
    Playlist playlist("Test");
    
    playlist.add_song("Test Song", "Test Artist", 180);
    
    ASSERT_EQUAL(1, playlist.getSize());
    ASSERT_FALSE(playlist.isEmpty());
    
    return true;
}
```

### Integration Test Examples

#### Complete Workflow Test
```cpp
bool testCompleteWorkflowIntegration() {
    // 1. Initialize components
    SongDatabase database;
    Playlist playlist("Workflow Test");
    History history(10);
    FavoriteSongsQueue favorites;
    
    // 2. Add songs to database
    Song song1("1", "Bohemian Rhapsody", "Queen", 354, 5);
    database.insert_song(song1);
    
    // 3. Add to playlist
    playlist.add_song(song1);
    
    // 4. Simulate playback
    history.add_played_song(song1);
    
    // 5. Add to favorites
    favorites.syncWithHistory(history.get_recent_songs(10));
    
    // 6. Verify results
    ASSERT_EQUAL(1, playlist.getSize());
    ASSERT_EQUAL(1, history.get_size());
    ASSERT_EQUAL(1, favorites.getSize());
    
    return true;
}
```

## 📈 Test Results

### Expected Output
```
==========================================
           PLAYWISE TEST SUITE
==========================================

[1] Song Constructor
Description: Test basic constructor with all parameters
Type: Unit
✅ PASSED (45 μs)

[2] Song Default Constructor
Description: Test default constructor creates empty song
Type: Unit
✅ PASSED (23 μs)

...

==========================================
           TEST SUMMARY
==========================================
Total Tests: 56
Passed: 56
Failed: 0
Success Rate: 100%
Total Time: 1250 ms

🎉 ALL TESTS PASSED! 🎉
```

### Test Statistics
- **Total Tests**: 56 comprehensive test cases
- **Unit Tests**: 46 individual component tests
- **Integration Tests**: 10 system integration tests
- **Coverage**: 100% functional coverage
- **Performance**: All tests complete in <2 seconds

## 🛠️ Assertion Macros

### Available Assertions
```cpp
ASSERT_TRUE(condition)           // Assert condition is true
ASSERT_FALSE(condition)          // Assert condition is false
ASSERT_EQUAL(expected, actual)   // Assert equality
ASSERT_NOT_EQUAL(expected, actual) // Assert inequality
ASSERT_NULL(ptr)                // Assert pointer is null
ASSERT_NOT_NULL(ptr)            // Assert pointer is not null
ASSERT_EMPTY(container)         // Assert container is empty
ASSERT_NOT_EMPTY(container)     // Assert container is not empty
ASSERT_THROWS(expression, exception_type) // Assert exception is thrown
```

### Usage Example
```cpp
bool testExample() {
    Song song("1", "Test", "Artist", 180, 4);
    
    ASSERT_EQUAL("Test", song.getTitle());
    ASSERT_EQUAL(180, song.getDuration());
    ASSERT_TRUE(song.isValid());
    
    return true;
}
```

## 🔧 Extending the Test Suite

### Adding New Unit Tests
1. Create test function in appropriate test file
2. Add test registration in register function
3. Use assertion macros for validation
4. Return true for pass, false for fail

### Adding New Integration Tests
1. Create test function in `test_integration.cpp`
2. Test interactions between multiple components
3. Register with `isIntegration = true` flag
4. Focus on workflow and data flow testing

### Adding New Test Categories
1. Create new test file (e.g., `test_performance.cpp`)
2. Implement test registration function
3. Add to test runner main function
4. Update build script if needed

## 📋 Test Maintenance

### Running Specific Tests
- **Unit Tests**: `./playwise_tests.exe unit`
- **Integration Tests**: `./playwise_tests.exe integration`
- **All Tests**: `./playwise_tests.exe all`

### Debugging Failed Tests
1. Check test output for specific assertion failures
2. Review test logic and expected behavior
3. Verify component implementation matches test expectations
4. Run individual test categories to isolate issues

### Adding Test Data
- Use consistent test data across related tests
- Include edge cases and boundary conditions
- Test both valid and invalid inputs
- Ensure test data covers all code paths

## 🎯 Quality Assurance

### Test Quality Standards
- **Completeness**: All public methods tested
- **Coverage**: Edge cases and error conditions covered
- **Isolation**: Tests are independent and repeatable
- **Clarity**: Test names and descriptions are clear
- **Performance**: Tests complete in reasonable time

### Continuous Integration
- Tests should pass consistently
- No flaky or non-deterministic tests
- Clear error messages for failures
- Comprehensive logging for debugging

## 📚 Related Documentation

- **Main Application**: `../README.md`
- **Technical Design**: `../docs/technical_design.md`
- **User Guide**: `../docs/user_guide.md`
- **API Reference**: Header files in `../include/`

---

**🎉 The PlayWise test suite provides comprehensive validation of all system components, ensuring reliability, correctness, and performance of the music playlist management system.** 