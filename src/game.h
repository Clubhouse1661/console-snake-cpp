#pragma once
#include "snake.h"
#include "food.h"
#include "console.h"
#include "utils.h"
#include <string>

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    HIGH_SCORE_ENTRY,
    EXIT
};

enum Difficulty {
    EASY,
    NORMAL,
    HARD
};

class Game {
private:
    Console console;
    Snake snake;
    Food food;
    GameState state;
    Difficulty difficulty;
    
    // Game variables
    int score;
    int highScore;
    int level;
    int speed;
    int gameWidth;
    int gameHeight;
    int borderWidth;
    int borderHeight;
    
    // Timing
    int frameDelay;
    int frameCounter;
    bool frameReady;
    
    // Player info
    std::string playerName;
    
    // Game loop
    void gameLoop();
    void update();
    void render();
    void handleInput();
    void processCollisions();
    
    // Menu system
    void showMainMenu();
    void showDifficultyMenu();
    void showPauseMenu();
    void showGameOverMenu();
    void showHighScoreEntry();
    void showHighScores();
    
    // Game initialization
    void initializeGame();
    void resetGame();
    void setupGameArea();
    
    // Difficulty management
    void setDifficulty(Difficulty diff);
    int getFrameDelay() const;
    std::string getDifficultyName() const;
    
    // UI rendering
    void drawBorder();
    void drawScore();
    void drawGameInfo();
    void drawInstructions();
    void clearGameArea();
    
    // Game logic
    void checkFoodCollision();
    void checkGameOver();
    void increaseScore(int points);
    void increaseLevel();
    
public:
    Game();
    ~Game();
    
    // Main game functions
    bool initialize();
    void run();
    void cleanup();
    
    // Game state management
    void setState(GameState newState);
    GameState getState() const;
    
    // Game properties
    int getScore() const;
    int getHighScore() const;
    int getLevel() const;
    Difficulty getDifficulty() const;
    
    // Player management
    void setPlayerName(const std::string& name);
    std::string getPlayerName() const;
    
    // Utility
    bool isRunning() const;
    void pause();
    void resume();
};
