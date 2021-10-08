#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

typedef struct labirinto
{
    int linhas;
    int colunas;
    int solx;
    int soly;
    int blocos;
    char pergunta[3];
} lab_t;

char* change_ex(char* filename);

void inserir_dados(char *linha, int aux, lab_t *lab);

int check_if_outside(lab_t lab);

int A1(int** tab, lab_t lab);

int A2_4(int** tab, lab_t lab, int v);

int A3(int** tab, lab_t lab);

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
    }/*
    if(strcmp(lab.pergunta, "A5") == 0)
    {
        return A5(tab, lab);
    }
    if(strcmp(lab.pergunta, "A6") == 0)
    {
        return A6(tab, lab);
    }*/
    exit(1);
}

/*
FILE* output_file(int resposta, char* filename, lab_t lab)
{
    FILE* ficheiro;

    char* file_end = (char*)malloc(strlen(filename) * sizeof(char) + 2);
    strcpy(change_ex(filename), file_end);

    ficheiro = fopen("adsasdaddsa.sol1", "w");
    if(ficheiro == NULL)
    {
        exit(1);
    }
       
    fprintf(ficheiro, "%d\n", resposta);

    return ficheiro;
}*/

lab_t init_maze(){
    lab_t lab;
    lab.linhas = 0;
    lab.colunas = 0;
    lab.blocos = 0;
    lab.solx = 0;
    //lab.pergunta[3] = {'0', '0'};
    lab.soly = 0;
    return lab;
}

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

void free_tab(int** tab, lab_t lab)
{
    int i;
    for (i = 0; i < lab.linhas; i++)
        {
            free(tab[i]);
        }
    free(tab);
}

void modo1(char* filename, FILE* ficheiro)
{
    lab_t lab = init_maze();
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux_tamanho = 0, resposta = 0;
    FILE* fp;
    int** tab = NULL;
    char* file_end = (char*)malloc(strlen(filename) * sizeof(char) + 2);
    strcpy(change_ex(filename), file_end);

    fp = fopen("adsasdaddsa.sol1", "w");
    if(fp == NULL)
    {
        exit(1);
    }
       
    


    while(ficheiro != NULL)
    {
    if(fscanf(ficheiro,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos) != 6)
    {
        fclose(ficheiro);
        exit(1);
    }
    
        tab = init_tab(lab);

        while (aux_tamanho != lab.blocos)
        {
            fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo);
            aux_x--;
            aux_y--;
            tab[aux_x][aux_y] = aux_custo;
            aux_tamanho++;
        }
        if(check_if_outside(lab) == -2)
        {
            resposta = -2;
        }else{
            resposta = menu_perguntas(tab, lab);
        }
        free_tab(tab, lab);
        aux_tamanho = 0;
        fprintf(fp, "%d\n\n", resposta);
    }
        
    
    fclose(fp);
    fclose(ficheiro);   
}


int check_if_outside(lab_t lab)
{
    if(lab.solx > lab.linhas || lab.soly > lab.colunas || lab.solx < 1 || lab.soly < 1)
        return -2;
    return 0;
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
/*
int A5(int** tab, lab_t lab)
{
   
}

int A6(int** tab, lab_t lab)
{
    
}*/

int check_filename(char* filename)
{
    int i = 0, j = 0, t = 0;
    char ex[4];

    i = strlen(filename);
    t = i - 4;
    for(j = 0; t < i+1; j++, t++)
    {
        ex[j] = filename[t];
    }

    if(strcmp(ex, ".in1") == 0);
    return 1;
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

int main(int argc, char *argv[])
{
    FILE *ficheiro;
    //ver nome ficheiro antes de o abrir
    if(check_filename(argv[2]) == 1)
    {
        if (argc != 3 || strcmp(argv[1], "-s") != 0)
        exit(1);

        ficheiro = fopen(argv[2], "r");
        if (ficheiro == NULL)
        {
            exit(EXIT_FAILURE);
        }

        modo1(argv[2], ficheiro);
    }
    
    return 0;
}