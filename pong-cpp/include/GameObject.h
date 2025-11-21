// --- GameObject.h ---
// Define a classe base para todos os objetos visíveis no jogo (como a bola e as raquetes).
// Usar uma classe base como esta ajuda a organizar o código e a evitar repetição.
// Propriedades comuns a todos os objetos (posição, tamanho, velocidade) são definidas aqui.

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

class GameObject {
public:
    // --- Atributos Públicos ---

    // Posição: Coordenadas (x, y) do canto superior esquerdo do objeto.
    glm::vec2 Position;
    // Tamanho: Dimensões (largura, altura) do objeto.
    glm::vec2 Size;
    // Velocidade: Vetor que indica a direção e a magnitude do movimento do objeto.
    glm::vec2 Velocity;

    // --- Construtor ---
    // Cria uma nova instância de GameObject.
    // Parâmetros:
    // - pos: Posição inicial.
    // - size: Tamanho do objeto.
    // - velocity: Velocidade inicial (opcional, padrão é (0,0) - parado).
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    // --- Métodos ---

    // move: Atualiza a posição do objeto com base na sua velocidade e no tempo decorrido.
    // A palavra-chave 'virtual' indica que classes derivadas (como Ball ou Player)
    // podem fornecer sua própria implementação deste método.
    // Parâmetros:
    // - dt: Delta time - o tempo que passou desde o último frame. Usar 'dt' garante
    //       que o movimento seja suave e independente da taxa de quadros (framerate).
    // - window_width: Largura da janela, para checagem de limites.
    // - window_height: Altura da janela, para checagem de limites.
    virtual void move(float dt, unsigned int window_width, unsigned int window_height);
};

#endif