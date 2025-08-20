# Source Code Directory

This directory contains the C++ source code for the Console Snake game.

## 📁 File Structure

```
src/
├── main.cpp         # Entry point and game initialization
├── game.cpp/.h      # Core game logic and state management  
├── snake.cpp/.h     # Snake entity and movement logic
├── food.cpp/.h      # Food generation and collision detection
├── console.cpp/.h   # Windows console API wrapper
└── utils.cpp/.h     # Utility functions and helpers
```

## 🛠️ Build System

- **CMakeLists.txt**: CMake build configuration
- **build.bat**: Windows batch build script
- **run_game.bat**: Easy game launcher

## 🪟 Windows Console Implementation

The game utilizes:
- **Windows Console API** for terminal manipulation
- **No external dependencies** - pure C++ and Windows SDK
- **Compatible** with Command Prompt and Windows Terminal
- **Lightweight** design for optimal performance

## 🎮 Game Features

### ✅ Implemented Features
1. **High Score System**: Persistent score storage in local file
2. **Difficulty Levels**: Easy/Normal/Hard speed settings
3. **Color Support**: Enhanced console colors for better visuals
4. **Sound Effects**: Console beep integration for eating/game over
5. **Menu System**: Interactive menus with navigation
6. **Game States**: Menu, Playing, Paused, Game Over states
7. **Collision Detection**: Wall and self-collision handling
8. **Score Tracking**: Real-time score and level progression

### Core Components
1. **Game Loop**: Main game logic and timing
2. **Snake Entity**: Movement, growth, and collision
3. **Food System**: Random generation and consumption
4. **Console Interface**: Screen buffer management
5. **Input Handler**: Keyboard input processing
6. **High Score Manager**: File-based score persistence

### Design Principles
- **Zero dependencies**: Uses only standard C++ and Windows API
- **Terminal-based**: Designed for console/terminal environment
- **Efficient**: Minimal resource usage and fast execution
- **Portable**: Clean separation of platform-specific code