#ifndef HEADER_IA
#define HEADER_IA

#include "puissance4.h"
#include "rule.h"

float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW]);
int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove);
float negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height, int increment, int nbMove);

#endif /* HEADER_IA */
