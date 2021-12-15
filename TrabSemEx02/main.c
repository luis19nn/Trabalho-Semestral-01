#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrabSemEx02.h"
#include "TrabSemEx02.c"

int main() {
    /* CRIA LISTA DE ROTAS */
    ListaDeRotas *listaRotas = NULL;
    Rota *li = NULL;

    char entrada, nomeRota[20];

    //funcao que aloca memoria para lista de rotas
    listaRotas = criaListaDeRotas();

    if (listaRotas == NULL) {
        printf("\n\n###ERRO AO INICIAR O PROGRAMA!\nNao foi possivel alocar memoria para a estrutura. \n\n");
        exit(0);
    } else {
        printf("\nBem vindo(a) a lista de rotas da companhia de onibus intermunicipal do Estado do Parana! \n");
    }

    /* LOOP COM O MENU PRINCIPAL */
    while (1) {
        printf("\n ==== MENU PRINCIPAL ==== ");
        printf("\n 1. Cadastrar Rota");
        printf("\n 2. Excluir Rota");
        printf("\n 3. Visitar Rota");
        printf("\n 4. Sair");
        printf("\n ======================== ");
        printf("\n\nOpcao: ");
        scanf("%c", &entrada);
        fflush(stdin);

        switch (entrada) {
            /* CADASTRO DE ROTA */
            case '1': ;
                //Cria rota
                printf("\nInforme o nome da rota (deve ser igual o nome da cidade de destino): ");
                fgets(nomeRota, 20, stdin);

                //funcao que aloca memoria para rota e coloca na lista
                li = criaRota(listaRotas, nomeRota);

                if (li == NULL) {
                    printf("\n\n###ERRO AO CRIAR!\nSeus erros podem ser:\nNao foi possivel alocar memoria para a estrutura.\nEh necessario criar uma Lista de rotas antes de criar uma rota.\nO nome da rota pode ja estar sendo utilizado.\n\n");
                } else {
                    printf("\nRota criada com sucesso!");
                    printf("\nFaca a insercao das cidades pertencentes a essa rota seguindo a ordem do percurso. \n\nIMPORTANTE: ");
                    printf("\n- O programa inicia inserindo a cidade de origem da rota (Curitiba). ");
                    printf("\n- Coloque as demais cidades na ordem correta do trajeto. ");

                    //Insercao de cidades na rota
                    char teste;

                    do {
                        printf("\n ----------------------------------------------------------------------------- ");
                        printf("\n CRIACAO DA ROTA: ");
                        printf("\n(1) Inserir uma cidade na rota ");
                        printf("\n(2) ou aperte qualquer outra tecla para parar a insercao e finalizar a rota");
                        printf("\n ----------------------------------------------------------------------------- ");
                        printf("\n\nOpcao: ");
                        scanf("%c", &teste);
                        fflush(stdin);

                        //cria e insere cidade na rota
                        if (teste == '1') {
                            //funcao para criar cidade com o nome e descricao e inserir na rota
                            int liInsereCidade = insereCidade(li);

                            if (liInsereCidade) {
                                printf("\nCidade inserida com sucesso na rota!\n");
                            } else {
                                printf("\n\n###ERRO AO INSERIR!\n\n");
                            }
                        }
                    } while (teste == '1');

                break;

            /* REMOVER ROTA */
            case '2': ;
                //ve se tem rotas
                if (!usarImprimeTodasRotasEmLinha(listaRotas)) {
                    printf("\n\n###ERRO!\nA Lista de Rotas esta vazia ou nao existe.\n\n");
                    break;
                }

                printf("\nDigite o nome da Rota a ser removida da Lista de Rotas: ");
                fgets(nomeRota, 20, stdin);

                //funcao para remover rota da lista
                int listaRemoveRota = removeRota(listaRotas, nomeRota);

                if (listaRemoveRota) {
                    printf("\nRota removida com sucesso da Lista de Rotas!\n");
                } else {
                    printf("\n\n###ERRO AO REMOVER!\nA Lista de Rotas esta nula ou a Rota informada nao foi encontrada.\n\n");
                }

                break;

            /* VISITAR ROTA */
            case '3': ;
                //ve se tem rotas
                if (!usarImprimeTodasRotasEmLinha(listaRotas)) {
                    printf("\n\n###ERRO!\nA Lista de Rotas esta vazia ou nao existe.\n\n");
                    break;
                }

                printf("\nDigite a rota que deseja acessar: ");
                fgets(nomeRota, 20, stdin);

                //Busca a rota desejada para acessar
                li = acessaRota(listaRotas, nomeRota);

                if (li != NULL) {
                    //acessa rota escolhida para imprimir
                    int liImprimeRotaAtual = imprimeRotaAtual(li);

                    if (!liImprimeRotaAtual) {
                        printf("\n\n###ERRO AO IMPRIMIR!\nA Rota esta vazia ou nao existe.\n\n");
                    }
                } else {
                    printf("\n\n###ERRO AO ACESSAR!\nA Lista de Rotas esta nula ou a Rota informada nao foi encontrada.\n\n");
                }

                break;

            /* SAIR DO PROGRAMA */
            case '4': ;
                if (listaRotas != NULL) {
                    liberaListaDeRotas(listaRotas);
                    listaRotas = NULL;

                    printf("\nA Lista de Rotas foi liberada!\n");
                }

                exit(0);
            default:
                printf("\n\n###ERRO!\nOpcao de menu invalida.\n\n");
            }
        }
    }

    return 0;
}
