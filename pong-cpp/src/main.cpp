// --- main.cpp ---
// O ponto de entrada de qualquer programa C++.
// A sua única responsabilidade é criar o objeto principal do jogo e executá-lo.
// Manter o 'main' simples e limpo é uma boa prática de design de software.

#include "Game.h"
#include "GameConstants.h" // Incluído para usar as constantes de tela.

int main()
{
	// 1. Cria uma instância da classe Game, passando a largura e altura da tela.
	//    O construtor da classe Game cuidará de toda a inicialização.
	Game pongGame(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	// 2. Chama o método 'run', que inicia o loop principal do jogo.
	//    O programa ficará "preso" dentro de 'run' até que o jogador feche a janela.
	pongGame.run();
	
	// 3. Quando 'run' termina, o programa encerra.
	//    O 'return 0' indica que o programa terminou com sucesso.
	return 0;
}