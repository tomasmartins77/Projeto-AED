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
        printf("%d\n", lab.linhas);
        printf("%d\n", lab.colunas);
        printf("%d\n", lab.solx);
        printf("%d\n", lab.soly);
        printf("%s\n", lab.pergunta);
        printf("%d\n", lab.blocos);

        int **tab = (int **)calloc(lab.linhas, sizeof(int *));
        
        for (int i = 1; i <= lab.linhas; i++)
        {
            tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        }

        while (fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo) != EOF)
        {
                    printf("%d ", aux_x);
                    printf("%d ", aux_y);
                    printf("%d\n", aux_custo);

            tab[aux_x][aux_y] = aux_custo;
        }

        fclose(ficheiro);
}


int main(int argc, char *argv[])
{
    int mode;

    if (argc != 3)
        exit(0);
    //ver se argv1 é -s
    if (strstr(argv[2], ".in1") != 0)
    {
        modo1(argc, argv[2]);
    }
    else
        exit(0);

    return 0;
}
/*
void inserir_dados(char *linha, int aux, lab_t *lab)
{
    switch (aux)
    {
    case 0:
        lab->linhas = atoi(linha);
        break;
    case 1:
        lab->colunas = atoi(linha);
        break;
    case 2:
        lab->solx = atoi(linha);
        break;
    case 3:
        lab->soly = atoi(linha);
        break;
    case 4:
        strcpy(linha, lab->pergunta);
        break;
    case 5:
        lab->blocos = atoi(linha);
        break;
    }
}*/

/** \brief menu de utilizacao*/
void utilizacao()
{
    fprintf(stderr, "\t\tPRIMEIRA FASE\n\n");
    fprintf(stderr, "opcoes validas:\n");
    fprintf(stderr, "[-s \n");
}
