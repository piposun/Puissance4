# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "menu.h"
# include "enter.h"
# include "logger.h"

//______________________________________________________________________________
void menuMain (int *choiceMain){

    INFO("\n\n## Menu principal ##\n");
    INFO("0 : Quitter");
    INFO("1 : Changer le joueur B");
    INFO("2 : Lancer la partie");
    INFO("\nChoix : ");
    enterInt(choiceMain, 0, 2); //Ne pas oublier de limiter le chiffre maximum.
}

//______________________________________________________________________________
void selectPlayer (int choiceUnder, int *choicePlayer){

    switch (choiceUnder){

      case 0:
        break;

      case 1 :
        *choicePlayer = 0;
        break;

      case 2:
        *choicePlayer = 2;
        break;

      case 3:
        *choicePlayer = 4;
        break;

      case 4:
        *choicePlayer = 6;
        break;

      default :
        INFO("\nChoix inexistant\n");
        break;
    }
}

//______________________________________________________________________________
void menuChoicePlayer (int *choiceUnder, char position){

    INFO("\n\n## Choix du joueur %c ##\n", position);
    INFO(" 0 : Retour au menu principal");
    INFO(" 1 : Humain");
    INFO(" 2 : IA niveau faible");
    INFO(" 3 : IA niveau moyen");
    INFO(" 4 : IA niveau difficile");
    INFO("\nChoix : ");
    enterInt(choiceUnder, 0, 4); //Ne pas oublier de limiter le chiffre maximum.
}

//______________________________________________________________________________
void displayChoicePlayer( int choicePlayerA, int choicePlayerB){

  INFO("\n\n-------------- Configuration actuelle du jeu --------------");
  INFO("|  Joueur A : Humain                                      |");

  if (choicePlayerB == 0){
    INFO("|  Joueur B : Humain                                      |");
  } else if (choicePlayerB == 2) {
    INFO("|  Joueur B : IA avec un niveau faible                    | ");
  } else if (choicePlayerB == 4) {
    INFO("|  Joueur B : IA avec un niveau moyen                     | ");
  } else if (choicePlayerB == 6) {
    INFO("|  Joueur B : IA avec un niveau fort                      | ");
  }


  INFO("-----------------------------------------------------------");

}
