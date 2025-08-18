# Source Code Directory

This directory will contain the C++ source code for the Console Snake game.

## 📁 Planned File Structure

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

- **CMakeLists.txt**: CMake build configuration (planned)
- **Makefile**: Alternative build system (optional)

## 🪟 Windows Console Implementation

The game will utilize:
- **Windows Console API** for terminal manipulation
- **No external dependencies** - pure C++ and Windows SDK
- **Compatible** with Command Prompt and Windows Terminal
- **Lightweight** design for optimal performance

## 🎮 Game Architecture

### Core Components
1. **Game Loop**: Main game logic and timing
2. **Snake Entity**: Movement, growth, and collision
3. **Food System**: Random generation and consumption
4. **Console Interface**: Screen buffer management
5. **Input Handler**: Keyboard input processing

### Design Principles
- **Zero dependencies**: Uses only standard C++ and Windows API
- **Terminal-based**: Designed for console/terminal environment
- **Efficient**: Minimal resource usage and fast execution
- **Portable**: Clean separation of platform-specific code