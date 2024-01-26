#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "NFA2DFA.h"

typedef struct
{
    State *states[MAX_STATES];
    int count;
} State_Set;

int is_substate(State *sub, State_Set *parent)
{
    for (int i = 0; i < parent->count; i++)
    {
        if (sub == parent->states[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_state_subset(State_Set *sub, State_Set *parent)
{
    for (int i = 0; i < sub->count; i++)
    {
        if (!is_substate(sub->states[i], parent))
        {
            return 0;
        }
    }
    return 1;
}

int cal_epsilon_closure(State *state, State **epsilon_closure)
{
    if (!state)
    {
        printf("State is NULL\n");
        return 0;
    }

    State **stack = (State **)malloc(sizeof(State *) * MAX_STATES);
    int top = -1;

    stack[++top] = state;

    int *visited = (int *)malloc(sizeof(int) * MAX_STATES);
    for (int i = 0; i < MAX_STATES; i++)
    {
        visited[i] = 0;
    }

    int num_states = 0;
    epsilon_closure[num_states++] = state;
    while (top >= 0)
    {
        State *current_state = stack[top--];

        for (int i = 0; i < current_state->num_edges; i++)
        {
            Edge *edge = current_state->edges[i];
            if (EPSILON != edge->input_symbol)
            {
                continue;
            }

            State *target_state = edge->target_state;
            if (!visited[target_state->id])
            {
                epsilon_closure[num_states++] = edge->target_state;
                visited[target_state->id] = 1;
                stack[++top] = target_state;
            }
        }
    }
    free(stack);
    free(visited);
    return num_states;
}

State_Set find_target_stateset(State_Set *stateset, char symbol)
{
    State_Set target_stateset;
    target_stateset.count = 0;
    for (int i = 0; i < stateset->count; i++)
    {
        State *state = stateset->states[i];
        for (int j = 0; j < state->num_edges; j++)
        {
            Edge *edge = state->edges[j];
            if (edge->input_symbol == symbol)
            {
                target_stateset.states[target_stateset.count++] = edge->target_state;
            }
        }
    }
    return target_stateset;
}

int cal_symbols(NFA *nfa, char *symbols)
{
    if (!nfa)
    {
        printf("NFA is NULL\n");
        return 0;
    }

    State *start_state = nfa->start_state;
    if (!start_state)
    {
        printf("Start state is NULL\n");
        return 0;
    }

    int alphabet_size = 0;
    State **stack = (State **)malloc(sizeof(State *) * MAX_STATES);
    int top = -1;

    stack[++top] = start_state;

    int *visited_symbols = (int *)malloc(MAX_SYMBOLS * sizeof(int));

    while (top >= 0)
    {
        State *current_state = stack[top--];

        for (int i = 0; i < current_state->num_edges; i++)
        {
            int transition_symbol = current_state->edges[i]->input_symbol;
            if (!visited_symbols[transition_symbol])
            {
                visited_symbols[transition_symbol] = 1;
                alphabet_size++;
            }

            State *target_state = current_state->edges[i]->target_state;
            stack[++top] = target_state;
        }
    }

    free(stack);
    free(visited_symbols);

    return alphabet_size;
}

DFA convert_NFA_to_DFA(NFA *nfa)
{
    reset_id();
    State_Set dfa_states;
    dfa_states.states[0] = create_state(unique_id(), 0);
    dfa_states.count = 1;
    int cur = 0;

    State_Set visited[MAX_STATES];

    State_Set tmp;
    tmp.states[0] = nfa->start_state;
    tmp.count = 1;
    State_Set *queue = (State_Set *)malloc(sizeof(State_Set) * MAX_STATES);
    int rear = 0, head = 0;
    queue[head++] = tmp;

    State *epsilon_closure[MAX_STATES];
    State_Set epsilon_closure_unique;
    char symbols_visited[MAX_SYMBOLS];

    while (rear != head && head < MAX_STATES)
    {
        State_Set *current_state_set = &queue[rear++];

        for (int i = 0; i < current_state_set->count; i++)
        {
            State *current_state = current_state_set->states[i];
            int num_epsilon_states = cal_epsilon_closure(current_state, epsilon_closure);
            for (int j = 0; j < num_epsilon_states; j++)
            {
                if (is_substate(epsilon_closure[j], &epsilon_closure_unique))
                {
                    continue;
                }
                epsilon_closure_unique.states[epsilon_closure_unique.count++] = epsilon_closure[j];
            }
        }

        visited[cur] = epsilon_closure_unique;

        for (int i = 0; i < MAX_SYMBOLS; i++)
        {
            symbols_visited[i] = 0;
        }
        symbols_visited[EPSILON] = 1;

        for (int i = 0; i < epsilon_closure_unique.count; i++)
        {
            State *state = epsilon_closure_unique.states[i];
            for (int j = 0; j < state->num_edges; j++)
            {
                Edge *edge = state->edges[j];
                if (symbols_visited[edge->input_symbol])
                {
                    continue;
                }
                symbols_visited[edge->input_symbol] = 1;

                State_Set next = find_target_stateset(&epsilon_closure_unique, edge->input_symbol);

                int flag = 0;
                for (int k = 0; k < dfa_states.count; k++)
                {
                    if (is_state_subset(&next, &visited[k]))
                    {
                        flag = 1;
                        add_edge(dfa_states.states[cur], create_edge(edge->input_symbol, dfa_states.states[k]));
                        break;
                    }
                }
                if (flag)
                {
                    continue;
                }

                queue[head++] = next;
                dfa_states.states[dfa_states.count++] = create_state(unique_id(), 0);
                add_edge(dfa_states.states[cur], create_edge(edge->input_symbol, dfa_states.states[dfa_states.count - 1]));
            }
        }
        epsilon_closure_unique.count = 0;
        cur++;
    }

    int dfa_end_idx[MAX_STATES];
    int dfa_end_count = 0;
    for (int i = 0; i < cur; i++)
    {
        for (int j = 0; j < visited[i].count; j++)
        {
            if (visited[i].states[j]->is_end)
            {
                dfa_states.states[i]->is_end = 1;
                dfa_end_idx[dfa_end_count++] = i;
                break;
            }
        }
    }

    free(queue);
    destroyNFA(nfa);
    return createDFA(dfa_states.states, 0, dfa_end_idx, dfa_end_count);
}
