#include "modos.h"
#include "Funcionalidades.h"
#include "Utility.h"

int main(int argc, char *argv[])
{
    FILE *fp_in;
    FILE *fp_out;

    char* file_end = (char*)malloc(strlen(argv[2]) * sizeof(char) + 2);
    if(file_end == NULL)
    {
            exit(1);
    }

    if(argc == 3 && check_filename(argv[2], argc+1) == 1 && strcmp(argv[1], "-s") == 0)
    {
        fp_in = fopen(argv[2], "r");
        if (fp_in == NULL)
        {
            free(file_end);
            exit(1);
        }

        strcpy(file_end, change_ex(argv[2]));

        fp_out = fopen("adsasdaddsa.sol1", "w");
        if(fp_out == NULL)
        {
            free(file_end);
            exit(1);
        }
        free(file_end);
        modo1(fp_in, fp_out);
    }
    
    return 0;
}