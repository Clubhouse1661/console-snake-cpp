# Makefile for Console Snake Game
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = snake
SOURCES = snake.cpp
HEADERS = snake.h

# Default target
all: $(TARGET)

# Build the game
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe *.txt

# Install dependencies (placeholder for future use)
install:
	@echo "No dependencies to install - zero dependency game!"

# Run the game
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install run