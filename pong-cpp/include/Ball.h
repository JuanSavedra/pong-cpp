// --- Ball.h ---
// Define a classe Ball, que representa a bola do jogo.
// Assim como o Player, esta classe herda de GameObject.

#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

// Ball é uma classe filha de GameObject.
class Ball : public GameObject {
public:
    // --- Construtor ---
    // Cria uma nova instância da bola.
    Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity);

    // --- Métodos Públicos ---

    // Inverte a velocidade no eixo Y. Usado quando a bola colide com
    // as bordas superior ou inferior da tela.
    void invertVelocityY();

    // Inverte a velocidade no eixo X. Usado quando a bola colide
    // com uma das raquetes.
    void invertVelocityX();

    // Aumenta a velocidade da bola por um determinado fator.
    // Isso torna o jogo progressivamente mais difícil.
    void increaseSpeed(float factor);

    // Reposiciona a bola em sua posição inicial (geralmente o centro da tela)
    // e com sua velocidade inicial. Chamado quando um jogador pontua.
    void reset(glm::vec2 pos, glm::vec2 vel);
};

#endif