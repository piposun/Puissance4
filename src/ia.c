#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ia.h"
#include "rule.h"
#include "puissance4.h"
#include "logger.h"
#include "expertSystem.h"

int convColorToValue(char color) {
  int value = 0;

  if (color == RED) {
    value = PLAYER;
  }
  else if (color == YELLOW) {
    value = IA;
  }

  return value;
}

void evalSerie(Rule *list, int idPlayer, char grid[NB_COLUMN][NB_ROW], int row, int column, int moveR, int moveC,   int *lastColor, int *serie, float *result) {
  Rule *list2 = NULL;
  Hypothesis *listFact = NULL, *fact = NULL;
  char string[50];

  memset(string, 0, sizeof(char)*50);

  sprintf(string, "Player==%d", idPlayer+1);
  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  if ((row > 0 && grid[column][row-1] != EMPTY) || row == 0) {
    sprintf(string, "ColorCase==%d", convColorToValue(grid[column][row]));
  }
  else {
    sprintf(string, "ColorCase==%d", -1);
  }

  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  if ((row - moveR) >= 0 && (column - moveC) >= 0) {
    if (grid[column-moveC][row-moveR] != EMPTY) {
      *lastColor = convColorToValue(grid[column-moveC][row-moveR]);
    }
    //INFO("%d %c : %d", row+1, grid[column-moveC][row-moveR], *lastColor);
    sprintf(string, "ColorAdjacente==%d", *lastColor);
  }
  else {
    sprintf(string, "ColorAdjacente==%d", -10);
  }

  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  list2 = duplicateRule(list);

  frontChaining(&list2, list2, listFact);

  fact = searchFact(listFact, "Gain");

  if (fact != NULL) {
    (*result) += atof(fact->value);
    (*serie)++;
  }
  else if ((row-moveR) >= 0 && (column-moveC) >= 0 && convColorToValue(grid[column-moveC][row-moveR]) != convColorToValue(grid[column][row]) && grid[column][row] != EMPTY) {
    //detection changement de couleur
    *result = 0;
    *serie = 0;
  }

  freeAllRule(list2);
  freeAllHypothesis(listFact);

  list2 = NULL;
  listFact = NULL;
}

