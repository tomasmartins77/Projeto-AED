#include "PQueue.h"

static int *queue;
static int ffree;
static int qsize;
static int *posicao;

void PQinit(int size)
{
    queue = (int *)calloc(size, sizeof(int));
    if (queue == NULL)
        exit(1);
    posicao = (int *)malloc(size * sizeof(int));
    if (posicao == NULL)
        exit(1);

    qsize = size;
    ffree = 0;

    for (int i = 0; i < size; i++)
        posicao[i] = -1;
}

void PQinsert(int I, int *wt)
{
    if ((ffree + 1) < qsize)
    {
        queue[ffree] = I;
        posicao[I] = ffree;
        FixUp(ffree, wt);
        ffree++;
    }
}

int PQEmpty()
{
    return ffree == 0 ? 1 : 0;
}

void FixUp(int Idx, int *wt)
{
    while (Idx > 0 && comparisonItemWeight(queue[(Idx - 1) / 2], queue[Idx], wt) == 1)
    {
        posicao[queue[(Idx - 1) / 2]] = Idx;
        posicao[queue[Idx]] = (Idx - 1) / 2;
        exch(queue[Idx], queue[(Idx - 1) / 2]);

        Idx = (Idx - 1) / 2;
    }
}

void FixDown(int Idx, int N, int *wt)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Idx + 1;

        if (Child < (N - 1) && comparisonItemWeight(queue[Child], queue[Child + 1], wt) == 1)
            Child++;
        if (comparisonItemWeight(queue[Idx], queue[Child], wt) == -1)
            break;
        // printf("    %d %d\n", posicao[Idx], posicao[Child]);

        posicao[queue[Child]] = Idx;
        posicao[queue[Idx]] = Child;
        exch(queue[Idx], queue[Child]);
        // printf("    %d %d\n", posicao[Idx], posicao[Child]);

        /* continua a descer a árvore */
        Idx = Child;
    }
}

void GRAPHpfs(Graph *G, int s, int st[], int wt[])
{
    int v, w;
    Lista *t;
    Edge *edge;

    PQinit(G->vertex);
    for (v = 0; v < G->vertex; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
    }

    PQinsert(s, wt);
    wt[s] = 0;
    while (!PQEmpty())
    {
        v = PQdelmin(wt);
        posicao[v] = -2;
        if (v == 0)
            continue;
        for (t = G->adj[v]; t != NULL; t = getNextNodeLista(t)) /*percorre a lista do vertice que agora tem maior prioridade (?)*/
        {
            edge = getItemLista(t);
            if (wt[w = edge->V] > wt[v] + edge->W && wt[0] > wt[v] + edge->W)
            {
                /*int k = -1;
                int i;
                for (i = 0; i < ffree; i++)
                    if (queue[i] == w)
                    {
                        k = i;
                        break;
                    }*/

                wt[w] = wt[v] + edge->W;
                // printf("%d\n", queue[w]);
                if (posicao[w] == -1)
                    PQinsert(w, wt);

                FixUp(posicao[w], wt);

                st[w] = v;
            }
        }
    }
    free(posicao);
    free(queue);
}

int PQdelmin(int *wt)
{
    /* troca MENOR elemento com último da tabela e reordena com FixDown */
    posicao[queue[ffree - 1]] = 0;
    posicao[queue[0]] = -2;
    exch(queue[0], queue[ffree - 1]);

    FixDown(0, ffree - 1, wt);
    /* ultimo elemento não considerado na reordenação */
    return queue[--ffree];
}
