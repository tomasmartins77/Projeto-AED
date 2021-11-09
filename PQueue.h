#ifndef PQueue
#define PQueue

#include "Utility2.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GRAPHpfs(Graph *G, int s, int st[], int wt[], int sala_final);

void FixUp(int Idx);

void FixDown(int Idx, int N);

int PQEmpty();

void exch(int queueA, int queueB, int posicaoA, int posicaoB);

void PQinsert(int I);

void PQinit(int size);

int PQdelmin();

#endif