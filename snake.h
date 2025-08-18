#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

// Game constants
const int BOARD_WIDTH = 40;
const int BOARD_HEIGHT = 20;
const std::string HIGH_SCORE_FILE = "highscore.txt";

// Direction enum
enum Direction {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

// Difficulty levels
enum Difficulty {
    EASY = 250,    // Slow speed
    NORMAL = 150,  // Normal speed
    HARD = 75      // Fast speed
};

// Position structure
struct Position {
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class SnakeGame {
private:
    std::vector<Position> snake;
    Position food;
    Direction direction;
    int score;
    int highScore;
    bool gameOver;
    Difficulty difficulty;
    
#ifndef _WIN32
    struct termios oldTermios;
    
    void enableRawMode();
    void disableRawMode();
    bool kbhit();
    char getch();
#endif
    
    void generateFood();
    bool isSnakePosition(const Position& pos);
    void clearScreen();
    void sleepMs(int ms);
    void loadHighScore();
    void saveHighScore();
    Difficulty chooseDifficulty();

public:
    SnakeGame();
    ~SnakeGame();
    
    void draw();
    void input();
    void logic();
    void run();
    
    bool isGameOver() const;
    int getScore() const;
    int getHighScore() const;
};

#endif // SNAKE_GAME_H