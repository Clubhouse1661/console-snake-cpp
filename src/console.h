#pragma once
#include <windows.h>
#include <string>

class Console {
private:
    HANDLE hConsole;
    HANDLE hInput;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD cursorPosition;
    DWORD bytesWritten;
    DWORD bytesRead;
    INPUT_RECORD inputBuffer[128];
    DWORD numEvents;

public:
    Console();
    ~Console();
    
    // Console setup and cleanup
    bool initialize();
    void cleanup();
    void setConsoleTitle(const std::string& title);
    void hideCursor();
    void showCursor();
    void clearScreen();
    
    // Screen buffer management
    void setCursorPosition(int x, int y);
    void getCursorPosition(int& x, int& y);
    void getConsoleSize(int& width, int& height);
    
    // Color support
    void setTextColor(int color);
    void setBackgroundColor(int color);
    void resetColors();
    void setColor(int foreground, int background);
    
    // Drawing functions
    void drawChar(int x, int y, char ch, int color = 7);
    void drawString(int x, int y, const std::string& str, int color = 7);
    void drawBox(int x, int y, int width, int height, char border = '#', int color = 7);
    
    // Input handling
    bool isKeyPressed();
    int getKeyPressed();
    bool isArrowKey(int key);
    void flushInputBuffer();
    
    // Sound effects
    void playBeep(int frequency = 800, int duration = 100);
    void playEatSound();
    void playGameOverSound();
    void playMoveSound();
    
    // Utility functions
    void sleep(int milliseconds);
    void setConsoleMode();
};

// Color constants
enum Colors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    BRIGHT_BLACK = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};
