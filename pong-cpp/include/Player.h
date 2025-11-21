#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

enum class Direction {
    UP,
    DOWN,
    IDLE
};

class Player : public GameObject {
public:
    Player(glm::vec2 pos, glm::vec2 size);

    void changeDirection(Direction newDirection);
    Direction getCurrentDirection() const { return currentDirection; }
    void move(float dt, unsigned int window_width, unsigned int window_height) override;

private:
    Direction currentDirection;
    Direction nextDirection;
};

#endif