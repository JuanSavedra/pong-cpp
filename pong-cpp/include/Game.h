#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game {
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void run();

private:
	const unsigned int screenWidth;
	const unsigned int screenHeight;
	const int gridWidth;
	const int gridHeight;

	GLFWwindow* window;

	unsigned int VAO, VBO;

	void init();
	void update();
	void render();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif