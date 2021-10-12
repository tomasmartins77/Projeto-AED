#include "Funcionalidades.h"
#include "Utility.h"

int menu_perguntas(int** tab, lab_t lab, int sec_cordx, int sec_cordy)
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
        return A5(tab, lab);
    }
    if(strcmp(lab.pergunta, "A6") == 0)
    {
       // return A6(tab, lab, sec_cordx, sec_cordy);
    }
    exit(1);
}

int A1(int** tab, int x, int y)
{
    int resultado = 0;
    return resultado = tab[x-1][y-1];
}

int A234(int** tab, lab_t lab, int x, int y)
{
    int resultado = 0, i, j;

    for(i = -1; i<=1; i+=2)
    {
        if(check_if_outside(lab, x+i, y) == 0)
        {
            resultado = A1(tab, x+i, y);
        if(verifica_coord(tab, lab, resultado) == 1)
            return 1;
        else
            return 0;
        }
        if(j == 1)
            break;
        for(j=-1; j<=1; j+=2)
        {
            if(check_if_outside(lab, x+i, y) == 0)
            {
                resultado = A1(tab, x, y+j);
                if(verifica_coord(tab, lab, resultado) == 1)
                    return 1;
                else
                    return 0;
            }
        }     
    }
    return -2;
}

int verifica_coord(int** tab, lab_t lab, int custo)
{
    switch(lab.pergunta[1])
    {
        case '2':
            if(custo == 0)
                return 1;
        case '3':
            if(custo > 0)
                return 1;
        case '4':
            if(custo == -1)
                return 1;
    }
     return 0;
}

//nao esta a 100%
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

/*int A6(int** tab, lab_t lab, int sec_cordx, int sec_cordy)
{
    int i = 0, j = 0;
    while(i != j)
    {
        for (i = lab.solx; i != tab[i]; i = tab[i])
      
        for (j = sec_cordx; j != tab[j]; j = tab[j])
        
        if(i == j)
        {
            lab.solx = i;
            sec_cordx = i;
            break;
        }

            if(lab.solx < sec_cordx)
            {
                tab[i] = j;
                tab[j] += tab[i][lab.soly];
            }else{
                tab[j] = i;
                tab[i] += tab[j][sec_cordy];
            }
            lab.solx++;
            sec_cordx--;
    }
    
    while(i != j)
    {
        for (i = lab.soly; i != tab[i]; i = tab[i])
      
        for (j = sec_cordy; j != tab[j]; j = tab[j])
        
        if(i == j)
        {
            lab.soly = i;
            sec_cordy = i;
            break;
        }

            if(lab.soly < sec_cordy)
            {
                tab[i] = j;
                tab[j] += tab[lab.solx][i];
            }else{
                tab[j] = i;
                tab[i] += tab[sec_cordx][j];
            }
            lab.soly++;
            sec_cordy--;
            printf("%d-%d    %d-%d\n", lab.solx, lab.soly, sec_cordx, sec_cordy);
    }
    return 0;
}*/