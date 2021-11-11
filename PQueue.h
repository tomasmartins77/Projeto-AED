#ifndef PQueue
#define PQueue

#include "Utility2.h"
#include "Listas.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue
{
    int *queue;   /*fila de prioridade*/
    int ffree;    /*primeira posicao vazia*/
    int *posicao; /*posicao do vertice na fila*/
} Queue;

#define exch(A, B) \
    {              \
        int t = A; \
        A = B;     \
        B = t;     \
    }

/** @brief algoritmo de dijkstras
 *
 */
void Dijkstras(Graph *G, int s, int st[], int wt[]);

/** @brief altera uma certa posicao da fila para o seu valor correto de prioridade, de menos prioridade para mais
 *        prioridade, se o seu "pai" tiver um custo menor, vai trocar de posicao
 *        fazendo isto ate chegar a posicao correta
 */
Queue *FixUp(Queue *pq, int Idx, int *wt);

/** @brief altera uma certa posicao da fila para o seu valor correto de prioridade, de mais prioridade para menos
 *        prioridade, percorre a fila, verificando para que ramo da arvore o valor vai descer para
 *        de acordo com o seu custo
 */
Queue *FixDown(Queue *pq, int Idx, int N, int *wt);

/** @brief verifica se a fila esta vazia ou nao
 *
 */
int PQEmpty(Queue *pq);

/** @brief insere um vertice na priority queue na primeira posicao vazia
 *
 */
Queue *PQinsert(Queue *pq, int I, int *wt, int size);

/** @brief inicializa a priority queue, o array de posicao(indica a posicao do vertice na fila)
 *
 */
Queue *PQinit(Queue *pq, int size);

/** @brief elimina elemento de maior prioridade da lista, troca o elemento de maior prioridade com
 *        o de menor, e diminui uma posicao total da fila, retirando-o figurativamente da fila
 *
 */
int PQdelmin(Queue *pq, int *wt);

#endif