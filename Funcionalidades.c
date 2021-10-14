#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

/** \brief
 *
 * \param tab int**
 * \param lab lab_t
 * \return int
 *
 */
int menu_perguntas(int** tab, lab_t lab)
{
    if(strcmp(lab.pergunta, "A1") == 0)
    {
        return A1(tab, lab.solx, lab.soly);
    }
    if(strcmp(lab.pergunta, "A2") == 0)
    {
        return A234(tab, lab, lab.solx, lab.soly);
    }
    if(strcmp(lab.pergunta, "A3") == 0)
    {
        return A234(tab, lab, lab.solx, lab.soly);
    }
    if(strcmp(lab.pergunta, "A4") == 0)
    {
        return A234(tab, lab, lab.solx, lab.soly);
    }
    if(strcmp(lab.pergunta, "A5") == 0)
    {
        if(tab[lab.solx-1][lab.soly-1] < 1)
            return -1;
        else
            return A5(tab, lab);
    }
    exit(1);
}

/** \brief
 *
 * \param tab int**
 * \param x int
 * \param y int
 * \return int
 *
 */
int A1(int** tab, int x, int y)
{
    return tab[x-1][y-1];
}

/** \brief
 *
 * \param tab int**
 * \param lab lab_t
 * \param x int
 * \param y int
 * \return int
 *
 */
int A234(int** tab, lab_t lab, int x, int y)
{
    int resultado = 0, i;

    for(i = -1; i <= 1; i += 2)
    {
        if(check_if_outside(lab, x + i, y) == 0)
        {
            resultado = A1(tab, x + i, y);
            if(verifica_coord(lab, resultado) == 1)
                return 1;
        }
    }
    for(i = -1; i <= 1; i += 2)
    {
        if(check_if_outside(lab, x, y + i) == 0)
        {
            resultado = A1(tab, x, y + i);
            if(verifica_coord(lab, resultado) == 1)
                return 1;
        }
    }
    return 0;
}

/** \brief
 *
 * \param tab int**
 * \param lab lab_t
 * \return int
 *
 */
int A5(int** tab, lab_t lab)
{
    if(tab[lab.solx-1][lab.soly-1]>0)
    {
        if(check_if_outside(lab, lab.solx-1, lab.soly) != -2 && tab[lab.solx-2][lab.soly-1] == 0 && check_if_outside(lab, lab.solx+1, lab.soly) != -2 && tab[lab.solx][lab.soly-1] == 0)
            return 1;
        else if(check_if_outside(lab, lab.solx, lab.soly-1) != -2 && tab[lab.solx-1][lab.soly-2] == 0 && check_if_outside(lab, lab.solx, lab.soly+1) != -2 && tab[lab.solx-1][lab.soly] == 0)
            return 1;
        else
            return 0;
    }
    return -1;
}

int A6(int** tab, lab_t lab, int A6_x, int A6_y)
{
    int i = 0, aux = 0, p = lab.solx*lab.soly-1, j = 0, q = A6_x*A6_y-1, size = lab.linhas*lab.colunas, x = 0, y = 0;

    int* tab_id = (int*)calloc(size, sizeof(int));
    int* tab_size = (int*)calloc(size, sizeof(int));
    if(tab_id == NULL || tab_size == NULL)
    {
        free_tab(tab, lab);
        exit(1);
    }

    if(upper_coord(tab, lab, A6_x, A6_y) == 1)
    {
        x = lab.solx;
        y = lab.soly;
    }
    if(upper_coord(tab, lab, A6_x, A6_y) == 0)
    {
        x = A6_x;
        y = A6_y;
    }

    while (aux != size)
   {
      for (i = p; i != tab_id[i]; i = tab_id[i])
      {
        if(A234(tab, lab, x, y) == 1)
            tab_id[i] = 1;
      }
      for (j = q; j != tab_id[j]; j = tab_id[j])
      {
        if(A234(tab, lab, x, y) == 1)
            tab_id[j] = 1;
      }

        if(tab_id[i] != 1 && tab_id[j] != 1)
        {
            if (tab_size[i] < tab_size[j])
            {
            tab_id[i] = j;
            tab_size[j] += tab_size[i];
        }
        else
        {
            tab_id[j] = i;
            tab_size[i] += tab_size[j];
        }
        }
      
      p++;
      q--;
      aux++;
    }
    free(tab_id);
    free(tab_size);
}

int upper_coord(int** tab, lab_t lab, int A6_x, int A6_y)
{
    if(lab.solx < A6_x)
        return 1;
    else
        return 0;   
}

int down_coord(int** tab, lab_t lab, int A6_x, int A6_y)
{
    if(lab.solx > A6_x)
        return (lab.solx-1)*lab.colunas + lab.soly-1;
    else
        return (A6_x-1)*lab.colunas + A6_y-1;;   
}