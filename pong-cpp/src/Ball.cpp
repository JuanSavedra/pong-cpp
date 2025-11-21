#include "Ball.h"

Ball::Ball(glm::vec2 pos, glm::vec2 vel)
    : m_position(pos), m_velocity(vel) {
}

void Ball::move(float dt) {
    m_position += m_velocity * dt;
}

glm::vec2 Ball::getPosition() const {
    return m_position;
}

glm::vec2 Ball::getVelocity() const {
    return m_velocity;
}

void Ball::setVelocity(glm::vec2 vel) {
    m_velocity = vel;
}

void Ball::invertVelocityY() {
    m_velocity.y = -m_velocity.y;
}

void Ball::invertVelocityX() {
    m_velocity.x = -m_velocity.x;
}

void Ball::increaseSpeed(float factor) {
    m_velocity *= factor;
}

void Ball::reset(glm::vec2 pos, glm::vec2 vel) {
    m_position = pos;
    m_velocity = vel;
}
