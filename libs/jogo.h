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
    time_t tempo;           // Tempo de jogo
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

    // Função para limpar buffer, geralmente acompanhada de um scanf

    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}


int charToInt(char c) {

    // Função que converte char em int

    return c - '0';
}

void geraGabarito(Elemento*** tab, int n, char dif) {
    switch (dif)
    {
    case 'F':
        // Gera um gabarito para o jogo (sem restrições)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                (*tab)[i][j].gabarito = rand()%2;
            }
        }
        break;
    
    default:
        int valida;

        do {
            valida = 0;

            // Gera um gabarito para o jogo (sem restrições)
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    (*tab)[i][j].gabarito = rand()%2;
                }
            }

            // Faz a soma das linhas e colunas para futura validação
            for (int i = 0; i < n; i++) {
                int somaLinha = 0, somaColuna = 0;
                for (int j = 0; j < n; j++) {
                    somaLinha += (*tab)[i][j].gabarito;
                    somaColuna += (*tab)[j][i].gabarito;
                }
                if (!somaLinha || !somaColuna || somaLinha == n || somaColuna == n) {
                    valida++;
                }
            }

        // Verifica se há alguma linha ou coluna com soma igual a 0 ou igual à soma de todos os números dela
        } while (valida);
        break;
    }
}

void preencheTabuleiro (Elemento*** tab, int n, char dif) {
    switch (dif)
    {
    case 'D':
        // Gera números aleatórios de -9 a 9 para compor o tabuleiro
        for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++) {
                (*tab)[i][j].num = rand()%19 - 9;
            }
        }
        break;

    default:
        // Gera números aleatórios de 1 a 9 para compor o tabuleiro
        for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++) {
                (*tab)[i][j].num = rand()%9 + 1;
            }
        }
        break;
    }
}

