#include "Player.h"
#include <iostream>
#include <glm/glm.hpp>

Player::Player(glm::vec2 pos) : m_position(pos) {
    currentDirection = Direction::IDLE;
    nextDirection = Direction::IDLE;
}

void Player::move(float dt) {
    currentDirection = nextDirection;
    float speed = 200.0f; // Define a basic speed

    switch (currentDirection) {
    case Direction::UP:
        m_position.y += speed * dt;
        break;
    case Direction::DOWN:
        m_position.y -= speed * dt;
        break;
    case Direction::IDLE:
        // Do nothing
        break;
    }
}

void Player::changeDirection(Direction newDirection) {
    nextDirection = newDirection;
}

glm::vec2 Player::getPosition() const {
    return m_position;
}