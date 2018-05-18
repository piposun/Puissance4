#ifndef HEADER_HYPOTHESIS
#define HEADER_HYPOTHESIS

#define MAX_SIZE_NAME 20
#define MAX_SIZE_VALUE 20

typedef enum {
  OPERATOR_UNK = -1,
  OPERATOR_EQUAL,
  OPERATOR_DIFF,
  OPERATOR_GREATER,
  OPERATOR_GREATER_OR_EQUAL,
  OPERATOR_LESS,
  OPERATOR_LESS_OR_EQUAL
}OPERATOR;

typedef struct hypothesis {
  char name[MAX_SIZE_NAME];
  OPERATOR operator;
  char value[MAX_SIZE_VALUE];
  struct hypothesis *next;
}Hypothesis;

char * convOperatorChar(OPERATOR operator);
OPERATOR convCharOperator(char * operator);
Hypothesis * searchFact(Hypothesis *fact, char *name);

Hypothesis * createHypothesis(char *name, char *value, OPERATOR operator);
Hypothesis * decodeHypothesis(char *argument);
Hypothesis * addFact(Hypothesis *root, Hypothesis *node);
Hypothesis * duplicateHypothesis(Hypothesis *hypo);

Hypothesis * freeHypothesis(Hypothesis *parent, Hypothesis *hypo, char *name);
void freeAllHypothesis(Hypothesis *hypo);

void displayHypothesis(Hypothesis *hypo, char *string);
void displayAllHypothesis(Hypothesis *hypo, char *string);

#endif /* HEADER_HYPOTHESIS */
