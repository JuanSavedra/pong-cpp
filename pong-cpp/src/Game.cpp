#include "Game.h"
#include "GameConstants.h"
#include "ResourceManager.h"
#include <iostream>

Game::Game(unsigned int width, unsigned int height)
	: screenWidth(width), screenHeight(height),
	player(glm::vec2(50.0f, height / 2.0f), PLAYER_SIZE),
	ball(glm::vec2(width / 2.0f, height / 2.0f), BALL_SIZE, INITIAL_BALL_VELOCITY),
	window(nullptr), Renderer(nullptr),
	deltaTime(0.0f) {
	init();
}

Game::~Game() {
	delete Renderer;
	ResourceManager::Clear();
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

	// Carregar shaders
	ResourceManager::LoadShader("res/shaders/racket.vert", "res/shaders/racket.frag", "sprite");

	glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").use();
	ResourceManager::GetShader("sprite").setMat4("projection", projection);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
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
	player.move(dt, screenWidth, screenHeight);
	ball.move(dt, screenWidth, screenHeight);
	checkCollisions();
}

void Game::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Renderer->drawSprite(player.Position, player.Size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer->drawSprite(ball.Position, ball.Size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Game::checkCollisions() {
    // Colisão com as bordas superior e inferior
    if (ball.Position.y + ball.Size.y / 2 >= screenHeight || ball.Position.y - ball.Size.y / 2 <= 0) {
        ball.invertVelocityY();
    }

    // Colisão com a borda direita
    if (ball.Position.x + ball.Size.x / 2 >= screenWidth) {
        ball.invertVelocityX();
    }

    // Colisão com a borda esquerda (derrota)
    if (ball.Position.x - ball.Size.x / 2 <= 0) {
        ball.reset(glm::vec2(screenWidth / 2.0f, screenHeight / 2.0f), INITIAL_BALL_VELOCITY);
    }

    // Colisão com o jogador (AABB)
    bool collisionX = ball.Position.x - ball.Size.x / 2 <= player.Position.x + player.Size.x / 2 &&
                      ball.Position.x + ball.Size.x / 2 >= player.Position.x - player.Size.x / 2;
    bool collisionY = ball.Position.y - ball.Size.y / 2 <= player.Position.y + player.Size.y / 2 &&
                      ball.Position.y + ball.Size.y / 2 >= player.Position.y - player.Size.y / 2;

    if (collisionX && collisionY && ball.Velocity.x < 0) {
        // Calcular o ponto de impacto
        float diff = ball.Position.y - player.Position.y;
        float normalized_diff = diff / (player.Size.y / 2);
        
        // Inverter a velocidade X
        ball.invertVelocityX();

        // Definir a nova velocidade Y com base no ponto de impacto
        glm::vec2 new_vel = ball.Velocity;
        new_vel.y = normalized_diff * BALL_BOUNCE_FORCE;
        ball.Velocity = new_vel;

        // Aumentar a velocidade
        ball.increaseSpeed(BALL_SPEED_INCREASE_FACTOR);
    }
}
