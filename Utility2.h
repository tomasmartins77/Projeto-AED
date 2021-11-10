#ifndef Utility2
#define Utility2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modos.h"

typedef void *Item;

typedef struct _Lista
{
    Item value;
    struct _Lista *next;
} Lista;

typedef struct _Graph
{
    int vertex;
    int edge;
    Lista **adj;
} Graph;

typedef struct _Edge
{
    int V;
    int W; /* peso ou custo */
    int x;
    int y;
} Edge;

/** \brief inicializa uma lista a NULL
 *
 */
Lista *initLista(void);

/** \brief cria e inicializa uma nova lista de adjacencias
 *
 * \param grafo Graph* grafo
 * \return Lista de adjacencias
 *
 */
Lista **criaLista(Graph *grafo);

/** \brief liberta a memoria alocada para a lista
 *
 * \param first  Lista* primeiro elemento da lista
 * \return void
 *
 */
void freeLista(Lista *lista, void(destruir_fn)(Item));

/** \brief retorna o node seguinte de uma lista
 *
 * \param node  Lista* node atual de uma lista
 * \return o node seguinte de uma lista. retorna NULL se o node atual estiver vazio ou se nao houver node seguinte 
 *
 */
Lista *getNextNodeLista(Lista *node);

/** \brief retorna o item (valor) de um certo node nessa lista
 *
 * \param node  Lista* node de uma lista
 * \return Item (valor) de um node
 *
 */
Item getItemLista(Lista *node);

/** \brief verifica os vizinhos horizontais e verticais de uma parede atualizando os valores de ESQ, DIR, CIM, BAI
 *
 * \param tab int** labirinto completo
 * \param lab lab_t linhas e colunas 
 * \param posx int posicao atual
 * \param posy int posicao atual
 * \param ESQ int* vizinho da esquerda
 * \param DIR int* vizinho da direita
 * \param CIM int* vizinho de cima
 * \param BAI int* vizinho de baixo
 * \return void 
 *
 */
void vizinhos(int **tab, lab_t lab, int posx, int posy, int *ESQ, int *DIR, int *CIM, int *BAI);

/** \brief verifica se uma parede e quebravel no contexto dado
 *
 * \param tab int** labirinto completo
 * \param lab lab_t linhas e colunas 
 * \param x int posicao atual
 * \param y int posicao atual
 * \return int 0 se nao for quebravel, 1 se for quebravel
 *
 */
int quebravel(int **tab, lab_t lab, int x, int y);

/** \brief compara dois inteiros
 *
 * \param item1 int 
 * \param item1 int 
 * \return valor menor, igual ou maior do que 0 consoante o item1 seja menor, igual ou maior que o item2, respetivamente
 *
 */
int comparisonItemFnt(int item1, int item2);

/** \brief compara o peso dois inteiros
 *
 * \param item1 int 
 * \param item1 int 
 * \param wt *int peso 
 * \return valor menor, igual ou maior do que 0 consoante o peso do item1 seja menor, igual ou maior que o peso do item2, respetivamente
 *
 */
int comparisonItemWeight(int item1, int item2, int *wt);

/** \brief insere um node ordenadamente numa lista
 *
 * \param first Lista* primeiro node da lista
 * \param item Edge* aresta
 * \return 
 *
 */
Lista *insertSortedLista(Lista *first, Edge *item, int (*compareItems)(int it1, int it2));

/** \brief conta o numero de salas e "pinta" todas as salas com o mesmo id negativo e consecutivo
 *
 * \param tab int** labirinto completo
 * \param lab lab_t linhas e colunas
 * \param tab_id int* id de cada sala
 * \param salas int** numero de salas
 * \return void
 *
 */
void verifica_salas(int **tab, lab_t lab, int *tab_id, int **salas);

#endif