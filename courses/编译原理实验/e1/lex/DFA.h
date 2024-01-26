#ifndef __DFA_H
#define __DFA_H
#include "NFA.h"

typedef NFA DFA;

DFA createDFA(State **, int start_idx, int *, int end_num);
void printDFA(DFA *);
void saveDFA2graphviz(DFA *, const char *filename, const char *digraph_name);
void destroyDFA(DFA *);

#endif