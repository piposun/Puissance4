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

  // Initialisation des faits initiaux
  sprintf(string, "Player==%d", idPlayer+1);
  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  // On verifie si la case en dessous de celle qu'on analyse est pleine
  if ((row > 0 && grid[column][row-1] != EMPTY) || row == 0) {
    // On indique la couleur
    sprintf(string, "ColorCase==%d", convColorToValue(grid[column][row]));
  }
  else {
    // La case est inaccessible
    sprintf(string, "ColorCase==%d", -1);
  }

  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  // On verifie si on peut observer la case precedente dans le sens du mouvement
  if ((row - moveR) >= 0 && (column - moveC) >= 0) {
    if (grid[column-moveC][row-moveR] != EMPTY) {
      // Si la case n'est pas vide on sauvegarde la couleur
      *lastColor = convColorToValue(grid[column-moveC][row-moveR]);
    }
    // Cela permet de simuler des serie de pion avec des case vide
    sprintf(string, "ColorAdjacente==%d", *lastColor);
  }
  else {
    sprintf(string, "ColorAdjacente==%d", -10);
  }

  fact = decodeHypothesis(string);
  if (fact != NULL) {
    listFact = addFact(listFact, fact);
  }

  // Duplication de la liste des regles de base
  list2 = duplicateRule(list);

  // Chainage avant
  frontChaining(&list2, list2, listFact);

  // Recherche du fait Gain
  fact = searchFact(listFact, "Gain");

  // Si il y a un Gain on ajoute sa valeur et incremente la serie
  if (fact != NULL) {
    (*result) += atof(fact->value);
    (*serie)++;
  }
  // Si il n'y a pas de Gain et que la couleur precedente est differente de la couleur actuel alors changement de couleur
  else if ((row-moveR) >= 0 && (column-moveC) >= 0 && convColorToValue(grid[column-moveC][row-moveR]) != convColorToValue(grid[column][row]) && grid[column][row] != EMPTY) {
    //detection changement de couleur
    *result = 0;
    *serie = 0;
  }

  // Liberation
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

    // Sauvegarde de la valeur max
    if (max < result) {
      max = result;
    }

    // Reinit pour l'analyse d'une nouvelle colonne
    result = 0;
    serie = 0;
    lastColor = 0;

    for (int row = 0; row < NB_ROW; row++) {

      // Si la case en dessous en vide alors on stop l'analyse de la colonne
      if (row > 0 && grid[column][row-1] == EMPTY) {
        break;
      }

      // Evaluation de la colonne
      evalSerie(list, idPlayer, grid, row, column, 1, 0, &lastColor, &serie, &result);

      // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
      if (result >= 3.5) {
        return result;
      }
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les lignes G->D
  for (int row = 0; row < NB_ROW; row++) {

    // Sauvegarde de la valeur max
    if (max < result) {
      max = result;
    }

    // Reinit pour l'analyse d'une nouvelle ligne
    result = 0;
    serie = 0;
    nbToken = 0;
    lastColor = 0;

    for (int column = 0; column < NB_COLUMN; column++) {

      // S'il n'y a pas de resultat avant la moitier du plateau on stop l'analyse de la ligne ou si on a deja une serie de 4 pions
      if ((column > NB_COLUMN / 2 && result == 0) || serie >= 4) {
        break;
      }

      // On compte le nombre de jeton dans la ligne
      if (grid[column][row] != EMPTY) {
        nbToken++;
      }

      // Evaluation de la ligne
      evalSerie(list, idPlayer, grid, row, column, 0, 1, &lastColor, &serie, &result);

      // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
      if (result >= 3.5) {
        return result;
      }
    }

    // Si il n'y a aucun jeton sur la ligne on stop l'analyse des lignes
    if (nbToken == 0) {
      break;
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les lignes D->G
  for (int row = 0; row < NB_ROW; row++) {

    // Sauvegarde de la valeur max
    if (max < result) {
      max = result;
    }

    // Reinit pour l'analyse d'une nouvelle ligne
    result = 0;
    serie = 0;
    nbToken = 0;
    lastColor = 0;

    for (int column = NB_COLUMN-1; column >= 0; column--) {

      // S'il n'y a pas de resultat avant la moitier du plateau on stop l'analyse de la ligne ou si on a deja une serie de 4 pions
      if ((column < NB_COLUMN / 2 && result == 0) || serie >= 4) {
        break;
      }

      // On compte le nombre de jeton dans la ligne
      if (grid[column][row] != EMPTY) {
        nbToken++;
      }

      // Evaluation de la ligne
      evalSerie(list, idPlayer, grid, row, column, 0, -1, &lastColor, &serie, &result);

      // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
      if (result >= 3.5) {
        return result;
      }
    }

    // Si il n'y a aucun jeton sur la ligne on stop l'analyse des lignes
    if (nbToken == 0) {
      break;
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal BG->HD
  for (int column = -2; column < NB_COLUMN; column++) {
    int row = 0;

    // Reinit pour l'analyse d'une nouvelle diagonal
    serie = 0;
    result = 0;
    lastColor = 0;

    for (int index = 0; index < NB_ROW; index++) {
      // Si on a une serie de 4 ou qu'il n'y a pas assez de case pour avoir une serie complete, on stop l'analyse des diagonal
      if (serie >= 4 || (row == 0 && column > NB_COLUMN/2)) {
        break;
      }
      // Verification que les indexs sont dans les bornes
      if (row+index < NB_ROW && column+index >= 0 && column+index < NB_COLUMN) {
        // Evaluation de la diagonal
        evalSerie(list, idPlayer, grid, row+index, column+index, 1, 1, &lastColor, &serie, &result);
        // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal HD->BG
  for (int column = NB_COLUMN+1; column >= 0; column--) {
    int row = NB_ROW-1;

    // Reinit pour l'analyse d'une nouvelle diagonal
    serie = 0;
    result = 0;
    lastColor = 0;

    for (int index = 0; index < NB_ROW; index++) {
      // Si on a une serie de 4 ou qu'il n'y a pas assez de case pour avoir une serie complete, on stop l'analyse des diagonal
      if (serie >= 4 || (row == NB_ROW-1 && column < NB_COLUMN/2)) {
        break;
      }
      // Verification que les indexs sont dans les bornes
      if (row-index >= 0 && column-index >= 0 && column-index < NB_COLUMN) {
        // Evaluation de la diagonal
        evalSerie(list, idPlayer, grid, row-index, column-index, -1, -1, &lastColor, &serie, &result);
        // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal HG->BD
  for (int column = -2; column < NB_COLUMN; column++) {
    int row = NB_ROW-1;

    // Reinit pour l'analyse d'une nouvelle diagonal
    serie = 0;
    result = 0;
    lastColor = 0;

    for (int index = 0; index < NB_ROW; index++) {
      // Si on a une serie de 4 ou qu'il n'y a pas assez de case pour avoir une serie complete, on stop l'analyse des diagonal
      if (serie >= 4 || (row == NB_ROW-1 && column > NB_COLUMN/2)) {
        break;
      }
      // Verification que les indexs sont dans les bornes
      if (row-index >= 0 && column+index >= 0 && column+index < NB_COLUMN) {
        // Evaluation de la diagonal
        evalSerie(list, idPlayer, grid, row-index, column+index, -1, 1, &lastColor, &serie, &result);
        // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Calcule des scores pour les diagonal BD->HG
  for (int column = NB_COLUMN+1; column >= 0; column--) {
    int row = 0;

    // Reinit pour l'analyse d'une nouvelle diagonal
    serie = 0;
    result = 0;
    lastColor = 0;

    for (int index = 0; index < NB_ROW; index++) {
      // Si on a une serie de 4 ou qu'il n'y a pas assez de case pour avoir une serie complete, on stop l'analyse des diagonal
      if (serie >= 4 || (row == 0 && column < NB_COLUMN/2)) {
        break;
      }
      // Verification que les indexs sont dans les bornes
      if (row+index >= 0 && column-index >= 0 && column-index < NB_COLUMN) {
        // Evaluation de la diagonal
        evalSerie(list, idPlayer, grid, row+index, column-index, 1, -1, &lastColor, &serie, &result);
        // Si on trouve la valeur la plus eleve avant celle de gagnee on stop l'analyse complete
        if (result >= 3.5) {
          return result;
        }
      }
    }
  }

  // Sauvegarde de la valeur max
  if (max < result) {
    max = result;
  }

  // Retourne la valeur max
  return max;
}

float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW]) {

  float result[2];
  float maxValue = 0;

  result[0] = 0;
  result[1] = 0;

  for (int idPlayer = 0; idPlayer < 2; idPlayer++) {
    result[idPlayer] = evalGridWhithPlayer(list, grid, idPlayer);
    // Si le joueur obtient une grose note, rien ne sert d'analyse le jeu de l'IA
    if (result[idPlayer]>= 3.5) {
      break;
    }
  }

  // On retourne la plus grosse note, la note du joueur est prioritaire
  if (result[1] < result[0]) {
    // Inversion de la note du joueur
    maxValue = -result[0];
  } else {
    maxValue = result[1];
  }

return maxValue;
}

float negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height, int increment) {
    int start = 0;
// On verifie si le joueur ou l'IA a gagne
  for(int idPlayer = PLAYER; idPlayer <= IA; idPlayer++) {
    int game = endGame(list, maxToken(player == IA ? YELLOW : RED, grid), idPlayer, IA);
    if (game != 0) {
      // On augmente le score et on rajoute la notion de prioritee avec la profondeur
      return game * 1000 * (profondeur+1);
    }
  }

  // Si la profondeur est atteinte, on evalue la grille
  if (profondeur == 0) {
    return evalGrid(list, grid);
  }

    if((profondeur%2 == 0)&&(increment>0)){
        increment = -increment;
        start = NB_COLUMN-1;
    } else {
        increment = -increment;
        start = 0;
    }


  for (int column = start; column < NB_COLUMN && column >= 0; column+=increment) {
    float score = 0;
    if(checkMove(grid, column+1) == FALSE) {
      continue;
    }

    // Hauteur max de simulation de la colonne
    if (height == 0) {
      height = 3;
      continue;
    }

    // On joue le coup
    play(player, grid, column+1);

    play(player, grid, column+1);
    score = -negamax(list, grid, (player == IA) ? PLAYER : IA, -beta, -alpha, profondeur-1, height-1, increment);
    displayGrid(grid);
    if (score > alpha) {
      alpha = score;
    }

    // On annule le coups
    cancelMove(grid, column+1);

    // Principe d'elagage de l'algo negamax
    if (alpha >= beta) {
      return alpha;
    }

  }

  return alpha;
}

int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW]) {

  int col = 0;
  float bestScore = -1000000;
    char string[50] = {0};

  INFO("JOUEUR: IA - Je reflechis ...");

//--------------------------------------------------------------
    Rule *list2 = NULL;
    Hypothesis *listFact = NULL, *fact = NULL;

    sprintf(string, "NbToken==%d", nbMove);
    fact = decodeHypothesis(string);
    if (fact != NULL) {
        listFact = addFact(listFact, fact);
    }
    list2 = duplicateRule(list);

    frontChaining(&list2, list2, listFact);
    fact = searchFact(listFact, "ToPlay");

    if (fact != NULL) {
        col = atoi(fact->value);
    }

    freeAllRule(list2);
    freeAllHypothesis(listFact);
    //--------------------------------------------------------

  // Simulation des coups
  for (int column = 0; column < NB_COLUMN; column++) {

    // On verifie si le coup est jouable
    if(checkMove(grid, column+1) == FALSE) {
      continue;
    }

    // On joue le coup
    play(IA, grid, column+1);
    // On recupere le score de l'algo de decision
    float score = negamax(list, grid, PLAYER, -1000000, 1000000, 6, 2);
    // On annule le coup
    cancelMove(grid, column+1);

    // On sauvegarde le meilleur score
    if (bestScore < score) {
      bestScore = score;
      // On ajoute 1 a la colonne car les fonctions se base sur un numero de colonne de 1 a 7
      col = column+1;
      break;
    }
  } else if(col == 0) {
        for (int column = 0; column < NB_COLUMN; column++) {
            if (checkMove(grid, column + 1) == FALSE) {
                continue;
            }

            play(IA, grid, column + 1);
            float score = negamax(list, grid, PLAYER, -1000000, 1000000, 6, 2, 1);
            cancelMove(grid, column + 1);

            //INFO("Score : %f pour la colonne %d", score, column+1);

            if (bestScore < score) {
                bestScore = score;
                col = column + 1;
            }
        }
    }

  INFO("JOUEUR: IA - quelle column voulez vous jouer? %d", col);

  // On retourne la colonne a jouer
  return col;
}
