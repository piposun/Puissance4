#ifndef HEADER_HYPOTHESIS
#define HEADER_HYPOTHESIS

/*! \file hypothesis.h
    \brief Structure des faits.
    \version 0.1

    C'est la definition des faits.
*/

/*! \def MAX_SIZE_NAME
    \brief Taille max pour le champ name d'un fait
*/
#define MAX_SIZE_NAME 20

/*! \def MAX_SIZE_VALUE
    \brief Taille max pour le champ value d'un fait
*/
#define MAX_SIZE_VALUE 20

/*! \enum OPEN_FILE
    \brief Gere les type d'operateur.
*/
typedef enum {
  OPERATOR_UNK = -1, /**< Operateur inconnu */
  OPERATOR_EQUAL, /**< Operateur egal */
  OPERATOR_DIFF, /**< Operateur different */
  OPERATOR_GREATER, /**< Operateur superieur */
  OPERATOR_GREATER_OR_EQUAL, /**< Operateur superieur ou egal */
  OPERATOR_LESS, /**< Operateur inferieur */
  OPERATOR_LESS_OR_EQUAL /**< Operateur superieur ou egal */
}OPERATOR;

/*! \struct Hypothesis
    \brief Gere la liste des hypotheses.
*/
typedef struct hypothesis {
  char name[MAX_SIZE_NAME]; /**< Le nom de l'hypothese */
  OPERATOR operator; /**< L'operateur' */
  char value[MAX_SIZE_VALUE]; /**< La valeur de l'hypothese */
  struct hypothesis *next; /**< Liste des hypotheses */
}Hypothesis;

/*! \fn char * convOperatorChar(OPERATOR operator)
    \brief Cette fonction convertit les operateurs en chaine de caractere.

    \param operator l'operateur a convertir'.
    \return Renvoie l'operateur sous forme de chaine de caractere.
*/
char * convOperatorChar(OPERATOR operator);

/*! \fn OPERATOR convCharOperator(char * operator)
    \brief Cette fonction convertit une chaine de caractere en operateur.

    \param operator la chaine a convertir.
    \return Renvoie l'operateur.
*/
OPERATOR convCharOperator(char * operator);

/*! \fn Hypothesis * searchFact(Hypothesis *fact, char *name)
    \brief Cette fonction recherche un fait dans une liste

    \param fact la liste des faits.
    \param name le nom du fait a rechercher.
    \return Renvoie le fait.
*/
Hypothesis * searchFact(Hypothesis *fact, char *name);

/*! \fn Hypothesis * createHypothesis(char *name, char *value, OPERATOR operator)
    \brief Cette fonction cree un fait avec les information passees en parametre

    \param name le nom du fait.
    \param value la valeur.
    \param operator le type d'operateur.
    \return Renvoie le fait.
*/
Hypothesis * createHypothesis(char *name, char *value, OPERATOR operator);

/*! \fn Hypothesis * decodeHypothesis(char *argument)
    \brief Cette fonction decode un fait via une chaine de caractere

    \param argument la chaine de caractere a analyser
    \return Renvoie le fait.
*/
Hypothesis * decodeHypothesis(char *argument);

/*! \fn Hypothesis * addFact(Hypothesis *root, Hypothesis *node)
    \brief Cette fonction ajoute un fait dans la liste a la suite

    \param root le fait precedent
    \param node le fait a ajouter
    \return Renvoie la tete.
*/
Hypothesis * addFact(Hypothesis *root, Hypothesis *node);

/*! \fn Hypothesis * duplicateHypothesis(Hypothesis *hypo)
    \brief Cette fonction duplique une liste de faits

    \param hypo la liste
    \return Renvoie la nouvelle liste.
*/
Hypothesis * duplicateHypothesis(Hypothesis *hypo);

/*! \fn Hypothesis * freeHypothesis(Hypothesis *parent, Hypothesis *hypo, char *name)
    \brief Cette fonction libere un fait par rapport a son nom

    \param parent le fait precedant
    \param hypo le fait courant
    \param name le nom du fait a liberer
    \return Renvoie la tete.
*/
Hypothesis * freeHypothesis(Hypothesis *parent, Hypothesis *hypo, char *name);

/*! \fn void freeAllHypothesis(Hypothesis *hypo)
    \brief Cette fonction libere la liste des faits complet

    \param hypo la liste.
*/
void freeAllHypothesis(Hypothesis *hypo);

/*! \fn void displayHypothesis(Hypothesis *hypo, char *string)
    \brief Cette fonction prepare l'affichage d'un fait

    \param hypo le fait courant
    \param string la chaine de caratere contenant l'affichage du fait
*/
void displayHypothesis(Hypothesis *hypo, char *string);

/*! \fn void displayHypothesis(Hypothesis *hypo, char *string)
    \brief Cette fonction prepare l'affichage de la liste des faits

    \param hypo le fait courant
    \param string la chaine de caratere contenant l'affichage des faits
*/
void displayAllHypothesis(Hypothesis *hypo, char *string);

#endif /* HEADER_HYPOTHESIS */
