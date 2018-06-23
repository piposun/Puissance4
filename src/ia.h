#ifndef HEADER_IA
#define HEADER_IA

/*! \file ia.h
    \brief Intelligence artificielle du jeu de Puissance 4.
    \version 0.1

    Ce sont les fonctions propres au fonctionnement de l'IA.
*/

#include "puissance4.h"
#include "rule.h"

/*! \fn int convColorToValue(char color)
    \brief Cette fonction associe les couleurs des jetons au joueur qui les a joués (IA ou Humain).

    \param color la valeur du jeton.
    \return Renvoie PLAYER si le jeton appartient au joueur humain ou IA sinon.
*/
int convColorToValue(char color);

/*! \fn void evalSerie(Rule *list, int idPlayer, char grid[NB_COLUMN][NB_ROW], int row, int column, int moveR, int moveC,   int *lastColor, int *serie, float *result)
    \brief Cette fonction evalue une case en fonction des règles.

    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param int idPlayer Le joueur dont on evalue la serie (Humain ou IA).
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int row La ligne du plateau de jeu.
    \param int column La colonne du plateau de jeu.
    \param int moveR Le deplacement en ligne lors du parcours des séries.
    \param int moveC Le deplacement en colonne lors du parcours des séries.
    \param int *lastColor La couleur du dernier jeton parcouru.
    \param int *serie Pointeur vers le nombre de séries comptées.
    \param float *result Pointeur vers la somme pondérant la série parcouru.
*/
void evalSerie(Rule *list, int idPlayer, char grid[NB_COLUMN][NB_ROW], int row, int column, int moveR, int moveC, int *lastColor, int *serie, float *result);

/*! \fn float evalGridWhithPlayer(Rule *list, char grid[NB_COLUMN][NB_ROW], int idPlayer)
    \brief Cette fonction evalue le score du joueur en fonction des regles

    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int idPlayer Le joueur dont on evalue la serie (Humain ou IA).
    \return Renvoie result, le score d'evaluation du joueur.
*/
float evalGridWhithPlayer(Rule *list, char grid[NB_COLUMN][NB_ROW], int idPlayer);

/*! \fn float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW])
    \brief ette fonction evalue la grille en fonction des regles.

    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \return Renvoie maxValue, le score d'evaluation du plateau.
*/
float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW]);

/*! \fn int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA)
    \brief Cette fonction choisit le coup à jouer pour l'IA.

    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int nbMove Le nombre de coups joués au cours de la partie par les deux joueurs.
    \param int levelIA La profondeur de simulation de l'IA (nombre de coups anticipés à l'avance).
    \return Renvoie maxValue, le meilleur coup à jouer pour l'IA.
*/
int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA);

/*! \fn negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height, int increment, int nbMove)
    \brief Cette fonction simule et remonte le meilleur coup à jouer pour l'IA

    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param alpha Valeur de seuil de l'algo.
    \param beta Valeur de seuil de l'algo.
    \param float beta score Borne maxi du score.
    \param int profondeur profondeur de simulation (nombres de coups simulés à l'avance).
    \param int height hauteur des séries sur le plateau.
    \param int increment La variable d'incrementation lors de la simulation des coups du joueur et de l'IA.
    \param int nbMove Le nombre de coups joués au cours de la partie par les deux joueurs.
    \return Renvoie alpha, le score du meilleur coup simulé.
*/
float negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height, int increment, int nbMove);

#endif /* HEADER_IA */
