// Marcelo Vieira Magalhães 23.1.4007

/*
Este é o código fonte main.c

Neste se executa o jogo Sumplete pelas funções das bibliotecas menu.h e jogo.h
*/

#include <locale.h>
#include "libs/menu.h"

int main() {

    setlocale(LC_ALL, "Portuguese");

    Jogo jogo;

    char escolha = 0;
    int isJogoUp = 0;

    printTitle();

    do
    {
        switch (escolha) {
            case '0':
            // Encerra o programa
                break;
            case '1':
                // TODO: novo jogo
                isJogoUp = 1;
                op1(&jogo, &isJogoUp);     
                break;
            case '2':
                // TODO: continuar jogo salvo em arquivo
                break;
            case '3':
                // TODO: continuar jogo atual
                op3(&jogo, &isJogoUp);
                break;
            case '4':
                // TODO: exibir ranking
                break;
        }
        telaDeInicio(&escolha);
    } while (escolha != '0');

    if(isJogoUp) {
        liberaMatriz(jogo.tabuleiro, jogo.n);
    }
    
    return 0;
}