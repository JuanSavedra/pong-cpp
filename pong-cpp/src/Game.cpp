#include <Game.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(unsigned int width, unsigned int height)
	: screenWidth(width), screenHeight(height),
	player(glm::vec2(50.0f, height / 2.0f)),
	window(nullptr), shader(nullptr),
	VAO(0), VBO(0),
	deltaTime(0.0f) {
	init();
}

Game::~Game() {
	delete shader;
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

	float vertices[] = {
		// Tri�ngulo 1
		-0.5f, -0.5f, 0.0f,  // V�rtice inferior esquerdo
		 0.5f, -0.5f, 0.0f,  // V�rtice inferior direito
		 0.5f,  0.5f, 0.0f,  // V�rtice superior direito
		 // Tri�ngulo 2
		  0.5f,  0.5f, 0.0f,  // V�rtice superior direito
		 -0.5f,  0.5f, 0.0f,  // V�rtice superior esquerdo
		 -0.5f, -0.5f, 0.0f   // V�rtice inferior esquerdo
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader = new Shader("res/shaders/racket.vert", "res/shaders/racket.frag");
	shader->use();

	glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
	shader->setMat4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	shader->setMat4("view", view);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Game::run() {
	float lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput();

		update(deltaTime);
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Game::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		player.changeDirection(Direction::UP);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		player.changeDirection(Direction::DOWN);
	else
		player.changeDirection(Direction::IDLE);
}

void Game::update(float dt) {
	player.move(dt);
}

void Game::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader->use();

	glm::vec2 playerSize(20.0f, 100.0f);
	drawSquare(player.getPosition(), playerSize, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Game::drawSquare(glm::vec2 position, glm::vec2 size, const glm::vec4& color) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader->setMat4("model", model);
	shader->setVec4("objectColor", color);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
