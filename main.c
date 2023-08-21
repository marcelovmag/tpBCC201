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

    char escolha;
    int isJogoUp = 0;

    printTitle();
    telaDeInicio(&escolha);


    do
    {
        switch (escolha) {
            case '0':
            // Encerra o programa
                break;
            case '1':
                // TODO: novo jogo
                isJogoUp = 1;
                op1(&jogo);     
                break;
            case '2':
                // TODO: continuar jogo salvo em arquivo
                break;
            case '3':
                // TODO: continuar jogo atual
                op3(isJogoUp, &jogo);
                break;
            case '4':
                // TODO: exibir ranking
                break;
        }
    } while (escolha != '0');
    
    return 0;
}