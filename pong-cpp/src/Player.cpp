// --- Player.cpp ---
// Implementação da classe Player.

#include "Player.h"
#include <GameConstants.h> // Inclui as constantes do jogo (velocidade, tamanho, etc.)

// --- Construtor ---
// Chama o construtor da classe pai (GameObject) para inicializar posição e tamanho.
// Em seguida, inicializa as direções como 'IDLE' (parado).
Player::Player(glm::vec2 pos, glm::vec2 size)
    : GameObject(pos, size), currentDirection(Direction::IDLE), nextDirection(Direction::IDLE) { }

// --- Implementação dos Métodos ---

// Armazena a próxima direção de movimento. Isso é útil para desacoplar a
// captura de input (que pode acontecer a qualquer momento) da lógica de atualização do jogo.
void Player::changeDirection(Direction newDirection) {
    nextDirection = newDirection;
}

// Sobrescreve o método 'move' de GameObject.
void Player::move(float dt, unsigned int window_width, unsigned int window_height) {
    // Atualiza a direção atual com base na última entrada do usuário.
    currentDirection = nextDirection;

    // Define a velocidade vertical com base na direção.
    // Em coordenadas de tela, o eixo Y cresce para baixo.
    // Portanto, para mover para CIMA, diminuímos o valor de Y.
    // Para mover para BAIXO, aumentamos o valor de Y.
    switch (currentDirection) {
    case Direction::UP:
        this->Velocity.y = -PLAYER_SPEED; // Negativo para subir
        break;
    case Direction::DOWN:
        this->Velocity.y = PLAYER_SPEED; // Positivo para descer
        break;
    case Direction::IDLE:
        this->Velocity.y = 0; // Parado
        break;
    }

    // Atualiza a posição vertical com base na velocidade e no delta time.
    this->Position.y += this->Velocity.y * dt;

    // --- Verificação de Limites da Janela ---
    // Impede que a raquete saia da tela.
    // A 'Position' em nosso jogo representa o canto superior esquerdo do objeto.

    // Se a posição (canto superior) for menor que 0, travamos em 0.
    if (this->Position.y < 0.0f) {
        this->Position.y = 0.0f;
    }
    // Se a borda inferior (posição + altura) ultrapassar a altura da tela,
    // travamos a posição para que a borda inferior fique na borda da tela.
    else if (this->Position.y + this->Size.y > window_height) {
        this->Position.y = window_height - this->Size.y;
    }
}

