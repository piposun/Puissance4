#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "hypothesis.h"

char * convOperatorChar(OPERATOR operator) {
  switch (operator) {
    case OPERATOR_EQUAL:
    {
      return "==";
    }
    case OPERATOR_DIFF:
    {
      return "!=";
    }
    case OPERATOR_GREATER:
    {
      return ">>";
    }
    case OPERATOR_GREATER_OR_EQUAL:
    {
      return ">=";
    }
    case OPERATOR_LESS:
    {
      return "<<";
    }
    case OPERATOR_LESS_OR_EQUAL:
    {
      return "<=";
    }
    default:
      return "??";
  }

  return "??";
}

OPERATOR convCharOperator(char * operator) {
  if (strcmp(operator, "==") == 0) {
    return OPERATOR_EQUAL;
  }
  else if (strcmp(operator, "!=") == 0) {
    return OPERATOR_DIFF;
  }
  else if (strcmp(operator, ">>") == 0) {
    return OPERATOR_GREATER;
  }
  else if (strcmp(operator, ">=") == 0) {
    return OPERATOR_GREATER_OR_EQUAL;
  }
  else if (strcmp(operator, "<<") == 0) {
    return OPERATOR_LESS;
  }
  else if (strcmp(operator, "<=") == 0) {
    return OPERATOR_LESS_OR_EQUAL;
  }

  return OPERATOR_UNK;
}

Hypothesis * searchFact(Hypothesis *fact, char *name) {

  // Si fact est NULL, cela signifie que la liste des hypothese est vide
  if(fact == NULL) {
    return NULL;
  }

  // Comparaison des noms
  if (strcmp(fact->name, name) == 0) {
    // On retourne le fait trouve
    return fact;
  }

  // On relance avec le fait suivant
  return searchFact(fact->next, name);
}

Hypothesis * createHypothesis(char *name, char *value, OPERATOR operator) {
  Hypothesis *hypo = NULL;

  // Allocation
  hypo = (Hypothesis *) malloc(sizeof(Hypothesis));

  // Verification de l'allocation
  if (hypo == NULL) {
    return NULL;
  }

  // Initialisation des champs
  strcpy(hypo->name, name);
  strcpy(hypo->value, value);
  hypo->operator = operator;
  hypo->next = NULL;

  return hypo;
}

Hypothesis * decodeHypothesis(char *argument) {
  int index = 0;
  char *cpy = NULL, *tmp = NULL, *nom = NULL, *value = NULL;
  Hypothesis *hypo = NULL;
  char *operators[6] = {"==", "!=", ">>", ">=", "<<", "<="};

  // Verification si l'operateur de l'hypothese existe dans la liste des operateurs connus
  while (index < 6 && strstr(argument, operators[index]) == NULL) index++;

  // index >= 6, cela signifie que la boucle while est sortie avec sa premier condition donc pas de correspondance avec les operateurs
  if (index >= 6) {
    WARN("operator : ???");
    return NULL;
  }

  cpy = strdup(argument);  //On réserve la mémoire de la string
  tmp = cpy; //On concerve le pointer pour pouvoir effectuer un free
  nom = strsep(&cpy, operators[index]); //nom du fait
  strsep(&cpy, operators[index]); // operateur
  value = strsep(&cpy, operators[index]); //valeur

  // Creation de l'hypothese
  hypo = createHypothesis(nom, value, convCharOperator(operators[index]));

  // Liberation du pointer
  free(tmp);

  // Retourne l'hypothese cree
  return hypo;
}

Hypothesis * addFact(Hypothesis *root, Hypothesis *node) {

  // Si node est NULL, cela signifie que l'hypothese a ajouter est NULL, on retourne la tete
  if (node == NULL) {
    return root;
  }
  // Si la root est NULL, cela signifie que la tete est NULL, on retourne l'hypothese comme tete
  if (root == NULL) {
    return node;
  }

  // On ajoute a la suite
  root->next = addFact(root->next, node);

  // On retourne la racine du noeud courant
  return root;
}

Hypothesis * duplicateHypothesis(Hypothesis *hypo) {
  Hypothesis * node;

  // L'hypothese a dupliquer est NULL
  if (hypo == NULL) {
    return NULL;
  }

  // On cree une hypothese a partir d'une autre hypothese
  node = createHypothesis(hypo->name, hypo->value, hypo->operator);

  // On relance avec l'hypothese suivante
  node->next = duplicateHypothesis(hypo->next);

  // On retourne le noeud
  return node;
}

Hypothesis * freeHypothesis(Hypothesis *parent, Hypothesis *hypo, char *name) {
  Hypothesis *hypoNext = NULL;

  // Si hypo est NULL, cela signifie qu'il n'y a rien a liberer
  if (hypo == NULL) {
    return parent;
  }

  // Correspondance
  if (strcmp(hypo->name, name) == 0) {
    // Si parent est NULL, cela signifie que hypo est la tete de liste
    if (parent == NULL) {
      // Sauvegarde de l'hypothese suivante
      hypoNext = hypo->next;
      // Liberation de l'hypothese
      free(hypo);
      hypo = NULL;
      // On retourne la nouvelle tete
      return hypoNext;
    }
    else {
      // On refait le lien des hypothese
      parent->next = hypo->next;
      // Liberation de l'hypothese
      free(hypo);
      hypo = NULL;
    }

    // On retourne l'hypothese parent de l'hypothese supprimee
    return parent;
  }

  // On relance avec l'hypothese suivante
  freeHypothesis(hypo, hypo->next, name);

  // On retourne l'hypothese
  return hypo;
}

void freeAllHypothesis(Hypothesis *hypo) {

  // Si hypo est NULL, cela signifie qu'il n'y a plus rien a liberer
  if (hypo == NULL) {
    return;
  }

  // On relance avec l'hypothese suivante
  freeAllHypothesis(hypo->next);

  // On libere l'hypothese
  free(hypo);
  hypo = NULL;
}

void displayHypothesis(Hypothesis *hypo, char *string) {
  // Preparation de l'affichage de l'hypothese. On decale le pointer du nombre de caractaire deja present
  sprintf(string + strlen(string), "%s%s%s", hypo->name, convOperatorChar(hypo->operator), hypo->value);
}

void displayAllHypothesis(Hypothesis *hypo, char *string) {

  // Ajoute l'information de l'hypothese dans la chaine principale
  displayHypothesis(hypo, string);

  // Si hypo->next est NULL, cela signifie qu'il n'y a plus d'hypothese
  if (hypo->next == NULL) {
    return;
  }

  // On ajoute un mot cle
  sprintf(string + strlen(string), " ET ");

  // On relance avec l'hypothese suivante
  displayAllHypothesis(hypo->next, string);
}
