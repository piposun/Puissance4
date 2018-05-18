#ifndef HEADER_EXPERT_SYSTEM
#define HEADER_EXPERT_SYSTEM

#include "rule.h"
#include "hypothesis.h"

char * updateFact(Rule * ruleList, Hypothesis *listFact);
void frontChaining(Rule **headList, Rule *ruleList, Hypothesis *listFact);
int checkRule(Rule *rule, Hypothesis *ruleCondition, Hypothesis *factHead, Hypothesis *fact);

#endif /* HEADER_EXPERT_SYSTEM */
