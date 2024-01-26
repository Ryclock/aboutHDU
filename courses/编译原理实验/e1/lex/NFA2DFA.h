#ifndef __NFA_TO_DFA_H
#define __NFA_TO_DFA_H
#define MAX_SYMBOLS 125
#include "DFA.h"

int cal_epsilon_closure(State *state, State **epsilon_closure);
DFA convert_NFA_to_DFA(NFA *nfa);

#endif