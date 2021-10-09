#ifndef Funcionalidades
#define Funcionalidades

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct labirinto
{
    int linhas;
    int colunas;
    int solx;
    int soly;
    int blocos;
    char pergunta[3];
} lab_t;

int menu_perguntas(int** tab, lab_t lab);

int A1(int** tab, lab_t lab);

int A2_4(int** tab, lab_t lab, int v);

int A3(int** tab, lab_t lab);

int A5(int** tab, lab_t lab);

//int A6(int** tab, lab_t lab);

#endif