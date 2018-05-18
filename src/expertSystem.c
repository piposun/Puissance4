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

  if (fact == NULL) {
    DEBUG("Not found %s in fact list", ruleCondition->name);
    return 0;
  }

  if (ruleCondition == NULL) {
    return 1;
  }

  if (strcmp(ruleCondition->name, fact->name) == 0) {
    DEBUG("Found %s in fact list", ruleCondition->name);
    if (strcmp(ruleCondition->value, "X") == 0) {
      if (strlen(rule->variable) == 0) {
        strcpy(ruleCondition->value, fact->value);
        strcpy(rule->variable, fact->value);
      }
      else {
        strcpy(ruleCondition->value, rule->variable);
      }
    }
    if(checkFact(ruleCondition->value, ruleCondition->operator, fact->value) == 1) {
      DEBUG("Contion checked %s %s %s", fact->value, convOperatorChar(ruleCondition->operator), ruleCondition->value);
      return checkRule(rule, ruleCondition->next, factHead, factHead);
    }
    else {
      DEBUG("Contion not checked %s %s %s", fact->value, convOperatorChar(ruleCondition->operator), ruleCondition->value);
      return 0;
    }
  }

  return checkRule(rule, ruleCondition, factHead, fact->next);
}

char * updateFact(Rule * ruleList, Hypothesis *listFact) {

  if (ruleList == NULL) {
    return NULL;
  }

  if (checkRule(ruleList, ruleList->nextFact, listFact, listFact) == 1) {
    Hypothesis *node = NULL;

    DEBUG("Regle %s validee", ruleList->name);

    if (strcmp(ruleList->result->value, "X") == 0) {
      strcpy(ruleList->result->value, ruleList->variable);
    }

    node = duplicateHypothesis(ruleList->result);
    listFact->next = addFact(listFact->next, node);
    return ruleList->name;
  }
  else {
    DEBUG("Regle %s invalidee", ruleList->name);
    return NULL;
  }

  return updateFact(ruleList->next, listFact);
}

void frontChaining(Rule **headList, Rule *ruleList, Hypothesis *listFact) {
  char *nameRule = NULL;

  if (ruleList == NULL) {
    return;
  }

  nameRule = updateFact(ruleList, listFact);

  if (nameRule != NULL) {
    *headList = freeRule(NULL, *headList, nameRule);
    frontChaining(headList, *headList, listFact);
  }
  else {
    frontChaining(headList, ruleList->next, listFact);
  }
}
