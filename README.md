# 🐍 Console Snake C++

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/Platform-Windows-blue.svg)](https://www.microsoft.com/windows)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Console](https://img.shields.io/badge/Console-Terminal-green.svg)](https://docs.microsoft.com/en-us/windows/terminal/)

Classic Snake game implemented in **C++** that runs directly in the **Windows console terminal**. Zero dependencies, lightweight, and ready to play - just double-click to start!

## 🎮 Features

- **Pure C++** implementation with no external dependencies
- **Windows console** based - runs in Command Prompt or Windows Terminal
- **Lightweight** and fast - minimal resource usage
- **Easy to run** - no installation required, just execute
- **Classic gameplay** - nostalgic Snake game experience
- **Cross-compile ready** - designed for CMake build system

### 🏆 High Score System
- Persistent score storage in local file (`highscores.txt`)
- Automatic high score detection and entry
- View top 10 high scores from main menu
- Player name entry for new records

### ⚡ Difficulty Levels
- **Easy**: Slow speed (200ms frame delay)
- **Normal**: Medium speed (150ms frame delay) 
- **Hard**: Fast speed (100ms frame delay)
- Dynamic speed increase as levels progress

### 🎨 Color Support
- Enhanced console colors for better visuals
- Different colors for snake head, body, and food
- Color-coded UI elements and menus
- Bright colors for important information

### 🔊 Sound Effects
- Console beep integration for eating food
- Game over sound effects
- Different frequencies for different events
- Optional movement sounds (commented out)

## 🛠️ Technical Details

- **Language**: C++
- **Platform**: Windows
- **Terminal**: Console application for Windows Command Prompt/Terminal
- **Dependencies**: None (no-dependencies)
- **Build System**: CMake (planned)
- **Game Type**: Console-based arcade game

## 🚀 Quick Start

### Option 1: Run Pre-built Executable
1. Download `ConsoleSnakeCpp.exe`
2. Double-click to run or use `run_game.bat`
3. Use arrow keys to control the snake
4. Eat food to grow and increase your score
5. Avoid hitting walls or yourself!

### Option 2: Build from Source
1. Ensure you have GCC installed
2. Run `build.bat` to compile the game
3. Run `run_game.bat` to start playing

### 🎮 Game Controls
- **Arrow Keys**: Move snake
- **Space/ESC**: Pause game
- **Number Keys**: Navigate menus
- **Enter**: Confirm selections

## 🎯 Game Development

This project showcases:
- **Console game development** in C++
- **Terminal graphics** and input handling
- **Game loop** implementation
- **No-dependency** C++ programming
- **Windows console** API usage

## 📁 Project Structure

```
console-snake-cpp/
├── LICENSE             # MIT License
├── README.md           # Project documentation
├── REPOSITORY_SETUP.md # GitHub repository configuration guide
├── CMakeLists.txt      # CMake build configuration
├── .gitignore          # Git ignore rules
├── docs/               # Documentation directory
├── src/                # Source code directory (planned)
└── scripts/            # Utility scripts
    ├── verify-metadata.py  # Repository metadata verification
    └── README.md           # Scripts documentation
```

## 🏷️ Topics

`cpp` `cplusplus` `game` `console` `snake` `cmake` `windows` `terminal` `gamedev` `no-dependencies`

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features  
- Submit pull requests
- Improve documentation

### 📋 Repository Setup

For repository administrators, see:
- **[METADATA_CHECKLIST.md](METADATA_CHECKLIST.md)** - Complete configuration checklist
- **[REPOSITORY_SETUP.md](REPOSITORY_SETUP.md)** - Detailed setup guide
- **[scripts/verify-metadata.py](scripts/verify-metadata.py)** - Automated verification tool

---

*A simple, fun C++ console game perfect for learning game development and terminal programming.*
