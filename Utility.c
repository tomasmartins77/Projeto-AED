#include "Utility.h"


int** init_tab(lab_t lab)
{
    int i;
    int **tab = (int **)calloc(lab.linhas, sizeof(int *));
        
        for (i = 0; i < lab.linhas; i++)
        {
            tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        }
    return tab;
}

lab_t init_maze()
{
    int i;
    lab_t lab;
    lab.linhas = 0;
    lab.colunas = 0;
    lab.blocos = 0;
    lab.solx = 0;
    for(i = 0; i < 2; i++)
    lab.pergunta[i] = 0;
    lab.soly = 0;
    return lab;
}

void free_tab(int** tab, lab_t lab)
{
    int i;
    for (i = 0; i < lab.linhas; i++)
        {
            free(tab[i]);
        }
    free(tab);
}

int check_if_outside(lab_t lab)
{
    if(lab.solx > lab.linhas || lab.soly > lab.colunas || lab.solx < 1 || lab.soly < 1)
        return -2;
    return 0;
}

int check_filename(char* filename, int offset)
{
    int i = 0, j = 0, t = 0;
    char ex[offset];

    i = strlen(filename);
    t = i - offset;
    for(j = 0; t < i; j++, t++)
    {
        ex[j] = filename[t];
    }

    if(offset == 4)
    {
        if(strcmp(ex, ".in1") == 0);
            return 1;
    }
    return 0;
}

char* change_ex(char* filename)
{
    int i = 0, j = 0, t = 0;
    char ex[6] = ".sol1";

    i = strlen(filename);
    t = i - 5;
    for(j = 0; t < i+1; j++, t++)
    {
        filename[t+1] = ex[j];
    }
    return filename;
}

void close_files(FILE* fp1, FILE* fp2)
{
    fclose(fp1);
    fclose(fp2);
}