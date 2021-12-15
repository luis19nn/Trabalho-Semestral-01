#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrabSemEx02.h"

/*
### STRUCT DAS ROTAS ###
*/

struct Cidade {
    char nome[20];
    char descricao[60];
    struct Cidade *prox;
    struct Cidade *ante;

};

struct DescritorRota {
    char nome[20];
    struct Cidade *inicio;
    struct Cidade *final;
    struct DescritorRota *prox;
    int qtd;
};

struct ListaRotas {
    struct DescritorRota *inicio;
    struct DescritorRota *final;
    int qtd;
};



/*
### CRIAÇÃO DA LISTA DE ROTAS ###
*/

ListaDeRotas* criaListaDeRotas() {
    //aloca memoria
    ListaDeRotas* listaRotas = (ListaDeRotas*) malloc(sizeof(ListaDeRotas));

    if (listaRotas != NULL) {
        //seta valores
        listaRotas->inicio = NULL;
        listaRotas->final = NULL;
        listaRotas->qtd = 0;
    }

    return listaRotas;
}



/*
### LIBERAÇÃO DA LISTA DE ROTAS ###
*/

void liberaListaDeRotas(ListaDeRotas* listaRotas) {
    if (listaRotas != NULL) {
        Rota* li;

        //loop para percorrer rota
        while (listaRotas->inicio != NULL) {
            li = listaRotas->inicio;
            listaRotas->inicio = listaRotas->inicio->prox;

            //libera cada rota
            free(li);
        }

        //libera lista de rotas
        free(listaRotas);
    }
}



/*
### CRIAÇÃO DA ROTA ###
*/

Rota* criaRota(ListaDeRotas* listaRotas, char *nome) {

    //aloca memoria para rota
    Rota* li = (Rota*) malloc(sizeof(Rota));

    //se existe uma lista de rotas valida
    if (li != NULL && listaRotas != NULL) {
        //coloca primeira rota nas variaveis
        Rota *liTesteNome = listaRotas->inicio;

        //compara nome da primeira rota (se nao nula) com o nome inserido para nova rota
        while (liTesteNome != NULL && strcmp(liTesteNome->nome, nome)) {
            //caminha nas rotas
            liTesteNome = liTesteNome->prox;
        }
        
        //se nao for nulo
        if (liTesteNome != NULL) {
            li = NULL;

        //se for nulo
        } else {

            //atribui valores para a li que e a rota
            strcpy(li->nome, nome);
            li->inicio = NULL;
            li->final = NULL;
            li->qtd = 0;
            li->prox = NULL;

            //atribui rota como inicio da lista se for null na lista de rotas
            if (listaRotas->inicio == NULL)
                listaRotas->inicio = li;
            //caso contrario, rota e adicionada ao final da lista
            else
                listaRotas->final->prox = li;

            listaRotas->final = li;
            listaRotas->qtd++;
        }

    } else {
        li = NULL;
    }

    return li;
}



/*
### REMOÇÃO DA ROTA ###
*/

int removeRota(ListaDeRotas* listaRotas, char *nome) {
    if (listaRotas == NULL)
        return 0;

    Rota *ant, *li = listaRotas->inicio;

    //busca rota com o nome desejado para excluir
    while (li != NULL && strcmp(li->nome, nome)) {
        ant = li;
        li = li->prox;
    }

    if (li == NULL)
        return 0;

    //se a rota for a primeira da lista de rotas, seta null
    if (li == listaRotas->inicio) {
        if (li->prox == NULL) {
            listaRotas->inicio = NULL;
            listaRotas->final = NULL;
        } else {
            listaRotas->inicio = li->prox;
        }

    //caso contrario, retira da lista apenas a rota escolhida    
    } else {
        ant->prox = li->prox;

        if (li->prox == NULL) {
            listaRotas->final = ant;
        }
    }

    //libera rota
    free(li);

    listaRotas->qtd--;

    return 1;
}



/*
### INFORMAÇÕES DA ROTA ###
*/

int tamanhoRota(Rota* li) {
    if (li == NULL)
        return 0;

    return li->qtd;
}

int RotaVazia(Rota* li) {
    if (li == NULL)
        return 1;
    if (li->inicio == NULL)
        return 1;

    return 0;
}



/*
### INSERÇÃO DE CIDADES NA ROTA ###
*/

