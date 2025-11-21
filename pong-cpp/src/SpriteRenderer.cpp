// --- SpriteRenderer.cpp ---
// Implementação da classe SpriteRenderer.

#include "SpriteRenderer.h"

// --- Construtor ---
SpriteRenderer::SpriteRenderer(Shader& shader) {
    this->shader = shader;
    // Chama o método para inicializar os dados de renderização (o VAO do quad)
    // assim que um SpriteRenderer é criado.
    this->initRenderData();
}

// --- Destrutor ---
SpriteRenderer::~SpriteRenderer() {
    // Libera a memória do VAO que foi alocada na GPU.
    // É importante limpar os recursos que não serão mais usados.
    glDeleteVertexArrays(1, &this->quadVAO);
}

// --- Método de Desenho ---
void SpriteRenderer::drawSprite(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
    // 1. Ativa o shader para este desenho.
    this->shader.use();

    // 2. Monta a matriz "model".
    // A matriz "model" transforma os vértices do quad do "espaço do modelo"
    // para o "espaço do mundo". O espaço do modelo é como definimos os vértices
    // em initRenderData (um quad de 0,0 a 1,1). O espaço do mundo é o sistema
    // de coordenadas da nossa cena/janela.
    glm::mat4 model = glm::mat4(1.0f); // Começa com uma matriz identidade (sem transformação).
    
    // Primeiro, transladamos o quad. Isso move o canto superior esquerdo (0,0) do nosso
    // modelo para a 'position' desejada na tela.
    model = glm::translate(model, glm::vec3(position, 0.0f));
    
    // Em seguida, escalamos o quad. Como nosso modelo tem tamanho 1x1, escalá-lo
    // por 'size' (largura, altura) faz com que ele adquira as dimensões corretas.
    model = glm::scale(model, glm::vec3(size, 1.0f));
    // A ordem importa! Escalar e depois transladar daria um resultado diferente.

    // 3. Envia as uniforms para o shader.
    this->shader.setMat4("model", model); // Envia a matriz de transformação.
    this->shader.setVec4("objectColor", color); // Envia a cor do objeto.

    // 4. Desenha o quad.
    glBindVertexArray(this->quadVAO); // "Amarra" o VAO, ativando toda a configuração de vértices.
    glDrawArrays(GL_TRIANGLES, 0, 6); // Desenha! Diz ao OpenGL para desenhar 6 vértices (2 triângulos)
                                     // a partir do início do buffer, usando o modo de triângulos.
    glBindVertexArray(0); // "Desamarra" o VAO por segurança.
}

// --- Método de Inicialização ---
void SpriteRenderer::initRenderData() {
    unsigned int VBO;
    
    // Vértices para um quad 2D que vai do canto superior esquerdo (0,0) ao canto inferior direito (1,1).
    // Usar este sistema de coordenadas (0 a 1) simplifica as transformações na função drawSprite.
    // Desenhamos um retângulo usando dois triângulos.
    float vertices[] = {
        // Triângulo 1
        0.0f, 1.0f, 0.0f, // Vértice superior esquerdo
        1.0f, 0.0f, 0.0f, // Vértice inferior direito
        0.0f, 0.0f, 0.0f, // Vértice inferior esquerdo
        
        // Triângulo 2
        0.0f, 1.0f, 0.0f, // Vértice superior esquerdo
        1.0f, 1.0f, 0.0f, // Vértice superior direito
        1.0f, 0.0f, 0.0f  // Vértice inferior direito
    };

    // 1. Cria o Vertex Array Object (VAO) e o Vertex Buffer Object (VBO) na GPU.
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    // 2. Configura o VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // "Amarra" o VBO para ser o buffer de vértices ativo.
    // Envia os dados dos nossos 'vertices' para a GPU, para o buffer atualmente amarrado (VBO).
    // GL_STATIC_DRAW é uma dica para o OpenGL de que esses dados não mudarão com frequência.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. Configura o VAO
    glBindVertexArray(this->quadVAO); // "Amarra" o VAO para gravar a configuração.
    // Habilita o primeiro atributo de vértice (location = 0 no shader).
    glEnableVertexAttribArray(0); 
    // Diz ao OpenGL como interpretar os dados no VBO.
    // - 0: O índice do atributo (location = 0).
    // - 3: O atributo é um vec3 (3 componentes).
    // - GL_FLOAT: Os componentes são floats.
    // - GL_FALSE: Não normalizar os dados.
    // - 3 * sizeof(float): O "stride" - tamanho de um vértice completo (3 floats).
    // - (void*)0: O "offset" - onde os dados deste atributo começam no buffer (no início).
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 4. Limpeza
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Desamarra o VBO (o VAO já "sabe" qual VBO usar).
    glBindVertexArray(0); // Desamarra o VAO para não modificá-lo acidentalmente.

    // O VBO pode ser deletado aqui, pois o VAO mantém uma referência a ele.
    // glDeleteBuffers(1, &VBO); // Opcional
}