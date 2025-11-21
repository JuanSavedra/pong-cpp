#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject {
public:
    Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity);

    void invertVelocityY();
    void invertVelocityX();
    void increaseSpeed(float factor);

    void reset(glm::vec2 pos, glm::vec2 vel);
};

#endif