int insereCidade(Rota* li) {
    if (li == NULL)    
        return 0;

    //aloca espaco para cidade
    Nodo* no = (Nodo*) malloc(sizeof(Nodo));

    if (no == NULL)
        return 0;

    char descricao[60];
    char nome[20];
    printf("\n- Importante: Nunca digite acentos ou caracteres especiais!\n");

    //se rota vazia, insere curitiba como primeira cidade
    if (RotaVazia(li)) {
        no->prox = li->inicio;
        no->ante = NULL;

        char * cidadeOrigem;
        cidadeOrigem = "Curitiba";

        printf("\nA cidade de origem da rota dessa empresa eh: %s. ", cidadeOrigem);

        printf("\nFaca uma breve descricao dessa cidade (maximo 60 caracteres): ");
        fgets(descricao, 60, stdin);

        strcpy(no->nome, cidadeOrigem);
        strcpy(no->descricao, descricao);

        li->inicio = no;
        li->qtd++;

    //se ja tem cidade na rota, insere no final da rota
    } else {
        printf("\nInforme o nome da cidade (maximo 20 caracteres): ");
        fgets(nome, 20, stdin);

        printf("\nFaca uma breve descricao da cidade (maximo 60 caracteres): ");
        fgets(descricao, 60, stdin);

        strcpy(no->nome, nome);
        strcpy(no->descricao, descricao);

        Nodo *ant, *atual = li->inicio;
        while (atual != NULL) {
            ant = atual;
            atual = atual->prox;
        }
        
        no->prox = ant->prox;
        no->ante = ant;
        ant->prox = no;

        li->final = no;
        li->qtd++;
    }

    return 1;
}



/*
### IMPRIME A ROTA ATUAL ###
*/

int imprimeRotaAtual(Rota* li) {
    if (li == NULL)
        return 0;
    if (li->inicio == NULL)
        return 0;

    //pega cidade inicial da rota
    Nodo *no = li->inicio;

    char entrada;

    printf("\nBem vindo(a) a rota: %s", li->nome);
    printf("\nA cidade de origem eh: %s\n", li->nome);
    printf("\n======================================\n");
    printf("\nNome da cidade: %s\n", no->nome);
    printf("Breve descricao: %s",no->descricao);
    printf("\n======================================\n ");

    while (1) {
        printf("\n 1) Ir para proxima cidade");
        printf("\n 2) Voltar para a cidade anterior");
        printf("\n 3) Voltar para o Menu de Rotas");
        printf("\n\nOpcao: ");
        scanf("%c", &entrada);
        fflush(stdin);

        switch (entrada) {
            case '1': ;
                //avanca cidade se nao chegar na ultima
                if (no != NULL && no->prox != NULL ) {
                    printf("Voce esta visitando a rota: %s\n", li->nome);
                    printf("\n======================================\n");
                    no = no->prox;
                    printf("\nNome da cidade: %s", no->nome);
                    printf("Breve descricao: %s",no->descricao);
                    printf("\n======================================\n ");

                //avisa que nao e possivel avancar mais cidades
                } else {
                    printf("Nao e possivel avancar mais, essa eh a ultima cidade da rota: %s", li->nome);
                    printf("\n======================================\n");
                    printf("\nNome da cidade: %s", no->nome);
                    printf("Breve descricao: %s",no->descricao);
                    printf("\n======================================\n ");
                }

                break;
            case '2': ;
                //retorna cidade se nao for a primeira
                if (no != NULL && no->ante != NULL ) {
                    printf("Voce esta visitando a seguinte rota: %s\n", li->nome);
                    printf("\n======================================\n");
                    no = no->ante;
                    printf("\nNome da cidade: %s", no->nome);
                    printf("\nBreve descricao: %s",no->descricao);
                    printf("\n======================================\n ");

                //avisa que nao e possivel retornar mais cidades
                } else {
                    printf("Não eh possivel retornar mais, essa e a primeira cidade da rota: %s", li->nome);
                    printf("\n======================================\n");
                    printf("\nNome da cidade: %s\n", no->nome);
                    printf("Breve descricao: %s",no->descricao);
                    printf("\n======================================\n ");
                }

                break;
            case '3': ;
                return 1;

            default:
                printf("\n\n###ERRO!\nOpcao de menu invalida.\n\n");
        }
    }

    printf("\n");
    return 1;
}



/*
### IMPRIME TODAS AS ROTAS DISPONÍVEIS ###
*/

int imprimeTodasRotasEmLinha(ListaDeRotas* listaRotas) {
    if (listaRotas == NULL)
        return 0;
    if (listaRotas->inicio == NULL)
        return 0;

    //pega a primeira rota da lista
    Rota *li = listaRotas->inicio;
    printf("\nA Lista de Rotas possui as seguintes Rotas: \n");

    //loop para exibir rotas
    while (li != NULL) {
        printf("- %s", li->nome);
        li = li->prox;
    }
    printf("\n");

    return 1;
}

int usarImprimeTodasRotasEmLinha(ListaDeRotas* listaRotas) {
    //utiliza a funcao que imprime todas as rotas
    int listaImprimeTodasRotasEmLinha = imprimeTodasRotasEmLinha(listaRotas);

    if (!listaImprimeTodasRotasEmLinha) {
        return 0;
    }

    return 1;
}



/*
### ACESSA UMA ROTA  ###
*/

Rota* acessaRota(ListaDeRotas* listaRotas, char *nome) {
    //avalia validade da lista de rotas
    if (listaRotas == NULL)
        return NULL;

    //percorre lista de rotas ate encontrar a desejada
    Rota *li = listaRotas->inicio;
    while (li != NULL && strcmp(li->nome, nome)) {
        li = li->prox;
    }

    return li;
}
