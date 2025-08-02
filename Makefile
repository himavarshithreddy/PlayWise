# PlayWise Music Playlist Management System Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2
INCLUDES = -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Demo source files (excluding main.cpp for demo)
DEMO_SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(wildcard $(SRCDIR)/*.cpp)) $(SRCDIR)/demo_auto_sort.cpp
DEMO_OBJECTS = $(DEMO_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Test source files
TEST_SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(wildcard $(SRCDIR)/*.cpp)) tests/test_auto_sort.cpp
TEST_OBJECTS = $(TEST_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o) $(OBJDIR)/test_auto_sort.o

# Target executables
TARGET = $(BINDIR)/playwise
DEMO_TARGET = $(BINDIR)/auto_sort_demo
TEST_TARGET = $(BINDIR)/auto_sort_test

# Default target
all: $(TARGET) $(DEMO_TARGET) $(TEST_TARGET)

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile test object files
$(OBJDIR)/%.o: tests/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link main executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Link demo executable
$(DEMO_TARGET): $(DEMO_OBJECTS) | $(BINDIR)
	$(CXX) $(DEMO_OBJECTS) -o $(DEMO_TARGET)

# Link test executable
$(TEST_TARGET): $(TEST_OBJECTS) | $(BINDIR)
	$(CXX) $(TEST_OBJECTS) -o $(TEST_TARGET)

# Run the main program
run: $(TARGET)
	./$(TARGET)

# Run the auto-sorting demo
demo: $(DEMO_TARGET)
	./$(DEMO_TARGET)

# Run the auto-sorting tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Clean and rebuild
rebuild: clean all

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y build-essential g++

# Install dependencies (for Windows with Chocolatey)
install-deps-windows:
	choco install mingw

# Install dependencies (for macOS with Homebrew)
install-deps-macos:
	brew install gcc

# Help target
help:
	@echo "PlayWise Music Playlist Management System"
	@echo "========================================"
	@echo "Available targets:"
	@echo "  all          - Build the project (default)"
	@echo "  run          - Build and run the main program"
	@echo "  demo         - Build and run the auto-sorting demo"
	@echo "  test         - Build and run the auto-sorting tests"
	@echo "  clean        - Remove build files"
	@echo "  rebuild      - Clean and rebuild"
	@echo "  install-deps - Install dependencies (Ubuntu/Debian)"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Usage:"
	@echo "  make         - Build the project"
	@echo "  make run     - Build and run main program"
	@echo "  make demo    - Build and run auto-sorting demo"
	@echo "  make test    - Build and run auto-sorting tests"
	@echo "  make clean   - Clean build files"
	@echo ""
	@echo "Auto-Sorting Features:"
	@echo "  - Priority Queue (Max Heap) implementation"
	@echo "  - Auto-sorting by listening duration"
	@echo "  - Real-time updates and reordering"
	@echo "  - Multi-level sorting (time, play count, title)"
	@echo "  - Statistics and analytics"
	@echo "  - Comprehensive test suite"

# Phony targets
.PHONY: all run demo test clean rebuild install-deps install-deps-windows install-deps-macos help 