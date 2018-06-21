#ifndef HEADER_EXPERT_SYSTEM
#define HEADER_EXPERT_SYSTEM

/*! \file expertSystem.h
    \brief Systeme expert.
    \version 0.1

    C'est le moteur d'inference du systeme expert.
*/

#include "rule.h"
#include "hypothesis.h"

/*! \fn int checkFact(char *value, OPERATOR operator, char *compare)
    \brief Cette fonction verifie si le fait est valide.

    \param value la valeur de l'hypothese de la regle.
    \param operator l'operateur de la condition'.
    \param compare la valeur du fait.
    \return Renvoie 1 si la condition est vrai sinon 0.
*/
int checkFact(char *value, OPERATOR operator, char *compare);

/*! \fn char * updateFact(Rule * ruleList, Hypothesis *listFact)
    \brief Cette fonction met à jour la liste des faits initiaux avec le resultat des regles qui sont validees.

    \param ruleList la liste des regles de base.
    \param listFact la liste des faits initiaux.
    \return Renvoie le nom de la regle validee.
*/
char * updateFact(Rule * ruleList, Hypothesis *listFact);

/*! \fn frontChaining(Rule **headList, Rule *ruleList, Hypothesis *listFact)
    \brief Cette fonction effectue le chainage avant du moteur d'inference.
     Une fois une regle validee, celle-ci est retiree de la liste puis on relance la fonction.

    \param headList la tete de la liste des regles de base.
    \param ruleList la regle a analyser.
    \param listFact la liste des faits initiaux.
*/
void frontChaining(Rule **headList, Rule *ruleList, Hypothesis *listFact);

/*! \fn int checkRule(Rule *rule, Hypothesis *ruleCondition, Hypothesis *factHead, Hypothesis *fact)
    \brief Cette fonction test les hypotheses de la liste des fait initiaux avec celle de la regle.

    \param rule la regle a analyser.
    \param ruleCondition la liste des hypotheses de la regle.
    \param factHead la tete de la liste des faits initiaux.
    \param fact le fait a comparer.
    \return Renvoie 1 si la regle est validee sinon 0.
*/
int checkRule(Rule *rule, Hypothesis *ruleCondition, Hypothesis *factHead, Hypothesis *fact);

#endif /* HEADER_EXPERT_SYSTEM */
