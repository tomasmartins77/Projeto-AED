#include "Funcionalidades.h"

int menu_perguntas(int** tab, lab_t lab)
{
    if(strcmp(lab.pergunta, "A1") == 0)
    {
        return A1(tab, lab);
    }
    if(strcmp(lab.pergunta, "A2") == 0)
    {
        return A2_4(tab, lab, 0);
    }
    if(strcmp(lab.pergunta, "A3") == 0)
    {
        return A3(tab, lab);
    }
    if(strcmp(lab.pergunta, "A4") == 0)
    {
        return A2_4(tab, lab, -1);
    }
    if(strcmp(lab.pergunta, "A5") == 0)
    {
        return A5(tab, lab);
    }/*
    if(strcmp(lab.pergunta, "A6") == 0)
    {
        return A6(tab, lab);
    }*/
    exit(1);
}

int A1(int** tab, lab_t lab)
{
    int resultado = 0;
    return resultado = tab[lab.solx-1][lab.soly-1];
}

int A3(int** tab, lab_t lab)
{
    if((lab.solx - 1 >= 1 && tab[lab.solx-2][lab.soly-1] > 0) || (lab.solx + 1 <= lab.linhas && tab[lab.solx][lab.soly-1] > 0))
    {
        return 1;
    }else if((lab.soly - 1 >= 1 && tab[lab.solx-1][lab.soly-2] > 0) || (lab.soly + 1 <= lab.colunas && tab[lab.solx-1][lab.soly] > 0))
    {
        return 1;
    }
    return 0;
}

int A2_4(int** tab, lab_t lab, int v)
{
    if((lab.solx - 1 >= 1 && tab[lab.solx-2][lab.soly-1] == v) || (lab.solx + 1 <= lab.linhas && tab[lab.solx][lab.soly-1] == v))
    {
        return 1;
    }else if((lab.soly - 1 >= 1 && tab[lab.solx-1][lab.soly-2] == v) || (lab.soly + 1 <= lab.colunas && tab[lab.solx-1][lab.soly] == v))
    {
        return 1;
    }
    return 0;
}

int A5(int** tab, lab_t lab)
{
    if(lab.solx-1 >= 1 && lab.solx+1 < lab.colunas && tab[lab.solx-1][lab.soly-1]>0)
    {
        if(tab[lab.solx-2][lab.soly-1] == 0 || tab[lab.solx][lab.soly-1] == 0)
            return 1;  
        else
            return 0;
    }else if(lab.soly-1 >= 1 && lab.soly+1 < lab.linhas && tab[lab.solx-1][lab.soly-1]>0)
    {
        if((lab.soly-1 >= 1 && tab[lab.solx-1][lab.soly-2] == 0) || (lab.soly+1 <= lab.colunas && tab[lab.solx-1][lab.soly] == 0))
            return 1;
        else
            return 0;
    }
    return -1;
}
/*
int A6(int** tab, lab_t lab)
{
    
}*/