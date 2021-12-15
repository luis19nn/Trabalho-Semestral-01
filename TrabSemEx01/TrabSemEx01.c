#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrabSemEx01.h"

/*
### STRUCT DAS MATRIZES ###
*/

struct Matriz {
    float dado;
    int lin, col;
    struct Matriz *prox;
};

struct Descritor {
    char nome[30];
    struct Matriz *inicio;
    struct Matriz *final;
    struct Descritor *prox;
    int qtd, linMAX, colMAX;
};

struct ListaMatrizes {
    struct Descritor *inicio;
    struct Descritor *final;
    int qtd;
};



/*
### CRIAÇÃO E LIBERAÇÃO DA MATRIZ PAI ###
*/

//CRIA A LISTA DE MATRIZES QUE IRÁ ARMAZENAR OS DESCRITORES DAS MATRIZES
MatrizPai* criaMatrizPai() {
    MatrizPai* mp = (MatrizPai*) malloc(sizeof(MatrizPai));

    if (mp != NULL) {
        mp->inicio = NULL;
        mp->final = NULL;
        mp->qtd = 0;
    }
    
    return mp;
}

//LIBERA A MATRIZ, EXCLUINDO OS NÓS DESCRITORES
void liberaMatrizPai(MatrizPai* mp) {
    if (mp != NULL) {
        MatrizEsparsa* li;
        while (mp->inicio != NULL) {
            li = mp->inicio;
            mp->inicio = mp->inicio->prox;
            free(li);
        }
        free(mp);
    }
}



/*
### CRIAÇÃO E REMOÇÃO DA MATRIZ ESPARSA ###
*/

//CRIA A MATRIZ QUE ARMAZENARÁ OS DADOS E INCLUI ELA NA LISTA DE MATRIZES
MatrizEsparsa* criaMatriz(MatrizPai* mp, char *nome, int linMAX, int colMAX) {
    MatrizEsparsa* li = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));

    if ((li != NULL && mp != NULL) &&
        (linMAX > 0 && colMAX > 0)) {
        
        //VERIFICA SE O NOME ESCOLHIDO JÁ É UTILIZADO, PARA NÃO TER 
        //NOMES REPETIDOS NA LISTA DE MATRIZES
        MatrizEsparsa *liTesteNome = mp->inicio;
        while (liTesteNome != NULL && strcmp(liTesteNome->nome, nome)) {
            liTesteNome = liTesteNome->prox;
        }

        //SE LI FOR DIFERENTE DE NULL, SIGNIFICA QUE FOI ENCONTRADO 
        //UM NOME IGUAL NA LISTA, LOGO NÃO PODERÁ SER INSERIDA A LISTA
        if (liTesteNome != NULL) {
            li = NULL;
        } else {
            strcpy(li->nome, nome);
            li->inicio = NULL;
            li->final = NULL;
            li->qtd = 0;
            li->linMAX = linMAX;
            li->colMAX = colMAX;
            li->prox = NULL;


            if (mp->inicio == NULL)
                mp->inicio = li;
            else
                mp->final->prox = li;
            
            mp->final = li;
            mp->qtd++;
        }

    } else {
        li = NULL;
    }

    return li;
}

//RETIRA A MATRIZ DA LISTA DE MATRIZES
int removeMatriz(MatrizPai* mp, char *nome) {
    if (mp == NULL)
        return 0;
    if (mp->inicio == NULL)
        return 0;

    //PROCURA A MATRIZ QUE SERÁ RETIRADA PELO NOME DELA, 
    //COMPARANDO OS NOMES DAS MATRIZES SALVAS COM O NOME DADO PELO USUÁRIO
    MatrizEsparsa *ant, *li = mp->inicio;
    while (li != NULL && strcmp(li->nome, nome)) {
        ant = li;
        li = li->prox;
    }
    
    //SE LI FOR NULL SIGNIFICA QUE NÃO FOI ENCONTRADO O NOME
    if (li == NULL)
        return 0;
    
    if (li == mp->inicio) {
        //VERIFICA SE O ELEMENTO RETIRADO É O ÚNICO DA MATRIZ
        if (li->prox == NULL) {
            mp->inicio = NULL;
            mp->final = NULL;
        } else {
            mp->inicio = li->prox;
        }
    } else {
        ant->prox = li->prox;

        //SE LI APONTA PRA NULL, SIGNIFICA QUE ELE É O ÚLTIMO ELEMENTO
        if (li->prox == NULL) {
            mp->final = ant;
        }
    }

    free(li);

    mp->qtd--;

    return 1;
}



