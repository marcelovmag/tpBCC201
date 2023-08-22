#include <stdio.h>
#include <stdlib.h>

#include "cores.h"
#include "jogo.h"

void printaJogo(Jogo* jogo){
    printf(TAB_TL);
    for (int i = 0; i < 12; i++){
        printf(TAB_HOR);
    }
    printf(TAB_TR "\n");
    printf(TAB_VER "SUMPLETE %dx%d" TAB_VER "\n", jogo->n, jogo->n);
    printf(TAB_BL);
    for (int i = 0; i < 12; i++){
        printf(TAB_HOR);
    }
    printf(TAB_BR "\n\n");

    printf("    " TAB_TL);
    for (int i = 0; i < jogo->n - 1; i++){
        printf(TAB_HOR TAB_HOR TAB_HOR TAB_TJ);
    }
    printf(TAB_HOR TAB_HOR TAB_HOR TAB_TR "\n    " TAB_VER);
    for (int i = 1; i <= jogo->n; i++){
        printf(BOLD("%2.d ") TAB_VER, i);
    }
    printf("\n" TAB_TL);
    for (int i = 0; i < jogo->n + 1; i++){
        printf(TAB_HOR TAB_HOR TAB_HOR TAB_MJ);
    }
    printf(TAB_HOR TAB_HOR TAB_HOR TAB_TR "\n");
    for(int i = 0; i < jogo->n; i++){
       printf(TAB_VER BOLD("%2.d "), i + 1);
        for (int j = 0; j < jogo->n; j++){
            if (jogo.entrada[i][j] == 1){
                printf(TAB_VER);
                if(jogo.valores[i][j] != 0){
                    printf(GREEN("%2.d "), jogo.valores[i][j]);
                } else {
                    printf(GREEN(" 0 "));
                }
            } else if(jogo.entrada[i][j] == 0){
                printf(TAB_VER);
                if(jogo.valores[i][j] != 0){
                    printf(RED("%2.d "), jogo.valores[i][j]);
                } else {
                    printf(RED(" 0 "));
                }
            }else{
                printf(TAB_VER);
                if(jogo.valores[i][j] != 0){
                    printf("%2.d ", jogo.valores[i][j]);
                } else {
                    printf(" 0 ");
                }
            }
        }
        if(jogo.gabHorz[i] != 0){
            if(jogo.userHorz[i] == jogo.gabHorz[i]){
                if(jogo.gabHorz[i] <= -9){
                    printf(TAB_VER GREEN("%3.d")TAB_VER "\n", jogo.gabHorz[i]);                
                }else{
                    printf(TAB_VER GREEN(" %2.d")TAB_VER "\n", jogo.gabHorz[i]);                
                }
            }else{
                if(jogo.gabHorz[i] <= -9){
                    printf(TAB_VER "%3.d" TAB_VER "\n", jogo.gabHorz[i]);                
                }else{
                    printf(TAB_VER " %2.d" TAB_VER "\n", jogo.gabHorz[i]);                
                }
            }
        } else {
            if(jogo.userHorz[i] == jogo.gabHorz[i]){
                printf(TAB_VER GREEN("  0") TAB_VER "\n");                
            }else{
                printf(TAB_VER "  0" TAB_VER "\n");
            }
        }

        if(i < jogo->n - 1){
            printf(TAB_ML);
            for (int j = 0; j < jogo->n + 1; j++){
                printf(TAB_HOR TAB_HOR TAB_HOR TAB_MJ);
            }
            printf(TAB_HOR TAB_HOR TAB_HOR TAB_MR "\n");
        }
    }
    printf(TAB_BL TAB_HOR TAB_HOR TAB_HOR);
    for (int i = 0; i < jogo->n + 1; i++){
        printf(TAB_MJ TAB_HOR TAB_HOR TAB_HOR);
    }
    printf(TAB_BR "\n    " TAB_VER);
    for (int i = 0; i < jogo->n; i++){
        if(jogo.gabVert[i] != 0){
            if (jogo.userVert[i] == jogo.gabVert[i]){
                if(jogo.gabVert[i] <= -9){
                    printf(GREEN("%3.d") TAB_VER, jogo.gabVert[i]);                
                }else{
                    printf(GREEN(" %2.d") TAB_VER, jogo.gabVert[i]);                
                }          
            }else{
                if(jogo.gabVert[i] <= -9){
                    printf("%3.d" TAB_VER, jogo.gabVert[i]);                
                }else{
                    printf(" %2.d" TAB_VER, jogo.gabVert[i]);                
                }
            }
        } else {
            if (jogo.userVert[i] == jogo.gabVert[i]){
                printf(GREEN("  0") TAB_VER);             
            }else{
                printf("  0" TAB_VER);
            }
        }
    }
    printf("\n    " TAB_BL TAB_HOR TAB_HOR TAB_HOR);
    for (int i = 0; i < jogo->n - 1; i++){
        printf(TAB_BJ TAB_HOR TAB_HOR TAB_HOR);
    }
    printf(TAB_BR "\n\n\n" BOLD("Selecione uma Ação:\n\n") TAB_TL);
    for (int i = 0; i < 15; i++){
        printf(TAB_HOR);
    }
    printf(TAB_TR"\n");
    printf(TAB_VER GREEN("Manter\t\t") TAB_VER "\n" TAB_VER RED("Remover\t") TAB_VER "\n");
    printf(TAB_VER "Salvar\t\t" TAB_VER "\n" TAB_VER "Dica\t\t" TAB_VER "\n" TAB_VER "Resolver\t" TAB_VER "\n" TAB_VER "Voltar\t\t" TAB_VER "\n" TAB_BL);
    for (int i = 0; i < 15; i++){
        printf(TAB_HOR);
    }
    printf(TAB_BR "\n\n");
}