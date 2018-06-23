#ifndef HEADER_MENU
#define HEADER_MENU

/*! \file enter.h
    \brief Affichage des menus et saisie des choix.
    \author Philippe Piboule
    \version 1.0
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//Fonctions fichier

/*! \fn void menuMain(int *choiceMain)
    \brief Cette fonction affiche le menu principal.
    \param choiceMain Le choix realisé dans le menu principal
*/
void menuMain(int *choiceMain);

/*! \fn void menuChoicePlayer (int *choiceUnder, char position)
    \brief Cette fonction permet la saisie securisée de réel.
    \param choiceUnder Le choix réalisé dans le sous menu
    \param position Le nom du joueur pour adapter le menu
*/
void menuChoicePlayer (int *choiceUnder, char position);

/*! \fn selectPlayer (int choiceUnder, int *choicePlayer)
    \brief Cette fonction permet le choix du joueur (humain / IA) et du niveau de profondeur de l'IA.
    \param choiceUnder Le choix réalisé dans le sous menu.
    \param choicePlayer Le choix du joueur.
*/
void selectPlayer (int choiceUnder, int *choicePlayer);

/*! \fn displayChoicePlayer( int choicePlayerA, int choicePlayerB)
    \brief Cette fonction permet la saisie securisée de réel.
    \param choicePlayerA Le choix du joueur pour adapter le menu.
    \param choicePlayerB Le choix du joueur pour adapter le menu.
*/
void displayChoicePlayer( int choicePlayerA, int choicePlayerB);

#endif /* HEADER_MENU */
