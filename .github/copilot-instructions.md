# Console Snake C++

Console Snake C++ is a classic Snake game implementation in C++ designed to run in Windows console. This repository is currently in early development - the core game source files have not yet been implemented.

Always reference these instructions first and fallback to search or bash commands only when you encounter unexpected information that does not match the info here.

## Repository Status

**IMPORTANT**: This repository currently contains only basic project files (README, LICENSE, .gitignore) with no actual game source code. The Snake game implementation needs to be developed.

## Working Effectively

### Development Environment
- **Platform**: Designed for Windows console, but can be developed/tested on Linux
- **Current Development Platform**: Ubuntu 24.04.2 LTS with g++ 13.3.0
- **Required Tools**: 
  - C++ compiler (g++ available at `/usr/bin/g++`)
  - Make build system (available at `/usr/bin/make`)
  - CMake (available at `/usr/local/bin/cmake`)

### Building and Testing
**Current repository state**: No source files exist yet - building will fail until source code is implemented.

#### When source code exists, use these validated commands:

- **Simple compilation**: 
  - `g++ -std=c++11 -Wall -O2 -o snake main.cpp` 
  - Build time: < 1 second for simple programs
  - NEVER CANCEL: Even complex builds should complete in under 10 seconds

- **Using Make** (requires Makefile):
  - `make`
  - Build time: < 1 second for typical single-file programs
  - NEVER CANCEL: Set timeout to 30+ seconds for safety

- **Using CMake** (requires CMakeLists.txt):
  - `mkdir -p build && cd build`
  - `cmake ..` -- Configuration takes ~1-2 seconds
  - `make` -- Build takes < 1 second for simple programs
  - NEVER CANCEL: Set timeout to 60+ seconds for cmake configuration, 30+ seconds for build

### Testing and Validation
- **Manual Testing**: Run the compiled executable directly: `./snake`
- **Expected Output**: Since this is a console game, expect text-based interface
- **Platform Note**: Game is designed for Windows console - on Linux, expect basic functionality but may lack Windows-specific console features

### Standard C++ Development Workflow
1. **Create source files**: Typically `main.cpp` and header files as needed
2. **Choose build system**: Direct g++ compilation, Makefile, or CMakeLists.txt
3. **Compile**: Use appropriate build command from above
4. **Test**: Run executable and validate functionality
5. **Iterate**: Make changes and rebuild

## Common Tasks

### Current Repository Structure
```
.
├── .git/           # Git repository data
├── .gitignore      # C++ build artifacts exclusion
├── LICENSE         # MIT license
└── README.md       # Basic project description
```

### Expected Project Structure (when implemented)
```
.
├── src/            # Source code directory
│   ├── main.cpp    # Main game entry point
│   ├── snake.h     # Snake class header
│   ├── snake.cpp   # Snake class implementation
│   └── game.h      # Game logic header
├── Makefile        # Build configuration
└── README.md       # Project documentation
```

### Compilation Standards
- **C++ Standard**: Use C++11 minimum (`-std=c++11`)
- **Compiler Flags**: Use `-Wall -O2` for warnings and optimization
- **Dependencies**: Project is designed to have zero external dependencies

### Typical Console Game Requirements
- Include `<iostream>` for basic I/O
- Include `<vector>`, `<string>` for STL containers
- For Windows console: May need `<windows.h>` and `<conio.h>` (not available on Linux)
- For cross-platform: Use standard C++ I/O instead of Windows-specific functions

## Platform-Specific Notes

### Linux Development (Current Environment)
- All basic C++ compilation works correctly
- Console manipulation will be limited compared to Windows
- Good for core game logic development and testing

### Windows Console (Target Platform)
- Full console manipulation features available
- `<conio.h>` for keyboard input without Enter
- `<windows.h>` for console screen buffer manipulation
- Direct executable (.exe) can be double-clicked to run

## Validation Scenarios

When implementing the Snake game, always test:
1. **Compilation**: Code compiles without errors or warnings
2. **Basic Execution**: Program starts and displays initial game state
3. **Input Handling**: Game responds to keyboard input (arrow keys, WASD, etc.)
4. **Game Logic**: Snake moves, grows when eating food, detects collisions
5. **Exit Condition**: Game ends properly and returns to console

## Failed Commands Documentation

- **No current build failures**: All tested compilation commands work correctly
- **Windows-specific code**: Cannot test Windows console APIs on Linux development environment
- **GUI Libraries**: Not applicable - this is a console-only application

## Development Tips

- Start with basic C++ structure and console output
- Implement game loop with simple text display first
- Add input handling incrementally
- Test frequently with the validation scenarios above
- Keep the "zero dependencies" design goal - avoid external libraries

## File Locations

- **Main entry point**: `src/main.cpp` (when created)
- **Core game logic**: `src/snake.cpp` and `src/game.cpp` (when created)
- **Build files**: `Makefile` or `CMakeLists.txt` in repository root
- **Documentation**: `README.md` in repository root