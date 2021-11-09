#include "PQueue.h"

PQ *PQinit(PQ *pq, int size)
{
    int i = 0;
    pq = (PQ *)malloc(sizeof(PQ));
    if (pq == NULL)
        exit(1);

    pq->queue = (int *)calloc(size, sizeof(int));
    if (pq->queue == NULL)
        exit(1);

    pq->posicao = (int *)malloc(size * sizeof(int));

    pq->qsize = size;
    pq->ffree = 0;

    for (i = 0; i < size; i++)
        pq->posicao[i] = -1;

    return pq;
}

PQ *PQinsert(PQ *pq, int *wt, int I)
{
    if ((pq->ffree + 1) < pq->qsize)
    {
        pq->queue[pq->ffree] = I;
        pq->posicao[I] = pq->ffree;
        pq = FixUp(pq, pq->ffree, wt);
        pq->ffree++;
    }
    printf("    %d %d\n", pq->queue[0], pq->queue[1]);

    return pq;
}

void exch(PQ *pq, int i, int j)
{
    int aux = 0;
    aux = pq->queue[i];
    pq->queue[i] = pq->queue[j];
    pq->queue[j] = aux;

    aux = pq->posicao[i];
    pq->posicao[i] = pq->posicao[j];
    pq->posicao[j] = aux;

    return;
}

int PQEmpty(PQ *pq)
{
    return pq->ffree == 0 ? 1 : 0;
}

PQ *FixUp(PQ *pq, int Idx, int *wt)
{
    while (Idx > 0 && comparisonItemWeight((Idx - 1) / 2, Idx, wt) == 1)
    {
        exch(pq, Idx, (Idx - 1) / 2);
        Idx = (Idx - 1) / 2;
    }
    return pq;
}

PQ *FixDown(PQ *pq, int Idx, int N, int *wt)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Idx + 1;

        if (Child < (N - 1) && comparisonItemWeight(Child, Child + 1, wt) == 1)
            Child++;
        if (comparisonItemWeight(Idx, Child, wt) == -1)
            break;

        exch(pq, Idx, Child);
        /* continua a descer a árvore */
        Idx = Child;
    }
    return pq;
}

void GRAPHpfs(Graph *G, int s, int st[], int wt[])
{
    int v, w;
    Lista *t;
    Edge *edge;
    PQ *pq = NULL;
    pq = PQinit(pq, G->vertex);

    for (v = 0; v < G->vertex; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
    }
    printf("%d %d\n", pq->queue[0], pq->queue[1]);
    pq = PQinsert(pq, wt, s);
    wt[s] = 0;
    printf("        %d %d\n", pq->queue[0], pq->queue[1]);

    while (!PQEmpty(pq) && pq->posicao[0] != -2)
    {
        v = PQdelmin(pq, wt);

        pq->posicao[v] = -2;
        if (v == 0)
            continue;
        for (t = G->adj[v]; t != NULL; t = getNextNodeLista(t)) /*percorre a lista do vertice que agora tem maior prioridade (?)*/
        {
            edge = getItemLista(t);
            if (wt[w = edge->V] > wt[v] + edge->W && wt[0] > wt[v] + edge->W)
            {
                wt[w] = wt[v] + edge->W;

                if (pq->posicao[w] == -1)
                    pq = PQinsert(pq, wt, w);

                pq = FixUp(pq, w, wt);

                st[w] = v;
            }
        }
    }
    // printf("acabei\n");
    free(pq->queue);
    free(pq->posicao);
    free(pq);
}

int PQdelmin(PQ *pq, int *wt)
{
    /* troca MENOR elemento com último da tabela e reordena com FixDown */
    exch(pq, 0, pq->ffree - 1);
    pq = FixDown(pq, 0, pq->ffree - 1, wt);
    /* ultimo elemento não considerado na reordenação */
    return pq->queue[--pq->ffree];
}
