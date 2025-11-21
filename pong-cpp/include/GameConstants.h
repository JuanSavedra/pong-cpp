// --- GameConstants.h ---
// Este arquivo define constantes globais usadas em todo o jogo.
// Manter essas "variáveis mágicas" em um só lugar torna o código mais fácil de ler
// e permite ajustar o comportamento do jogo (como velocidade, tamanho, etc.) rapidamente.

#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <glm/glm.hpp>

// --- Dimensões da Tela ---
// Define a largura e altura da janela do jogo em pixels.
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// --- Propriedades do Jogador (Raquete) ---
// PLAYER_SIZE: Define o tamanho (largura, altura) da raquete do jogador.
const glm::vec2 PLAYER_SIZE(20.0f, 100.0f);
// PLAYER_SPEED: Define a velocidade de movimento da raquete em pixels por segundo.
const float PLAYER_SPEED = 200.0f;

// --- Propriedades da Bola ---
// BALL_SIZE: Define o tamanho (largura, altura) da bola.
const glm::vec2 BALL_SIZE(20.0f, 20.0f);
// INITIAL_BALL_VELOCITY: Define a velocidade inicial da bola nos eixos X e Y.
const glm::vec2 INITIAL_BALL_VELOCITY(200.0f, 200.0f);
// BALL_SPEED_INCREASE_FACTOR: Fator que multiplica a velocidade da bola a cada rebatida.
const float BALL_SPEED_INCREASE_FACTOR = 1.1f;
// BALL_BOUNCE_FORCE: Força aplicada à bola ao colidir, para dar um efeito mais dinâmico.
const float BALL_BOUNCE_FORCE = 250.0f;

#endif