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
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux = 0, i = 0;
    char line[MAX] = {0};

    ficheiro = fopen(filename, "r");
    if (ficheiro == NULL)
    {
        exit(EXIT_FAILURE);
    }
    printf("sadasdggrgggggg\n");

    while (fgets(line, MAX, ficheiro) != NULL)
    {
        if (aux == 6)
            break;

        const char s[2] = " ";
        char *token;

        /* get the first token */
        token = strtok(line, s);
        lab.linhas = atoi(token);
        aux++;
        printf("adsasdasdadas\n\n");
        /* walk through other tokens */
        while (token != NULL)
        {
            token = strtok(NULL, s);
            if (aux == 1)
                lab.colunas = atoi(token);
            if (aux == 2)
                lab.solx = atoi(token);
            if (aux == 3)
                lab.soly = atoi(token);
            if (aux == 4)
                strcpy(token, lab.pergunta);
            if (aux == 5)
                lab.blocos = atoi(token);
            aux++;
        }

        int **tab = (int **)calloc(lab.linhas, sizeof(int *));

        for (int i = 0; i < lab.linhas; i++)
        {
            tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        }

        printf("%d", lab.linhas);

        while (fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo) != EOF)
        {
            tab[aux_x][aux_y] = aux_custo;
        }

        fclose(ficheiro);
    }
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
}

/** \brief menu de utilizacao*/
void utilizacao()
{
    fprintf(stderr, "\t\tPRIMEIRA FASE\n\n");
    fprintf(stderr, "opcoes validas:\n");
    fprintf(stderr, "[-s \n");
}
