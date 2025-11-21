#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity) { }

void GameObject::move(float dt, unsigned int window_width, unsigned int window_height) {
    this->Position += this->Velocity * dt;
}