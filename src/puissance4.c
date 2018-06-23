#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "puissance4.h"
#include "ia.h"
#include "logger.h"
#include "expertSystem.h"
#include "rule.h"
#include "hypothesis.h"
#include "enter.h"
#include "menu.h"

//________________________________________________________________________________________________________
int main (int argc, char *argv[]) {

  /* Lexique des numéros de Joueur
  1 à n : IA avec niveau de profondeur n (1 à 6)
  0 : Humain sans sauvegarde
  */

  int choiceMain = 0;
  int choiceUnder = 0;
  int choicePlayerA = 0; //Valeur par defaut écrit dans le menu
  int choicePlayerB = 6; //Valeur par defaut écrit dans le menu

  if(argc == 3){
    choicePlayerA = atoi(argv[1]);
    choicePlayerB = atoi(argv[2]);
    choiceMain = 3; //Valeur par defaut pour lancer la partie
  }

  do{
    if (argc != 4){
      displayChoicePlayer( choicePlayerA, choicePlayerB);
      menuMain(&choiceMain);
    }
    switch (choiceMain){

      case 0:
      printf("\nBye bye\n\n");
      break;

      case 1:
      menuChoicePlayer(&choiceUnder, 'B');
      selectPlayer(choiceUnder, &choicePlayerB);
      break;

      case 2:
      launchGame(choicePlayerB);
      break;

      default :
      INFO("\nChoix inexistant\n\n");
      break;
    }

  }while (choiceMain != 0);

  return 0;
}
//___________________________________________________________________________________________________

int endGame(Rule *list, int score, int idPlayer, int idHuman) {
  Rule *list2 = NULL;
  Hypothesis *listFact = NULL, *fact = NULL;

  char string[50] = {0};
  int result = 0;

  // Initialisation des fait initiaux
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

  // On duplique la liste pour pouvoir effectuer des modification sans affecter la liste de base
  list2 = duplicateRule(list);

  // Chainage avant
  frontChaining(&list2, list2, listFact);

  // Trace de debug
  DEBUG("****** LIST FACT FINAL *******");
  if (listFact != NULL) {
    char string[500] = {0};
    displayAllHypothesis(listFact, string);
    DEBUG("%s", string);
  }
  DEBUG("*******************");

  // Recherche du fait Partie
  fact = searchFact(listFact, "Partie");

  // Si le fait existe, cela signifie que la partie est terminee
  if (fact != NULL) {
    if (atoi(fact->value) == 1) {
      result = 1; // GAGNEE
    }
    else {
      result = -1; // PERDUE
    }
  }

  // Lineration
  freeAllRule(list2);
  freeAllHypothesis(listFact);

  return result;
}

int playPlayer(char grid[NB_COLUMN][NB_ROW], int idPlayer) {
  int col = 0;

  INFO("\nTapez 0 pour quitter.\nJOUEUR: %s - quelle column voulez vous jouer?", (idPlayer == PLAYER) ? "RED":"YELLOW");
  enterInt(&col,0,7); // Controle de saisie

  return col;
}

int checkMove(char grid[NB_COLUMN][NB_ROW], int column) {
  int y;
  int freeCase = -1;

  // On decrement car les valeurs saisie par les humain sont comprisent en 1 et 7 or notre tableau va de 0 a 6
  column -= 1;

  // Verification des bornes de l'index
  if (column < 0 || column >= NB_COLUMN) {
    return FALSE;
  }

  // On recheche la premiere case vide en partant du haut du plateau
  for (y = NB_ROW-1; y >= 0; y--) {
    if (grid[column][y] == EMPTY) {
      freeCase = y;
      break;
    }
  }

  // Pas de case vide
  if (freeCase == -1) {
    return FALSE;
  }

  return TRUE;
}

void initGrid(char grid[NB_COLUMN][NB_ROW]) {
  // Initialisation du plateau
  for(int width = 0; width < NB_COLUMN; width++) {
    for(int height = 0; height < NB_ROW; height++) {
      grid[width][height] = EMPTY;
    }
  }
}

