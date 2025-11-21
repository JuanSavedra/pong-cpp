// --- Shader.cpp ---
// Implementação da classe Shader.

#include "Shader.h" 

#include <iostream>

// --- Implementação dos Métodos ---

void Shader::Compile(const char* vertexSource, const char* fragmentSource) {
    unsigned int sVertex, sFragment;

    // 1. Compilação do Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER); // Cria um objeto de shader vazio na GPU.
    glShaderSource(sVertex, 1, &vertexSource, NULL); // Anexa o código fonte ao objeto.
    glCompileShader(sVertex); // Compila o shader.
    checkCompileErrors(sVertex, "VERTEX"); // Verifica se a compilação foi bem-sucedida.

    // 2. Compilação do Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER); // Cria o objeto de shader.
    glShaderSource(sFragment, 1, &fragmentSource, NULL); // Anexa o código fonte.
    glCompileShader(sFragment); // Compila.
    checkCompileErrors(sFragment, "FRAGMENT"); // Verifica erros.

    // 3. Lincagem do Programa de Shader
    // Um "Programa de Shader" é o objeto final que contém múltiplos shaders (no nosso caso, o vertex e o fragment)
    // lincados (unidos) e prontos para serem usados.
    this->ID = glCreateProgram(); // Cria um programa de shader vazio.
    glAttachShader(this->ID, sVertex); // Anexa o vertex shader compilado.
    glAttachShader(this->ID, sFragment); // Anexa o fragment shader compilado.
    glLinkProgram(this->ID); // Linca os shaders anexados.
    checkCompileErrors(this->ID, "PROGRAM"); // Verifica se a lincagem deu certo.

    // 4. Limpeza
    // Após lincar os shaders ao programa, os objetos de shader individuais (sVertex, sFragment)
    // não são mais necessários. Eles já foram "copiados" para o programa.
    // Liberar a memória que eles ocupavam na GPU é uma boa prática.
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

// Ativa o programa de shader. Todas as chamadas de renderização subsequentes usarão este shader.
void Shader::use() {
    glUseProgram(this->ID);
}

// --- Funções para Definir Uniforms ---
// O padrão para definir uma uniform é:
// 1. Obter a "localização" (um ID/endereço) da variável uniform no programa de shader
//    usando glGetUniformLocation. Isso pode ser um pouco lento se feito a cada frame,
//    mas para um projeto simples, é aceitável.
// 2. Chamar a função glUniform* apropriada para enviar o valor para essa localização.

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

#include <glm/gtc/type_ptr.hpp> // Para a função glm::value_ptr

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    // Para matrizes, usamos glUniformMatrix4fv.
    // O último argumento, glm::value_ptr(mat), converte a matriz da GLM para um formato
    // que o OpenGL entende (um ponteiro para o primeiro elemento).
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    // Para vetores, usamos glUniform4fv.
    // O &value[0] passa o endereço do primeiro elemento do vetor.
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

// Método auxiliar para checar erros de compilação/lincagem.
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") { // Se estivermos checando um Vertex ou Fragment Shader
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success); // Pega o status da compilação.
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog); // Pega a mensagem de erro.
            std::cerr << "ERRO::SHADER::" << type << "::FALHA_COMPILACAO\n" << infoLog << std::endl;
        }
    }
    else { // Se estivermos checando o Programa de Shader
        glGetProgramiv(shader, GL_LINK_STATUS, &success); // Pega o status da lincagem.
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog); // Pega a mensagem de erro.
            std::cerr << "ERRO::SHADER::PROGRAMA::FALHA_LINKAGEM\n" << infoLog << std::endl;
        }
    }
}