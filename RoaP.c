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


void inserir_dados(char *linha, int aux, lab_t *lab);

void modo1(int argc, char *filename)
{
    FILE *ficheiro;
    lab_t lab;
    int aux_x = 0, aux_y = 0, aux_custo = 0;
    
    ficheiro = fopen(filename, "r");
    if (ficheiro == NULL)
    {
        exit(EXIT_FAILURE);
    }

        fscanf(ficheiro,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos);

        int **tab = (int **)calloc(lab.linhas, sizeof(int *));
        
        for (int i = 1; i <= lab.linhas; i++)
        {
            tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        }

        while (fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo) != EOF)
        {
            tab[aux_x][aux_y] = aux_custo;
        }

        fclose(ficheiro);
}

int A1(int** tab, lab_t lab)
{
    int resultado = 0;
    return resultado = tab[lab.solx][lab.soly];
}

int A3(int** tab, lab_t lab)
{
    int resultado = 0;
    if(tab[lab.solx][lab.soly] > 0 )
    return resultado = tab[lab.solx][lab.soly];
}

int A4(int** tab, lab_t lab)
{
    int resultado = 0;
    if(tab[lab.solx][lab.soly] == -1 )
    return resultado = tab[lab.solx][lab.soly];
}

int main(int argc, char *argv[])
{
    int mode;

    if (argc != 3 || strcmp(argv[1], "-s") != 0)
        exit(0);

    if (strstr(argv[2], ".in1") != 0)
    {
        modo1(argc, argv[2]);
    }
    else
        exit(0);

    return 0;
}

/** \brief menu de utilizacao*/
void utilizacao()
{
    fprintf(stderr, "\t\tPRIMEIRA FASE\n\n");
    fprintf(stderr, "opcoes validas:\n");
    fprintf(stderr, "[-s \n");
}
