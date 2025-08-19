#include "snake.h"
#include "console.h"
#include <algorithm>

Snake::Snake(int startX, int startY) 
    : direction(RIGHT), nextDirection(RIGHT), growing(false), growthCounter(0) {
    reset(startX, startY);
}

void Snake::update() {
    // Update direction
    direction = nextDirection;
    
    // Get current head position
    Position head = getHead();
    Position newHead = head;
    
    // Calculate new head position based on direction
    switch (direction) {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
    }
    
    // Add new head
    body.insert(body.begin(), newHead);
    
    // Remove tail if not growing
    if (!growing) {
        body.pop_back();
    } else {
        growing = false;
    }
}

void Snake::setDirection(Direction dir) {
    // Prevent 180-degree turns
    if (canChangeDirection(dir)) {
        nextDirection = dir;
    }
}

Direction Snake::getDirection() const {
    return direction;
}

bool Snake::canChangeDirection(Direction newDir) const {
    // Prevent 180-degree turns
    if (direction == UP && newDir == DOWN) return false;
    if (direction == DOWN && newDir == UP) return false;
    if (direction == LEFT && newDir == RIGHT) return false;
    if (direction == RIGHT && newDir == LEFT) return false;
    
    return true;
}

void Snake::grow() {
    growing = true;
}

void Snake::reset(int startX, int startY) {
    body.clear();
    
    // Initialize with 3 segments
    body.emplace_back(startX, startY);     // Head
    body.emplace_back(startX - 1, startY); // Body
    body.emplace_back(startX - 2, startY); // Tail
    
    direction = RIGHT;
    nextDirection = RIGHT;
    growing = false;
    growthCounter = 0;
}

int Snake::getLength() const {
    return static_cast<int>(body.size());
}

const std::vector<Position>& Snake::getBody() const {
    return body;
}

Position Snake::getHead() const {
    if (body.empty()) {
        return Position(0, 0);
    }
    return body[0];
}

Position Snake::getTail() const {
    if (body.empty()) {
        return Position(0, 0);
    }
    return body.back();
}

bool Snake::checkCollision(int x, int y) const {
    Position pos(x, y);
    return std::find(body.begin(), body.end(), pos) != body.end();
}

bool Snake::checkWallCollision(int gameWidth, int gameHeight) const {
    const Position& head = getHead();
    return head.x <= 0 || head.x >= gameWidth + 1 || head.y <= 0 || head.y >= gameHeight + 1;
}

bool Snake::checkSelfCollision() const {
    const Position& head = getHead();
    // Check collision with body parts, starting from the second segment
    for (size_t i = 1; i < body.size(); ++i) {
        if (head == body[i]) {
            return true;
        }
    }
    return false;
}

void Snake::draw(Console& console) const {
    // Draw head
    console.drawChar(body[0].x, body[0].y, 'O', BRIGHT_GREEN);
    
    // Draw body
    for (size_t i = 1; i < body.size(); ++i) {
        console.drawChar(body[i].x, body[i].y, 'o', BRIGHT_GREEN);
    }
}