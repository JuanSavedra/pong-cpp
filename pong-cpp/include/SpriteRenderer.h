// --- SpriteRenderer.h ---
// Define a classe SpriteRenderer, responsável por desenhar sprites (imagens 2D ou,
// neste caso, retângulos coloridos) na tela.
//
// Por que usar um SpriteRenderer?
// - Abstração: Esconde os detalhes complexos de baixo nível do OpenGL para desenhar um
//   retângulo (quad). Sem esta classe, o loop principal do jogo ficaria poluído com
//   chamadas ao `glBindVertexArray`, `glDrawArrays`, etc., para cada objeto.
// - Eficiência: Embora esta implementação seja simples, um renderer mais avançado
//   poderia otimizar a renderização agrupando múltiplos sprites em uma única
//   chamada de desenho (batching), melhorando muito a performance.
// - Reutilização: Uma vez criada, esta classe pode ser usada para desenhar qualquer
//   retângulo no jogo (jogador, bola, paredes, etc.).

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer {
public:
    // --- Construtor e Destrutor ---
    // O construtor recebe o shader que será usado para desenhar os sprites.
    SpriteRenderer(Shader& shader);
    // O destrutor é responsável por limpar os recursos do OpenGL (VAO, VBO)
    // que foram alocados por este renderer.
    ~SpriteRenderer();

    // --- Método Principal de Desenho ---
    // Desenha um único sprite (retângulo) na tela.
    // Parâmetros:
    // - position: Posição (x, y) do canto superior esquerdo do sprite.
    // - size: Tamanho (largura, altura) do sprite.
    // - color: Cor do sprite (R, G, B, A). O padrão é branco.
    void drawSprite(glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));

private:
    // --- Membros Privados ---

    // O shader que será usado para renderizar os quads.
    Shader shader;
    
    // VAO (Vertex Array Object) do Quad.
    // O que é um VAO? É um objeto do OpenGL que encapsula todo o estado necessário
    // para desenhar um objeto. Ele "lembra" do VBO, dos atributos de vértice, etc.
    // Ao desenhar, em vez de reconfigurar tudo, você simplesmente "amarra" (bind) o VAO
    // e faz a chamada de desenho.
    unsigned int quadVAO;

    // Método de inicialização que cria o VAO e o VBO para um quad.
    // Como todos os nossos sprites são retângulos, podemos usar o mesmo
    // modelo de quad para todos eles e apenas aplicar transformações (posição, tamanho)
    // via matrizes no shader.
    void initRenderData();
};

#endif