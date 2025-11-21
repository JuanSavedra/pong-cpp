// --- Ball.cpp ---
// Implementação da classe Ball.

#include "Ball.h"

// --- Construtor ---
// Simplesmente chama o construtor da classe pai (GameObject) para inicializar
// os atributos de posição, tamanho e velocidade.
Ball::Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity) : GameObject(pos, size, velocity) { }

// --- Implementação dos Métodos ---

// Inverte a componente Y da velocidade.
void Ball::invertVelocityY() {
    this->Velocity.y = -this->Velocity.y;
}

// Inverte a componente X da velocidade.
void Ball::invertVelocityX() {
    this->Velocity.x = -this->Velocity.x;
}

// Multiplica o vetor velocidade por um fator escalar, aumentando a velocidade geral.
void Ball::increaseSpeed(float factor) {
    this->Velocity *= factor;
}

// Redefine a posição e a velocidade da bola para os valores iniciais.
void Ball::reset(glm::vec2 pos, glm::vec2 vel) {
    this->Position = pos;
    this->Velocity = vel;
}
