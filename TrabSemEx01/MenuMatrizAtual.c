#include <stdio.h>
#include <stdlib.h>

int menuMatrizAtual(MatrizEsparsa* li) {

    char entrada;

    while (1) {
        printf("\n=================MENU=DA=MATRIZ==================");
        printf("\n 1) Inserir um elemento");
        printf("\n 2) Remover um elemento");
        printf("\n 3) Buscar um elemento");
        printf("\n 4) Imprimir a Matriz Atual");
        printf("\n 5) Imprimir a Matriz Atual Transposta");
        printf("\n 6) Imprimir a Diagonal Principal da Matriz Atual");
        printf("\n 7) Voltar para o Menu Principal");
        printf("\n=================================================");
        printf("\n\nOpcao: ");
        scanf("%c", &entrada);
        fflush(stdin);

        switch (entrada) {
            case '1': ;
                int lin, col, tipoLin, tipoCol;
                float dadoAInserir, tipoDadoAInserir;

                printf("\nDigite a linha em que esta o valor a ser inserido na Matriz: ");
                tipoLin = scanf("%d", &lin);
                fflush(stdin);

                printf("\nDigite a coluna em que esta o valor a ser inserido na Matriz: ");
                tipoCol = scanf("%d", &col);
                fflush(stdin);

                printf("\nDigite o valor a ser inserido na Matriz: ");
                tipoDadoAInserir = scanf("%f", &dadoAInserir);
                fflush(stdin);
                
                if (tipoLin && tipoCol && tipoDadoAInserir) {
                    int liInsereDado = insereDado(li, dadoAInserir, lin, col);

                    if (liInsereDado) {
                        printf("\nNumero inserido com sucesso na Matriz!\n");
                    } else {
                        printf("\n\n###ERRO AO INSERIR!\nSeus erros podem ser:\nEsqueceu de criar a Matriz.\nO dado inserido eh igual a zero.\nA linha ou coluna informada pode ter ultrapassado o valor maximo informado.\nA linha e coluna inseridas podem ja ter sido informadas para guardar outro.\nA matriz ja esta completa.\n\n");
                    }
                } else {
                    printf("\n\n###ERRO NA ENTRADA DE DADOS!\nOs valores de linha e coluna devem ser inteiros.\nO valor a ser inserido na matriz deve ser um numero.\n\n");
                }

                break;
            case '2': ;
                if (matrizEsparsaVazia(li)) {
                    printf("\n\n###ERRO AO REMOVER!\nA Matriz esta vazia.\n\n");
                } else {
                    int lin, col, tipoLin, tipoCol;

                    printf("\nDigite a linha em que esta o valor a ser removido na Matriz: ");
                    tipoLin = scanf("%d", &lin);
                    fflush(stdin);

                    printf("\nDigite a coluna em que esta o valor a ser removido na Matriz: ");
                    tipoCol = scanf("%d", &col);
                    fflush(stdin);

                    if (tipoLin && tipoCol) {
                        int liRemoveDado = removeDado(li, lin, col);

                        if (liRemoveDado) {
                            printf("\nNumero removido com sucesso da Matriz!\n");
                        } else {
                            printf("\n\n###ERRO AO REMOVER!\nA Matriz esta nula ou o numero nao foi encontrado.\n\n");
                        }
                    } else {
                        printf("\n\n###ERRO NA ENTRADA DE DADOS!\nOs valores de linha e coluna devem ser inteiros.\n\n");
                    }
                }

                break;
            case '3': ;
                float dadoInformado;
                int buscaLin, buscaCol, tipoDadoInformado;

                printf("\nDigite o numero que voce deseja buscar para descobrir a sua posicao na Matriz: ");
                tipoDadoInformado = scanf("%f", &dadoInformado);
                fflush(stdin);

                int liBuscaLinhaColuna = buscaLinhaColuna(li, dadoInformado, &buscaLin, &buscaCol);

                if(tipoDadoInformado) {
                    if (liBuscaLinhaColuna) {
                        printf("\nO dado informado de valor %.2f esta na linha %d e coluna %d na Matriz!\n", dadoInformado, buscaLin, buscaCol);
                    } else {
                        printf("\n\n###ERRO AO BUSCAR!\nNumero informado nao consta na Matriz.\n\n");
                    }
                } else {
                    printf("\n\n###ERRO NA ENTRADA DE DADOS!\nO valor a ser buscado na matriz deve ser um numero.\n\n");
                }

                break;
            case '4': ;
                int liImprimeMatrizAtual = imprimeMatrizAtual(li);

                if (!liImprimeMatrizAtual) {
                    printf("\n\n###ERRO AO IMPRIMIR!\nA Matriz esta vazia ou nao existe.\n\n");
                }

                break;
            case '5': ;
                int liImprimeMatrizAtualTransposta = imprimeMatrizAtualTransposta(li);

                if (!liImprimeMatrizAtualTransposta) {
                    printf("\n\n###ERRO AO IMPRIMIR A TRANSPOSTA!\nA Matriz esta vazia ou nao existe.\n\n");
                }

                break;
            case '6': ;
                int liImprimeMatrizDiagonalPrincipal = imprimeMatrizDiagonalPrincipal(li);

                if (!liImprimeMatrizDiagonalPrincipal) {
                    printf("\n\n###ERRO AO IMPRIMIR A DIAGONAL PRINCIPAL!\nA Matriz esta vazia ou nao existe.\n\n");
                }

                break;
            case '7': ;
                return 1;
            default:
                printf("\n\n###ERRO!\nOpcao de menu invalida.\n\n");
        }
    }
}
