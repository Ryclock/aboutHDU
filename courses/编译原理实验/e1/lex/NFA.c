#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "NFA.h"

NFA createNFA(State *start_state, State **end_states, int num_end_state)
{
    NFA nfa;
    nfa.start_state = start_state;
    nfa.num_end_state = num_end_state;
    for (int i = 0; i < num_end_state; i++)
    {
        nfa.end_states[i] = end_states[i];
    }
    return nfa;
}

NFA createNFA_single_char(char c)
{
    State *start_state = create_state(unique_id(), 0);
    State *end_state = create_state(unique_id(), 1);
    add_edge(start_state, create_edge(c, end_state));

    State *end_states[1] = {end_state};
    return createNFA(start_state, end_states, 1);
}

NFA createNFA_concat(NFA *nfa1, NFA *nfa2)
{
    State *new_start_state = create_state(unique_id(), 0);
    State *new_end_state = create_state(unique_id(), 1);
    add_edge(new_start_state, create_edge(EPSILON, nfa1->start_state));

    for (int i = 0; i < nfa1->num_end_state; i++)
    {
        add_edge(nfa1->end_states[i], create_edge(EPSILON, nfa2->start_state));
        set_end_state(nfa1->end_states[i], 0);
    }
    nfa1->num_end_state = 0;

    for (int i = 0; i < nfa2->num_end_state; i++)
    {
        add_edge(nfa2->end_states[i], create_edge(EPSILON, new_end_state));
        set_end_state(nfa2->end_states[i], 0);
    }
    nfa2->num_end_state = 0;

    return createNFA(new_start_state, &new_end_state, 1);
}

NFA createNFA_union(NFA *nfa1, NFA *nfa2)
{
    State *new_start_state = create_state(unique_id(), 0);
    State *new_end_state = create_state(unique_id(), 1);
    add_edge(new_start_state, create_edge(EPSILON, nfa1->start_state));
    add_edge(new_start_state, create_edge(EPSILON, nfa2->start_state));

    for (int i = 0; i < nfa1->num_end_state; i++)
    {
        add_edge(nfa1->end_states[i], create_edge(EPSILON, new_end_state));
        set_end_state(nfa1->end_states[i], 0);
    }
    nfa1->num_end_state = 0;

    for (int i = 0; i < nfa2->num_end_state; i++)
    {
        add_edge(nfa2->end_states[i], create_edge(EPSILON, new_end_state));
        set_end_state(nfa2->end_states[i], 0);
    }
    nfa2->num_end_state = 0;

    return createNFA(new_start_state, &new_end_state, 1);
}

NFA createNFA_Kleene_star(NFA *nfa)
{
    State *new_start_state = create_state(unique_id(), 0);
    State *new_end_state = create_state(unique_id(), 1);
    add_edge(new_start_state, create_edge(EPSILON, nfa->start_state));
    add_edge(new_start_state, create_edge(EPSILON, new_end_state));

    for (int i = 0; i < nfa->num_end_state; i++)
    {
        add_edge(nfa->end_states[i], create_edge(EPSILON, nfa->start_state));
        add_edge(nfa->end_states[i], create_edge(EPSILON, new_end_state));
        set_end_state(nfa->end_states[i], 0);
    }
    nfa->num_end_state = 0;

    return createNFA(new_start_state, &new_end_state, 1);
}

void set_start_state(NFA *nfa, State *start_state)
{
    nfa->start_state = start_state;
}

State *get_start_state(NFA *nfa)
{
    return nfa->start_state;
}

State **get_end_states(NFA *nfa)
{
    return nfa->end_states;
}

int get_num_end_state(NFA *nfa)
{
    return nfa->num_end_state;
}

void printNFA(NFA *nfa, int is_nfa)
{
    if (!nfa)
    {
        printf("NFA is NULL\n");
        return;
    }
    if (is_nfa)
    {
        printf("Non-Deterministic Finite Automaton (NFA):\n");
    }
    else
    {
        printf("Deterministic Finite Automaton (DFA):\n");
    }

    State *start_state = nfa->start_state;
    if (!start_state)
    {
        printf("Start state is NULL\n");
        return;
    }

    State **stack = (State **)malloc(sizeof(State *) * MAX_STATES);
    int top = -1;

    stack[++top] = start_state;

    int *visited = (int *)malloc(sizeof(int) * MAX_STATES);
    for (int i = 0; i < MAX_STATES; i++)
    {
        visited[i] = 0;
    }

    while (top >= 0)
    {
        State *current_state = stack[top--];

        if (visited[current_state->id])
        {
            continue;
        }

        visited[current_state->id] = 1;
        print_state(current_state);
        printf("\n");

        for (int i = 0; i < current_state->num_edges; i++)
        {
            State *target_state = current_state->edges[i]->target_state;
            if (visited[target_state->id])
            {
                continue;
            }
            stack[++top] = target_state;
        }
    }

    free(stack);
    free(visited);
}

void saveNFA2graphviz(NFA *nfa, const char *filename, const char *digraph_name)
{
    if (!nfa)
    {
        printf("NFA is NULL\n");
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    fprintf(file, "digraph %s {\n", digraph_name);

    State **stack = (State **)malloc(sizeof(State *) * MAX_STATES);
    int top = -1;

    stack[++top] = nfa->start_state;

    int *visited = (int *)malloc(sizeof(int) * MAX_STATES);
    for (int i = 0; i < MAX_STATES; i++)
    {
        visited[i] = 0;
    }

    while (top >= 0)
    {
        State *current_state = stack[top--];

        if (visited[current_state->id])
        {
            continue;
        }

        visited[current_state->id] = 1;

        fprintf(file, "  %d [shape=circle", current_state->id);
        if (current_state->is_end)
        {
            fprintf(file, ", peripheries=2");
        }
        fprintf(file, "];\n");

        for (int i = 0; i < current_state->num_edges; i++)
        {
            State *target_state = current_state->edges[i]->target_state;
            fprintf(file, "  %d -> %d [label=\"%c\"];\n", current_state->id, target_state->id, current_state->edges[i]->input_symbol);
            if (visited[target_state->id])
            {
                continue;
            }
            stack[++top] = target_state;
        }
    }

    fprintf(file, "}\n");
    fclose(file);

    free(stack);
    free(visited);
}

void destroyNFA(NFA *nfa)
{
    reset_id();
    if (!nfa)
    {
        return;
    }

    State **stack = (State **)malloc(sizeof(State *) * MAX_STATES);
    int top = -1;

    stack[++top] = nfa->start_state;

    int *visited = (int *)malloc(sizeof(int) * MAX_STATES);
    for (int i = 0; i < MAX_STATES; i++)
    {
        visited[i] = 0;
    }

    while (top >= 0)
    {
        State *current_state = stack[top--];

        if (visited[current_state->id])
        {
            continue;
        }

        visited[current_state->id] = 1;

        for (int i = 0; i < current_state->num_edges; i++)
        {
            State *target_state = current_state->edges[i]->target_state;
            if (target_state->id < global_id_counter && !visited[target_state->id])
            {
                stack[++top] = target_state;
            }
        }

        destroy_state(current_state);
    }

    free(stack);
    free(visited);
}
