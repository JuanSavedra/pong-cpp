#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

struct GridPosition {
    int x;
    int y; 

    bool operator==(const GridPosition& other) const {
        return x == other.x && y == other.y;
    }
};

enum class Direction {
    UP,
    DOWN,
    IDLE
};

class Player {
public:
    Player(int startX, int startY);

    void move();

    void changeDirection(Direction newDirection);
    bool isOutOfBounds(int gridHeight) const;

    GridPosition getPlayerPosition() const;

    Direction getCurrentDirection() const { return currentDirection; }

private:
    glm::vec2 m_position;
    glm::vec2 m_size;

    Direction currentDirection;
    Direction nextDirection;
};

#endif