void displayGrid(char grid[NB_COLUMN][NB_ROW]) {
  // On vide le terminal
  system("clear");

  // Modifie la couleur par defaut
  INFO("");

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
      char* outColor = COL_INFO;
      // changement de la couleur
      if (grid[width][height] == RED) {
        outColor = COL_ERROR;
      }
      else {
        outColor = COL_WARN;
      }
      printf("%s", outColor);
      printf(" %c ", grid[width][height]);
      // la couleur par defaut
      outColor = COL_INFO;
      printf("%s", outColor);
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

  // Initialisation de la grille a 1
  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      game[column][row] = 1;
    }
  }

  // pour le horizontal
  for (row = 0; row < NB_ROW; row++) {
    for (column = 1; column < NB_COLUMN; column++) {
      if ((grid[column][row] == grid[column-1][row]) && (grid[column][row] == token)) {
        // Si la couleur correspond alors on ajout a la case courante la valeur de la case precedante
        game[column][row] = game[column-1][row] + 1;
      }
    }
  }

  // Reinitialisation de la grille a 1 et on saugarde le meilleur score
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
        // Si la couleur correspond alors on ajout a la case courante la valeur de la case precedante
        game[column][row] = game[column][row-1] + 1;
      }
    }
  }

  // Reinitialisation de la grille a 1 et on saugarde le meilleur score
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
        // Si la couleur correspond alors on ajout a la case courante la valeur de la case precedante
        game[column][row] = game[column+1][row-1] + 1;
      }
    }
  }

  // Reinitialisation de la grille a 1 et on saugarde le meilleur score
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
        // Si la couleur correspond alors on ajout a la case courante la valeur de la case precedante
        game[column][row] = game[column-1][row-1] + 1;
      }
    }
  }

  // Reinitialisation de la grille a 1 et on saugarde le meilleur score
  for (row = 0; row < NB_ROW; row++) {
    for (column = 0; column < NB_COLUMN; column++) {
      if (game[column][row] > max) {
        max = game[column][row];
      }
      game[column][row] = 1;
    }
  }

  // rectoure le meilleur score
  return max;
}

void cancelMove(char grid[NB_COLUMN][NB_ROW], int column) {
  // On decrement car les valeurs saisie par les humain sont comprisent en 1 et 7 or notre tableau va de 0 a 6
  column -= 1;

  // Verification des bornes de l'index
  if (column < 0 || column >= NB_COLUMN) {
    return;
  }

  // On recheche la premiere case pleine en partant du haut et on la vide
  for (int y = NB_ROW-1; y >= 0; y--) {
    if (grid[column][y] != EMPTY) {
      grid[column][y] = EMPTY;
      break;
    }
  }
}

void play(int player, char grid[NB_COLUMN][NB_ROW], int column) {
  int freeRow = -1;

  // On decrement car les valeurs saisie par les humain sont comprisent en 1 et 7 or notre tableau va de 0 a 6
  column -= 1;

  // Verification des bornes de l'index
  if (column < 0 || column >= NB_COLUMN) {
    return;
  }

  // On recheche la premiere case vide en partant du haut
  for (int y = NB_ROW-1; y >= 0; y--) {
    if (grid[column][y] == EMPTY) {
      freeRow = y;
    }
  }

  // Si pa de case vide alors on ne fait rien
  if (freeRow == -1) {
    return;
  }

  // On place le pion de la bonne couleur
  grid[column][freeRow] = (player == IA || player == PLAYER2) ? YELLOW : RED;
}

int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA) {
  int col;

  // Recupere la colonne a jouer en fonction du type de joueur
  switch (player) {
    case PLAYER:
    {
      col = playPlayer(grid, player);
    } break;
    case PLAYER2:
    {
      col = playPlayer(grid, player);
    } break;
    case IA:
    {
      col = playerIA(list, grid, nbMove, levelIA);
    } break;
    default:
    break;
  }

  return col;
}

void launchGame(int playerTypeB) {
  int move = -1, nbMove = 0, end = 0, game = 0, player = PLAYER, levelIA = playerTypeB;
  char grid[NB_COLUMN][NB_ROW];
  Rule *list = NULL;

  // Init la valeur aleatoire
  srand(time(NULL));

  // Init la liste de regle de base
  list = initRules("TestRule.txt");

  // Initialisation du plateau
  initGrid(grid);

  // affichage du plateau
  displayGrid(grid);

  // On joue tant que la partie est en cours
  while (end == 0) {
    // Demande au joueur de jouer
    do {
      move = choose(player, list, grid,nbMove, levelIA);
      if (move == 0){
        return; //si partie annulée
      }
      // si le coup n'est pas possible alors on redemande un coup
    }while(checkMove(grid, move) == FALSE);

    // On joue le coup
    play(player, grid, move);

    // On affiche le plateau
    displayGrid(grid);

    // On incremente le nombre de coups total
    nbMove++;

    // On verifie si la partie est terminee
    game = endGame(list, maxToken((player == IA || player == PLAYER2) ? YELLOW : RED, grid), player, PLAYER);

    // Si le nombre de coup total est egale au nombre de possibilite alors il y a egalite
    if (nbMove == NB_COLUMN*NB_ROW) {
      INFO("Match NUL (%d coups)", nbMove);
      end = 1;
    } else if (game < 0) {
      INFO("La partie est PERDUE en %d coups", nbMove);
      end = 1;
    } else if (game > 0) {
      INFO("La partie est GAGNEE en %d coups", nbMove);
      end = 1;
    }

    // Verification si le deuxieme joueur est une IA
    if (playerTypeB != 0){
      if (player == IA) {
        player = PLAYER;
      } else {
        player = IA;
      }
    } else {
      if (player == PLAYER2) {
        player = PLAYER;
      } else {
        player = PLAYER2;
      }
    }
  }
}
