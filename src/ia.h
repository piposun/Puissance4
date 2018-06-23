#ifndef HEADER_IA
#define HEADER_IA

/*! \file ia.h
    \brief Le moteur d'IA.
    \version 0.1

    C'est le moteur de l'IA.
*/

#include "puissance4.h"
#include "rule.h"

/*! \fn float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW])
    \brief Cette fonction evalue la grille en fonction des regles

    \param list la liste des regles de base
    \param grid le plateau.
    \return Renvoie le score d'evaluation du plateau.
*/
float evalGrid(Rule *list, char grid[NB_COLUMN][NB_ROW]);

/*! \fn void evalSerie(Rule *list, int idPlayer, char grid[NB_COLUMN][NB_ROW], int row, int column, int moveR, int moveC,   int *lastColor, int *serie, float *result)
    \brief Cette fonction evalue une case en fonction des regles

    \param list La liste des regles de base
    \param idPlayer L'id du joueur
    \param grid Le plateau.
    \param row La ligne a analyser
    \param column La colonne a analyser
    \param moveR Le deplaceement horizontal
    \param moveC Le deplacement vertical
    \param lastColor Entree/Sortie : La derniere couleur detectee
    \param serie Entree/Sortie : Le nombre de pion alignes
    \param result Entree/Sortie : Le score de l'evaluation
*/
void evalSerie(Rule *list, int idPlayer, char grid[NB_COLUMN][NB_ROW], int row, int column, int moveR, int moveC,   int *lastColor, int *serie, float *result);

/*! \fn float evalGridWhithPlayer(Rule *list, char grid[NB_COLUMN][NB_ROW], int idPlayer)
    \brief Cette fonction evalue le score du joueur en fonction des regles

    \param list La liste des regles de base
    \param grid Le plateau.
    \param idPlayer L'id du joueur
    \return Renvoie le score d'evaluation du joueur.
*/
float evalGridWhithPlayer(Rule *list, char grid[NB_COLUMN][NB_ROW], int idPlayer);

/*! \fn int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA)
    \brief Cette fonction calcule le coup de l'IA

    \param list La liste des regles de base
    \param grid Le plateau.
    \param nbMove Le nombre de coups total
    \param levelIA Le niveau de l'IA
    \return Renvoie le coup de l'IA.
*/
int playerIA(Rule *list, char grid[NB_COLUMN][NB_ROW], int nbMove, int levelIA);

/*! \fn float negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height, int increment, int nbMove)
    \brief Cette fonction remonte le meilleur coup pour l'IA

    \param list La liste des regles de base
    \param grid Le plateau.
    \param player l'id du joueur
    \param alpha Valeur de seuil de l'algo
    \param beta Valeur de seuil de l'algo
    \param profondeur Nombre de coup restant a simuler
    \param height Nombre de coup max a jouer dans une colonne
    \param increment Sens de simulation des coups
    \param nbMove Nombre de coups total
    \return Renvoie le score du meilleur coup
*/
float negamax(Rule *list, char grid[NB_COLUMN][NB_ROW], int player, float alpha, float beta, int profondeur, int height, int increment, int nbMove);

#endif /* HEADER_IA */
