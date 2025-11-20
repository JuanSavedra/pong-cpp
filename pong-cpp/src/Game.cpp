#include <Game.h>
#include <iostream>

Game::Game(unsigned int width, unsigned int height)
	: screenWidth(width), screenHeight(height),
	gridWidth(20), gridHeight(20),
	window(nullptr),
	VAO(0), VBO(0) {
	init();
}

Game::~Game() {
	glfwTerminate();
}

void Game::init() {
	if (!glfwInit()) {
		std::cerr << "Falha ao inicializar o GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, "Pong Game", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Falha ao criar janela GLFW" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Falha ao inicializar GLAD" << std::endl;
		return;
	}
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Game::run() {
	while (!glfwWindowShouldClose(window)) {
		update();
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Game::update() {
	//Todo
}

void Game::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}