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
    int W; // peso ou custo
    int x;
    int y;
} Edge;

Lista *initLista(void);

Lista **criaLista(Graph *grafo);

void freeLista(Lista *lista, void(destruir_fn)(Item));

Lista *insertUnsortedLista(Lista *lista, Item value);

Lista *getNextNodeLista(Lista *node);

Item getItemLista(Lista *node);

void vizinhos(int **tab, lab_t lab, int posx, int posy, int *ESQ, int *DIR, int *CIM, int *BAI);

int quebravel(int **tab, lab_t lab, int x, int y);

int comparisonItemFnt(int item1, int item2);

Lista *insertSortedLista(Lista *first, Edge *item, int (*compareItems)(int it1, int it2));

void verifica_salas(int **tab, lab_t lab, int *tab_id, int **salas);

#endif