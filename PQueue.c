#include "PQueue.h"

static int *queue;
static int ffree;
static int qsize;
static int *posicao;

void PQinit(int size)
{
    int i = 0;
    queue = (int *)calloc(size, sizeof(int));
    if (queue == NULL)
        exit(1);

    posicao = (int *)malloc(size * sizeof(int));
    if (posicao == NULL)
        exit(1);

    qsize = size;
    ffree = 0;
    for (i = 0; i < size; i++)
        posicao[i] = -3;
}

void PQinsert(int I)
{
    if ((ffree + 1) < qsize)
    {
        queue[ffree] = I;
        posicao[ffree] = ffree;
        FixUp(ffree);
        ffree++;
    }
}

void exch(int queueA, int queueB, int posicaoA, int posicaoB)
{
    int t = queueA;
    queueA = queueB;
    queueB = t;

    t = posicaoA;
    posicaoA = posicaoB;
    posicaoB = t;
}

int PQEmpty()
{
    return ffree == 0 ? 1 : 0;
}

void FixUp(int Idx)
{
    while (Idx > 0 && comparisonItemFnt(queue[(Idx - 1) / 2], queue[Idx]) == 1)
    {
        exch(queue[Idx], queue[(Idx - 1) / 2], posicao[Idx], posicao[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
}

void FixDown(int Idx, int N)
{
    int Child; /* índice de um nó descendente */
    while (2 * Idx < N - 1)
    { /* enquanto não chegar às folhas */
        Child = 2 * Idx + 1;

        if (Child < (N - 1) && comparisonItemFnt(queue[Child], queue[Child + 1]) == 1)
            Child++;
        if (comparisonItemFnt(queue[Idx], queue[Child]) == -1)
            break;

        exch(queue[Idx], queue[Child], posicao[Idx], posicao[Child]);
        /* continua a descer a árvore */
        Idx = Child;
    }
}

void GRAPHpfs(Graph *G, int s, int st[], int wt[], int sala_final)
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

    PQinsert(s);
    wt[s] = 0;
    while (!PQEmpty())
    {
        v = PQdelmin();
        if (v == 0)
            continue;
        for (t = G->adj[v]; t != NULL; t = getNextNodeLista(t)) /*percorre a lista do vertice que agora tem maior prioridade (?)*/
        {
            edge = getItemLista(t);
            if (wt[w = edge->V] > wt[v] + edge->W && wt[0] > wt[v] + edge->W)
            {
                wt[w] = wt[v] + edge->W;

                if (posicao[w] == -3)
                    PQinsert(w);

                FixUp(w);

                st[w] = v;
            }
        }
    }
    free(queue);
    free(posicao);
}

int PQdelmin()
{
    /* troca MENOR elemento com último da tabela e reordena com FixDown */
    exch(queue[0], queue[ffree - 1], posicao[0], posicao[ffree - 1]);
    FixDown(0, ffree - 1);
    /* ultimo elemento não considerado na reordenação */
    return queue[--ffree];
}
