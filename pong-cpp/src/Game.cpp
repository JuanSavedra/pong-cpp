// --- Game.cpp ---
// Implementação da classe principal Game.

#include "Game.h"
#include "GameConstants.h"
#include "ResourceManager.h"
#include <iostream>

// --- Construtor ---
// Usa a lista de inicialização para configurar os membros da classe.
Game::Game(unsigned int width, unsigned int height)
	: screenWidth(width), screenHeight(height),
	  // Inicializa o jogador na borda esquerda, no meio da tela.
	  player(glm::vec2(50.0f, height / 2.0f - PLAYER_SIZE.y / 2.0f), PLAYER_SIZE),
	  // Inicializa a bola no centro da tela com a velocidade inicial.
	  ball(glm::vec2(width / 2.0f - BALL_SIZE.x / 2.0f, height / 2.0f - BALL_SIZE.y / 2.0f), BALL_SIZE, INITIAL_BALL_VELOCITY),
	  window(nullptr), // Inicializa ponteiros como nulos.
	  Renderer(nullptr),
	  deltaTime(0.0f) {
	// O corpo do construtor chama o método init para fazer o trabalho pesado.
	init();
}

// --- Destrutor ---
Game::~Game() {
	// Libera a memória alocada dinamicamente e finaliza os sistemas.
	delete Renderer;
	ResourceManager::Clear(); // Limpa os shaders carregados.
	glfwTerminate(); // Finaliza o GLFW.
}

// --- Método de Inicialização ---
void Game::init() {
	// 1. Inicializa o GLFW.
	if (!glfwInit()) {
		std::cerr << "Falha ao inicializar o GLFW" << std::endl;
		return;
	}

	// 2. Configura a versão do OpenGL (estamos usando 3.3 Core).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 3. Cria a janela do jogo.
	window = glfwCreateWindow(screenWidth, screenHeight, "Pong C++", NULL, NULL);
	if (window == NULL) {
		std::cerr << "Falha ao criar janela GLFW" << std::endl;
		glfwTerminate();
		return;
	}

	// 4. Define o contexto OpenGL atual para a janela que acabamos de criar.
	glfwMakeContextCurrent(window);
	// 5. Registra nosso callback para redimensionamento da janela.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 6. Inicializa o GLAD para carregar os ponteiros de função do OpenGL.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Falha ao inicializar GLAD" << std::endl;
		return;
	}

	// 7. Carrega os shaders usando nosso ResourceManager.
	ResourceManager::LoadShader("res/shaders/racket.vert", "res/shaders/racket.frag", "sprite");

	// 8. Configura a matriz de projeção.
	// Uma projeção ortográfica mapeia as coordenadas da cena diretamente para as coordenadas da tela.
	// Aqui, estamos dizendo que o canto inferior esquerdo é (0,0) e o superior direito é (screenWidth, screenHeight).
	glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").use();
	ResourceManager::GetShader("sprite").setMat4("projection", projection);

	// 9. Cria nosso SpriteRenderer, passando o shader que ele deve usar.
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

// Callback estático para redimensionar o viewport do OpenGL quando a janela GLFW é redimensionada.
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// --- Loop Principal do Jogo ---
void Game::run() {
	float lastFrame = 0.0f; // Tempo do último frame.
	while (!glfwWindowShouldClose(window)) { // O loop continua até que a janela deva ser fechada.
		// Cálculo do Delta Time.
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 1. Processa Input
		processInput();
		// 2. Atualiza a Lógica do Jogo
		update(deltaTime);
		// 3. Renderiza a Cena
		render();

		// Troca os buffers (dianteiro e traseiro) para exibir o que foi renderizado.
		glfwSwapBuffers(window);
		// Verifica se há eventos (teclado, mouse, etc.) pendentes e chama os callbacks.
		glfwPollEvents();
	}
}

// Processa o input do teclado.
void Game::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Define a direção do jogador com base nas teclas pressionadas.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		player.changeDirection(Direction::UP);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		player.changeDirection(Direction::DOWN);
	else
		player.changeDirection(Direction::IDLE);
}

// Atualiza o estado de todos os objetos do jogo.
void Game::update(float dt) {
	player.move(dt, screenWidth, screenHeight);
	ball.move(dt, screenWidth, screenHeight);
	checkCollisions(); // Verifica colisões após mover os objetos.
}

// Renderiza a cena.
void Game::render() {
	// Limpa a tela com uma cor de fundo (preto).
	glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha o jogador e a bola usando nosso renderer.
	Renderer->drawSprite(player.Position, player.Size, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	Renderer->drawSprite(ball.Position, ball.Size, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

// Lógica de detecção e resposta a colisões.
void Game::checkCollisions() {
    // --- Colisão da Bola com as Bordas da Tela ---
    // A 'Position' é o canto superior esquerdo.

    // Colisão com a borda inferior
    if (ball.Position.y + ball.Size.y >= screenHeight) {
        ball.invertVelocityY();
        ball.Position.y = screenHeight - ball.Size.y; // Corrige a posição para evitar que a bola "entre" na parede.
    }
    // Colisão com a borda superior
    if (ball.Position.y <= 0) {
        ball.invertVelocityY();
        ball.Position.y = 0; // Corrige a posição.
    }
    // Colisão com a borda direita (ponto do jogador 1)
    if (ball.Position.x + ball.Size.x >= screenWidth) {
        // Neste jogo simples, vamos apenas rebater. Em um jogo completo, o jogador 1 pontuaria.
        ball.invertVelocityX();
        ball.Position.x = screenWidth - ball.Size.x;
    }
    // Colisão com a borda esquerda (ponto do oponente/reset)
    if (ball.Position.x <= 0) {
        // Reseta a bola para o centro da tela.
        ball.reset(glm::vec2(screenWidth / 2.0f, screenHeight / 2.0f), INITIAL_BALL_VELOCITY);
    }

    // --- Colisão da Bola com a Raquete do Jogador (Teste AABB) ---
    // AABB = Axis-Aligned Bounding Box

    bool collisionX = ball.Position.x < player.Position.x + player.Size.x &&
                      ball.Position.x + ball.Size.x > player.Position.x;
    bool collisionY = ball.Position.y < player.Position.y + player.Size.y &&
                      ball.Position.y + ball.Size.y > player.Position.y;

    if (collisionX && collisionY && ball.Velocity.x < 0) { // A colisão só ocorre se a bola estiver indo para a esquerda.
        // Inverte a direção X
        ball.invertVelocityX();
        
        // Lógica para ricochete mais interessante:
        // Calcula a diferença vertical do ponto de impacto em relação ao centro da raquete.
        float playerCenterY = player.Position.y + player.Size.y / 2.0f;
        float ballCenterY = ball.Position.y + ball.Size.y / 2.0f;
        float diff = ballCenterY - playerCenterY;
        
        // Normaliza a diferença (um valor entre -1 e 1).
        float normalized_diff = diff / (player.Size.y / 2.0f);
        
        // Influencia a velocidade Y da bola com base no ponto de impacto.
        // Se acertar no meio, a bola vai mais reto. Se acertar nas pontas, o ângulo é maior.
        ball.Velocity.y = normalized_diff * BALL_BOUNCE_FORCE;

        // Aumenta a velocidade da bola a cada rebatida para aumentar a dificuldade.
        ball.increaseSpeed(BALL_SPEED_INCREASE_FACTOR);
    }
}

