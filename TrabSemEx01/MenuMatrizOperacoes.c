#include <stdio.h>
#include <stdlib.h>

int menuMatrizOperacoes(MatrizPai* mp, int *index) {
    char nome1[10], nome2[10], nome3[30];
    char operacao, sair;
    int i = 0;
    
    printf("\nDigite o nome da primeira Matriz: ");
    scanf("%s", nome1);
    fflush(stdin);

    printf("\nDigite a operacao desejada (*/+/-): ");
    scanf("%c", &operacao);
    fflush(stdin);

    printf("\nDigite o nome da segunda Matriz: ");
    scanf("%s", nome2);
    fflush(stdin);

    while (1) {
        if (i != 0) {
            printf("\nDigite a operacao desejada (+/-/*): ");
            scanf("%c", &operacao);
            fflush(stdin);

            printf("\nDigite o nome da proxima Matriz: ");
            scanf("%s", nome2);
            fflush(stdin);
        }

        switch (operacao) {
            case '*': ;
                snprintf(nome3, 30, "MatrizMultiplicacao%d", index[0]);

                int mpMultiplicaMatrizes = multiplicaMatrizes(mp, nome1, nome2, nome3);

                if (mpMultiplicaMatrizes) {
                    printf("\n\nMultiplicacao realizada com sucesso!\n\n");
                    //COPIO O NOME3 PARA O NOME1, ASSIM, NO PRÓXIMO LOOP, NOME1 VAI FAZER REFERENCIA À ÚLTIMA MATRIZ RESULTANTE
                    strcpy(nome1, nome3);
                    //M, SM E SB SERVEM PARA MODIFICAR O NOME DA MATRIZ 3
                    //PARA PODER SALVAR, JÁ QUE NÃO É POSSÍVEL SALVAR COM NOMES IGUAIS
                    index[0]++;
                } else {
                    printf("\n\n###ERRO!\nHouve um erro na multiplicacao das duas Matrizes.\n\n");
                }

                break;
            case '+': ;
                snprintf(nome3, 30, "MatrizSoma%d", index[1]);    

                int mpSomaMatrizes = somaMatrizes(mp, nome1, nome2, nome3);

                if (mpSomaMatrizes) {
                    printf("\n\nSoma realizada com sucesso!\n\n");
                    strcpy(nome1, nome3);
                    index[1]++;
                } else {
                    printf("\n\n###ERRO!\nHouve um erro na soma das duas Matrizes.\n\n");
                }

                break;
            case '-': ;
                snprintf(nome3, 30, "MatrizSubtrai%d", index[2]);

                int mpSubtraiMatrizes = subtraiMatrizes(mp, nome1, nome2, nome3);

                if (mpSubtraiMatrizes) {
                    printf("\n\nSubtracao realizada com sucesso!\n\n");
                    strcpy(nome1, nome3);
                    index[2]++;
                } else {
                    printf("\n\n###ERRO!\nHouve um erro na subtracao das duas Matrizes.\n\n");
                }

                break;
            default:
                printf("\n\n###ERRO!\nOpcao de operacao invalida.\n\n");
        }

        i++;

        printf("\nPara sair digite \"=\", para continuar digite outra tecla: ");
        scanf("%c", &sair);
        fflush(stdin);

        if (sair == '=')
            return 1;
    }
}