/*
### INFORMAÇÕES DA MATRIZ ESPARSA ###
*/

int tamanhoMatrizEsparsa(MatrizEsparsa* li) {
    if (matrizEsparsaVazia(li))
        return 0;
    
    return li->qtd;
}

int matrizEsparsaVazia(MatrizEsparsa* li) {
    if (li == NULL)
        return 1;
    if (li->inicio == NULL)
        return 1;
    
    return 0;
}



/*
### INSERÇÃO NA MATRIZ ESPARSA ###
*/

int insereDado(MatrizEsparsa* li, float dadoNovo, int lin, int col) {
    if (li == NULL)
        return 0;
    //IMPEDE DE INSERIR UM DADO IGUAL A 0
    if (dadoNovo == 0)
        return 0;
    //VERIFICA SE A MATRIZ JÁ FOI COMPLETAMENTE PREENCHIDA
    if (li->qtd > (li->linMAX * li->colMAX)) 
        return 0;
    
    //VERIFICA SE A LINHA E COLUNA DO DADO NOVO ESTÁ ENTRE 1 E O LIMITE MÁXIMO,
    //POIS NÃO HÁ LINHA OU COLUNA MENOR OU IGUAL A ZERO E NEM PODE SER INSERIDO
    //UM NUMERO NUMA LINHA OU COLUNA QUE PASSE DO LIMITE
    if (lin <= li->linMAX && lin > 0 &&
        col <= li->colMAX && col > 0) {
        Nodo* no = (Nodo*) malloc(sizeof(Nodo));

        if (no == NULL)
            return 0;

        no->dado = dadoNovo;
        no->lin = lin;
        no->col = col;

        //SE A MATRIZ AINDA ESTIVER VAZIA, O ELEMENTO ATUAL É O PRIMEIRO
        if (matrizEsparsaVazia(li)) {
            no->prox = li->inicio;
            li->inicio = no;

            li->qtd++;

            return 1;
        } else {
            Nodo *ant, *atual = li->inicio;

            //VERIFICA SE ALGUM ELEMENTO JÁ INSERIDO POSSUI A MESMA LINHA E COLUNAS
            //DO ELEMENTO QUE ESTÁ TENTANDO INSERIR, ASSIM IMPEDE QUE SEJA INSERIDO
            //UM ELEMENTO NUMA LINHA E COLUNA JÁ PREENCHIDA
            while (atual != NULL && (atual->lin != lin || atual->col != col)) {
                ant = atual;
                atual = atual->prox;
            }

            if (atual != NULL) {
                return 0;
            }

            atual = li->inicio;

            //INSERE A LINHA DE FORMA ORDENADA NA MATRIZ
            //PROCURANDO O PRIMEIRO ELEMENTO NA MATRIZ QUE POSSUA A LINHA
            //IGUAL OU SUPERIOR À DA LINHA DO DADO NOVO
            //PARA QUE O DADO NOVO SEJA INSERIDO AO LADO DELE, DEPENDENDO DA COLUNA
            while (atual != NULL && atual->lin < lin) {
                ant = atual;
                atual = atual->prox;
            }

            //SE ATUAL FOR DIFERENTE DE NULL, SIGNIFICA QUE FOI ENCONTRADO
            //UM ELEMENTO QUE POSSUA A LINHA IGUAL OU SUPERIOR À LINHA DO DADO NOVO
            //CASO ATUAL SEJA IGUAL A NULL, O ELSE SERÁ EXECUTADO, SIGNIFICANDO QUE
            //A MATRIZ FOI COMPLETAMENTE PERCORRIDA E NÃO HÁ ELEMENTO COM LINHA IGUAL OU SUPERIOR
            //À LINHA DO DADO NOVO
            if (atual != NULL) {
                //AGORA QUE FOI ENCONTRADO O ELEMENTO COM A LINHA IGUAL OU SUPERIOR AO DO ELEMENTO QUE QUEREMOS INSERIR
                //FAREMOS UM LOOP PARA PROCURAR ONDE INSERIR ELE NAQUELA LINHA, COM BASE NA COLUNA
                while (atual != NULL && atual->lin <= lin && atual->col < col) {
                    ant = atual;
                    atual = atual->prox;
                }

                //SE O IF FOR VERDADEIRO, SIGNIFICA QUE O ELEMENTO ATUAL É O PRIMEIRO ELEMENTO DA MATRIZ, E O ELEMENTO
                //QUE QUEREMOS INSERIR DEVE SER INSERIDO ANTES DELE, SE TORNANDO O NOVO PRIMEIRO ELEMENTO
                if (atual == li->inicio) {
                    no->prox = li->inicio;
                    li->inicio = no;
                //SE O IF FOR FALSO, SIGNIFICA QUE IREMOS INSERIR O ELEMENTO NO MEIO DA MATRIZ, ENTRE O ATUAL E O ANTERIOR
                } else {
                    no->prox = ant->prox;
                    ant->prox = no;
                }

                li->qtd++;

                return 1;
            } else {
                no->prox = ant->prox;
                ant->prox = no;

                li->final = no;

                return 1;
            }
        }
    } else {
        return 0;
    }
}


