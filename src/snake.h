#pragma once
#include <vector>
#include <utility>
#include "console.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Position {
    int x, y;
    
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

class Snake {
private:
    std::vector<Position> body;
    Direction direction;
    Direction nextDirection;
    bool growing;
    int growthCounter;
    
    bool canChangeDirection(Direction newDir) const;
    
public:
    Snake(int startX = 10, int startY = 10);
    
    // Movement
    void update();
    void setDirection(Direction dir);
    Direction getDirection() const;
    
    // Body management
    void grow();
    void reset(int startX, int startY);
    int getLength() const;
    
    // Getters
    const std::vector<Position>& getBody() const;
    Position getHead() const;
    Position getTail() const;
    
    // Collision detection
    bool checkCollision(int x, int y) const;
    bool checkWallCollision(int gameWidth, int gameHeight) const;
    bool checkSelfCollision() const;
    
    // Drawing
    void draw(Console& console) const;
};