# pong-cpp

Este documento fornece um resumo do projeto `pong-cpp`, sua estrutura e como construí-lo e executá-lo.

## Visão Geral do Projeto

Este é um projeto C++ que implementa um jogo simples de Pong.

*   **Linguagem:** C++
*   **Gráficos:** OpenGL
*   **Janelamento:** GLFW
*   **Matemática:** GLM
*   **Sistema de Build:** CMake

O projeto é estruturado com uma classe principal `Game` que encapsula a lógica do jogo. Dependências como GLFW e GLM são obtidas automaticamente durante o processo de configuração do CMake usando `FetchContent`.

## Construindo e Executando

Para construir e executar o projeto, você precisará de um compilador C++, CMake e Git instalados.

1.  **Configurar o projeto:**
    Crie um diretório de build e execute o CMake a partir da raiz do projeto. Isso fará o download das dependências e gerará os arquivos de build.
    ```bash
    cmake -B build
    ```

2.  **Construir o projeto:**
    Compile o projeto usando os arquivos de build gerados pelo CMake. Isso também copiará o diretório `res` com os shaders para o diretório do executável.
    ```bash
    cmake --build build
    ```

3.  **Executar o jogo:**
    O executável, nomeado `pong-cpp`, estará localizado no diretório `build/pong-cpp`. Execute-o a partir da raiz do projeto.
    ```bash
    ./build/pong-cpp/pong-cpp
    ```

## Estrutura do Código

### Classes Principais

*   **`Game`**: A classe principal que impulsiona a aplicação. É responsável por:
    *   Inicializar GLFW, GLAD e a janela do jogo.
    *   Gerenciar o loop principal do jogo (`run`).
    *   Processar a entrada do usuário (`processInput`).
    *   Atualizar o estado do jogo (`update`).
    *   Renderizar a cena (`render`).
    *   Possui os objetos `Player` e `Shader`.

*   **`Player`**: Representa a raquete de um jogador. Destina-se a gerenciar a posição e o movimento do jogador em resposta à entrada. A lógica do jogo sugere um sistema de movimento baseado em grade.

*   **`Shader`**: Uma classe utilitária para carregar, compilar e vincular shaders GLSL. Ela lê o código-fonte do shader de arquivos, verifica erros de compilação e fornece uma interface para definir variáveis uniformes.

### Shaders

O projeto usa um par de shaders simples:
*   `racket.vert`: Um shader de vértice básico de passagem.
*   `racket.frag`: Um shader de fragmento simples que colore fragmentos com uma única cor uniforme.

### Convenções de Desenvolvimento

*   **Estilo de Código:** O código é escrito em um estilo orientado a objetos.
*   **Loop do Jogo:** A lógica central segue um padrão de loop de jogo `init()`, `update()`, `render()` padrão.
*   **Dependências:** As dependências C++ são gerenciadas pelo `FetchContent` do CMake.
*   **Recursos:** Recursos do jogo como shaders estão localizados no diretório `pong-cpp/res` e são copiados automaticamente para o diretório de saída da build.