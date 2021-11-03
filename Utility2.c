#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"
#include "Utility2.h"

void change_tab(maze_t maze, int **tab, int *tab_id)
{
    int x = 0, y = 0, i = 0, j = 0;

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