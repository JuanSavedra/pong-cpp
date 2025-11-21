#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>

class Ball {
public:
    Ball(glm::vec2 pos, glm::vec2 vel);

    void move(float dt);

    glm::vec2 getPosition() const;
    glm::vec2 getVelocity() const;

    void setVelocity(glm::vec2 vel);
    void invertVelocityY();
    void invertVelocityX();
    void increaseSpeed(float factor);

    void reset(glm::vec2 pos, glm::vec2 vel);
private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
};

#endif