#include "game.h"
#include <iostream>
#include <sstream>

Game::Game() 
    : state(MENU), difficulty(NORMAL), score(0), highScore(0), level(1), speed(1),
      gameWidth(40), gameHeight(20), borderWidth(42), borderHeight(22),
      frameDelay(150), frameCounter(0), frameReady(false), snake(gameWidth / 2, gameHeight / 2) {
    Utils::seedRandom();
}

Game::~Game() {
    cleanup();
}

bool Game::initialize() {
    if (!console.initialize()) {
        return false;
    }
    
    // Load high score
    highScore = Utils::getHighestScore();
    
    // Setup game area
    setupGameArea();
    
    return true;
}

void Game::run() {
    while (state != EXIT) {
        switch (state) {
            case MENU:
                showMainMenu();
                break;
            case PLAYING:
                gameLoop();
                break;
            case PAUSED:
                showPauseMenu();
                break;
            case GAME_OVER:
                showGameOverMenu();
                break;
            case HIGH_SCORE_ENTRY:
                showHighScoreEntry();
                break;
        }
    }
}

void Game::cleanup() {
    console.cleanup();
}

void Game::gameLoop() {
    while (state == PLAYING) {
        // Frame timing
        frameCounter++;
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            frameReady = true;
        }

        // Handle input
        handleInput();

        if (frameReady) {
            // Update game state
            update();

            // Render only on update ticks to reduce flicker
            render();
        }

        // Small delay to prevent excessive CPU usage
        console.sleep(10);
    }
}

void Game::update() {
    if (!frameReady) {
        return;
    }
    
    frameReady = false;
    
    // Update snake
    snake.update();
    
    // Check collisions
    processCollisions();
    
    // Check game over conditions
    checkGameOver();
}

void Game::render() {
    // Clear game area
    clearGameArea();
    
    // Draw border
    drawBorder();
    
    // Draw snake
    snake.draw(console);
    
    // Draw food
    food.draw(console);
    
    // Draw UI
    drawScore();
    drawGameInfo();
}

void Game::handleInput() {
    if (!console.isKeyPressed()) {
        return;
    }
    
    int key = console.getKeyPressed();
    
    switch (key) {
        case VK_UP:
            snake.setDirection(UP);
            break;
        case VK_DOWN:
            snake.setDirection(DOWN);
            break;
        case VK_LEFT:
            snake.setDirection(LEFT);
            break;
        case VK_RIGHT:
            snake.setDirection(RIGHT);
            break;
        case VK_ESCAPE:
            setState(PAUSED);
            break;
        case VK_SPACE:
            if (state == PLAYING) {
                setState(PAUSED);
            }
            break;
    }
}

void Game::processCollisions() {
    // Check food collision
    checkFoodCollision();
    
    // Check wall collision
    if (snake.checkWallCollision(gameWidth, gameHeight)) {
        setState(GAME_OVER);
        console.playBeep(200, 500);
        return;
    }
    
    // Check self collision
    if (snake.checkSelfCollision()) {
        setState(GAME_OVER);
        console.playBeep(200, 500);
        return;
    }
}

void Game::showMainMenu() {
    console.clearScreen();
    
    int centerX = 40;
    int centerY = 10;
    
    // Title
    console.drawString(centerX - 8, centerY - 4, "SNAKE GAME", BRIGHT_GREEN);
    console.drawString(centerX - 12, centerY - 3, "====================", BRIGHT_GREEN);
    
    // Menu options
    console.drawString(centerX - 6, centerY, "1. Start Game", WHITE);
    console.drawString(centerX - 6, centerY + 1, "2. Difficulty", WHITE);
    console.drawString(centerX - 6, centerY + 2, "3. High Scores", WHITE);
    console.drawString(centerX - 6, centerY + 3, "4. Exit", WHITE);
    
    // Current difficulty
    console.drawString(centerX - 8, centerY + 5, "Difficulty: " + getDifficultyName(), BRIGHT_CYAN);
    
    // Instructions
    console.drawString(centerX - 15, centerY + 7, "Use number keys to select option", BRIGHT_YELLOW);
    
    // Wait for input
    while (state == MENU) {
        if (console.isKeyPressed()) {
            int key = console.getKeyPressed();
            
            switch (key) {
                case '1':
                    setState(PLAYING);
                    initializeGame();
                    break;
                case '2':
                    showDifficultyMenu();
                    // Redraw main menu after returning from the difficulty menu
                    console.clearScreen();
                    console.drawString(centerX - 8, centerY - 4, "SNAKE GAME", BRIGHT_GREEN);
                    console.drawString(centerX - 12, centerY - 3, "====================", BRIGHT_GREEN);
                    console.drawString(centerX - 6, centerY, "1. Start Game", WHITE);
                    console.drawString(centerX - 6, centerY + 1, "2. Difficulty", WHITE);
                    console.drawString(centerX - 6, centerY + 2, "3. High Scores", WHITE);
                    console.drawString(centerX - 6, centerY + 3, "4. Exit", WHITE);
                    console.drawString(centerX - 8, centerY + 5, "Difficulty: " + getDifficultyName(), BRIGHT_CYAN);
                    console.drawString(centerX - 15, centerY + 7, "Use number keys to select option", BRIGHT_YELLOW);
                    break;
                case '3':
                    showHighScores();
                    // Redraw main menu after returning from the high scores screen
                    console.clearScreen();
                    console.drawString(centerX - 8, centerY - 4, "SNAKE GAME", BRIGHT_GREEN);
                    console.drawString(centerX - 12, centerY - 3, "====================", BRIGHT_GREEN);
                    console.drawString(centerX - 6, centerY, "1. Start Game", WHITE);
                    console.drawString(centerX - 6, centerY + 1, "2. Difficulty", WHITE);
                    console.drawString(centerX - 6, centerY + 2, "3. High Scores", WHITE);
                    console.drawString(centerX - 6, centerY + 3, "4. Exit", WHITE);
                    console.drawString(centerX - 8, centerY + 5, "Difficulty: " + getDifficultyName(), BRIGHT_CYAN);
                    console.drawString(centerX - 15, centerY + 7, "Use number keys to select option", BRIGHT_YELLOW);
                    break;
                case '4':
                    setState(EXIT);
                    break;
            }
        }
        console.sleep(50);
    }
}

