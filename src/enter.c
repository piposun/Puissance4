# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "enter.h"
# include "logger.h"

int enterFloat(float *number, float min, float max) {
/*  On passe à la fonction la variable qui va contenir le chiffre et la taille min et max du chiffre*/
    char numberText[NBDIGITFLOATMAX] = {"vide"}; //
    int testChar = 0;

    do {
      if (enterChar(numberText, NBDIGITFLOATMAX) == 0){
        /*=0 indique une demande de nombre a la fonction enterChar puis on test le code retour*/
          if( (testChar = sscanf(numberText, " %f", number) == 0) || ((*number) < min || (*number) > max) ){
            /*converti la chaine de caractere en float, vérifie la reussite de la conversion
            puis verifie que la valeur est dans l'intervale voulu */
            INFO ("\nVeuillez saisir une valeur comprise entre %.2f et %.2f : ", min, max);
          }
      }
      else{
          return 4; /*  Si erreur du programme de saisie on retourne 4  */
      }
    } while(testChar != 0 || (*number) < min || (*number) > max);

    return 0;  /* Saisie sans erreur on retourne 0 */
}

//____________________________________________________________________________________________________________________________________
int enterInt(int *number, int min, int max) {
/*  On passe à la fonction la variable qui va contenir le chiffre et la taille min et max du chiffre*/

    char numberText[NBDIGITINTMAX] = {0}; // 9 équivalent à 999999999
    int testChar = 0;

    do {
      if (enterChar(numberText, NBDIGITINTMAX) == 0){
      /*=0 indique une demande de nombre a la fonction enterChar puis on test le code retour*/
          if( (testChar = sscanf(numberText, "%d", number) == 0) || ((*number) < min || (*number) > max) ){
            /*converti la chaine de caractere en int, vérifie la reussite de la conversion
            puis verifie que la valeur est dans l'intervale voulu */
            INFO ("\nVeuillez saisir une valeur comprise entre %d et %d : ", min, max);
          }
      }
      else{
          return 4; /*  Si erreur du programme de saisie on retourne 4  */
      }
    } while(testChar != 0 || (*number) < min || (*number) > max);

    return 0;  /* Saisie sans erreur on retourne 0 */
}

//____________________________________________________________________________________________________________________________________
int enterChar(char *string, int nbCharMax) {
/*  On passe à la fonction la variable qui va contenir la chaine de caractere
et le nombre de caracteres maximum, 0 signifie qu'on demande un nombre*/

  char *charReturn = NULL; /* Pointeur qui va pointer l'adresse du caractere "\n" */
  int nbCharToo = 0;
  int nbEscape = 0;

    do {
      if (fgets(string, nbCharMax, stdin) != NULL) {
        /*  Lecture de la saisie clavier avec test d'erreur */
        charReturn = strchr(string, '\n');
        /*  Recherche du caractere "\n" genere lors de la saisie par le "entrer" operateur) */
        if (charReturn != NULL) { /*  Si on trouve le \n  */
          *charReturn = '\0'; /*  On remplace "\n" par caractere "\0" */
          nbCharToo = 0; /* Necessaire en cas de boucle */
          DEBUG("\nCaractere '\\n' trouve\n");
          nbEscape = 0; /* Necessaire en cas de boucle */
          for (int i = 0; string[i] == ' '; i++){ /* Compte du nombre de caractere espace en début de chaine */
            nbEscape++;
          }
          DEBUG("Nombre d'espace en debut de saisie : %d\n\n", nbEscape);
          for (int j = 0; j < nbCharMax ; j++){
            string[j] = string[j+nbEscape]; /*On remplace les espaces du debut par les caractères suivants */
          }
        }
        else{ /* Si on n'a pas trouver le "/n", alors le buffer n'est pas vide */
          clearBuffer(&nbCharToo); /*  Donc on vide le buffer  */
          DEBUG("\nCaractere '\\n' non trouve\n");
          INFO("Vous avez saisi %d caractere(s) en trop. Veuillez saisir %d caracteres maximum : ", nbCharToo, nbCharMax-2);
        }
        if(strlen(string) == 0) {
          INFO("Vous devez saisir au moins un caractere : ");
        }
      }
      else{  /* Si erreur de la commande de saisie */
          clearBuffer(&nbCharToo); /* Par sécurite, on vide le buffer */
          return 4; /* Erreur de saisie, retourne 4 */
      }
    }while (nbCharToo > 0 || strlen(string) == 0);
    /*On boucle si la saisie operateur est vide ou superieur au nombre de caractere maximum*/

    return 0; /* Saisie sans erreur on retourne 0 */
}

//____________________________________________________________________________________________________________________________________
int clearBuffer(int *nbCharToo){
  int buffer = 0;
  do{
    (*nbCharToo)++; /* Compte le nombre de caracteres restant dans le buffer stdin*/
  }while( (buffer = getchar()) != '\n' && buffer != EOF);
  /*On parcours le buffer jusqu'à la fin pour le decharger dans la variable temporaire */

  return 0;
}
