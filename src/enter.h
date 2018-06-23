# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//____________________________________________________________________________________________________________________________________
//Declaration a recopier
#define NBDIGITFLOATMAX  19
#define NBDIGITINTMAX     9

//____________________________________________________________________________________________________________________________________
// Fonctions saisie
int enterFloat(float *number, float min, float max);
int enterInt(int *number, int min, int max);
int enterChar(char *string, int nbCharMax);
int clearBuffer(int *nbCharToo);