float evalGridWhithPlayer(Rule *list, char grid[NB_COLUMN][NB_ROW], int idPlayer) {

  int lastColor = 0;
  float result = 0;
  float max = 0;
  int serie = 0;
  int nbToken = 0;

  // Calcule des scores pour les colonnes
  for (int column = 0; column < NB_COLUMN; column++) {
    serie = 0;
    nbToken = 0;
    lastColor = 0;
    if (max < result) {
      max = result;
    }
    result = 0;
    for (int row = 0; row < NB_ROW; row++) {

      if (row > 0 && grid[column][row-1] == EMPTY) {
        break;
      }

      evalSerie(list, idPlayer, grid, row, column, 1, 0, &lastColor, &serie, &result);

      if (result >= 3.5) {
        return result;
      }
    }
  //  INFO("column:%d value%f id:%d", column, result, idPlayer);
  }

  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les lignes G->D
  for (int row = 0; row < NB_ROW; row++) {
    serie = 0;
    nbToken = 0;
    lastColor = 0;
    if (max < result) {
      max = result;
    }
    result = 0;
    for (int column = 0; column < NB_COLUMN; column++) {

      if ((column > NB_COLUMN / 2 && result == 0) || serie >= 4) {
        break;
      }

      if (grid[column][row] != EMPTY) {
        nbToken++;
      }

      evalSerie(list, idPlayer, grid, row, column, 0, 1, &lastColor, &serie, &result);
  //  INFO("G->D row:%d value%f id:%d", row, result, idPlayer);
      if (result >= 3.5) {
        return result;
      }
    }

    if (nbToken == 0) {
      break;
    }

  //  INFO("END G->D row:%d value%f id:%d", row, result, idPlayer);
  }

  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les lignes D->G
  for (int row = 0; row < NB_ROW; row++) {
    serie = 0;
    nbToken = 0;
    lastColor = 0;
    if (max < result) {
      max = result;
    }
    result = 0;
    for (int column = NB_COLUMN-1; column >= 0; column--) {

      if ((column < NB_COLUMN / 2 && result == 0) || serie >= 4) {
        break;
      }

      if (grid[column][row] != EMPTY) {
        nbToken++;
      }

      evalSerie(list, idPlayer, grid, row, column, 0, -1, &lastColor, &serie, &result);
      if (result >= 3.5) {
        return result;
      }
    }

    if (nbToken == 0) {
      break;
    }
  }

  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal BG->HD
  for (int column = -2; column < NB_COLUMN; column++) {
    int row = 0;
    serie = 0;
    result = 0;
    lastColor = 0;
    for (int index = 0; index < NB_ROW; index++) {
      if (serie >= 4 || (row == 0 && column > NB_COLUMN/2)) {
        break;
      }
      if (row+index < NB_ROW && column+index >= 0 && column+index < NB_COLUMN) {
        evalSerie(list, idPlayer, grid, row+index, column+index, 1, 1, &lastColor, &serie, &result);
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal HD->BG
  for (int column = NB_COLUMN+1; column >= 0; column--) {
    int row = NB_ROW-1;
    serie = 0;
    result = 0;
    lastColor = 0;
    for (int index = 0; index < NB_ROW; index++) {
      if (serie >= 4 || (row == NB_ROW-1 && column < NB_COLUMN/2)) {
        break;
      }
      if (row-index >= 0 && column-index >= 0 && column-index < NB_COLUMN) {
        evalSerie(list, idPlayer, grid, row-index, column-index, -1, -1, &lastColor, &serie, &result);
        //INFO("HD->BG row:%d column:%d value%f id:%d", row-index, column-index, result, idPlayer);
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal HG->BD
  for (int column = -2; column < NB_COLUMN; column++) {
    int row = NB_ROW-1;
    serie = 0;
    result = 0;
    lastColor = 0;
    for (int index = 0; index < NB_ROW; index++) {
      if (serie >= 4 || (row == NB_ROW-1 && column > NB_COLUMN/2)) {
        break;
      }
      if (row-index >= 0 && column+index >= 0 && column+index < NB_COLUMN) {
        evalSerie(list, idPlayer, grid, row-index, column+index, -1, 1, &lastColor, &serie, &result);
        //INFO("HG->BD row:%d column:%d value%f id:%d", row-index, column+index, result, idPlayer);
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal BD->HG
  for (int column = NB_COLUMN+1; column >= 0; column--) {
    int row = 0;
    serie = 0;
    result = 0;
    lastColor = 0;
    for (int index = 0; index < NB_ROW; index++) {
      if (serie >= 4 || (row == 0 && column < NB_COLUMN/2)) {
        break;
      }
      if (row+index >= 0 && column-index >= 0 && column-index < NB_COLUMN) {
        evalSerie(list, idPlayer, grid, row+index, column-index, 1, -1, &lastColor, &serie, &result);
        //INFO("HD->BG row:%d column:%d value%f id:%d", row+index, column-index, result, idPlayer);
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  if (max < result) {
    max = result;
  }

  return max;
}

float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW]) {

  float result[2];
  float maxValue = 0;

  result[0] = 0;
  result[1] = 0;

  for (int idPlayer = 0; idPlayer < 2; idPlayer++) {
    result[idPlayer] = evalGridWhithPlayer(list, grid, idPlayer);
    //INFO("%d %f", idPlayer, result[idPlayer]);
    if (result[idPlayer]>= 3.5) {
      break;
    }
  }

  if (result[1] < result[0]) {
    maxValue = -result[0];
  } else {
    maxValue = result[1];
  }

//INFO("MAX %f", maxValue);

return maxValue;
}

float negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height) {
  for(int idPlayer = PLAYER; idPlayer <= IA; idPlayer++) {
    int game = endGame(list, maxToken(player == IA ? YELLOW : RED, grid), idPlayer, IA);
    if (game != 0) {
      return game * 1000 * (profondeur+1);
    }
  }


  if (profondeur == 0) {
    return evalGrid(list, grid);
  }

  for (int column = 0; column < NB_COLUMN; column++) {
    float score = 0;
    if(checkMove(grid, column+1) == FALSE) {
      continue;
    }

    if (height == 0) {
      height = 3;
      continue;
    }

    //INFO("TEST alpha:%f beta:%f player:%s", alpha, beta, (player == IA) ? "IA" : "PLAYER");

    play(player, grid, column+1);
    //displayGrid(grid);
    score = -negamax(list, grid, (player == IA) ? PLAYER : IA, -beta, -alpha, profondeur-1, height-1);

    if (score > alpha) {
      alpha = score;
    }
    cancelMove(grid, column+1);

    if (alpha >= beta) {
      return alpha;
    }

  }

  return alpha;
}

int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW]) {

  int col = 0;
  float bestScore = -1000000;

  INFO("JOUEUR: IA - Je reflechis ...");

  for (int column = 0; column < NB_COLUMN; column++) {
    if(checkMove(grid, column+1) == FALSE) {
      continue;
    }

    play(IA, grid, column+1);
    float score = negamax(list, grid, PLAYER, -1000000, 1000000, 6, 2);
    cancelMove(grid, column+1);

    //INFO("Score : %f pour la colonne %d", score, column+1);

    if (bestScore < score) {
      bestScore = score;
      col = column+1;
    }
  }

  INFO("JOUEUR: IA - quelle column voulez vous jouer? %d", col);
  //scanf("%d", &col);

  return col;
}