void Game::showDifficultyMenu() {
    console.clearScreen();
    
    int centerX = 40;
    int centerY = 10;
    
    console.drawString(centerX - 8, centerY - 2, "SELECT DIFFICULTY", BRIGHT_GREEN);
    console.drawString(centerX - 12, centerY, "====================", BRIGHT_GREEN);
    
    console.drawString(centerX - 6, centerY + 2, "1. Easy (Slow)", WHITE);
    console.drawString(centerX - 6, centerY + 3, "2. Normal (Medium)", WHITE);
    console.drawString(centerX - 6, centerY + 4, "3. Hard (Fast)", WHITE);
    console.drawString(centerX - 6, centerY + 5, "4. Back to Menu", WHITE);
    
    while (state == MENU) {
        if (console.isKeyPressed()) {
            int key = console.getKeyPressed();
            
            switch (key) {
                case '1':
                    setDifficulty(EASY);
                    setState(MENU);
                    return; // return to main menu
                case '2':
                    setDifficulty(NORMAL);
                    setState(MENU);
                    return; // return to main menu
                case '3':
                    setDifficulty(HARD);
                    setState(MENU);
                    return; // return to main menu
                case '4':
                    setState(MENU);
                    return; // return to main menu
            }
        }
        console.sleep(50);
    }
}

void Game::showPauseMenu() {
    int centerX = 40;
    int centerY = 10;
    
    console.drawString(centerX - 4, centerY, "PAUSED", BRIGHT_YELLOW);
    console.drawString(centerX - 8, centerY + 2, "Press SPACE to resume", WHITE);
    console.drawString(centerX - 8, centerY + 3, "Press ESC to quit", WHITE);
    
    while (state == PAUSED) {
        if (console.isKeyPressed()) {
            int key = console.getKeyPressed();
            
            switch (key) {
                case VK_SPACE:
                    setState(PLAYING);
                    break;
                case VK_ESCAPE:
                    setState(GAME_OVER);
                    break;
            }
        }
        console.sleep(50);
    }
}

void Game::showGameOverMenu() {
    console.clearScreen();
    
    int centerX = 40;
    int centerY = 10;
    
    console.drawString(centerX - 5, centerY - 2, "GAME OVER", BRIGHT_RED);
    console.drawString(centerX - 8, centerY, "Final Score: " + std::to_string(score), WHITE);
    console.drawString(centerX - 8, centerY + 1, "High Score: " + std::to_string(highScore), BRIGHT_CYAN);
    
    if (Utils::isNewHighScore(score)) {
        console.drawString(centerX - 8, centerY + 3, "NEW HIGH SCORE!", BRIGHT_YELLOW);
        setState(HIGH_SCORE_ENTRY);
        return;
    }
    
    console.drawString(centerX - 8, centerY + 4, "Press ENTER to play again", WHITE);
    console.drawString(centerX - 8, centerY + 5, "Press ESC to quit", WHITE);
    
    while (state == GAME_OVER) {
        if (console.isKeyPressed()) {
            int key = console.getKeyPressed();
            
            switch (key) {
                case VK_RETURN:
                    setState(MENU);
                    break;
                case VK_ESCAPE:
                    setState(EXIT);
                    break;
            }
        }
        console.sleep(50);
    }
}

void Game::showHighScoreEntry() {
    console.clearScreen();
    
    int centerX = 40;
    int centerY = 10;
    
    console.drawString(centerX - 8, centerY - 2, "NEW HIGH SCORE!", BRIGHT_YELLOW);
    console.drawString(centerX - 8, centerY, "Score: " + std::to_string(score), WHITE);
    console.drawString(centerX - 8, centerY + 2, "Enter your name:", WHITE);
    
    // Simple name input (in a real implementation, you'd want more sophisticated input handling)
    std::string name;
    console.showCursor();
    console.setCursorPosition(centerX - 8, centerY + 3);
    // For now, just use a default name
    name = "Player";
    playerName = Utils::sanitizePlayerName(name);
    
    // Save high score
    HighScore newScore(playerName, score, Utils::getCurrentDate());
    Utils::saveHighScore(newScore);
    
    console.hideCursor();
    setState(GAME_OVER);
}

