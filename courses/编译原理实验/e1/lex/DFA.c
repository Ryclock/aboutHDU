#include <stdio.h>
#include <stdlib.h>
#include "DFA.h"

DFA createDFA(State **state_array, int start_idx, int *end_idxs, int end_num)
{
    DFA dfa;
    dfa.start_state = state_array[0];
    dfa.num_end_state = end_num;
    for (int i = 0; i < end_num; i++)
    {
        dfa.end_states[i] = state_array[end_idxs[i]];
    }
    return dfa;
}
void printDFA(DFA *dfa)
{
    printNFA(dfa, 0);
}
void saveDFA2graphviz(DFA *dfa, const char *filename, const char *digraph_name)
{
    saveNFA2graphviz(dfa, filename, digraph_name);
}
void destroyDFA(DFA *dfa)
{
    destroyNFA(dfa);
}