
#ifndef HEADER_RULE
#define HEADER_RULE

/*! \file rule.h
    \brief Gestion des regles.
    \version 0.1

    Contient la description et le fonctionnement des regles.
*/

#include "hypothesis.h"

/*! \def MAX_SIZE_RULE
    \brief Taille max d'une regle dans le fichier.
*/
#define MAX_SIZE_RULE 5000

/*! \struct Rule
    \brief Gere la liste des regles en forme de liste peigne.
*/
typedef struct rule {
  char name[MAX_SIZE_NAME]; /**< Le nom de la regle */
  char variable[MAX_SIZE_VALUE]; /**< Sauvegarde de la valeur de definition */
  Hypothesis *nextFact; /**< List des hypotheses */
  Hypothesis *result; /**< Resultat de la regle */
  struct rule *next; /**< List des regles */
}Rule;

/*! \fn Rule * initRules(char *path)
    \brief Cette fonction initialise la liste des regles de base.

    \param path le chemin d'acces du fichier contenant les regles.
    \return Renvoie la tete de liste des regles.
*/
Rule * initRules(char *path);

/*! \fn Rule * createRule()
    \brief Cette fonction cree une regle vide.

    \return Renvoie la regle.
*/
Rule * createRule();

/*! \fn Rule * decodeRule(char *line)
    \brief Cette fonction decode la regle a partir d'une chaine de caractere.

    \param line Chaine de caractere contenant la regle.
    \return Renvoie la regle.
*/
Rule * decodeRule(char *line);

/*! \fn Rule * addRule(Rule *root, Rule *node)
    \brief Cette fonction ajoute la regle a la suite dans la liste.

    \param root racine du noeud.
    \param noeud regle a ajouter.
    \return Renvoie la tete de la liste.
*/
Rule * addRule(Rule *root, Rule *node);

/*! \fn Rule * duplicateRule(Rule *rule)
    \brief Cette fonction duplique la regle passee en parametre

    \param rule La regle a dupliquer.
    \return Renvoie la nouvelle regle dupliquee.
*/
Rule * duplicateRule(Rule *rule);

/*! \fn Rule * freeRule(Rule *parent, Rule *rule, char *name)
    \brief Cette fonction libere la memoire avec le nom de la regle

    \param parent Le parent de la regle courante.
    \param rule La regle courante.
    \param name Le nom de la regle a supprimer.
    \return Renvoie la tete de la liste des regles.
*/
Rule * freeRule(Rule *parent, Rule *rule, char *name);

/*! \fn void freeAllRule(Rule *rule)
    \brief Cette fonction libere toute la memoire des regles

    \param rule La regle courante.
*/
void freeAllRule(Rule *rule);

/*! \fn void displayRule(Rule *rule)
    \brief Cette fonction affiche la regle

    \param rule La regle courante.
*/
void displayRule(Rule *rule);

/*! \fn void displayRule(Rule *rule)
    \brief Cette fonction affiche toutes les regles

    \param rule La regle courante.
*/
void displayAllRule(Rule *rule);

#endif /* HEADER_RULE */
