#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrabSemEx01.h"
#include "TrabSemEx01.c"
#include "MenuMatrizAtual.c"
#include "MenuMatrizOperacoes.c"

int main() 
{
    MatrizPai *mp = NULL;
    MatrizEsparsa *li = NULL;

    char entrada, nome[10];
    int index[3] = {1, 1, 1};

    while (1) {
        printf("\n=========MENU=DE=MATRIZES==========");
        printf("\n 1) Criar uma Lista de Matrizes");
        printf("\n 2) Liberar uma Lista de Matrizes");
        printf("\n 3) Inserir uma Matriz");
        printf("\n 4) Remover uma Matriz");
        printf("\n 5) Acessar uma Matriz");
        printf("\n 6) Realizar operacoes com Matrizes");
        printf("\n 7) Imprimir todas as Matrizes");
        printf("\n 8) Sair");
        printf("\n==================================");
        printf("\n\nOpcao: ");
        scanf("%c", &entrada);
        fflush(stdin);

        switch (entrada) {
            case '1': ;
                mp = criaMatrizPai();

                if(mp == NULL) {
                    printf("\n\n###ERRO AO CRIAR!\nNao foi possivel alocar memoria para a estrutura.\n\n");
                } else {
                    printf("\n\nLista de Matrizes criada com sucesso!\n\n");
                }

                break;
            case '2':
                if (mp != NULL) {
                    liberaMatrizPai(mp);
                    mp = NULL;

                    printf("\n\nA Lista de Matrizes foi liberada!\n\n");
                } else {
                    printf("\n\n###ERRO!\nNao ha lista de matrizes para liberar.\n\n");
                }   

                break;
            case '3': ;
                int linMAX, colMAX, tipoLinMAX, tipoColMAX;

                printf("\nInforme o nome da Matriz: ");
                scanf("%s", nome);

                printf("\nInforme o numero de linhas totais da Matriz: ");
                tipoLinMAX = scanf("%d", &linMAX);
                fflush(stdin);

                printf("\nInforme o numero de colunas totais da Matriz: ");
                tipoColMAX = scanf("%d", &colMAX);
                fflush(stdin);

                if (tipoLinMAX && tipoColMAX) {
                    li = criaMatriz(mp, nome, linMAX, colMAX);

                    if(li == NULL) {
                        printf("\n\n###ERRO AO CRIAR!\nSeus erros podem ser:\nNao foi possivel alocar memoria para a estrutura.\nAs linhas e colunas informadas DEVEM ser maiores que zero.\nEh necessario criar uma Lista de Matrizes antes de criar uma Matriz.\nO nome da Matriz pode ja estar sendo utilizado.\n\n");
                    } else {
                        printf("\n\nMatriz criada com sucesso!\n\n");
                    }
                } else {
                    printf("\n\n###ERRO NA ENTRADA DE DADOS!\nOs valores de linha e coluna devem ser inteiros.\n\n");
                }

                break;
            case '4': ;
                if (!usarImprimeTodasMatrizesEmLinha(mp)) {
                    printf("\n\n###ERRO!\nA Lista de Matrizes esta vazia ou nao existe.\n\n");
                    break;
                }

                printf("\nDigite o nome da Matriz a ser removida da Lista de Matrizes: ");
                scanf("%s", nome);
                fflush(stdin);

                int mpRemoveMatriz = removeMatriz(mp, nome);

                if (mpRemoveMatriz) {
                    printf("\nMatriz removida com sucesso da Lista de Matrizes!\n\n");
                } else {
                    printf("\n\n###ERRO AO REMOVER!\nA Lista de Matrizes esta nula ou a Matriz informada nao foi encontrada.\n\n");
                }

                break;
            case '5': ;
                if (!usarImprimeTodasMatrizesEmLinha(mp)) {
                    printf("\n\n###ERRO!\nA Lista de Matrizes esta vazia ou nao existe.\n\n");
                    break;
                }

                printf("\nDigite o nome da Matriz a ser acessada na Lista de Matrizes: ");
                scanf("%s", nome);
                fflush(stdin);

                li = acessaMatriz(mp, nome);

                if (li != NULL) {
                    menuMatrizAtual(li);
                } else {
                    printf("\n\n###ERRO AO ACESSAR!\nA Lista de Matrizes esta nula ou a Matriz informada nao foi encontrada.\n\n");
                }

                break;
            case '6': ;
                if (!usarImprimeTodasMatrizesEmLinha(mp)) {
                    printf("\n\n###ERRO!\nA Lista de Matrizes esta vazia ou nao existe.\n\n");
                    break;
                }

                menuMatrizOperacoes(mp, index);

                break;
            case '7': ;
                if (!usarImprimeTodasMatrizesEmLinha(mp)) {
                    printf("\n\n###ERRO!\nA Lista de Matrizes esta vazia ou nao existe.\n\n");
                    break;
                }

                int mpImprimeTodasMatrizes = imprimeTodasMatrizes(mp);

                if (!mpImprimeTodasMatrizes) {
                    printf("\n\n###ERRO AO IMPRIMIR!\nA Lista de Matrizes esta vazia ou nao existe.\n\n");
                }

                break;
            case '8': ;
                if (mp != NULL) {
                    liberaMatrizPai(mp);
                }
                
                exit(0);
            default:
                printf("\n\n###ERRO!\nOpcao de menu invalida.\n\n");
        }
    }

    return 0;
}
