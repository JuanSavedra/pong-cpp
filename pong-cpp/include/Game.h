#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Player.h>
#include <Shader.h>
#include <Ball.h>
#include <SpriteRenderer.h>

class Game {
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void run();

private:
	Player player;
	Ball ball;

	const unsigned int screenWidth;
	const unsigned int screenHeight;

	GLFWwindow* window;
	SpriteRenderer* Renderer;

	void init();
	void processInput();
	void update(float dt);
	void render();
	void checkCollisions();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	float deltaTime;

};

#endif