void Game::showHighScores() {
    console.clearScreen();
    
    int centerX = 40;
    int centerY = 5;
    
    console.drawString(centerX - 6, centerY - 2, "HIGH SCORES", BRIGHT_GREEN);
    
    std::vector<HighScore> scores = Utils::loadHighScores();
    
    if (scores.empty()) {
        console.drawString(centerX - 8, centerY, "No high scores yet!", WHITE);
    } else {
        for (size_t i = 0; i < std::min(scores.size(), size_t(10)); i++) {
            std::string line = std::to_string(i + 1) + ". " + scores[i].playerName + " - " + std::to_string(scores[i].score);
            console.drawString(centerX - 8, centerY + static_cast<int>(i), line, WHITE);
        }
    }
    
    console.drawString(centerX - 10, centerY + 12, "Press ENTER to go back", BRIGHT_YELLOW);
    
    // Fix: Wait for ENTER key and return to menu
    while (state == MENU) {
        if (console.isKeyPressed()) {
            int key = console.getKeyPressed();
            if (key == VK_RETURN) { // VK_RETURN is usually the ENTER key
                setState(MENU);     // Return to main menu
                break;
            }
        }
        console.sleep(50);
    }
}


void Game::initializeGame() {
    resetGame();
    setDifficulty(difficulty);
    
    // Place initial food
    food.generate(gameWidth, gameHeight, snake);
}

void Game::resetGame() {
    score = 0;
    level = 1;
    snake.reset(gameWidth / 2, gameHeight / 2);
    food.reset();
    console.clearScreen();
}

void Game::setupGameArea() {
    // Set console window size to fit the game area + border
    // This is not standard but can be done on Windows
    // We'll rely on the default console size for now
}

void Game::drawBorder() {
    console.drawBox(0, 0, borderWidth, borderHeight, '#', BRIGHT_WHITE);
}

void Game::drawScore() {
    console.setCursorPosition(borderWidth + 2, 2);
    console.drawString(borderWidth + 2, 2, "Score: " + std::to_string(score), BRIGHT_YELLOW);
}

void Game::drawGameInfo() {
    console.setCursorPosition(borderWidth + 2, 4);
    console.drawString(borderWidth + 2, 4, "Level: " + std::to_string(level), BRIGHT_CYAN);
    console.drawString(borderWidth + 2, 5, "High Score: " + std::to_string(highScore), BRIGHT_MAGENTA);
}

void Game::clearGameArea() {
    // Fill the inner game area with spaces
    for (int y = 1; y < gameHeight + 1; y++) {
        for (int x = 1; x < gameWidth + 1; x++) {
            console.drawChar(x, y, ' ', BLACK);
        }
    }
}

void Game::checkFoodCollision() {
    if (food.checkCollision(snake.getHead().x, snake.getHead().y)) {
        increaseScore(food.getPoints());
        snake.grow();
        console.playBeep(400, 50);
        food.generate(gameWidth, gameHeight, snake);
    }
}

void Game::checkGameOver() {
    if (snake.checkWallCollision(gameWidth, gameHeight) || snake.checkSelfCollision()) {
        setState(GAME_OVER);
    }
}

void Game::increaseScore(int points) {
    score += points;
    if (score > highScore) {
        highScore = score;
    }
    if (score >= level * 50) {
        increaseLevel();
    }
}

void Game::increaseLevel() {
    level++;
    setDifficulty(difficulty); // Update speed based on new level
}

void Game::setDifficulty(Difficulty diff) {
    difficulty = diff;
    switch (difficulty) {
        case EASY:
            frameDelay = 8;
            break;
        case NORMAL:
            frameDelay = 6;
            break;
        case HARD:
            frameDelay = 4;
            break;
    }
}

std::string Game::getDifficultyName() const {
    switch (difficulty) {
        case EASY:
            return "Easy";
            break;
        case NORMAL:
            return "Normal";
            break;
        case HARD:
            return "Hard";
            break;
    }
    return "Unknown";
}

void Game::setState(GameState newState) {
    state = newState;
}

GameState Game::getState() const {
    return state;
}

int Game::getScore() const {
    return score;
}

int Game::getHighScore() const {
    return highScore;
}

int Game::getLevel() const {
    return level;
}

Difficulty Game::getDifficulty() const {
    return difficulty;
}

void Game::setPlayerName(const std::string& name) {
    playerName = name;
}

std::string Game::getPlayerName() const {
    return playerName;
}

bool Game::isRunning() const {
    return state != EXIT;
}

void Game::pause() {
    if (state == PLAYING) {
        setState(PAUSED);
    }
}

void Game::resume() {
    if (state == PAUSED) {
        setState(PLAYING);
    }
}