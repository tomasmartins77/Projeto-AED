#ifndef PQueue
#define PQueue

#include "Utility2.h"
#include "Listas.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/** @brief altera uma certa posicao da fila para o seu valor correto de prioridade,
 * de menos prioridade para mais
 */
void FixUp(int Idx, int *wt);

/** @brief altera uma certa posicao da fila para o seu valor correto de prioridade,
 * de mais prioridade para menos prioridade
 */
void FixDown(int Idx, int N, int *wt);

/** @brief verifica se a fila esta vazia ou nao
 *
 */
int PQEmpty();

/** @brief insere um vertice na priority queue
 *
 */
void PQinsert(int I, int *wt);

/** @brief inicializa a priority queue
 *
 */
void PQinit(int size);

/** @brief elimina elemento de maior prioridade da lista
 *
 */
int PQdelmin(int *wt);

#endif