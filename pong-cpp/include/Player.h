#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

enum class Direction {
    UP,
    DOWN,
    IDLE
};

class Player {
public:
    Player(glm::vec2 pos);

    void move(float dt, unsigned int screenHeight);
    void changeDirection(Direction newDirection);

    glm::vec2 getPosition() const;
    Direction getCurrentDirection() const { return currentDirection; }

private:
    glm::vec2 m_position;

    Direction currentDirection;
    Direction nextDirection;
};

#endif