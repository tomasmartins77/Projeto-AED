#ifndef PQueue
#define PQueue

#include "Utility2.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _PQ
{
    int *queue;
    int ffree;
    int qsize;
    int *posicao;
} PQ;

void GRAPHpfs(Graph *G, int s, int st[], int wt[]);

PQ *FixUp(PQ *pq, int Idx, int *wt);

PQ *FixDown(PQ *pq, int Idx, int N, int *wt);

int PQEmpty(PQ *pq);

void exch(PQ *pq, int i, int j);

PQ *PQinsert(PQ *pq, int *wt, int I);

PQ *PQinit(PQ *pq, int size);

int PQdelmin(PQ *pq, int *wt);

#endif