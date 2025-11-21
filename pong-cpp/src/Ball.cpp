#include "Ball.h"

Ball::Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity) : GameObject(pos, size, velocity) { }

void Ball::invertVelocityY() {
    this->Velocity.y = -this->Velocity.y;
}

void Ball::invertVelocityX() {
    this->Velocity.x = -this->Velocity.x;
}

void Ball::increaseSpeed(float factor) {
    this->Velocity *= factor;
}

void Ball::reset(glm::vec2 pos, glm::vec2 vel) {
    this->Position = pos;
    this->Velocity = vel;
}
