#include <stdio.h>
#include <stdlib.h>
#include "state.h"

State *create_state(int id, int is_end)
{
    State *state = (State *)malloc(sizeof(State));
    state->id = id;
    state->is_end = is_end;
    state->num_edges = 0;
    return state;
}

void add_edge(State *state, Edge *edge)
{
    state->edges[(state->num_edges)++] = edge;
}

void set_end_state(State *state, int is_end)
{
    state->is_end = is_end;
}

int is_end_state(State *state)
{
    return state->is_end;
}

void print_state(State *state)
{
    if (!state)
    {
        printf("State is NULL\n");
        return;
    }

    printf("State ID: %d\n", state->id);
    printf("Is End State: %d\n", state->is_end);
    printf("Edge Number: %d\n", state->num_edges);

    for (int i = 0; i < state->num_edges; i++)
    {
        printf("Edge %d:\n", i + 1);
        print_edge(state->edges[i]);
    }
}

void destroy_state(State *state)
{
    if (!state)
    {
        return;
    }
    for (int i = 0; i < state->num_edges; i++)
    {
        destroy_edge(state->edges[i]);
        state->edges[i] = NULL;
    }
    free(state);
}

Edge *create_edge(char input_symbol, State *target_state)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->input_symbol = input_symbol;
    edge->target_state = target_state;
    return edge;
}

void set_target_state(Edge *edge, State *target_state)
{
    edge->target_state = target_state;
}

State *get_target_state(Edge *edge)
{
    return edge->target_state;
}

char get_input_symbol(Edge *edge)
{
    return edge->input_symbol;
}

void print_edge(Edge *edge)
{
    if (!edge)
    {
        printf("Edge is NULL\n");
        return;
    }

    printf("Input Symbol: %c\n", edge->input_symbol);
    printf("Target State ID: %d\n", edge->target_state->id);
}

void destroy_edge(Edge *edge)
{
    if (!edge)
    {
        return;
    }
    free(edge);
}
