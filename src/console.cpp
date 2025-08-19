#include "console.h"
#include <iostream>

Console::Console() : hConsole(nullptr), hInput(nullptr), bytesWritten(0), bytesRead(0), numEvents(0) {
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
}

Console::~Console() {
    cleanup();
}

bool Console::initialize() {
    // Get console handles
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    
    if (hConsole == INVALID_HANDLE_VALUE || hInput == INVALID_HANDLE_VALUE) {
        return false;
    }
    
    // Get console info
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return false;
    }
    
    // Set console mode for input
    setConsoleMode();
    
    // Set console title
    setConsoleTitle("Console Snake C++");
    
    // Hide cursor initially
    hideCursor();
    
    return true;
}

void Console::cleanup() {
    showCursor();
    resetColors();
    clearScreen();
}

void Console::setConsoleTitle(const std::string& title) {
    SetConsoleTitleA(title.c_str());
}

void Console::hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Console::showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Console::clearScreen() {
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void Console::setCursorPosition(int x, int y) {
    cursorPosition.X = static_cast<SHORT>(x);
    cursorPosition.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(hConsole, cursorPosition);
}

void Console::getCursorPosition(int& x, int& y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    x = csbi.dwCursorPosition.X;
    y = csbi.dwCursorPosition.Y;
}

void Console::getConsoleSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Console::setTextColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void Console::setBackgroundColor(int color) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD currentAttrs = csbi.wAttributes;
    WORD newAttrs = (currentAttrs & 0xF0) | (color & 0x0F);
    SetConsoleTextAttribute(hConsole, newAttrs);
}

void Console::resetColors() {
    SetConsoleTextAttribute(hConsole, WHITE);
}

void Console::setColor(int foreground, int background) {
    WORD color = static_cast<WORD>(foreground | (background << 4));
    SetConsoleTextAttribute(hConsole, color);
}

void Console::drawChar(int x, int y, char ch, int color) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    DWORD written;
    SetConsoleCursorPosition(hConsole, coord);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    WriteConsoleA(hConsole, &ch, 1, &written, nullptr);
}

void Console::drawString(int x, int y, const std::string& str, int color) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    DWORD written;
    SetConsoleCursorPosition(hConsole, coord);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    WriteConsoleA(hConsole, str.c_str(), static_cast<DWORD>(str.length()), &written, nullptr);
}

void Console::drawBox(int x, int y, int width, int height, char border, int color) {
    // Draw top border
    for (int i = 0; i < width; i++) {
        drawChar(x + i, y, border, color);
    }
    
    // Draw bottom border
    for (int i = 0; i < width; i++) {
        drawChar(x + i, y + height - 1, border, color);
    }
    
    // Draw left border
    for (int i = 1; i < height - 1; i++) {
        drawChar(x, y + i, border, color);
    }
    
    // Draw right border
    for (int i = 1; i < height - 1; i++) {
        drawChar(x + width - 1, y + i, border, color);
    }
}

bool Console::isKeyPressed() {
    return WaitForSingleObject(hInput, 0) == WAIT_OBJECT_0;
}

int Console::getKeyPressed() {
    DWORD events = 0;
    PeekConsoleInput(hInput, inputBuffer, 128, &events);
    if (events > 0) {
        FlushConsoleInputBuffer(hInput);
        for (DWORD i = 0; i < events; ++i) {
            if (inputBuffer[i].EventType == KEY_EVENT && inputBuffer[i].Event.KeyEvent.bKeyDown) {
                return inputBuffer[i].Event.KeyEvent.wVirtualKeyCode;
            }
        }
    }
    return 0;
}

bool Console::isArrowKey(int key) {
    return key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT;
}

void Console::flushInputBuffer() {
    FlushConsoleInputBuffer(hInput);
}

void Console::sleep(int milliseconds) {
    Sleep(milliseconds);
}

void Console::setConsoleMode() {
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    mode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_MOUSE_INPUT);
    SetConsoleMode(hInput, mode);
}

void Console::playBeep(int frequency, int duration) {
    Beep(frequency, duration);
}