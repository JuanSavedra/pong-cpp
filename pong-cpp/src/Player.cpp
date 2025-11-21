#include "Player.h"
#include <GameConstants.h>

Player::Player(glm::vec2 pos, glm::vec2 size) : GameObject(pos, size) {
    currentDirection = Direction::IDLE;
    nextDirection = Direction::IDLE;
}

void Player::changeDirection(Direction newDirection) {
    nextDirection = newDirection;
}

void Player::move(float dt, unsigned int window_width, unsigned int window_height) {
    currentDirection = nextDirection;

    switch (currentDirection) {
    case Direction::UP:
        this->Velocity.y = PLAYER_SPEED;
        break;
    case Direction::DOWN:
        this->Velocity.y = -PLAYER_SPEED;
        break;
    case Direction::IDLE:
        this->Velocity.y = 0;
        break;
    }

    this->Position.y += this->Velocity.y * dt;

    if (this->Position.y + this->Size.y / 2 > window_height) {
        this->Position.y = window_height - this->Size.y / 2;
    }
    if (this->Position.y - this->Size.y / 2 < 0) {
        this->Position.y = this->Size.y / 2;
    }
}
