#ifndef HEADER_PUISSANCE4
#define HEADER_PUISSANCE4

/*! \file puissance4.h
    \brief Jeu du Puissance 4.
    \version 0.1

    Ce sont les fonctions propres au déroulement du jeu de Puissance 4.
*/

#include "rule.h"

#define NB_COLUMN 7
#define NB_ROW    6

#define EMPTY  ' '
#define RED    'x'
#define YELLOW 'o'

#define PLAYER  1
#define IA 2
#define PLAYER2 3

#define TRUE  1
#define FALSE 0

/*! \fn endGame(Rule *list, int score, int idPlayer, int idHuman)
    \brief Cette fonction termine la partie si les règles detectent une victoire.

    \param Rule *list La liste de règles.
    \param int score Le nombre de jetons alignés.
    \param int idPlayer Le joueur qui joue.
    \param int idHuman Le joueur humain.
    \return Renvoie result Le resultat de la règle validée.
*/
int endGame(Rule *list, int score, int idPlayer, int idHuman);

/*! \fn int playPlayer(char grid[NB_COLUMN][NB_ROW], int idPlayer)
    \brief Cette fonction joue le coup du joueur humain.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int idPlayer Le joueur qui joue.
    \return Renvoie col La colonne choisie par le joueur humain.
*/
int playPlayer(char grid[NB_COLUMN][NB_ROW], int idPlayer);

/*! \fn int checkMove(char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction verifie la validité du coup choisi.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int idPlayer Le joueur qui joue.
    \return Renvoie 1 (TRUE) si le coup est jouable ou 0 (FALSE) sinon.
*/
int checkMove(char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn void initGrid(char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction verifie la validité du coup choisi.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
*/
void initGrid(char grid[NB_COLUMN][NB_ROW]);

/*! \fn void displayGrid(char grid[NB_COLUMN][NB_ROW]);
    \brief Cette fonction affiche le plateau de jeu.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
*/
void displayGrid(char grid[NB_COLUMN][NB_ROW]);

/*! \fn int maxToken(char token, char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction détecte le nombre max de jetons alignés dans une série.

    \param char token Le pion du joueur
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \return Renvoie max Le nombre max de jetons alignés.
*/
int maxToken(char token, char grid[NB_COLUMN][NB_ROW]);

/*! \fn void play(int player, char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction effectue la chute d'un jeton si les cas inférieures sont vides.

    \param int player Le type de joueur qui doit jouer (IA ou Humain).
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int column La colonne à remplir avec un jeton.
*/
void play(int player, char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn cancelMove(char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction annule un coup joué lors des simulations de jeu de l'IA.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int column La colonne à remplir avec un jeton.
*/
void cancelMove(char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA)
    \brief Cette fonction annule un coup joué lors des simulations de jeu de l'IA.

    \param int player Le type de joueur qui doit jouer (IA ou Humain).
    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int nbMove Le nombre de coups joués au cours de la partie par les deux joueurs.
    \param int levelIA La profondeur de simulation de l'IA (nombre de coups anticipés à l'avance).
    \return Renvoie col La colonne dans laquelle jouer.
*/
int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA);

/*! \fn int launchGame(int playerTypeB)
    \brief Cette fonction annule un coup joué lors des simulations de jeu de l'IA.

    \param int playerTypeB Le type du joueur à affronter (IA ou Humain)(1 à 6 ou 0).
    \return Renvoie 0 si la partie est terminée.
*/
int launchGame(int playerTypeB);

#endif /* HEADER_PUISSANCE4 */
