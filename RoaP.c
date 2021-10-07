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


int** enche_labirinto(char* ficheiro){




}

lab_t init_maze(){
    lab_t lab;
    lab.linhas = 0;
    lab.colunas = 0;
    lab.blocos = 0;
    lab.solx = 0;
    lab.soly = 0;
    return lab;
}

int** init_tab(lab_t lab)
{
    int **tab = (int **)calloc(lab.linhas, sizeof(int *));
        
        for (int i = 1; i <= lab.linhas; i++)
        {
            tab[i] = (int *)calloc(lab.colunas, sizeof(int));
        }
    return tab;
}

void modo1(int argc, FILE* ficheiro)
{
    
    lab_t lab = init_maze();
    int aux_x = 0, aux_y = 0, aux_custo = 0, aux_tamanho = 0;
    
    fscanf(ficheiro,"%d %d %d %d %s %d", &lab.linhas, &lab.colunas, &lab.solx, &lab.soly, lab.pergunta, &lab.blocos);

    int** tab = init_tab(lab);

    while (fscanf(ficheiro, "%d %d %d", &aux_x, &aux_y, &aux_custo) != EOF)
    {
        tab[aux_x][aux_y] = aux_custo;
        if(aux_tamanho == lab.blocos)
        {
                aux_tamanho = 0;
                break;
        }
            aux_tamanho++;
    }

        //fclose(ficheiro); nao se pode fechar o ficheiro nesta função
}

int check_if_outside(lab_t lab)
{
    if(lab.solx > lab.linhas || lab.soly > lab.colunas)
        return -2;
    return 0;
}

int A1(int** tab, lab_t lab)
{
    //ver se esta fora do maze
    int resultado = 0;
    return resultado = tab[lab.solx][lab.soly];
}

int A3(int** tab, lab_t lab)
{
    
}

int A4(int** tab, lab_t lab)
{
   
}

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
    int mode;
    FILE *ficheiro;
    //ver nome ficheiro antes de o abrir
    if(check_filename(argv[2]) == 0)
    {
        exit(1);
    }
    char* file_end;
    strcpy(file_end, change_ex(argv[2]));
    
    printf("\n%s\n", file_end);
    ficheiro = fopen(argv[2], "r");
    if (ficheiro == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(feof(ficheiro) != 0)
    {


    }




// ficheiros podem ter .in1 no meio do nome
    if (argc != 3 || strcmp(argv[1], "-s") != 0)
        exit(0);

    if (strstr(argv[2], ".in1") != 0)
    {
        modo1(argc, ficheiro);
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
