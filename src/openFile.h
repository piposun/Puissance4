#ifndef HEADER_OPEN_FILE
#define HEADER_OPEN_FILE

/*! \file openFile.h
    \brief Gestionnare de fichier
    \version 0.1

    Contient les fonctions de gestion de fichiers.
*/

#include <stdio.h>

/*! \struct ListFiles
    \brief Gere la liste des noms de fichier.
*/
typedef struct {
  char **nameFiles; /**< List des nom de fichier */
  char extension[50]; /**< Contient l'extension des fichiers */
  int nbFiles;  /**< Contient le nombre de fichiers */
} ListFiles;

/*! \enum OPEN_FILE
    \brief Gere la valeur de retour.
*/
typedef enum {
  OPEN_FILE_FAILURE = 0, /**< Etat echec */
  OPEN_FILE_SUCCESS /**< Etat succes */
} OPEN_FILE;

/*! \fn int openFile(FILE **file, char *pathName, char *mode)
    \brief Cette fonction ouvre un fichier.

    \param file File descriptor.
    \param pathName Chemin d'acces du fichier a ouvrir.
    \param mode Mode d'ouverture du fichier.
    \return Indique si l'ouverture du fichier a reussi.
*/
int openFile(FILE **file, char *pathName, char *mode);

/*! \fn ListFiles *getListFile(char *pathRep, char *extension)
    \brief Cette fonction fournie la liste des nom des fichiers dans un répertoire.

    \param pathRep Chemin d'accès du répertoire
    \param extension Extension des fichiers à récupérer
    \return Renvoie la référence de la liste des fichiers
*/
ListFiles *getListFile(char *pathRep, char *extension);

/*! \fn void closeListFile(ListFiles *list)
    \brief Cette fonction libère les listes des fichiers.

    \param list Référence à la liste des fichiers
*/
void closeListFile(ListFiles *list);

#endif /* HEADER_OPEN_FILE */
