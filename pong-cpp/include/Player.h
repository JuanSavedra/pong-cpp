// --- Player.h ---
// Define a classe Player, que representa a raquete controlada pelo jogador.
// A classe herda de GameObject, reutilizando os atributos de posição, tamanho e velocidade.

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

// Enum para representar a direção do movimento do jogador.
// Usar um 'enum class' é mais seguro e explícito do que um 'enum' simples,
// pois evita conflitos de nomes e exige que você use o escopo (Direction::UP).
enum class Direction {
    UP,   // Mover para cima
    DOWN, // Mover para baixo
    IDLE  // Parado
};

// A sintaxe ': public GameObject' indica que Player é uma classe "filha" de GameObject.
// Isso significa que Player "herda" todos os membros (atributos e métodos) públicos
// e protegidos de GameObject.
class Player : public GameObject {
public:
    // --- Construtor ---
    // Cria uma nova instância de Player.
    Player(glm::vec2 pos, glm::vec2 size);

    // --- Métodos Públicos ---

    // Altera a direção do movimento do jogador.
    void changeDirection(Direction newDirection);

    // Retorna a direção atual do movimento.
    // 'const' no final do método significa que ele não modifica o estado do objeto.
    Direction getCurrentDirection() const { return currentDirection; }

    // 'override' indica que este método está sobrescrevendo um método 'virtual' da classe pai (GameObject).
    // Isso ajuda o compilador a garantir que a assinatura do método está correta.
    // Aqui, a lógica de movimento será específica para o jogador (ex: não sair da tela).
    void move(float dt, unsigned int window_width, unsigned int window_height) override;

private:
    // --- Atributos Privados ---
    // Apenas os métodos da própria classe Player podem acessar estes atributos.

    // Direção em que o jogador está se movendo no frame atual.
    Direction currentDirection;
    // Próxima direção que o jogador irá tomar (usado para input).
    Direction nextDirection;
};

#endif