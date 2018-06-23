#ifndef HEADER_ENTER
#define HEADER_ENTER

/*! \file enter.h
    \brief Saisie securisée.
    \author Philippe Piboule
    \version 1.0
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//____________________________________________________________________________________________________________________________________
//Declaration a recopier
#define NBDIGITFLOATMAX  19
#define NBDIGITINTMAX     9

//____________________________________________________________________________________________________________________________________
// Fonctions saisie

/*! \fn int enterFloat(float *number, float min, float max)
    \brief Cette fonction permet la saisie securisée de réel.
    \param number Le réel saisie
    \param min La limite minimum de la saisie.
    \param max La limite maximum de la saisie.
    \return Renvoi 0 si la saisie est valide sinon 4.
*/
int enterFloat(float *number, float min, float max);

/*! \fn int enterInt(int *number, int min, int max)
    \brief Cette fonction permet la saisie securisée d'un entier.
    \param number L'entier saisie
    \param min La limite minimum de la saisie.
    \param max La limite maximum de la saisie.
    \return Renvoi 0 si la saisie est valide sinon 4.
*/
int enterInt(int *number, int min, int max);

/*! \fn int enterChar(char *string, int nbCharMax)
    \brief Cette fonction permet la saisie securisée d'une chaine de caractère.
    \param string La chaine de caractère saisie
    \param nbCharMax Nombre de caractère maximum dans la chaine de caractère.
    \return Renvoi 0 si la saisie est valide sinon 4.
*/
int enterChar(char *string, int nbCharMax);

/*! \fn int clearBuffer(int *nbCharToo)
   \brief Cette fonction vide ce qui reste dans le buffer stdin après l'acquisition
   \param nbCharToo Compteur du nombre de caractère saisi en trop.
   \return Renvoi 0 pour indiquer le bon déroulement.
*/
int clearBuffer(int *nbCharToo);

#endif /* HEADER_ENTER */
