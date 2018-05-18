#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "rule.h"
#include "hypothesis.h"
#include "openFile.h"

Rule * initRules(char *path) {
  FILE *file = NULL;
  Rule *rule = NULL;
  Rule *list = NULL;
  char string[MAX_SIZE_RULE];

  openFile(&file, path, "r");

  if (file != NULL) {
    while (fgets(string, MAX_SIZE_RULE, file) != NULL) { // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
      string[strlen(string)-1] = 0; // Suppression du retour chariot
      DEBUG("%s", string);
      rule = decodeRule(string);
      if (rule != NULL) {
        list = addRule(list, rule);
      }
    }
    fclose(file);
  }

  return list;
}

Rule * createRule() {
  Rule *rule = NULL;

  rule = (Rule *) malloc(sizeof(Rule));

  if (rule == NULL) {
    return NULL;
  }

  rule->name[0] = 0;
  rule->variable[0] = 0;
  rule->nextFact = NULL;
  rule->result = NULL;
  rule->next = NULL;

  return rule;
}

Rule * decodeRule(char *line) {
  Hypothesis * hypo = NULL;
  char *cpy = NULL, *token = NULL, *tmp = NULL;
  int nbArgs = 0;
  int flagResult =0;
  int error = 0;
  Rule *rule = NULL;

  rule = createRule();

  if (rule == NULL) {
    return NULL;
  }

  cpy = strdup(line);  //On réserve la mémoire de la string
  tmp = cpy; //On concerve le pointer pour pouvoir effectuer un free

  while ((token = strsep(&cpy, " "))){
    if (nbArgs == 0) {
      strcpy(rule->name, token);
    }
    else if (nbArgs == 1 && strcmp(token, "SI") != 0) {
      WARN("Syntaxe error : SI != %s IN %s", token, line);
      error++;
      break;
    }
    else if(nbArgs != 1 && nbArgs%2 != 0 && strcmp(token, "ET") != 0 && strcmp(token, "ALORS") != 0) {
      WARN("Syntaxe error : ET or ALORS");
      error++;
      break;
    }
    else {
      if (strcmp(token, "ALORS") == 0) {
        flagResult = 1;
      }

      if (strcmp(token, "SI") != 0 && strcmp(token, "ET") != 0 && strcmp(token, "ALORS") != 0) {
        hypo = decodeHypothesis(token);
        if (hypo != NULL) {
          if (flagResult == 0) {
            rule->nextFact = addFact(rule->nextFact, hypo);
            DEBUG("FACT => name : %s, operator : %s, value : %s", hypo->name, convOperatorChar(hypo->operator), hypo->value);
          }
          else {
            rule->result = hypo;
            DEBUG("RESULT => name : %s, operator : %s, value : %s", hypo->name, convOperatorChar(hypo->operator), hypo->value);
          }
        }
        else {
          WARN("Syntaxe error : %s IN %s", token, line);
          error++;
          break;
        }
      }
    }
    nbArgs++;
  }

  if (error > 0) {
    freeAllRule(rule);
    rule = NULL;
  }

  free(tmp);

  return rule;
}

Rule * addRule(Rule *root, Rule *node) {

  if (node == NULL) {
    return root;
  }

  if (root == NULL) {
    return node;
  }

  root->next = addRule(root->next, node);

  return root;
}

Rule * duplicateRule(Rule *rule) {
  Rule *node = NULL;

  if (rule == NULL) {
    return NULL;
  }

  node = createRule();

  strcpy(node->name, rule->name);

  node->nextFact = duplicateHypothesis(rule->nextFact);
  node->result = createHypothesis(rule->result->name, rule->result->value, rule->result->operator);
  node->next = duplicateRule(rule->next);

  return node;
}

Rule * freeRule(Rule *parent, Rule *rule, char *name) {
  Rule *ruleNext = NULL;

  if (rule == NULL) {
    return parent;
  }

  if (strcmp(rule->name, name) == 0) {
    if (parent == NULL) {
      ruleNext = rule->next;

      freeAllHypothesis(rule->nextFact);

      free(rule->result);
      rule->result = NULL;

      free(rule);
      rule = NULL;

      return ruleNext;
    }
    else {
      parent->next = rule->next;

      freeAllHypothesis(rule->nextFact);

      free(rule->result);
      rule->result = NULL;

      free(rule);
      rule = NULL;
    }

    return parent;
  }

  freeRule(rule, rule->next, name);

  return rule;
}

void freeAllRule(Rule *rule) {

  if (rule == NULL) {
    return;
  }

  freeAllRule(rule->next);
  freeAllHypothesis(rule->nextFact);

  if (rule->result != NULL) {
    free(rule->result);
    rule->result = NULL;
  }

  free(rule);
  rule = NULL;
}

void displayRule(Rule *rule) {
  char string[500] = {0};

  if (rule == NULL) {
    return;
  }

  displayAllHypothesis(rule->nextFact, string);

  DEBUG("%s SI %s ALORS %s%s%s", rule->name, string, rule->result->name, "==", rule->result->value);
}

void displayAllRule(Rule *rule) {

  if (rule == NULL) {
    return;
  }

  displayRule(rule);

  displayAllRule(rule->next);
}
