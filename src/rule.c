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

  // Ouverture du fichier des regles
  openFile(&file, path, "r");

  if (file != NULL) {
    while (fgets(string, MAX_SIZE_RULE, file) != NULL) { // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
      string[strlen(string)-1] = 0; // Suppression du retour chariot
      DEBUG("%s", string);
      // Decodage de la regle
      rule = decodeRule(string);
      // Si la regle est correcte alors on l'ajoute dans la liste
      if (rule != NULL) {
        list = addRule(list, rule);
      }
    }
    // On ferme le fichier
    fclose(file);
  }

  // On retourne la liste des regles
  return list;
}

Rule * createRule() {
  Rule *rule = NULL;

  // Allocation
  rule = (Rule *) malloc(sizeof(Rule));

  if (rule == NULL) {
    return NULL;
  }

  // Initialisation
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
  int nbArgs = 0; // numero de l'argument en analyse
  int flagResult = 0; // flag pour savoir si on analyse le resultat de la regle
  int error = 0; // contient le nombre d'erreur
  Rule *rule = NULL;

  // Creer une regle vide
  rule = createRule();

  if (rule == NULL) {
    return NULL;
  }

  cpy = strdup(line);  // On réserve la mémoire de la string
  tmp = cpy; // On concerve le pointer pour pouvoir effectuer un free

  while ((token = strsep(&cpy, " "))){ // Tant qu'on peut separer
    if (nbArgs == 0) {// Le premier argument est le nom de la regle
      strcpy(rule->name, token);
    }
    else if (nbArgs == 1 && strcmp(token, "SI") != 0) { // Deuxieme doit etre "SI"
      WARN("Syntaxe error : SI != %s IN %s", token, line);
      error++;
      break;
    }
    // Il y a parite entre l'interval des mots cle sinon il y a une erreur
    else if(nbArgs != 1 && nbArgs%2 != 0 && strcmp(token, "ET") != 0 && strcmp(token, "ALORS") != 0) {
      WARN("Syntaxe error : ET or ALORS");
      error++;
      break;
    }
    else {
      // Detection du mot cle signifiant le resultat de la regle
      if (strcmp(token, "ALORS") == 0) {
        flagResult = 1;
      }

      // Si different des mots cle
      if (strcmp(token, "SI") != 0 && strcmp(token, "ET") != 0 && strcmp(token, "ALORS") != 0) {
        // Decodage de l'hypothese
        hypo = decodeHypothesis(token);
        if (hypo != NULL) {
          // L'hypothese est un fait
          if (flagResult == 0) {
            // On ajoute dans la liste des hypotheses
            rule->nextFact = addFact(rule->nextFact, hypo);
            DEBUG("FACT => name : %s, operator : %s, value : %s", hypo->name, convOperatorChar(hypo->operator), hypo->value);
          }
          else { // L'hypothse est un resultat
            rule->result = hypo;
            DEBUG("RESULT => name : %s, operator : %s, value : %s", hypo->name, convOperatorChar(hypo->operator), hypo->value);
          }
        }
        else { // Erreur de decodage
          WARN("Syntaxe error : %s IN %s", token, line);
          error++;
          break;
        }
      }
    }
    nbArgs++;
  }

  // Presence d'erreur, on libere les regles
  if (error > 0) {
    freeAllRule(rule);
    rule = NULL;
  }

  // Liberation pointer
  free(tmp);

  // Retourne la regle
  return rule;
}

Rule * addRule(Rule *root, Rule *node) {

  // Si node est NULL, cela signifie qu'il n'y a rien a ajouter, on retourne la tete
  if (node == NULL) {
    return root;
  }

  // Si root est NULL, cela signifie qu'il n'y a pas de tete, on retourne le noeud
  if (root == NULL) {
    return node;
  }

  // On ajoute a la suite
  root->next = addRule(root->next, node);

  // On retourne la racine du noeud courant
  return root;
}

Rule * duplicateRule(Rule *rule) {
  Rule *node = NULL;

  if (rule == NULL) {
    return NULL;
  }

  // On creer une regle vide
  node = createRule();

  // Initialisation avec une autre regle
  strcpy(node->name, rule->name);

  // On duplique la liste des hypotheses
  node->nextFact = duplicateHypothesis(rule->nextFact);
  // On duplique le resultat
  node->result = createHypothesis(rule->result->name, rule->result->value, rule->result->operator);
  // On duplique le reste des regles en relancant avec la regle suivante
  node->next = duplicateRule(rule->next);

  // On retourne la regle dupliquee
  return node;
}

Rule * freeRule(Rule *parent, Rule *rule, char *name) {
  Rule *ruleNext = NULL;

  // rule est NULL, cela signifie qu'il n'y a rien a liberer, on retourne la regle precedante
  if (rule == NULL) {
    return parent;
  }

  // Correspondance avec le nom
  if (strcmp(rule->name, name) == 0) {
    if (parent == NULL) {
      // Sauvegarde de la regle suivante
      ruleNext = rule->next;

      // Liberation de la liste des hypotheses
      freeAllHypothesis(rule->nextFact);

      // Liberation du resultat
      free(rule->result);
      rule->result = NULL;

      // Liberation de la regle
      free(rule);
      rule = NULL;

      // On retourne la regle suivante
      return ruleNext;
    }
    else {
      // On refait le lien
      parent->next = rule->next;

      // Liberation de la liste des hypotheses
      freeAllHypothesis(rule->nextFact);

      // Liberation du resultat
      free(rule->result);
      rule->result = NULL;

      // Liberation de la regle
      free(rule);
      rule = NULL;
    }

    // On retourne la regle parent
    return parent;
  }

  // On relance avec la regle suivante
  freeRule(rule, rule->next, name);

  // On retourne la regle
  return rule;
}

void freeAllRule(Rule *rule) {

  // Si rule est NULL, cela signifie qu'il n'y a rien a liberer
  if (rule == NULL) {
    return;
  }

  // On relance avec la regle suivante
  freeAllRule(rule->next);

  // Liberation de la liste des hypotheses
  freeAllHypothesis(rule->nextFact);

  // Liberation du resultat
  if (rule->result != NULL) {
    free(rule->result);
    rule->result = NULL;
  }

  // Liberation de la regle
  free(rule);
  rule = NULL;
}

void displayRule(Rule *rule) {
  char string[500] = {0};

  // Si rule est NULL, cela signifie qu'il n'y a rien a afficher
  if (rule == NULL) {
    return;
  }

  // On prepare toutes les information de la liste des hypotheses
  displayAllHypothesis(rule->nextFact, string);

  DEBUG("%s SI %s ALORS %s%s%s", rule->name, string, rule->result->name, "==", rule->result->value);
}

void displayAllRule(Rule *rule) {

  // Si rule est NULL, cela signifie qu'il n'y a rien a afficher
  if (rule == NULL) {
    return;
  }

  // On affiche la regle
  displayRule(rule);

  // On relance avec la regle suivante
  displayAllRule(rule->next);
}
