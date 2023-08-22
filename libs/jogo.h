// Marcelo Vieira Magalhães 23.1.4007

/*
Esta é a biblioteca jogo.h

Nesta biblioteca estão as principais funções que fazem o jogo funcionar e as definições de struct que são usadas por todo o programa;
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "cores.h"

#ifndef JOGO_H
#define JOGO_H

#define MAX 50


typedef struct{

    int num; // Número em display no tabuleiro

    int cor;
    /*
    Cores:
        0 -> Vermelho, marcado para não entrar na soma da linha/coluna
        1 -> Verde, marcado como que entra na soma linha/coluna
        2 -> Negrito, exclusivo para a soma de cada linha/coluna, se em negrito, a soma está correspondente
        outro -> Sem cor, entra na soma linha/coluna, a não ser que seja a própria soma da linha/coluna
    */

    int gabarito;
    /*
    Gabarito:
        0 -> não entra na soma
        1 -> entra na soma
    */
} Elemento;


typedef struct {
    Elemento** tabuleiro;   // Uma matriz de elementos, representa o tabuleiro
    int n;                  // Dimensões do tabuleiro
    char dif;               // Dificuldade
    char nome[MAX];         // Nome do jogador
    long long tempo;        // Tempo de jogo
} Jogo;


Elemento** criaMatriz (int m, int n) {

    // Função que cria uma matriz da struct Elemento

	Elemento** mat = malloc(m * sizeof(Elemento*));
	
	for (int i=0; i<m; i++)
		mat[i] = malloc(n * sizeof(Elemento));
	
	return mat;
}


void liberaMatriz (Elemento** matriz, int m) {

    // Função que libera uma matriz da struct Elemento

	for (int i=0; i<m; i++)
		free(matriz[i]);
	free(matriz);
}


void limpaBuffer() {

    // Função para limpar buffer, geralmente antes de um scanf

    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


int charToInt(char c) {

    // Função que converte char em int

    return c - '0';
}


Elemento** criaTabuleiro (int n) {

    // Função que cria e retorna uma matriz de Elementos (um tabuleiro) de tamanho n

    srand(time(NULL));

    Elemento** tab = criaMatriz(n+1, n+1);

    // Gera números aleatórios de 1 a 9 para compor o tabuleiro
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tab[i][j].num = rand()%9 + 1;
        }
    }
    
    // Gera um gabarito para o jogo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tab[i][j].gabarito = rand()%2;
        }
    }
    
    // Coloca as somas de cada linha e coluna na última posição
    for (int i = 0; i < n; i++) {
        int somaLinha = 0, somaColuna = 0;

        for (int j = 0; j < n; j++) {
            if(tab[i][j].gabarito)
                somaLinha += tab[i][j].num;
            if(tab[j][i].gabarito)
                somaColuna += tab[j][i].num;
        }

        tab[i][n].num = somaLinha;
        tab[n][i].num = somaColuna;
    }

    // Inicia o atributo "cor" de todos os elementos do tabuleiro em -1
    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < n+1; j++) {
            tab[i][j].cor = -1;
        }
    }

    return tab;
}


// *TODO: imprimeTabuleiro
void imprimeTabuleiro (Elemento** tab, int n) {
    printf("\n" TAB_TL);
    for (int j = 0; j < n-1; j++)
            printf(TAB_HOR TAB_TJ);
    printf(TAB_HOR TAB_TR);
    
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < n; j++)
        {   
            switch (tab[i][j].cor) {

                case 0:
                    printf(TAB_VER RED("%d"), tab[i][j].num);
                    break;
                case 1:
                    printf(TAB_VER GREEN("%d"), tab[i][j].num);
                    break;
                case 2:
                    printf(TAB_VER BOLD("%d"), tab[i][j].num);
                    break;
                default:
                    printf(TAB_VER "%d", tab[i][j].num);
            }
        }
        if(i<n)
            printf(TAB_VER"%d", tab[i][n].num);
        printf("\n");
    }
    
}


