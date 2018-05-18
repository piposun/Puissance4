#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "hypothesis.h"
#include "openFile.h"

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

  if(fact == NULL) {
    return NULL;
  }

  if (strcmp(fact->name, name) == 0) {
    return fact;
  }

  return searchFact(fact->next, name);
}

Hypothesis * createHypothesis(char *name, char *value, OPERATOR operator) {
  Hypothesis *hypo = NULL;

  hypo = (Hypothesis *) malloc(sizeof(Hypothesis));

  if (hypo == NULL) {
    return NULL;
  }

  strcpy(hypo->name, name);
  strcpy(hypo->value, value);
  hypo->operator = operator;
  hypo->next = NULL;

  return hypo;
}

Hypothesis * decodeHypothesis(char *argument) {
  int index = 0;
  char *cpy = NULL, *tmp = NULL, *arg1 = NULL, *arg2 = NULL;
  Hypothesis *hypo = NULL;
  char *operators[6] = {"==", "!=", ">>", ">=", "<<", "<="};

  while (index < 6 && strstr(argument, operators[index]) == NULL) index++;

  if (index >= 6) {
    WARN("operator : ???");
    return NULL;
  }

  cpy = strdup(argument);  //On réserve la mémoire de la string
  tmp = cpy; //On concerve le pointer pour pouvoir effectuer un free
  arg1 = strsep(&cpy, operators[index]);
  strsep(&cpy, operators[index]); // operateur
  arg2 = strsep(&cpy, operators[index]);

  hypo = createHypothesis(arg1, arg2, convCharOperator(operators[index]));

  free(tmp);

  return hypo;
}

Hypothesis * addFact(Hypothesis *root, Hypothesis *node) {

  if (node == NULL) {
    return root;
  }
  if (root == NULL) {
    return node;
  }

  root->next = addFact(root->next, node);

  return root;
}

Hypothesis * duplicateHypothesis(Hypothesis *hypo) {
  Hypothesis * node;

  if (hypo == NULL) {
    return NULL;
  }

  node = createHypothesis(hypo->name, hypo->value, hypo->operator);
  node->next = duplicateHypothesis(hypo->next);

  return node;
}

Hypothesis * freeHypothesis(Hypothesis *parent, Hypothesis *hypo, char *name) {
  Hypothesis *hypoNext = NULL;

  if (hypo == NULL) {
    return parent;
  }

  if (strcmp(hypo->name, name) == 0) {
    if (parent == NULL) {
      hypoNext = hypo->next;
      free(hypo);
      hypo = NULL;
      return hypoNext;
    }
    else {
      parent->next = hypo->next;
      free(hypo);
      hypo = NULL;
    }

    return parent;
  }

  freeHypothesis(hypo, hypo->next, name);

  return hypo;
}

void freeAllHypothesis(Hypothesis *hypo) {

  if (hypo == NULL) {
    return;
  }

  freeAllHypothesis(hypo->next);
  free(hypo);
  hypo = NULL;
}

void displayHypothesis(Hypothesis *hypo, char *string) {
  sprintf(string + strlen(string), "%s%s%s", hypo->name, convOperatorChar(hypo->operator), hypo->value);
}

void displayAllHypothesis(Hypothesis *hypo, char *string) {

  displayHypothesis(hypo, string);

  if (hypo->next == NULL) {
    return;
  }

  sprintf(string + strlen(string), " ET ");
  displayAllHypothesis(hypo->next, string);
}
