#include "Player.h"
#include <iostream>
#include <glm/glm.hpp>

Player::Player(int startX, int startY) {
    currentDirection = Direction::IDLE;
    nextDirection = Direction::IDLE;
}

void Player::move() {
    currentDirection = nextDirection;

    GridPosition player = getPlayerPosition();

    switch (currentDirection) {
    case Direction::UP:
        player.y += 1;
        break;
    case Direction::DOWN:
        player.y -= 1;
        break;
    }
}

void Player::changeDirection(Direction newDirection) {
    nextDirection = newDirection;
}

bool Player::isOutOfBounds(int gridHeight) const  {
    const GridPosition& player = getPlayerPosition();
    return player.y < 0 || player.y >= gridHeight;
}

GridPosition Player::getPlayerPosition() const {
    const float GAME_HEIGHT = 800.0f;
    const int GRID_SIZE = 30;         

    float playerY = m_position.y;

    GridPosition pos;

    pos.x =  0;

    float normalizedY = playerY / GAME_HEIGHT;
    int gridY = static_cast<int>(normalizedY * GRID_SIZE);


    if (gridY < 0) {
        gridY = 0;
    }
    else if (gridY >= GRID_SIZE) {
        gridY = GRID_SIZE - 1;
    }

    pos.y = GRID_SIZE - 1 - gridY;

    return pos;
}