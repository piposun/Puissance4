#ifndef HEADER_PUISSANCE4
#define HEADER_PUISSANCE4

#include "rule.h"

#define NB_COLUMN 7
#define NB_ROW    6

#define EMPTY  ' '
#define RED    'x'
#define YELLOW 'o'

#define PLAYER  1
#define IA 0

#define TRUE  1
#define FALSE 0

int endGame(Rule *list, int score, int idPlayer, int idHuman);
int player1(char grid[NB_COLUMN][NB_ROW]);
int checkMove(char grid[NB_COLUMN][NB_ROW], int column);
void initGrid(char grid[NB_COLUMN][NB_ROW]);
void displayGrid(char grid[NB_COLUMN][NB_ROW]);
int maxToken(char token, char grid[NB_COLUMN][NB_ROW]);
void play(int player, char grid[NB_COLUMN][NB_ROW], int column);
int choose(int player, char grid[NB_COLUMN][NB_ROW]);

#endif /* HEADER_PUISSANCE4 */