/*
### REMOÇÃO DA MATRIZ ESPARSA ###
*/

int removeDado(MatrizEsparsa* li, int lin, int col) {
    if (li == NULL)
        return 0;

    //O LOOP IRÁ PROCURAR A LINHA E A COLUNA QUE SEJAM IGUAIS ÀS INFORMADAS
    //PARA REMOVER O DADO, CASO ENCONTRE
    Nodo *ant, *no = li->inicio;
    while (no != NULL && (no->lin != lin || no->col != col)) {
        ant = no;
        no = no->prox;
    }

    if (no == NULL)
        return 0;
    
    if (no == li->inicio) {
        if (no->prox == NULL) {
            li->inicio = NULL;
            li->final = NULL;
        } else {
            li->inicio = no->prox;
        }
    } else {
        ant->prox = no->prox;

        if (no->prox == NULL) {
            li->final = ant;
        }
    }

    free(no);

    li->qtd--;

    return 1;
}


/*
### CONSULTA NA MATRIZ ESPARSA ###
*/

int buscaLinhaColuna(MatrizEsparsa* li, float dadoInformado, int *buscaLin, int *buscaCol) {
    if (li == NULL)
        return 0;
    
    Nodo *no = li->inicio;
    while (no != NULL && no->dado != dadoInformado) {
        no = no->prox;
    }

    if (no == NULL) {
        return 0;
    } else {
        *buscaLin = no->lin;
        *buscaCol = no->col;

        return 1;
    }
}

float buscaDado(MatrizEsparsa* li, int linha, int coluna) {
    Nodo *no = li->inicio;
    for (int i = 1; i <= li->linMAX; i++) {
        for (int j = 1; j <= li->colMAX; j++) {
            if (no != NULL && no->lin == linha && no->col == coluna) {
                return no->dado;
            } else if (no != NULL) {
                no = no->prox;
            }
        }
    }

    return 0.0;
}



/*
### IMPRIME AS MATRIZES ###
*/

