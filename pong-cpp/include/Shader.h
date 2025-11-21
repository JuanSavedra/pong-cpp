// --- Shader.h ---
// Define a classe Shader, uma ferramenta essencial para renderização com OpenGL.
//
// O que é um Shader?
// Shaders são pequenos programas que rodam na GPU (placa de vídeo). No OpenGL moderno,
// eles são indispensáveis. Existem vários tipos de shaders, mas os mais comuns são:
// 1. Vertex Shader: Executado para cada vértice (ponto) de um objeto. Sua função
//    principal é transformar a posição do vértice do espaço do objeto para o espaço da tela.
// 2. Fragment Shader (ou Pixel Shader): Executado para cada pixel que compõe o objeto
//    na tela. Sua função principal é determinar a cor final do pixel.
//
// Esta classe 'Shader' encapsula o processo de:
// - Carregar o código fonte dos shaders (vertex e fragment).
// - Compilar os shaders.
// - Lincar (unir) os shaders compilados em um "programa de shader".
// - Ativar/desativar o programa de shader durante a renderização.
// - Enviar dados (como cores, matrizes de transformação) do nosso código C++ para os shaders.

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h> // Biblioteca para carregar as funções do OpenGL
#include <glm/glm.hpp> // Biblioteca de matemática para gráficos (vetores, matrizes)
#include <glm/gtc/matrix_transform.hpp>

class Shader {
public:
    // --- Atributos Públicos ---

    // ID do Programa de Shader. O OpenGL se refere a objetos (shaders, texturas, etc.)
    // através de IDs (números inteiros). Este ID representa o programa de shader
    // lincado que contém nosso vertex e fragment shader.
    unsigned int ID;

    // --- Construtor ---
    // Construtor padrão. A inicialização real acontece no método 'Compile'.
    Shader() { }

    // --- Métodos Públicos ---

    // Compila e linca os shaders a partir do código fonte.
    // Parâmetros:
    // - vertexSource: String contendo o código do Vertex Shader.
    // - fragmentSource: String contendo o código do Fragment Shader.
    void Compile(const char* vertexSource, const char* fragmentSource);

    // Ativa este programa de shader para ser usado na próxima operação de renderização.
    // Apenas um programa de shader pode estar ativo por vez.
    void use();

    // --- Funções para definir "Uniforms" ---
    // "Uniforms" são variáveis globais (para os shaders) que você pode definir
    // no seu código C++ e usar dentro dos shaders. Elas são a principal forma de
    // passar dados da CPU para a GPU.
    // O nome (std::string& name) deve corresponder exatamente ao nome da variável
    // 'uniform' declarada no código do shader.

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;

private:
    // --- Métodos Privados ---

    // Método auxiliar para verificar erros de compilação ou lincagem dos shaders.
    // Parâmetros:
    // - shader: O ID do objeto shader ou do programa de shader a ser verificado.
    // - type: Uma string ("VERTEX", "FRAGMENT", ou "PROGRAM") para identificar
    //         o tipo de objeto e formatar a mensagem de erro.
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif