#ifndef TRABSEMEX02_H_INCLUDED
#define TRABSEMEX02_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/*
### TYPEDEF DAS ROTAS ###
*/

typedef struct DescritorRota Rota;
typedef struct Cidade Nodo;
typedef struct ListaRotas ListaDeRotas;

/*
### CRIAÇÃO E LIBERAÇÃO DA LISTA DE ROTAS ###
*/

ListaDeRotas* criaListaDeRotas();

void liberaListaDeRotas(ListaDeRotas* listaRotas);

/*
### CRIAÇÃO E REMOÇÃO DA ROTA ###
*/

Rota* criaRota(ListaDeRotas* listaRotas, char *nome);

int removeRota(ListaDeRotas* listaRotas, char *nome);

/*
### INFORMAÇÕES DA ROTA ###
*/

int tamanhoRota(Rota* li);

int RotaVazia(Rota* li);

/*
### INSERÇÃO DE CIDADE NA ROTA ###
*/

int insereCidade(Rota* li);

/*
### IMPRIME AS ROTAS ###
*/

int imprimeRotaAtual(Rota* li);

int imprimeTodasRotasEmLinha(ListaDeRotas* listaRotas);

Rota* acessaRota(ListaDeRotas* listaRotas, char *nome);


#endif // TRABSEMEX02_H_INCLUDED
