#include "utils.h"
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>

// HighScore implementation
HighScore::HighScore(const std::string& name, int s, const std::string& d) 
    : playerName(name), score(s), date(d) {
}

bool HighScore::operator<(const HighScore& other) const {
    return score > other.score; // Higher scores first
}

// Utils implementation
bool Utils::fileExists(const std::string& filename) {
    DWORD fileAttributes = GetFileAttributesA(filename.c_str());
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool Utils::createDirectory(const std::string& path) {
    return CreateDirectoryA(path.c_str(), nullptr) != 0;
}

std::string Utils::getCurrentDirectory() {
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    return std::string(buffer);
}

std::string Utils::getExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    return std::string(buffer);
}

std::string Utils::getHighScoreFileName() {
    std::string exePath = getExecutablePath();
    size_t lastSlash = exePath.find_last_of("\\/");
    std::string directory = exePath.substr(0, lastSlash);
    return directory + "\\highscores.txt";
}

bool Utils::saveHighScore(const HighScore& score) {
    std::string filename = getHighScoreFileName();
    std::ofstream file(filename, std::ios::app);
    
    if (!file.is_open()) {
        return false;
    }
    
    file << score.playerName << "|" << score.score << "|" << score.date << std::endl;
    file.close();
    return true;
}

std::vector<HighScore> Utils::loadHighScores() {
    std::vector<HighScore> scores;
    std::string filename = getHighScoreFileName();
    
    if (!fileExists(filename)) {
        return scores;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        return scores;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> parts = split(line, '|');
        if (parts.size() >= 3) {
            scores.emplace_back(parts[0], std::stoi(parts[1]), parts[2]);
        }
    }
    
    file.close();
    
    // Sort by score (highest first)
    std::sort(scores.begin(), scores.end());
    
    return scores;
}

int Utils::getHighestScore() {
    std::vector<HighScore> scores = loadHighScores();
    if (scores.empty()) {
        return 0;
    }
    return scores[0].score;
}

void Utils::displayHighScores() {
    std::vector<HighScore> scores = loadHighScores();
    
    if (scores.empty()) {
        std::cout << "No high scores yet!" << std::endl;
        return;
    }
    
    std::cout << "\n=== HIGH SCORES ===" << std::endl;
    std::cout << std::setw(3) << "Rank" << " | " 
              << std::setw(15) << "Player" << " | " 
              << std::setw(8) << "Score" << " | " 
              << "Date" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (size_t i = 0; i < std::min(scores.size(), size_t(10)); i++) {
        std::cout << std::setw(3) << (i + 1) << " | " 
                  << std::setw(15) << scores[i].playerName << " | " 
                  << std::setw(8) << scores[i].score << " | " 
                  << scores[i].date << std::endl;
    }
}

bool Utils::isNewHighScore(int score) {
    return score > getHighestScore();
}

std::string Utils::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::string Utils::toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Utils::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::vector<std::string> Utils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string Utils::getCurrentDate() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

std::string Utils::getCurrentTime() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return std::string(buffer);
}

int Utils::random(int min, int max) {
    return min + (rand() % (max - min + 1));
}

void Utils::seedRandom() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

std::string Utils::formatNumber(int number) {
    std::stringstream ss;
    ss << std::setw(6) << std::setfill('0') << number;
    return ss.str();
}

std::string Utils::formatScore(int score) {
    std::stringstream ss;
    ss << std::setw(8) << std::setfill(' ') << score;
    return ss.str();
}

bool Utils::isValidPlayerName(const std::string& name) {
    if (name.empty() || name.length() > 15) {
        return false;
    }
    
    for (char c : name) {
        if (!isalnum(c) && c != ' ' && c != '_' && c != '-') {
            return false;
        }
    }
    
    return true;
}

std::string Utils::sanitizePlayerName(const std::string& name) {
    std::string sanitized = trim(name);
    
    // Limit length
    if (sanitized.length() > 15) {
        sanitized = sanitized.substr(0, 15);
    }
    
    // Remove invalid characters
    std::string result;
    for (char c : sanitized) {
        if (isalnum(c) || c == ' ' || c == '_' || c == '-') {
            result += c;
        }
    }
    
    return result;
}

void Utils::clearLine(int y) {
    // This would need console access to implement properly
    // For now, just print spaces
    std::cout << std::string(80, ' ') << std::endl;
}

void Utils::drawCenteredText(int y, const std::string& text) {
    // This would need console access to implement properly
    // For now, just print the text
    std::cout << text << std::endl;
}

void Utils::drawRightAlignedText(int y, const std::string& text) {
    // This would need console access to implement properly
    // For now, just print the text
    std::cout << text << std::endl;
}

void Utils::logError(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
}

void Utils::logInfo(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;
}
