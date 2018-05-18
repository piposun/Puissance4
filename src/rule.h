
#ifndef HEADER_RULE
#define HEADER_RULE

#include "hypothesis.h"

#define MAX_SIZE_RULE 5000

typedef struct rule {
  char name[MAX_SIZE_NAME];
  char variable[MAX_SIZE_VALUE];
  Hypothesis *nextFact;
  Hypothesis *result;
  struct rule *next;
}Rule;

Rule * initRules(char *path);
Rule * createRule();
Rule * decodeRule(char *line);
Rule * addRule(Rule *root, Rule *node);
Rule * duplicateRule(Rule *rule);

Rule * freeRule(Rule *parent, Rule *rule, char *name);
void freeAllRule(Rule *rule);

void displayRule(Rule *rule);
void displayAllRule(Rule *rule);

#endif /* HEADER_RULE */
