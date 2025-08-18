# Console Snake C++
🐍 Classic Snake game in C++ that runs in Windows/Linux console - zero dependencies, just compile and play!

## Features
- Classic Snake gameplay with WASD controls
- **High Score System** - Persistent score storage in local file
- **Difficulty Levels** - Easy/Normal/Hard speed settings
- Cross-platform support (Windows/Linux/macOS)
- Simple console-based graphics
- Zero external dependencies

## How to Play
1. Run the game and choose your difficulty level (1-3)
2. Use **W, A, S, D** keys to move the snake
3. Eat the food (*) to grow and increase your score
4. Avoid hitting walls or yourself
5. Press **Q** to quit

## Building and Running

### Linux/macOS
```bash
make
./snake
```

### Windows
```bash
g++ -std=c++11 -o snake.exe snake.cpp
snake.exe
```

### Manual compilation
```bash
g++ -std=c++11 -Wall -Wextra -o snake snake.cpp
```

## Game Controls
- **W** - Move up
- **A** - Move left  
- **S** - Move down
- **D** - Move right
- **Q** - Quit game

## Difficulty Levels
- **Easy** - Slow speed, good for beginners
- **Normal** - Medium speed, balanced gameplay
- **Hard** - Fast speed, challenging for experts

## Scoring
- Each food item eaten: +10 points
- High scores are automatically saved to `highscore.txt`
- Challenge yourself to beat your personal best!

## Roadmap
This implementation provides a foundation for many exciting features planned:
- Color support for enhanced visuals  
- Sound effects and game statistics
- Power-ups and special game modes
- Pause/resume functionality
- Multiplayer support

See [Issue #4](../../issues/4) for the complete roadmap!

## Project Structure
```
console-snake-cpp/
├── snake.h          # Game class header
├── snake.cpp        # Main game implementation  
├── Makefile         # Build configuration
├── README.md        # This file
└── highscore.txt    # Persistent high score (auto-generated)
```

## Contributing
Contributions are welcome! Check out our roadmap and feel free to implement any of the planned features.

## License
MIT License - see [LICENSE](LICENSE) file for details.
