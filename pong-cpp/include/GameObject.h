#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

class GameObject {
public:
    glm::vec2 Position, Size, Velocity;

    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void move(float dt, unsigned int window_width, unsigned int window_height);
};

#endif