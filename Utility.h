#ifndef Utility
#define Utility

#include "Funcionalidades.h"

int** init_tab(lab_t lab);

lab_t init_maze();

void free_tab(int** tab, lab_t lab);

int check_if_outside(lab_t lab);

int check_filename(char* filename);

char* change_ex(char* filename);

void close_files(FILE* fp1, FILE* fp2);

#endif