// --- ResourceManager.h ---
// Define a classe ResourceManager, responsável por carregar e armazenar recursos do jogo.
//
// Por que usar um ResourceManager?
// 1. Evitar Duplicação: Garante que um recurso (como um shader ou textura) seja
//    carregado do disco apenas uma vez e reutilizado em todo o jogo. Isso economiza
//    memória e tempo de carregamento.
// 2. Organização: Centraliza todo o código de carregamento de recursos em um único lugar.
// 3. Gerenciamento de Memória: Facilita a liberação de todos os recursos quando
//    o jogo termina ou uma fase é descarregada.
//
// Design Pattern: Classe Estática
// Esta classe usa apenas membros e métodos estáticos. Isso significa que você não
// precisa criar uma instância dela (ex: `ResourceManager manager;`). Você acessa
// seus membros e métodos diretamente pelo nome da classe (ex: `ResourceManager::LoadShader(...)`).
// É uma forma simples de ter um "gerenciador global" sem usar o padrão Singleton,
// que pode ser mais complexo.

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "Shader.h"

class ResourceManager {
public:
    // --- Armazenamento de Recursos ---
    // Mapas estáticos que associam um nome (string) ao recurso carregado.
    // Assim, podemos pedir um shader pelo nome, como "sprite" ou "particle".
    static std::map<std::string, Shader> Shaders;

    // --- Métodos Públicos Estáticos ---

    // Carrega um shader a partir de arquivos, o armazena e retorna uma referência a ele.
    // Se o shader com o mesmo nome já foi carregado, ele simplesmente retorna o shader existente.
    // Parâmetros:
    // - vShaderFile: Caminho para o arquivo do vertex shader.
    // - fShaderFile: Caminho para o arquivo do fragment shader.
    // - name: O nome que será usado para identificar e recuperar este shader mais tarde.
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);

    // Recupera um shader armazenado pelo seu nome.
    static Shader& GetShader(std::string name);

    // Libera todos os recursos carregados. Deve ser chamado ao final do jogo
    // para limpar a memória da GPU.
    static void Clear();

private:
    // --- Construtor Privado ---
    // O construtor é privado para impedir que alguém crie uma instância desta classe.
    // Isso reforça o padrão de "classe estática".
    ResourceManager() { }

    // --- Métodos Privados Estáticos ---

    // Método auxiliar que realmente faz o trabalho de ler os arquivos de shader
    // do disco e compilá-los.
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
};

#endif