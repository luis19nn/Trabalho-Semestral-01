#ifndef TRABSEMEX01_H_INCLUDED
#define TRABSEMEX01_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/*
### TYPEDEF DAS MATRIZES ###
*/

typedef struct Descritor MatrizEsparsa;
typedef struct Matriz Nodo;
typedef struct ListaMatrizes MatrizPai;



/*
### MENUS DAS MATRIZES ###
*/

int menuMatrizAtual(MatrizEsparsa* li);

int menuMatrizOperacoes(MatrizPai* mp, int *index);


/*
### CRIAÇÃO E LIBERAÇÃO DA MATRIZ PAI ###
*/

MatrizPai* criaMatrizPai();

void liberaMatrizPai(MatrizPai* mp);



/*
### CRIAÇÃO E REMOÇÃO DA MATRIZ ESPARSA ###
*/

MatrizEsparsa* criaMatriz(MatrizPai* mp, char *nome, int linMAX, int colMAX);

int removeMatriz(MatrizPai* mp, char *nome);



/*
### INFORMAÇÕES DA MATRIZ ESPARSA ###
*/

int tamanhoMatrizEsparsa(MatrizEsparsa* li);

int matrizEsparsaVazia(MatrizEsparsa* li);



/*
### INSERÇÃO NA MATRIZ ESPARSA ###
*/

int insereDado(MatrizEsparsa* li, float dadoNovo, int lin, int col);



/*
### REMOÇÃO DA MATRIZ ESPARSA ###
*/

int removeDado(MatrizEsparsa* li, int lin, int col);



/*
### CONSULTA NA MATRIZ ESPARSA ###
*/

int buscaLinhaColuna(MatrizEsparsa* li, float dadoInformado, int *buscaLin, int *buscaCol);



/*
### IMPRIME AS MATRIZES ###
*/

int imprimeMatrizAtual(MatrizEsparsa* li);

int imprimeMatrizAtualTransposta(MatrizEsparsa* li);

int imprimeMatrizDiagonalPrincipal(MatrizEsparsa* li);

int imprimeTodasMatrizes(MatrizPai* mp);

int imprimeTodasMatrizesEmLinha(MatrizPai* mp);

int usarImprimeTodasMatrizesEmLinha(MatrizPai* mp);



/*
### ACESSA A MATRIZ ###
*/

MatrizEsparsa* acessaMatriz(MatrizPai* mp, char *nome);



/*
### OPERAÇÕES COM MATRIZES ###
*/

int multiplicaMatrizes(MatrizPai* mp, char *nome1, char *nome2, char *nome3);

int somaMatrizes(MatrizPai* mp, char *nome1, char *nome2, char* nome3);

int subtraiMatrizes(MatrizPai* mp, char *nome1, char *nome2, char* nome3);


#endif // TRABSEMEX01_H_INCLUDED
