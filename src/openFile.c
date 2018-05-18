#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "logger.h"
#include "openFile.h"

int openFile(FILE **file, char *pathFile, char *mode) {
  int success = OPEN_FILE_SUCCESS;  // Valeur de retour

  // Ouverture du fichier
  *file = fopen(pathFile, mode);

  /* Si l'ouverture du fichier a echoue et qu'on n'est pas en mode w+
  la fonction se rappelle elle meme avec le mode w+ */
  if (*file == NULL && strcmp(mode, "w+") != 0) {
    WARN("Impossible de lire le fichier %s ouverure en w+ !", pathFile);
    success = openFile(file, pathFile, "w+");
  }
  /* Si l'ouverture du fichier a echoue et qu'on est en mode w+
  alors on s'arrete */
  else if (*file == NULL) {
    ERROR("Impossible de lire le fichier %s meme en w+ !", pathFile);
    success = OPEN_FILE_FAILURE;
  }

  return success;
}

ListFiles * getListFile(char *pathRep, char *extension) {
  ListFiles *list = NULL;
  DIR* rep = NULL;
  struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

  // Ouverture du répertoire
  rep = opendir(pathRep);
  if (rep == NULL) {
    return NULL;
  }

  // Allocation de la liste des fichiers
  list = (ListFiles*)malloc(sizeof(ListFiles));

  if (list == NULL) {
    closedir(rep);
    return NULL;
  }

  // Copie de l'extension
  strcpy(list->extension, extension);

  list->nbFiles = 0;
  list->nameFiles = NULL;

  // Parcours l'ensemnle des fichiers dans le répertoire
  while ((fichierLu = readdir(rep)) != NULL) {
    // Extraction de la chaine de caractère correspondant à l'extension
    // Si NULL, cela signifie que l'extension n'est pas presente
    if (strstr (fichierLu->d_name, list->extension) != NULL) {
      // Incrément du nombre de fichier
      list->nbFiles++;
      // Allocation / Reallocation de la liste des nom de fichier
      if (list->nameFiles == NULL) {
        list->nameFiles = malloc(sizeof(char*));
      }
      else {
        list->nameFiles = realloc(list->nameFiles, sizeof(char*) * list->nbFiles);
      }

      // Allocation de la chaine de caractère contenant le nom du fichier
      list->nameFiles[list->nbFiles-1] = NULL;
      list->nameFiles[list->nbFiles-1] = malloc(sizeof(char) * 100);
      // Copie la partie de gauche entre le caractère séparatoire "."
      strcpy(list->nameFiles[list->nbFiles-1], strtok(fichierLu->d_name, "."));
    }
  }

  // Fermeture du réperoire
  if (closedir(rep) == -1) {
    return NULL;
  }

  return list;
}

void closeListFile(ListFiles *list) {
  if (list->nbFiles > 0) {
    for (int i = 0; i < list->nbFiles; i++) {
      free(list->nameFiles[i]); // On libère chaque ligne
    }

    free(list->nameFiles); // On libère la première dimension
  }

  free(list); // On libère la structure
}