Elemento** criaTabuleiro (int n, char dif) {

    // Função que cria e retorna uma matriz de Elementos (um tabuleiro) de tamanho n, na dificuldade Fácil

    srand(time(NULL));

    Elemento** tab = criaMatriz(n+1, n+1);

    preencheTabuleiro(&tab, n, dif);

    geraGabarito(&tab, n, dif);
    
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


void imprimeTabuleiro (Elemento** tab, int n) {
    printf("\n   ");
    for (int j = 0; j < n; j++)
            printf(YELLOW("c%d "), j+1);

    printf("\n  " TAB_TL);
    
    for (int j = 0; j < n-1; j++)
            printf(TAB_HOR TAB_HOR TAB_TJ);
    printf(TAB_HOR TAB_HOR TAB_TR "\n");
    
    for (int i = 0; i < n+1; i++)
    {
        if(i<n)
            printf(YELLOW("l%d"), i+1);

        for (int j = 0; j < n+1 && i < n; j++)
        {   
            switch (tab[i][j].cor) {

                case 0:
                    printf(TAB_VER RED("%2d"), tab[i][j].num);
                    break;
                case 1:
                    printf(TAB_VER GREEN("%2d"), tab[i][j].num);
                    break;
                case 2:
                    printf(TAB_VER CYAN("%2d"), tab[i][j].num);
                    break;
                default:
                    printf(TAB_VER "%2d", tab[i][j].num);
            }            
            
        }

        printf("\n");

        if (i<n-1) {
            printf("  "TAB_ML);
            for (int j = 0; j < n-1; j++)
                printf(TAB_HOR TAB_HOR TAB_MJ);
            printf(TAB_HOR TAB_HOR TAB_MR "\n");
            }
        else if (i<n) {
            printf("  "TAB_BL);
            for (int j = 0; j < n-1; j++)
                printf(TAB_HOR TAB_HOR TAB_BJ);
            printf(TAB_HOR TAB_HOR TAB_BR);
        }
        else {
            printf("  ");
            for (int j = 0; j < n; j++)
            {
                switch (tab[i][j].cor) {
                case 2:
                    printf(CYAN(" %2d"), tab[i][j].num);
                    break;
                default:
                    printf(" %2d", tab[i][j].num);
                }
            }
            printf("\n\n");
        }
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
            if (jogo->tabuleiro[i][j].cor) {
                somaLinha += jogo->tabuleiro[i][j].num;
            }
            if (jogo->tabuleiro[j][i].cor) {
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

        if (somaColuna == jogo->tabuleiro[jogo->n][i].num)
            jogo->tabuleiro[jogo->n][i].cor = 2;
        else {
            jogo->tabuleiro[jogo->n][i].cor = -1;
            erros++;
        }
    }

    // Checa se o jogo acabou
    if (!erros)
        return 1;
    else
        return 0;
}


void jogoGanho(Jogo* jogo, int* isJogoUp) {
    jogo->tempo += time(NULL);

    imprimeTabuleiro(jogo->tabuleiro, jogo->n);

    printf(GREEN("PARABÉNS!") " Você ganhou o jogo!\n\nJogador: %sTamanho: %d\nTempo: %ld\n\nPressione enter para continuar.", jogo->nome, jogo->n, jogo->tempo);
    char c;
    limpaBuffer();
    scanf("%c", &c);
    printf("\033[2J");
    liberaMatriz(jogo->tabuleiro, jogo->n);
    *isJogoUp = 0;
}


int dica(Jogo* jogo) {
    int m, n;
    srand(time(NULL));

    int count = 0;
    do
    {
        m = rand() % jogo->n;
        n = rand() % jogo->n;

        count++;
        if (count > 9000)
            return 1;

    } while (!jogo->tabuleiro[m][n].gabarito || jogo->tabuleiro[m][n].cor == 1);

    jogo->tabuleiro[m][n].cor = 1;
    
    return 0;
}


int salvar(Jogo* jogo) {

    // Lê o nome do arquivo
    //limpaBuffer();

    char c;
    scanf("%c", &c);

    char nomeArquivo[30] = {};
    fgets(nomeArquivo, 30, stdin);
    int tam = strlen(nomeArquivo);

    char txt[4];
 
    for (int i = 1; i < 5; i++) {
        txt[i] = nomeArquivo[tam - i];
    }

    // Valida se terminado em .txt
    if (strcmp(txt, ".txt"))
        return 1; // Retorna 1: nome inválido

    // No caso de válido, procede em criar o arquivo
    FILE* arquivo = fopen(strcat("./files/jogosSalvos/", nomeArquivo), "w");

    // Printa a dimensão da matriz quadrada
    fprintf(arquivo, "%d", jogo->n);

    // Printa os valores da matriz
    for (int i = 0; i < jogo->n; i++) {
        for (int j = 0; j < jogo->n; j++) {
            fprintf(arquivo, "%d", jogo->tabuleiro[i][j].num);
            if (i != jogo->n - 1)
                fprintf(arquivo, " ");
            else
                fprintf(arquivo, "\n");
        }
    }

    // Printa soma das linhas
    for (int i = 0; i < jogo->n; i++) {
        fprintf(arquivo, "%d", jogo->tabuleiro[i][jogo->n].num);
        if (i != jogo->n - 1)
                fprintf(arquivo, " ");
            else
                fprintf(arquivo, "\n");
    }
    
    // Printa soma das colunas
    for (int i = 0; i < jogo->n; i++) {
        fprintf(arquivo, "%d", jogo->tabuleiro[jogo->n][i].num);
        if (i != jogo->n - 1)
                fprintf(arquivo, " ");
            else
                fprintf(arquivo, "\n");
    }

    // Calcula o número m de valores marcados para manter e salva os índices destes
    int m = 0, ind[81][2];
    for (int i = 0; i<jogo->n; i++) {
        for (int j = 0; j<jogo->n; j++) {
            if (jogo->tabuleiro[i][j].cor) {
                ind[m][0] = i;
                ind[m][1] = j;
                m++;
            }
        }
    }

    // Printa o número m de valores marcados para manter
    fprintf(arquivo, "%d\n", m);

    // Printa os m números marcados para manter
    for (int i = 0; i < m; i++) {
        fprintf(arquivo, "%d %d\n", ind[m][0], ind[m][1]);
    }

    // Calcula o número r de valores marcados para manter e salva os índices destes
    int r = 0;
    for (int i = 0; i<jogo->n; i++) {
        for (int j = 0; j<jogo->n; j++) {
            if (!jogo->tabuleiro[i][j].cor) {
                ind[r][0] = i;
                ind[r][1] = j;
                r++;
            }
        }
    }

    // Printa o número r de valores marcados para manter
    fprintf(arquivo, "%d\n", r);

    // Printa os r números marcados para manter
    for (int i = 0; i < r; i++) {
        fprintf(arquivo, "%d %d\n", ind[r][0], ind[r][1]);
    }
    
    // Printa o nome do jogador
    fprintf(arquivo, "%s", jogo->nome);

    // Printa o tempo de jogo
    fprintf(arquivo, "%ld", jogo->tempo + time(NULL));

    // Retorna 0, jogo salvo
    return 0;
}


void duranteJogo(Jogo* jogo, int* isJogoUp) {

    jogo->tempo -= time(NULL);

    int saida = 1;

    while (saida) {
        confereSomas(jogo);
        imprimeTabuleiro(jogo->tabuleiro, jogo->n);

        leComando(&saida);

        switch(saida) {
            case 1:
            // manter
                if (manterOuRemover(jogo, 1)) {
                    printf("\033[2J");
                    printf("\nComando inválido, tente novamente");
                }
                else if(confereSomas(jogo)) {
                    printf("\033[2J");
                    jogoGanho(jogo, isJogoUp);
                    saida = 0;
                }
                else
                    printf("\033[2J");
                break;
            case 2:
            // remover
                if (manterOuRemover(jogo, 0)) {
                    printf("\033[2J");
                    printf("\nComando inválido, tente novamente");
                }
                else if(confereSomas(jogo)) {
                    printf("\033[2J");
                    jogoGanho(jogo, isJogoUp);
                    saida = 0;
                }
                else
                    printf("\033[2J");
                break;
            case 3:
            // dica
                if (dica(jogo)) {
                    printf("\033[2J");
                    printf("\nNão foi possível dar mais dicas!");
                }
                else 
                    printf("\033[2J");

                if(confereSomas(jogo)) {
                    printf("\033[2J");
                    jogoGanho(jogo, isJogoUp);
                    saida = 0;
                }
                break;
            case 4:
            // resolver

                break;
            case 5:
            // salvar
                if (salvar(jogo)) {
                    printf("Não foi possível salvar o jogo, tente informar um nome com final .txt\n");
                }
                else {

                }
                break;
            case 0:
            // voltar
                printf("\033[2J");
                limpaBuffer();
                jogo->tempo += time(NULL);
                break;
            default:
                printf("\033[2J");
                printf("\nComando inválido, tente novamente");
        }
    }
    
}

// *TODO: resolveJogo()

#endif