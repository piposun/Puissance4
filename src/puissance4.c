#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "puissance4.h"
#include "ia.h"
#include "logger.h"
#include "expertSystem.h"
#include "rule.h"
#include "hypothesis.h"

int endGame(Rule *list, int score, int idPlayer, int idHuman) {
  Rule *list2 = NULL;
  Hypothesis *listFact = NULL, *fact = NULL;

  char string[50] = {0};
  int result = 0;

  sprintf(string, "Joueur==%d", idHuman);
  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  sprintf(string, "JoueurPion==%d", idPlayer);
  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  sprintf(string, "MaxPion==%d", score);
  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  list2 = duplicateRule(list);

  frontChaining(&list2, list2, listFact);

  DEBUG("****** LIST FACT FINAL *******");
  if (listFact != NULL) {
    char string[500] = {0};
    displayAllHypothesis(listFact, string);
    DEBUG("%s", string);
  }
  DEBUG("*******************");

  fact = searchFact(listFact, "Partie");

  if (fact != NULL) {
    if (atoi(fact->value) == 1) {
      result = 1;
    }
    else {
      result = -1;
    }
  }

  freeAllRule(list2);
  freeAllHypothesis(listFact);

  return result;
}

int player1(char grid[NB_COLUMN][NB_ROW]) {
  int col = 0;

  INFO("JOUEUR: RED - quelle column voulez vous jouer?");
  scanf("%d", &col);

  return col;
}

int checkMove(char grid[NB_COLUMN][NB_ROW], int column) {
  int y;
  int freeCase = -1;

  column -= 1;

  if (column < 0 || column >= NB_COLUMN) {
    return FALSE;
  }

  for (y = NB_ROW-1; y >= 0; y--) {
    if (grid[column][y] == EMPTY) {
      freeCase = y;
    }
  }

  if (freeCase == -1) {
    return FALSE;
  }

  return TRUE;
}

void initGrid(char grid[NB_COLUMN][NB_ROW]) {
  for(int width = 0; width < NB_COLUMN; width++) {
    for(int height = 0; height < NB_ROW; height++) {
      grid[width][height] = EMPTY;
    }
  }

  /*grid[0][0] = YELLOW;
  grid[1][0] = YELLOW;
  grid[1][1] = YELLOW;
  grid[2][0] = RED;
  grid[2][1] = YELLOW;
  grid[2][2] = YELLOW;

  grid[3][0] = RED;
  grid[3][1] = RED;
  grid[3][2] = YELLOW;*/

}

void displayGrid(char grid[NB_COLUMN][NB_ROW]) {
  system("clear");

  printf("|");
  for(int width = 0; width < NB_COLUMN; width++) {
    printf(" %d ", width+1);
  }
  printf("|\n");

  printf("|");
  for(int width = 0; width < NB_COLUMN; width++) {
    printf("___");
  }
  printf("|\n");

  for(int height = NB_ROW-1; height >= 0; height--) {
    printf("|");
    for(int width = 0; width < NB_COLUMN; width++) {
      printf(" %c ", grid[width][height]);
    }
    printf("|\n");
  }

  printf("|");
  for(int width = 0; width < NB_COLUMN; width++) {
    printf("___");
  }
  printf("|\n");
}

int maxToken(char token, char grid[NB_COLUMN][NB_ROW]) {
  int game[NB_COLUMN][NB_ROW];
  int row = 0, column = 0, max = 0;

  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      game[column][row] = 1;
    }
  }

  // pour le horizontal
  for (row = 0; row < NB_ROW; row++) {
    for (column = 1; column < NB_COLUMN; column++) {
      if ((grid[column][row] == grid[column-1][row]) && (grid[column][row] == token)) {
        game[column][row] = game[column-1][row] + 1;
      }
    }
  }

  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      if (game[column][row] > max) {
        max = game[column][row];
      }
      game[column][row] = 1;
    }
  }

  // pour le vertical
  for (row = 1; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      if ((grid[column][row] == grid[column][row-1]) && (grid[column][row] == token)) {
        game[column][row] = game[column][row-1] + 1;
      }
    }
  }

  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      if (game[column][row] > max) {
        max = game[column][row];
      }
      game[column][row] = 1;
    }
  }

  // pour le diagonal gauche: de bas a gauche vers haut a droite
  for (row = 1; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN-1; column++) {
      if ((grid[column][row] == grid[column+1][row-1]) && (grid[column][row] == token)) {
        game[column][row] = game[column+1][row-1] + 1;
      }
    }
  }

  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      if (game[column][row] > max) {
        max = game[column][row];
      }
      game[column][row] = 1;
    }
  }

  // pour le diagonal droite: de haut a gauche vers bas a droite
  for (row = 1; row < NB_ROW; row++) {
    for (column = 1; column < NB_COLUMN; column++) {
      if ((grid[column][row] == grid[column-1][row-1]) && (grid[column][row] == token)) {
        game[column][row] = game[column-1][row-1] + 1;
      }
    }
  }

  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      if (game[column][row] > max) {
        max = game[column][row];
      }
      game[column][row] = 1;
    }
  }

  return max;
}

void cancelMove(char grid[NB_COLUMN][NB_ROW], int column) {
  column -= 1;

  if (column < 0 || column >= NB_COLUMN) {
    return;
  }

  for (int y = NB_ROW-1; y >= 0; y--) {
    if (grid[column][y] != EMPTY) {
      grid[column][y] = EMPTY;
      break;
    }
  }
}

void play(int player, char grid[NB_COLUMN][NB_ROW], int column) {
  int freeRow = -1;

  column -= 1;

  if (column < 0 || column >= NB_COLUMN) {
    return;
  }

  for (int y = NB_ROW-1; y >= 0; y--) {
    if (grid[column][y] == EMPTY) {
      freeRow = y;
    }
  }

  if (freeRow == -1) {
    return;
  }

  grid[column][freeRow] = (player == IA) ? YELLOW : RED;
}

int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW]) {
  int col;

  switch (player) {
    case PLAYER:
    {
      col = player1(grid);
    } break;
    case IA:
    {
      col = playerIA(list, grid);
    } break;
    default:
    break;
  }

  return col;
}

int main (int argc, char *argv[]) {
  int move = -1, nbMove = 0, end = 0, game = 0, player = PLAYER;
  char grid[NB_COLUMN][NB_ROW];
  Rule *list = NULL;

  srand(time(NULL));

  list = initRules("TestRule.txt");

  INFO("");
  initGrid(grid);
  displayGrid(grid);

  while (end == 0) {
    do {
      move = choose(player, list, grid);
    }while(checkMove(grid, move) == FALSE);

    play(player, grid, move);
    displayGrid(grid);
    evalGrid(list, grid);

    nbMove++;

    game = endGame(list, maxToken(player == IA ? YELLOW : RED, grid), player, PLAYER);

    if (game > 0) {
      INFO("La partie est GAGNEE en %d coups", nbMove);
      end = 1;
    } else if (game < 0) {
      INFO("La partie est PERDUE en %d coups", nbMove);
      end = 1;
    } else if (nbMove == NB_COLUMN*NB_ROW) {
      INFO("Match NUL (%d coups)", nbMove);
      end = 1;
    }

    if (player == IA) {
      player = PLAYER;
    } else {
      player = IA;
    }
  }

  return 0;
}
