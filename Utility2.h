#ifndef Utility2
#define Utility2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modos.h"

typedef void *Item;

typedef struct _Lista
{
    Item value;          /*aresta*/
    struct _Lista *next; /*proximo elemento da lista*/
} Lista;

typedef struct _Graph
{
    int vertex;  /*total de vertices = numero de salas do tabuleiro*/
    Lista **adj; /*lista de adjacencias*/
} Graph;

typedef struct _Edge
{
    int V; /*indice da aresta*/
    int W; /* peso ou custo */
    int x; /*coordenada da parede mais barata dessa aresta*/
    int y;
} Edge;

/** \brief verifica os vizinhos horizontais e
 *         verticais de uma parede atualizando os valores de ESQ, DIR, CIM, BAI
 **/
void vizinhos(int **tab, lab_t lab, int posx, int posy, int *ESQ, int *DIR, int *CIM, int *BAI);

/** \brief verifica se uma parede e quebravel no contexto dado
 *
 */
int quebravel(int **tab, lab_t lab, int x, int y);

/** \brief compara dois inteiros
 *
 */
int comparisonItemFnt(int item1, int item2);

/** \brief compara o peso de dois inteiros
 *
 */
int comparisonItemWeight(int item1, int item2, int *wt);

/** \brief conta o numero de salas e "pinta" todas as salas com o mesmo id negativo e consecutivo
 *
 */
void verifica_salas(int **tab, lab_t lab, int *tab_id, int **salas);

/**
 * \brief imprime para o ficheiro o numero de paredes partidas ou
 *        quais as paredes partidas
 */
void print_file(Graph *graph, FILE *fp_out, int *st, int flag);

#endif