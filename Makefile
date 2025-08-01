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

# Target executable
TARGET = $(BINDIR)/playwise

# Default target
all: $(TARGET)

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

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
	@echo "  run          - Build and run the program"
	@echo "  clean        - Remove build files"
	@echo "  rebuild      - Clean and rebuild"
	@echo "  install-deps - Install dependencies (Ubuntu/Debian)"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Usage:"
	@echo "  make         - Build the project"
	@echo "  make run     - Build and run"
	@echo "  make clean   - Clean build files"

# Phony targets
.PHONY: all run clean rebuild install-deps install-deps-windows install-deps-macos help 