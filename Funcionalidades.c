#include "modos.h"
#include "Utility.h"
#include "Funcionalidades.h"

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

int A1(int** tab, int x, int y)
{
    return tab[x-1][y-1];
}
/*quando esta tudo rodeado nao da*/
int A234(int** tab, lab_t lab, int x, int y)
{
    int resultado = 0, i = 0, j = 0;

    for(i = -1; i <= 1; i += 2)
    {
        if(check_if_outside(lab, x + i, y) == 0)
        {
            resultado = A1(tab, x + i, y);
            return verifica_coord(lab, resultado);
        }
        if(j == 1)
            break;
        for(j = -1; j <= 1; j += 2)
        {
            if(check_if_outside(lab, x, y + j) == 0)
            {
                resultado = A1(tab, x, y + j);
                return verifica_coord(lab, resultado);
            }
        }     
    }
    return 0;
}

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