// --- GameObject.cpp ---
// Implementação da classe GameObject.

#include "GameObject.h"

// --- Construtor ---
// A sintaxe com ":" é chamada de "lista de inicialização de membros".
// É uma forma mais eficiente de inicializar os atributos da classe, pois
// os constrói diretamente com os valores passados, em vez de criá-los
// primeiro e depois atribuir valores dentro do corpo do construtor {}.
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity) { }

// --- Implementação do Método 'move' ---
// Esta é a implementação base do movimento. Classes filhas podem (e vão)
// sobrescrever este método para adicionar lógicas mais complexas, como
// detecção de colisão com as bordas da tela.
void GameObject::move(float dt, unsigned int window_width, unsigned int window_height) {
    // A nova posição é calculada pela fórmula: P_final = P_inicial + Velocidade * tempo
    // Multiplicar a velocidade por 'dt' (delta time) garante que o objeto se mova
    // na mesma velocidade, não importa o quão rápido ou lento o computador
    // esteja renderizando os frames do jogo.
    this->Position += this->Velocity * dt;
}