// --- Game.h ---
// Define a classe Game, o coração do nosso jogo.
// Esta classe é responsável por:
// - Inicializar a janela e o contexto OpenGL.
// - Conter os objetos principais do jogo (jogador, bola).
// - Gerenciar o "Game Loop" (loop de jogo), o ciclo contínuo que
//   processa input, atualiza a lógica e renderiza a cena.
// - Orquestrar as interações entre os diferentes componentes (renderer, objetos, etc.).

#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h> // API de gerenciamento de janela e input
#include <glm/glm.hpp>
#include "Player.h"
#include "Ball.h"
#include "SpriteRenderer.h"

// Enum para o estado do jogo (não usado neste projeto, mas seria útil para adicionar menus, etc.)
// enum GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Game {
public:
    // --- Construtor e Destrutor ---
    Game(unsigned int width, unsigned int height);
    ~Game();

    // --- Método Principal ---
    // Inicia e executa o loop principal do jogo.
    void run();

private:
    // --- Objetos de Jogo ---
    // Instâncias diretas das nossas classes de jogo.
    Player player;
    Ball ball;

    // --- Configurações da Janela ---
    const unsigned int screenWidth;
    const unsigned int screenHeight;

    // --- Componentes ---
    // Ponteiro para a janela GLFW. A janela é criada e gerenciada pela biblioteca GLFW.
    GLFWwindow* window;
    // Ponteiro para nosso renderer. Usamos um ponteiro para poder criá-lo dinamicamente
    // após a inicialização do OpenGL (no método init).
    SpriteRenderer* Renderer;

    // --- Métodos do Game Loop ---
    // A estrutura clássica de um motor de jogo.
    void init();         // Configuração inicial (carregar shaders, criar objetos, etc.).
    void processInput(); // Processar input do usuário (teclado, mouse) a cada frame.
    void update(float dt); // Atualizar a lógica do jogo (movimento, física, IA) com base no tempo decorrido.
    void render();       // Desenhar todos os objetos na tela.

    // --- Lógica do Jogo ---
    void checkCollisions(); // Verifica e trata colisões entre os objetos.

    // --- Callbacks do GLFW ---
    // Funções que o GLFW chama em resposta a eventos específicos.
    // 'static' é necessário aqui porque o GLFW é uma biblioteca C e não entende
    // o ponteiro 'this' de uma classe C++. Uma função estática não possui 'this'.
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    // --- Controle de Tempo ---
    // Armazena o tempo decorrido entre o frame atual e o anterior (delta time).
    // Essencial para que a física e o movimento sejam independentes da taxa de quadros.
    float deltaTime;
};

#endif