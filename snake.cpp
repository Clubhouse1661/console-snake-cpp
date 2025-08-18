#include "snake.h"

using namespace std;

#ifndef _WIN32
void SnakeGame::enableRawMode() {
    tcgetattr(STDIN_FILENO, &oldTermios);
    struct termios raw = oldTermios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void SnakeGame::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldTermios);
}

bool SnakeGame::kbhit() {
    int ch = getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

char SnakeGame::getch() {
    return getchar();
}
#endif

void SnakeGame::generateFood() {
    do {
        food.x = rand() % (BOARD_WIDTH - 2) + 1;
        food.y = rand() % (BOARD_HEIGHT - 2) + 1;
    } while (isSnakePosition(food));
}

bool SnakeGame::isSnakePosition(const Position& pos) {
    for (const auto& segment : snake) {
        if (segment == pos) return true;
    }
    return false;
}

void SnakeGame::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void SnakeGame::sleepMs(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    this_thread::sleep_for(chrono::milliseconds(ms));
#endif
}

void SnakeGame::loadHighScore() {
    ifstream file(HIGH_SCORE_FILE);
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0;
    }
}

void SnakeGame::saveHighScore() {
    if (score > highScore) {
        highScore = score;
        ofstream file(HIGH_SCORE_FILE);
        if (file.is_open()) {
            file << highScore;
            file.close();
        }
    }
}

Difficulty SnakeGame::chooseDifficulty() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "          CONSOLE SNAKE C++" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Choose Difficulty Level:" << endl;
    cout << "1. Easy (Slow)" << endl;
    cout << "2. Normal (Medium)" << endl;
    cout << "3. Hard (Fast)" << endl;
    cout << endl;
    cout << "Enter your choice (1-3): ";
    
    char choice;
    cin >> choice;
    
    switch (choice) {
        case '1': return EASY;
        case '3': return HARD;
        default: return NORMAL;
    }
}

SnakeGame::SnakeGame() {
    // Initialize snake in the middle of the board
    snake.push_back(Position(BOARD_WIDTH / 2, BOARD_HEIGHT / 2));
    direction = RIGHT;
    score = 0;
    gameOver = false;
    
    srand(time(0));
    loadHighScore();
    
    // Choose difficulty before starting game
    difficulty = chooseDifficulty();
    
    generateFood();
    
#ifndef _WIN32
    enableRawMode();
#endif
}

SnakeGame::~SnakeGame() {
#ifndef _WIN32
    disableRawMode();
#endif
}
    
void SnakeGame::draw() {
    clearScreen();
    
    // Draw top border
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "#";
    }
    cout << endl;
    
    // Draw game area
    for (int y = 1; y < BOARD_HEIGHT - 1; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (x == 0 || x == BOARD_WIDTH - 1) {
                cout << "#";
            } else {
                Position current(x, y);
                if (current == snake[0]) {
                    cout << "O"; // Snake head
                } else if (isSnakePosition(current)) {
                    cout << "o"; // Snake body
                } else if (current == food) {
                    cout << "*"; // Food
                } else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    
    // Draw bottom border
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "#";
    }
    cout << endl;
    
    // Display score, high score, and difficulty
    cout << "Score: " << score << " | High Score: " << highScore;
    cout << " | Difficulty: ";
    switch (difficulty) {
        case EASY: cout << "Easy"; break;
        case NORMAL: cout << "Normal"; break;
        case HARD: cout << "Hard"; break;
    }
    cout << endl;
    cout << "Use WASD to move, Q to quit" << endl;
}
    
void SnakeGame::input() {
#ifdef _WIN32
    if (_kbhit()) {
        char key = _getch();
#else
    if (kbhit()) {
        char key = getch();
#endif
        switch (key) {
            case 'w': case 'W':
                if (direction != DOWN) direction = UP;
                break;
            case 's': case 'S':
                if (direction != UP) direction = DOWN;
                break;
            case 'a': case 'A':
                if (direction != RIGHT) direction = LEFT;
                break;
            case 'd': case 'D':
                if (direction != LEFT) direction = RIGHT;
                break;
            case 'q': case 'Q':
                gameOver = true;
                break;
        }
    }
}
    
void SnakeGame::logic() {
    if (gameOver) return;
    
    // Calculate new head position
    Position newHead = snake[0];
    switch (direction) {
        case UP: newHead.y--; break;
        case DOWN: newHead.y++; break;
        case LEFT: newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }
    
    // Check wall collision
    if (newHead.x <= 0 || newHead.x >= BOARD_WIDTH - 1 ||
        newHead.y <= 0 || newHead.y >= BOARD_HEIGHT - 1) {
        gameOver = true;
        return;
    }
    
    // Check self collision
    if (isSnakePosition(newHead)) {
        gameOver = true;
        return;
    }
    
    // Add new head
    snake.insert(snake.begin(), newHead);
    
    // Check food collision
    if (newHead == food) {
        score += 10;
        generateFood();
    } else {
        // Remove tail if no food eaten
        snake.pop_back();
    }
}

bool SnakeGame::isGameOver() const {
    return gameOver;
}

int SnakeGame::getScore() const {
    return score;
}

int SnakeGame::getHighScore() const {
    return highScore;
}

void SnakeGame::run() {
    while (!gameOver) {
        draw();
        input();
        logic();
        sleepMs(difficulty); // Use difficulty setting for game speed
    }
    
    // Save high score before showing game over screen
    saveHighScore();
    
    // Game over screen
    clearScreen();
    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    cout << "High Score: " << highScore << endl;
    
    if (score == highScore && score > 0) {
        cout << "NEW HIGH SCORE! Congratulations!" << endl;
    }
    
    cout << "Press Enter to exit..." << endl;
    cin.get();
}

int main() {
    SnakeGame game;
    game.run();
    return 0;
}