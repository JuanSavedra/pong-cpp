#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <glm/glm.hpp>

// Screen dimensions
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Player properties
const glm::vec2 PLAYER_SIZE(20.0f, 100.0f);
const float PLAYER_SPEED = 200.0f;

// Ball properties
const glm::vec2 BALL_SIZE(20.0f, 20.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(200.0f, 200.0f);
const float BALL_SPEED_INCREASE_FACTOR = 1.1f;
const float BALL_BOUNCE_FORCE = 250.0f;

#endif