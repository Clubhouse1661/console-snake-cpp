#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

struct HighScore {
    std::string playerName;
    int score;
    std::string date;
    
    HighScore(const std::string& name = "", int s = 0, const std::string& d = "");
    bool operator<(const HighScore& other) const;
};

class Utils {
public:
    // File operations
    static bool fileExists(const std::string& filename);
    static bool createDirectory(const std::string& path);
    static std::string getCurrentDirectory();
    static std::string getExecutablePath();
    
    // High score management
    static std::string getHighScoreFileName();
    static bool saveHighScore(const HighScore& score);
    static std::vector<HighScore> loadHighScores();
    static int getHighestScore();
    static void displayHighScores();
    static bool isNewHighScore(int score);
    
    // String utilities
    static std::string trim(const std::string& str);
    static std::string toUpper(const std::string& str);
    static std::string toLower(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string getCurrentDate();
    static std::string getCurrentTime();
    
    // Number utilities
    static int random(int min, int max);
    static void seedRandom();
    static std::string formatNumber(int number);
    static std::string formatScore(int score);
    
    // Validation
    static bool isValidPlayerName(const std::string& name);
    static std::string sanitizePlayerName(const std::string& name);
    
    // Menu utilities
    static void clearLine(int y);
    static void drawCenteredText(int y, const std::string& text);
    static void drawRightAlignedText(int y, const std::string& text);
    
    // Error handling
    static void logError(const std::string& message);
    static void logInfo(const std::string& message);
};
