#ifndef Utility
#define Utility

#include "modos.h"
#define DIREITA 1
#define ESQUERDA 0

int** init_tab(lab_t lab);

lab_t init_maze();

void free_tab(int** tab, lab_t lab);

int check_if_outside(lab_t lab, int x, int y);

int check_filename(char* filename, int offset);

char* change_ex(char* filename);

void close_files(FILE* fp1, FILE* fp2);

#endif