# Trabalho Semestral 01
Neste repositório, estão os dois exercícios feitos para o primeiro trabalho semestral de Estrutura de Dados 1 do curso de Análise e Desenvolvimento de Sistemas da UFPR.

## Exercício 01
Criar um programa em C que manipule matrizes esparsas, utilizando lista linear encadeada.
<br>OBS: Uma matriz é considerada esparsa quando a maioria dos seus dados são zeros.
<br>
<br>Exemplo de Matriz Esparsa:<br>
![image](https://user-images.githubusercontent.com/58374776/146098567-4db1b03a-0ed1-4c22-9a8d-f9ca847a7745.png)
<br>
<br>Em caso da matriz ser muito grande não é vantajoso, em termos de memória, armazenar todos os dados, até porque a maioria são zeros. Então o objetivo do trabalho é criar uma lista encadeada e armazenar somente os dados diferentes de zero, bem como a linha e a coluna onde esses dados estão localizados.
<br>
![image](https://user-images.githubusercontent.com/58374776/146098663-d9ced556-3e6a-481b-8177-eefefd0874de.png)
<br>
<br>Mas, no entanto, o programa deverá imprimir na saída a matriz inteira, tanto os dados diferentes de zero como os zeros. 
<br>
O programa deverá ser formado pela seguinte struct:
<br>
```
typedef struct Nodo {
    float dado;
    int lin, col;
    struct nodo *prox;
} Matriz_Esparsa;
```
<br>E pelas seguintes funções:
- Uma função que faz a alocação de memória para cada nodo criado para uma lista encadeada;
- Uma função que insere na lista encadeada um nodo alocado;
- Uma função que busca os dados em uma lista encadeada;
- Uma função que libera da memória uma lista encadeada;
- Uma função que lê os dados da matriz, via teclado, e inseri na lista encadeada somente os dados diferentes de zero;
- Uma função que soma duas matrizes;
- Uma função que subtrai duas matrizes;
- Uma função que multiplica duas matrizes;
- Uma função que gera a matriz transposta;
- Uma função que imprime todos os dados da matriz, inclusive os zeros;
- Uma função que imprime os elementos da diagonal principal, inclusive os zeros caso existam.

<br>Observações:
- O usuário pode entrar com quantas matrizes desejar.
- O usuário deve informar a dimensão de cada matriz.
- O usuário poderá fazer quantas operações desejar com as matrizes.
- Exemplo: MA * MB + MC - MD
- Considerar as regras de operações com matrizes para implementar a soma, subtração, multiplicação, transposta e diagonal principal de matrizes.
- As listas encadeadas (que representam as matrizes) devem ser passadas como parâmetros das funções.

## Exercício 02
Objetivo: Implementar uma Lista de Rotas de Ônibus utilizando Listas Duplamente Encadeadas.
- Este programa deverá gerenciar um conjunto de listas de rotas/linhas de uma companhia de ônibus intermunicipal do Estado do Paraná;
- Todas as rotas iniciam em Curitiba;
- Cada rota possui um nome que a identifica de forma única, dado pelo destino. Ex: "Campo Largo“;
- Cada rota possui a lista de todas as cidades por onde o ônibus passa, para ir de Curitiba ao destino;
- A rota de ônibus, ao retornar, passa pelos mesmos lugares. Portanto, pode ser representada por uma lista duplamente encadeada;
- O usuário deve poder escolher uma rota e poder navegar por ela, indo de cidade em cidade e voltando para a cidade anterior, usando para tanto as teclas de seta à esquerda e seta à direita ou 1- Ir para próxima cidade; 2 – Voltar para a ciadde anterior;
- Cada nodo representando uma cidade possui, além do nome, um texto descrevendo alguma característica desta cidade. Ex.: "Lá encontram-se as melhores porcelanas". Este texto é mostrado quando se visita um nodo.
- Implemente o programa de rotas como uma lista de listas;
- A lista que contém todas as rotas pode ser uma lista encadeada ou uma lista estática em vetor em vetor;
- Cada lista que representa uma rota deve ser uma lista duplamente encadeada;
- Aplicar o conceito de nó descritor na lista duplamente encadeada.
- Menu de Entrada:
```
    1. Cadastrar Rota
    2. Excluir Rota
    3. Visitar Rota
    4. Sair 
```
