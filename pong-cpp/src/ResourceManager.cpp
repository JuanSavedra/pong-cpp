// --- ResourceManager.cpp ---
// Implementação da classe ResourceManager.

#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

// --- Inicialização dos Membros Estáticos ---
// Os membros estáticos de uma classe precisam ser definidos fora da declaração da classe,
// geralmente no arquivo .cpp. Aqui, estamos criando o mapa de shaders.
std::map<std::string, Shader> ResourceManager::Shaders;

// --- Implementação dos Métodos Estáticos ---

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name) {
    // Carrega o shader do arquivo usando o método auxiliar.
    Shader shader = loadShaderFromFile(vShaderFile, fShaderFile);
    // Armazena o shader carregado no mapa, usando o nome fornecido como chave.
    // Se já existir um shader com esse nome, ele será substituído.
    Shaders[name] = shader;
    return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name) {
    // Retorna uma referência ao shader armazenado no mapa.
    // Usar Shaders[name] é conveniente. Uma alternativa mais segura seria usar Shaders.at(name),
    // que lançaria uma exceção se o shader não for encontrado, ajudando a depurar erros.
    return Shaders[name];
}

void ResourceManager::Clear() {
    // Itera sobre todos os elementos do mapa de shaders.
    // 'auto' infere o tipo do iterador, que é std::map<std::string, Shader>::iterator.
    for (auto iter : Shaders) {
        // 'iter.second' acessa o valor do mapa (o objeto Shader).
        // Chama glDeleteProgram para liberar os recursos do programa de shader na GPU.
        glDeleteProgram(iter.second.ID);
    }
    // Opcional: você também pode limpar o mapa da CPU se necessário.
    // Shaders.clear();
}

// Método privado que lida com a leitura dos arquivos de shader.
Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // Garante que os objetos ifstream possam lançar exceções em caso de falha.
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Abre os arquivos.
        vertexShaderFile.open(vShaderFile);
        fragmentShaderFile.open(fShaderFile);

        // Cria stringstreams para ler o conteúdo dos arquivos.
        std::stringstream vShaderStream, fShaderStream;

        // Lê o buffer do arquivo diretamente para o stringstream (uma forma eficiente de ler um arquivo inteiro).
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // Fecha os manipuladores de arquivo.
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Converte o conteúdo do stream para uma string.
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        // Captura exceções de IO (Input/Output) e imprime uma mensagem de erro.
        std::cout << "ERRO::SHADER: Nao foi possivel ler os arquivos de shader." << std::endl;
    }

    // Converte as std::strings para const char*, que é o formato esperado pela função Compile.
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // Cria um novo objeto Shader e o compila com o código lido dos arquivos.
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}