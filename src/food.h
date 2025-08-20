#pragma once
#include "snake.h"
#include "console.h"
#include <vector>

class Food {
private:
    Position position;
    char symbol;
    int color;
    bool active;
    int points;
    
public:
    Food(char symbol = '@', int color = BRIGHT_RED, int points = 10);
    
    // Food management
    void generate(int maxX, int maxY, const Snake& snake);
    void reset();
    void setPosition(int x, int y);
    Position getPosition() const;
    bool isActive() const;
    void setActive(bool active);
    
    // Collision detection
    bool checkCollision(const Snake& snake) const;
    bool checkCollision(int x, int y) const;
    
    // Drawing
    void draw(Console& console) const;
    
    // Getters
    int getPoints() const;
};