int imprimeMatrizAtual(MatrizEsparsa* li) {
    if (li == NULL)
        return 0;
    
    Nodo *no = li->inicio;
    printf("\nA Matriz %s possui os seguintes elementos: \n", li->nome);
    for (int lin = 1; lin <= li->linMAX; lin++) {
        printf("[ ");

        for (int col = 1; col <= li->colMAX; col++) {
            if (no != NULL && no->lin == lin && no->col == col) {
                printf("%.2f ", no->dado);
                no = no->prox;
            } else {
                printf("0.00 ");
            }
        }

        printf("]\n");
    }
    printf("\n");
    
    return 1;
}

int imprimeMatrizAtualTransposta(MatrizEsparsa* li) {
    if (li == NULL)
        return 0;
    
    Nodo *no = li->inicio;
    printf("\nA Matriz Transposta de %s equivale a: \n", li->nome);

    //DIFERENTE DE MOSTRAR A MATRIZ NORMAL, NA TRANSPOSTA VOCÊ TRAVA A COLUNA E PERCORRE AS LINHAS
    //DESSA FORMA AS LINHAS SE TORNAM COLUNAS E AS COLUNAS, LINHAS
    for (int col = 1; col <= li->colMAX; col++) {
        printf("[ ");

        for (int lin = 1; lin <= li->linMAX; lin++) {
            //O LOOP VERIFICA SE A LINHA E COLUNA DO ELEMENTO É IGUAL AOS DO FOR
            //É NECESSÁRIO O LOOP POIS DEVE-SE PERCORRER A MATRIZ PROCURANDO O ELEMENTO CORRESPONDENTE
            //E ENTÃO É NECESSÁRIO PERCORRER DE NOVO, DO INÍCIO
            //POIS OS ELEMENTOS ESTÃO SALVOS SEGUINDO A LINHA COMO PRINCIPAL FATOR
            //EXEMPLO: DADO 1X1 = 2, DADO 2X1 = 1
            //NA TRANSPOSTA, O DADO 2X1 É O SEGUNDO ELEMENTO, MAS O DADO 2X1 ESTÁ SALVO DEPOIS DO DADO 1X2, LOGO É O TERCEIRO ELEMENTO
            //DA MATRIZ FÍSICA, POR ISSO EU PRECISO FAZER UM LAÇO PARA PRINTAR NA ORDEM LÓGICA DA TRASNPOSTA
            while (no != NULL && (no->lin != lin || no->col != col)) {
                no = no->prox;
            }

            if (no == NULL) {
                printf("0.00 ");
                no = li->inicio;
            } else {
                printf("%.2f ", no->dado);
                no = li->inicio;
            }
        }

        printf("]\n");
    }
    printf("\n");
    
    return 1;
}

int imprimeMatrizDiagonalPrincipal(MatrizEsparsa* li) {
    if (li == NULL)
        return 0;
    
    Nodo *no = li->inicio;
    printf("\nA Diagonal Principal de %s equivale a: \n", li->nome);
    for (int lin = 1; lin <= li->linMAX; lin++) {
        printf("[ ");

        for (int col = 1; col <= li->colMAX; col++) {
            //A DIAGONAL PRINCIPAL POSSUI TODOS OS SEUS ELEMENTOS NAS POSIÇÕES
            //ONDE A LINHA E A COLUNA SÃO IGUAIS
            if (lin == col) {
                //SÓ SIGO PARA O PRÓXIMO ELEMENTO QUANDO A LINHA DO ELEMENTO FOR IGUAL À LINHA DO LOOP
                //E QUANDO A COLUNA DO ELEMENTO FOR IGUAL À COLUNA DO LOOP
                //ISSO PARA QUE O LOOP SEMPRE APONTE PARA O ELEMENTO QUE ESTÁ NA MESMA LINHA E COLUNA QUE ELE
                //CASO NÃO HAJA ELEMENTO NESSA LINHA E COLUNA, É PRINTADO 0 OU O ESPAÇO VAZIO MESMO
                //EXEMPLO: O PRIMEIRO ELEMENTO ESTÁ NA POSIÇÃO 1X2
                //O PRIMEIRO LOOP ESTÁ NA POSIÇÃO 1X1
                //O PRIMEIRO LOOP NÃO ENCONTRARÁ ELEMENTO CORRESPONDENTE E PRINTARÁ 0
                //CASO O NÓ SIGA PARA O PRÓXIMO, O LOOP VAI APONTAR PARA 1X2 E O NÓ ESTARÁ AGORA EM 1X3
                //POR ISSO, O NÓ SÓ PODE SEGUIR AO PRÓXIMO ELEMENTO SE A LINHA E COLUNA DELE FOREM IGUAIS À DO LOOP
                if (no != NULL && no->lin == no->col && (no->lin == lin && no->col == col)) {
                    printf("%.2f ", no->dado);
                    no = no->prox;
                } else {
                    printf("0.00 ");
                }
            } else {
                printf("     ");
                if (no != NULL && (no->lin == lin && no->col == col)) {
                    no = no->prox;
                }
            }
        }
        printf("]\n");
    }

    printf("\n");
    
    return 1;
}

