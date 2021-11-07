#include "PQueue.h"

void PQinit(int size)
{
    queue = (int *)malloc(size * sizeof(int));
    if (queue == NULL)
        exit(1);

    qsize = size;

    ffree = 0;
}

void PQinsert(int I)
{
    if ((ffree + 1) < qsize)
    {
        queue[ffree++] = I;
        FixUp(ffree);
        ffree++;
    }
}

int PQEmpty()
{
    return ffree == 0 ? 1 : 0;
}

void FixUp(int Idx)
{
    while (Idx > 0 && comparisonItemFnt(queue[(Idx - 1) / 2], queue[Idx]) == -1)
    {
        exch(queue[Idx], queue[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
}

void FixDown(int Idx, int N)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Idx + 1;
        /* Selecciona o maior descendente.
         */
        /* Nota: se índice Child é N-1, então só há um descendente */
        if (Child < (N - 1) && comparisonItemFnt(queue[Child], queue[Child + 1]) == -1)
            Child++;
        if (comparisonItemFnt(queue[Idx], queue[Child]) != -1)
            break; /* condição acervo */
        /* satisfeita
         */
        exch(queue[Idx], queue[Child]);
        /* continua a descer a árvore */
        Idx = Child;
    }
}

void GRAPHpfs(Graph *G, int s, int st[], int wt[])
{
    int v, w;
    Lista *t;
    Edge *edge = NULL;

    PQinit(G->vertex);
    for (v = 0; v < G->vertex; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
    }
    PQinsert(s);
    wt[s] = 0;
    while (!PQEmpty())
    {
        v = PQdelmin();

        for (t = G->adj[v]; t != NULL; t = t->next) /*percorre a lista do vertice que agora tem maior prioridade (?)*/
        {
            edge = getItemLista(t);
            PQinsert(edge->V);
            if (wt[w = edge->V] > P)
            {
                wt[w] = P;
                FixDown(edge->V, ffree - 1);
                st[w] = v;
            }
        }
    }
}

int PQdelmin()
{
    /* troca MENOR elemento com último da tabela e reordena com FixDown */
    exch(queue[0], queue[ffree - 1]);
    FixDown(0, ffree - 1);
    /* ultimo elemento não considerado na reordenação */
    return queue[--ffree];
}
