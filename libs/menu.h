// Marcelo Vieira Magalhães 23.1.4007

/*
Esta é a biblioteca menu.h

Nesta biblioteca estão as funções principais de exibição do menu inicial e de tratamento das escolhas do usuário no menu
*/

#include <stdio.h>
#include <stdlib.h>

#include "cores.h"
#include "jogo.h"

#define MAX 50


void printTitle() {
    FILE* title = fopen("../files/title.txt", "r");
    char linha[101];

    for (int i = 0; i < 8; i++) {
        if(feof(title))
            break;
        fgets(linha, 100, title);
        printf("%s", linha);
    }

    fclose(title);
}


void printaMenu() {
    printf("\n\nOpções:\n0. Sair do jogo\n1. Começar um novo jogo\n2. Continuar um jogo salvo em arquivo\n3. Continuar o jogo atual\n4. Exibir o ranking\n" BOLD("Durante o jogo, digite \"voltar\" para retornar ao menu.") "\n\nEscolha uma opção: ");
}


void telaDeInicio(char* escolha) {

    // Exibe o menu principal
    printaMenu();

    limpaBuffer();
    
    // Lê e trata a escolha do usuário
    scanf("%c", escolha);
    while (*escolha != '0' && *escolha != '1' && *escolha != '2' && *escolha != '3' && *escolha != '4') {
        printf("\nTente escolher uma opção válida.");
        printaMenu();
        scanf("%c", escolha);
    }
}


void op1(Jogo* jogo) {
    // Opção 1: Novo jogo

    char tam, dif;

    // Recebe e verifica o valor do tamanho do tabuleiro
    while (1) {
        printf("\nTamanho do tabuleiro (3 a 9): ");
        limpaBuffer();
        scanf("%c", &tam);

        if(tam == '3' || tam == '4' || tam == '5' || tam == '6' || tam == '7' || tam == '8' || tam == '9')
            break;

        printf("\nOpção inválida! [Dica: tente um número entre 3 e 9]");
    }

    // Verifica se o tamanho permite uma dificuldade além de fácil
    if(tam != '3' && tam != '4') {

        // Recebe e verifica o valor da dificuldade
        while (1) {
            printf("\nDificuldade (Fácil, Médio ou Difícil): ");
            limpaBuffer();
            scanf("%c", &dif);

            if(dif == 'F' || dif == 'M' || dif == 'D')
                break;

            printf("\nOpção inválida! [Dica: tente usar F, M ou D]");
        }
    }

    jogo->n = charToInt(tam);
    jogo->dif = dif;
    jogo->tabuleiro = criaTabuleiro(jogo->n);

    duranteJogo(jogo);
}


void op2() {
    char nomeArquivo[MAX];

    printf("\nInforme o nome do arquivo com o jogo salvo: ");
    limpaBuffer();
    fgets(nomeArquivo, MAX, stdin);

    FILE* arquivo = fopen(nomeArquivo, "r");

    if(!feof(arquivo)) {
        printf("\nOcorreu um erro ao ler o arquivo.");
    }
}


void op3(int valida, Jogo* jogo) {
    if (valida) {
        /* TODO: op3 */
    }
    else 
        printf("\nNão há nenhum jogo em aberto. Tente começar um novo jogo.");
}
