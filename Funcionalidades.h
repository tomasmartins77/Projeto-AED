#ifndef Funcionalidades
#define Funcionalidades

/** \brief
 *
 */
int menu_perguntas(int **tab, lab_t lab, int A6_x, int A6_y);

/** \brief
 *
 */
int A1(int **tab, int x, int y);

/** \brief
 *
 */
int A234(int **tab, lab_t lab, int x, int y);

/** \brief
 *
 */
int A5(int **tab, lab_t lab);

int A6(int **tab, lab_t lab, int A6_x, int A6_y);

int upper_coord(lab_t lab, int A6_x, int A6_y);

int A6_aux(int *tab, lab_t lab, int x);

int *change_tab(int **tab, int *tab_id, lab_t lab);

int check_if_outside_aux(lab_t lab, int x);

int A1_aux(int *tab, int x);

#endif