int imprimeTodasMatrizes(MatrizPai* mp) {
    if (mp == NULL)
        return 0;
    if (mp->inicio == NULL)
        return 0;

    MatrizEsparsa *li = mp->inicio;
    for (int i = 0; i < mp->qtd; i++) {
        imprimeMatrizAtual(li);
        li = li->prox;
    }

    return 1;
}

int imprimeTodasMatrizesEmLinha(MatrizPai* mp) {
    if (mp == NULL)
        return 0;
    if (mp->inicio == NULL)
        return 0;
    
    MatrizEsparsa *li = mp->inicio;
    printf("\nA Lista de Matrizes possui as seguintes Matrizes: ");
    while (li != NULL) {
        printf("%s ", li->nome);
        li = li->prox;
    }
    printf("\n");

    return 1;
}

int usarImprimeTodasMatrizesEmLinha(MatrizPai* mp) {
    int mpImprimeTodasMatrizesEmLinha = imprimeTodasMatrizesEmLinha(mp);

    if (!mpImprimeTodasMatrizesEmLinha) {
        return 0;
    }

    return 1;
}



/*
### ACESSA UMA MATRIZ ###
*/

MatrizEsparsa* acessaMatriz(MatrizPai* mp, char *nome) {
    if (mp == NULL)
        return NULL;

    MatrizEsparsa *li = mp->inicio;
    while (li != NULL && strcmp(li->nome, nome)) {
        li = li->prox;
    }

    if (li != NULL)
        return li;
    else
        return NULL;
}



/*
### OPERAÇÕES COM MATRIZES ###
*/

