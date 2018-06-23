#ifndef HEADER_PUISSANCE4
#define HEADER_PUISSANCE4

/*! \file puissance4.h
<<<<<<< HEAD
    \brief Le moteur du jeu du Puissance 4.
    \version 0.1

    C'est le moteur du jeu de Puissance 4.
*/

#include "rule.h"

/*! \def NB_COLUMN
    \brief Definition du nombre max de colonne
*/
#define NB_COLUMN 7

/*! \def NB_ROW
    \brief Definition du nombre max de ligne
*/
#define NB_ROW    6


/*! \def EMPTY
    \brief Definition de la couleur vide
*/
#define EMPTY  ' '

/*! \def RED
    \brief Definition de la couleur rouge
*/
#define RED    'x'
#define YELLOW 'o'

#define PLAYER  1
#define IA 2
#define PLAYER2 3

#define TRUE  1
#define FALSE 0

/*! \fn endGame(Rule *list, int score, int idPlayer, int idHuman)
    \brief Cette fonction determine via les regles si la partie est terminée

    \param Rule *list La liste de règles.
    \param int score Le meilleur score du joueur.
    \param int idPlayer L'id joueur qui joue.
    \param int idHuman L'id joueur humain.
    \return Renvoie l'etat de la partie : 1=>GAGNEE -1=>PERDUE 0=>EN COURS.
*/
int endGame(Rule *list, int score, int idPlayer, int idHuman);

/*! \fn int playPlayer(char grid[NB_COLUMN][NB_ROW], int idPlayer)
    \brief CCette fonction demande aux joueur humain de jouer

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int idPlayer Le joueur qui doit joue.
    \return Renvoie col La colonne, le coup, choisi par le joueur humain.
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
<<<<<<< HEAD
    \brief Cette fonction initialise la grille du jeu.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
*/
void initGrid(char grid[NB_COLUMN][NB_ROW]);

/*! \fn void displayGrid(char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction affiche le plateau de jeu.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
*/
void displayGrid(char grid[NB_COLUMN][NB_ROW]);

/*! \fn int maxToken(char token, char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction compte le nombre max de pion alignés par joueur.

    \param char token La couleur du pion à tester.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \return Renvoie max Le nombre max de jetons alignés par un joueur.
*/
int maxToken(char token, char grid[NB_COLUMN][NB_ROW]);

/*! \fn void play(int player, char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction joue le coup demandee.

    \param int player Le type de joueur qui doit jouer (IA ou Humain).
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int column La colonne à remplir avec un jeton.
*/
void play(int player, char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn cancelMove(char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction annule un coup joué lors des simulations de jeu de l'IA.

    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int column La colonne où annuler le dernier coup joué.
*/
void cancelMove(char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA)
    \brief Cette fonction le coup à jouer au joueur.

    \param int player Le type de joueur qui doit jouer (IA ou Humain).
    \param Rule *list La liste des règles configurant la vision du jeu par l'IA.
    \param char grid[NB_COLUMN][NB_ROW] Le plateau de jeu où les jetons sont placés.
    \param int nbMove Le nombre de coups joués au cours de la partie par les deux joueurs.
    \param int levelIA La profondeur de simulation de l'IA (nombre de coups anticipés à l'avance).
    \return Renvoie col La colonne dans laquelle jouer.
*/
int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA);

/*! \fn void launchGame(int playerTypeB);
    \brief Cette fonction lance le jeu

    \param playerTypeB le type de partie
*/
void launchGame(int playerTypeB);

#endif /* HEADER_PUISSANCE4 */
