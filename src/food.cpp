#include "food.h"
#include "console.h"
#include "utils.h"
#include <algorithm>

Food::Food(char symbol, int color, int points) 
    : symbol(symbol), color(color), active(false), points(points) {
    position = Position(0, 0);
}

void Food::generate(int maxX, int maxY, const Snake& snake) {
    if (maxX <= 0 || maxY <= 0) {
        active = false;
        return;
    }
    
    int attempts = 0;
    const int maxAttempts = 100;
    
    do {
        // Generate strictly within the inner play area (avoid borders at 0 and max+1)
        position.x = Utils::random(1, maxX);
        position.y = Utils::random(1, maxY);
        attempts++;
    } while (snake.checkCollision(position.x, position.y) && attempts < maxAttempts);
    
    // If we couldn't find a valid position, deactivate food
    if (attempts >= maxAttempts) {
        active = false;
    } else {
        active = true;
    }
}

void Food::reset() {
    active = false;
    position = Position(0, 0);
}

void Food::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
    active = true;
}

Position Food::getPosition() const {
    return position;
}

bool Food::isActive() const {
    return active;
}

void Food::setActive(bool active) {
    this->active = active;
}

bool Food::checkCollision(const Snake& snake) const {
    if (!active) {
        return false;
    }
    return snake.checkCollision(position.x, position.y);
}

bool Food::checkCollision(int x, int y) const {
    if (!active) {
        return false;
    }
    return position.x == x && position.y == y;
}

void Food::draw(Console& console) const {
    if (active) {
        console.drawChar(position.x, position.y, symbol, color);
    }
}

int Food::getPoints() const {
    return points;
}