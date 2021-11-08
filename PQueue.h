#ifndef PQueue
#define PQueue

#include "Utility2.h"

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

void GRAPHpfs(Graph *G, int s, int st[], int wt[]);

void FixUp(int Idx);

void FixDown(int Idx, int N);

int PQEmpty();

void PQinsert(int I);

void PQinit(int size);

int PQdelmin();

#endif