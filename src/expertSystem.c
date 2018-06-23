#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "expertSystem.h"
#include "openFile.h"

int checkFact(char *value, OPERATOR operator, char *compare) {
  int i_value = 0;
  int i_compare = 0;

  int result = 0;

  // Conversion chaine de caractere en entier
  i_value = atoi(value);
  i_compare = atoi(compare);

  switch (operator) {
    case OPERATOR_EQUAL:
    {
      if (i_compare == i_value) {
        result = 1;
      }
    } break;

    case OPERATOR_DIFF:
    {
      if (i_compare != i_value) {
        result = 1;
      }
    } break;

    case OPERATOR_GREATER:
    {
      if (i_compare > i_value) {
        result = 1;
      }
    } break;

    case OPERATOR_GREATER_OR_EQUAL:
    {
      if (i_compare >= i_value) {
        result = 1;
      }
    } break;

    case OPERATOR_LESS:
    {
      if (i_compare < i_value) {
        result = 1;
      }
    } break;

    case OPERATOR_LESS_OR_EQUAL:
    {
      if (i_compare <= i_value) {
        result = 1;
      }
    } break;
  default:
  break;
  }

  return result;
}

int checkRule(Rule *rule, Hypothesis *ruleCondition, Hypothesis *factHead, Hypothesis *fact) {

  // Si fact est NULL, cela signifie que l'une des hypotheses de la regle n'est pas present dans la liste des faits initiaux
  if (fact == NULL) {
    DEBUG("Not found %s in fact list", ruleCondition->name);
    return 0;
  }

  // Si ruleCondition est NULL, cela signifie que toutes les hypotheses de la regle sont satisfaite
  if (ruleCondition == NULL) {
    return 1;
  }

  if (strcmp(ruleCondition->name, fact->name) == 0) { // Correspondance
    DEBUG("Found %s in fact list", ruleCondition->name);
    if (strcmp(ruleCondition->value, "X") == 0) { // Valeur indefinie
      // verfication si une valeur d'une hypothese indefinie n'est pas deja sauvegardee
      if (strlen(rule->variable) == 0) {
        // Remplacement de X par la valeur
        strcpy(ruleCondition->value, fact->value);
        // Sauvegarde de la valeur dans la regle
        strcpy(rule->variable, fact->value);
      }
      else {
        // Remplacement de X par la valeur sauvegardee
        strcpy(ruleCondition->value, rule->variable);
      }
    }

    // Verification si les condition sontsatisfaites
    if(checkFact(ruleCondition->value, ruleCondition->operator, fact->value) == 1) {
      DEBUG("Contion checked %s %s %s", fact->value, convOperatorChar(ruleCondition->operator), ruleCondition->value);
      // Si oui, on relance avec la condition suivante de la regle
      return checkRule(rule, ruleCondition->next, factHead, factHead);
    }
    else {
      // Sinon, on stop l'analyse car si au moins une hypothese n'est pas valide alors la regle n'est pas valide
      DEBUG("Contion not checked %s %s %s", fact->value, convOperatorChar(ruleCondition->operator), ruleCondition->value);
      return 0;
    }
  }

  // On relance avec le fait suivant
  return checkRule(rule, ruleCondition, factHead, fact->next);
}

char * updateFact(Rule * ruleList, Hypothesis *listFact) {

  // Si ruleList est NULL, cela signifie qu'il n'y a plus de regle a verifier
  if (ruleList == NULL) {
    return NULL;
  }

  // On verifie si la regle est validee
  if (checkRule(ruleList, ruleList->nextFact, listFact, listFact) == 1) {
    Hypothesis *node = NULL;

    DEBUG("Regle %s validee", ruleList->name);

    // On verifie que la valeur du resultat de la regle n'est pas indefinie
    if (strcmp(ruleList->result->value, "X") == 0) {
      // Remplacement de X par la valeur sauvegardee
      strcpy(ruleList->result->value, ruleList->variable);
    }

    // Duplication du resultat de la regle
    node = duplicateHypothesis(ruleList->result);
    // Ajout dans la liste des faits initiaux le resultat de la regle
    listFact->next = addFact(listFact->next, node);

    // retourne le nom de la liste validee
    return ruleList->name;
  }
  else {
    DEBUG("Regle %s invalidee", ruleList->name);
    return NULL;
  }

  // Relance avec la regle suivante
  return updateFact(ruleList->next, listFact);
}

void frontChaining(Rule **headList, Rule *ruleList, Hypothesis *listFact) {
  char *nameRule = NULL;

  // Si ruleList est NULL, cela signifie qu'il n'y a plus de regle a analyser
  if (ruleList == NULL) {
    return;
  }

  // Recuperation du nom de la regle validee dans la liste
  nameRule = updateFact(ruleList, listFact);

  // Si different de NULL, alors une regle est validee
  if (nameRule != NULL) {
    // On retire la regle validee de la liste
    *headList = freeRule(NULL, *headList, nameRule);
    // On relance le chainage depuis le debut de la liste
    frontChaining(headList, *headList, listFact);
  }
  else {
    // On relance le chainage avec la regle suivante
    frontChaining(headList, ruleList->next, listFact);
  }
}
