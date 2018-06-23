#ifndef HEADER_PUISSANCE4
#define HEADER_PUISSANCE4

/*! \file puissance4.h
    \brief Le moteur du jeu.
    \version 0.1

    C'est le moteur du jeu.
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

/*! \fn int endGame(Rule *list, int score, int idPlayer, int idHuman)
    \brief Cette fonction determine via les regles si la partie est terminee

    \param list la liste des regles de base
    \param score le meilleur score du joueur
    \param idPlayer id du joueuer a analysee
    \param idHuman id du joueur humain
    \return Renvoie l'etat de la partie : 1=>GAGNEE -1=>PERDUE 0=>EN COURS.
*/
int endGame(Rule *list, int score, int idPlayer, int idHuman);

/*! \fn int playPlayer(char grid[NB_COLUMN][NB_ROW], int idPlayer)
    \brief Cette fonction demande aux joueur humain de jouee

    \param grid le plateau de jeu
    \param idPlayer id du joueuer qui doit jouer
    \return Renvoie le coup du joueur.
*/
int playPlayer(char grid[NB_COLUMN][NB_ROW], int idPlayer);

/*! \fn int checkMove(char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction verifie si le coup est possible

    \param grid le plateau de jeu
    \param column la colonne a tester
    \return Renvoie le si coup est possible.
*/
int checkMove(char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn void initGrid(char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction initialise la grille du jeu

    \param grid le plateau de jeu.
*/
void initGrid(char grid[NB_COLUMN][NB_ROW]);

/*! \fn void displayGrid(char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction affiche le plateau de jeu

    \param grid le plateau de jeu.
*/
void displayGrid(char grid[NB_COLUMN][NB_ROW]);

/*! \fn int maxToken(char token, char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction compte le nombre max de pion aligne par joueur

    \param token la couleur des pion a tester
    \param grid le plateau de jeu
    \return Renvoie le nombre max de pion aligne par joueur.
*/
int maxToken(char token, char grid[NB_COLUMN][NB_ROW]);

/*! \fn void play(int player, char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction joue le coup demandee

    \param player id du joueur
    \param grid le plateau de jeu
    \param column la colonne a jouer
*/
void play(int player, char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn void cancelMove(char grid[NB_COLUMN][NB_ROW], int column)
    \brief Cette fonction annule le coup d'un joueur

    \param grid le plateau de jeu
    \param column la colonne a annuler
*/
void cancelMove(char grid[NB_COLUMN][NB_ROW], int column);

/*! \fn int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA)
    \brief Cette fonction demande le coup demandee en fonction du joueur

    \param player id du joueur
    \param list la liste des regles de base
    \param grid le plateau de jeu
    \param nbMove le nombre de coups joues dans la partie
    \param levelIA le niveau de l'IA
    \return Renvoie le coup a jouer.
*/
int choose(int player, Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA);

/*! \fn void launchGame(int playerTypeB);
    \brief Cette fonction lance le jeu

    \param playerTypeB le type de partie
*/
void launchGame(int playerTypeB);

#endif /* HEADER_PUISSANCE4 */
