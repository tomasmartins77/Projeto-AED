#include "modos.h"
#include "Utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp_in;
    FILE *fp_out;

    char *file_end = (char *)malloc(strlen(argv[2]) * sizeof(char) + 2);
    if (file_end == NULL)
        exit(1);

    /*se o formato de invocacao do programa for correto e o ficheiro tiver a extensao correta*/
    if (argc == 3 && check_filename(argv[2]) == 1 && strcmp(argv[1], "-s") == 0)
    {
        /*abre o ficheiro para leitura*/
        fp_in = fopen(argv[2], "r");
        if (fp_in == NULL)
        {
            free(file_end);
            exit(1);
        }

        /*muda a extensao do file_end*/
        strcpy(file_end, change_ex(argv[2]));

        /*abre o ficheiro para escrita*/
        fp_out = fopen(file_end, "w");
        if (fp_out == NULL)
        {
            free(file_end);
            exit(1);
        }
        free(file_end);
        modo1(fp_in, fp_out);
    }
    return 0;
}