void leComando(int* saida){

    /*
    Função para ler o comando do jogador: altera o conteúdo para qual o parâmetro 'saida(int*)' aponta, de acordo com a seguinte padronização:
        0 -> voltar
        1 -> manter
        2 -> remover
        3 -> dica
        4 -> resolver
        5 -> salvar

        -1 -> Comando inválido
    */
    
    char comando[10], c;

    limpaBuffer();

    scanf("%c", &c); 

    int i = 0;
    while (((c != ' ') && (c != '\n')) && (i != 10)){
        comando[i] = c;
        scanf("%c", &c);
        i++;
    }

    ungetc(c, stdin);
    comando[i] = '\0';
    
    if((!strcmp(comando, "Manter")) || (!strcmp(comando, "manter")) || (!strcmp(comando, "MANTER"))){
        *saida = 1;
    } else if((!strcmp(comando, "Remover")) || (!strcmp(comando, "remover")) || (!strcmp(comando, "REMOVER"))){
        *saida = 2;
    } else if((!strcmp(comando, "Dica")) || (!strcmp(comando, "dica")) || (!strcmp(comando, "DICA"))){
        *saida = 3;
    } else if((!strcmp(comando, "Resolver")) || (!strcmp(comando, "resolver")) || (!strcmp(comando, "RESOLVER"))){
        *saida = 4;
    } else if((!strcmp(comando, "Salvar")) || (!strcmp(comando, "salvar")) || (!strcmp(comando, "SALVAR"))){
        *saida = 5;
    } else if((!strcmp(comando, "Voltar")) || (!strcmp(comando, "voltar")) || (!strcmp(comando, "VOLTAR"))){
        *saida = 0;
    } else {
        *saida = -1;
    }   
}


int manterOuRemover(Jogo* jogo, int manter) {

    // Função para os comandos manter e remover

    char comArgs[5];
    int m, n;

    fgets(comArgs, 5, stdin);

    if (isdigit(comArgs[1]) && isdigit(comArgs[2]) && ((comArgs[3] == '\n'))) {
        m = charToInt(comArgs[1]);
        n = charToInt(comArgs[2]);
        ungetc(comArgs[3], stdin);
    }
    else {
        m = 0;
        n = 0;
        ungetc('\n', stdin);
    }

    // Valida as coordenada do tabuleiro
    if (m < 1 || m > jogo->n || n < 1 || n > jogo->n)
        return 1;


    if (manter)
        jogo->tabuleiro[m-1][n-1].cor = 1;
    else   
        jogo->tabuleiro[m-1][n-1].cor = 0;

    return 0;
}


int confereSomas(Jogo* jogo) {

    // Confere se as somas estão batendo, se sim, muda a cor da soma ao final da tabela
    // Retorna 0 se o jogo ainda deve continuar e 1 se o jogador ganhou o jogo.

    int somaLinha, somaColuna;
    int erros = 0;

    for (int i = 0; i < jogo->n; i++) {
        somaLinha = 0;
        somaColuna = 0;

        for(int j = 0; j < jogo->n; j++) { 
            if (!jogo->tabuleiro[i][j].cor) {
                somaLinha += jogo->tabuleiro[i][j].num;
                somaColuna += jogo->tabuleiro[j][i].num;
            }
        }

        // Checa as somas e muda a cor caso a soma bata ou não
        if (somaLinha == jogo->tabuleiro[i][jogo->n].num)
            jogo->tabuleiro[i][jogo->n].cor = 2;
        else {
            jogo->tabuleiro[i][jogo->n].cor = -1;
            erros++;
        }
    }

    // Checa se o jogo acabou
    if (!erros)
        return 1;
    else
        return 0;
}


void jogoGanho() {
    printf(GREEN("PARABÉNS!") " Você ganhou o jogo!");
}


void duranteJogo(Jogo* jogo) {

    while (1) {
        imprimeTabuleiro(jogo->tabuleiro, jogo->n);

        int saida;
        leComando(&saida);

        switch(saida) {
            case 1:
                if (manterOuRemover(jogo, 1)) {
                    printf("\033[2J");
                    printf("\nComando inválido, tente novamente");
                }
                else if(confereSomas(jogo))
                    jogoGanho();
                else
                    printf("\033[2J");
                break;
            case 2:
                if (manterOuRemover(jogo, 0)) {
                    printf("\033[2J");
                    printf("\nComando inválido, tente novamente");
                }
                else if(confereSomas(jogo)) {
                    printf("\033[2J");
                    jogoGanho();
                }
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            default:
                printf("\033[2J");
                printf("\nComando inválido, tente novamente");
        }
    }
    
}

// *TODO: resolveJogo()

#endif