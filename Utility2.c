#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"
#include "Utility2.h"

void change_tab(maze_t maze, int **tab, int *tab_id)
{
    int x = 0, y = 0, i = 0, j = 0, salas;

    for (x = 0; x < maze.linhas; x++)
    {
        for (y = 0; y < maze.colunas; y++)
        {
            if (tab[x][y] != 0)
                continue;

            for (i = x * maze.colunas + y; i != tab_id[i]; i = tab_id[i])
                ;
        }
    }
}

Lista *initLista(void)
{
    return NULL;
}

/*cria e inicializa uma nova lista*/
Lista *criaLista()
{
    Lista *newList = (Lista *)malloc(sizeof(Lista));

    if (newList == NULL)
        exit(1);

    newList = initLista();

    return newList;
}

void freeLista(Lista *lista, void(destruir_fn)(void *))
{
    Node *curr;
    Node *next = lista->first;

    while (next != NULL)
    {
        curr = next;
        next = next->next;
        destruir_fn(curr->value);
        free(curr);
    }
    free(lista);
}

Lista *insertUnsortedLista(Lista *lista, void *value)
{
    /*allocate new value*/
    Node *new = (Node *)malloc(sizeof(Node));

    if (new == NULL)
    { //nao sei se e isto ou return new;
        free(new);
        exit(1);
    }

    new->next = NULL; //inicia o next como null porque esse passa a ser o ultimo elemento
    new->value = value;

    if (lista->first == NULL) //se a lista estiver vazia
        lista->first = new;   //elemento a inserir torna-se o primeiro da lista

    else
    {
        lista->last->next = new; //insere elemento no final da lista
    }
    lista->last = new; //torna esse node o ultimo pois inserimos no final

    return new;
}