int multiplicaMatrizes(MatrizPai* mp, char *nome1, char *nome2, char* nome3) {
    if (mp == NULL)
        return 0;
    
    MatrizEsparsa *matriz1, *matriz2, *matriz3;
    matriz1 = acessaMatriz(mp, nome1);
    matriz2 = acessaMatriz(mp, nome2);

    //NA MULTIPLICAÇÃO DE MATRIZES, VOCÊ TEM QUE MULTIPLICAR AS LINHAS DO PRIMEIRO COM AS COLUNAS DO SEGUNDO
    //E ENTÃO SOMAR TUDO PARA GERAR O PRIMEIRO ELEMENTO DA MATRIZ RESULTANTE
    if ((matriz1 != NULL && matriz2 != NULL) &&
        //SÓ É POSSÍVEL MULTIPLICAR DUAS MATRIZES SE O NÚMERO DE COLUNAS DE UMA FOR IGUAL À QUANTIA DE LINHAS DA OUTRA
        (matriz1->colMAX == matriz2->linMAX)) {

        int linhas1 = matriz1->linMAX, colunas1 = matriz1->colMAX, colunas2 = matriz2->colMAX;
        float dadoNovo = 0;

        matriz3 = criaMatriz(mp, nome3, linhas1, colunas2);
        
        //PRIMEIRO VOCÊ TRAVA A LINHA DA PRIMEIRA MATRIZ
        for (int i = 1; i <= linhas1; i++) {
            //E ENTÃO TRAVA A COLUNA DA SEGUNDA MATRIZ
            for (int k = 1; k <= colunas2; k++) {
                dadoNovo = 0;
                //POR FIM, PERCORRE A LINHA DA PRIMEIRA MATRIZ E A COLUNA DA SEGUNDA MATRIZ COM O J
                for (int j = 1; j <= colunas1; j++) {
                    //O DADO NOVO ARMAZENA A MULTIPLICAÇÃO DOS ELEMENTOS DA LINHA DA PRIMEIRA MATRIZ
                    //COM OS ELEMENTOS DA COLUNA DA SEGUNDA MATRIZ, E ENTÃO OS SOMA
                    //ELE REPRESENTA O DADO FINAL QUE SERÁ INSERIDO NA MATRIZ RESULTANTE
                    dadoNovo += buscaDado(matriz1, i, j) * buscaDado(matriz2, j, k);
                }
                    insereDado(matriz3, dadoNovo, i, k);
            }
        }
        
        return 1;
    } else {
        return 0;
    }
}

int somaMatrizes(MatrizPai* mp, char *nome1, char *nome2, char* nome3) {
    if (mp == NULL)
        return 0;

    MatrizEsparsa *matriz1, *matriz2, *matriz3;
    matriz1 = acessaMatriz(mp, nome1);
    matriz2 = acessaMatriz(mp, nome2);

    //A SOMA E A SUBTRAÇÃO SÃO IGUAIS, APENAS MUDA O SINAL
    //NELAS, VOCÊ SOMA OU SUBTRAI OS ELEMENTOS QUE ESTÃO NA MESMA POSIÇÃO DE CADA MATRIZ
    //POR ISSO, VOCÊ PRECISA QUE AS DUAS MATRIZES POSSUAM TAMANHOS IGUAIS
    if ((matriz1 != NULL && matriz2 != NULL) &&
        (matriz1->linMAX == matriz2->linMAX) &&
        (matriz1->colMAX == matriz2->colMAX)) {

        int linhas = matriz1->linMAX, colunas = matriz1->colMAX;
        float dadoNovo = 0;

        matriz3 = criaMatriz(mp, nome3, linhas, colunas);
        
        for (int i = 1; i <= linhas; i++) {
            for (int k = 1; k <= colunas; k++) {
                dadoNovo = buscaDado(matriz1, i, k) + buscaDado(matriz2, i, k);
                insereDado(matriz3, dadoNovo, i, k);
            }
        }
        
        return 1;
    } else {
        return 0;
    }
}

int subtraiMatrizes(MatrizPai* mp, char *nome1, char *nome2, char* nome3) {
    if (mp == NULL)
        return 0;

    MatrizEsparsa *matriz1, *matriz2, *matriz3;
    matriz1 = acessaMatriz(mp, nome1);
    matriz2 = acessaMatriz(mp, nome2);

    if ((matriz1 != NULL && matriz2 != NULL) &&
        (matriz1->linMAX == matriz2->linMAX) &&
        (matriz1->colMAX == matriz2->colMAX)) {

        int linhas = matriz1->linMAX, colunas = matriz1->colMAX;
        float dadoNovo = 0;

        matriz3 = criaMatriz(mp, nome3, linhas, colunas);
        
        for (int i = 1; i <= linhas; i++) {
            for (int k = 1; k <= colunas; k++) {
                dadoNovo = buscaDado(matriz1, i, k) - buscaDado(matriz2, i, k);
                insereDado(matriz3, dadoNovo, i, k);
            }
        }
        
        return 1;
    } else {
        return 0;
    }    
}