#ifndef __NFA_H
#define __NFA_H
#define MAX_STATES 256
#define MAX_END_STATES 10
#include "state.h"

typedef struct NFA
{
    State *start_state;
    State *end_states[MAX_END_STATES];
    int num_end_state;
} NFA;

NFA createNFA(State *, State **, int);
NFA createNFA_single_char(char);
NFA createNFA_concat(NFA *nfa1, NFA *nfa2);
NFA createNFA_union(NFA *nfa1, NFA *nfa2);
NFA createNFA_Kleene_star(NFA *);
void set_start_state(NFA *, State *);
State *get_start_state(NFA *);
State **get_end_states(NFA *);
int get_num_end_state(NFA *);
void printNFA(NFA *, int);
void saveNFA2graphviz(NFA *, const char *filename, const char *digraph_name);
void destroyNFA(NFA *);

#endif