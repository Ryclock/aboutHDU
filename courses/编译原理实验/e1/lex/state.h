#ifndef __STATE_H
#define __STATE_H
#define MAX_EDGES 100

typedef struct Edge
{
    char input_symbol;
    struct State *target_state;
} Edge;

typedef struct State
{
    int id;
    int is_end;
    struct Edge *edges[MAX_EDGES];
    int num_edges;
} State;

State *create_state(int id, int is_end);
void add_edge(State *, Edge *);
void set_end_state(State *, int);
int is_end_state(State *);
void print_state(State *);
void destroy_state(State *);

Edge *create_edge(char input_symbol, State *target_state);
void set_target_state(Edge *, State *);
State *get_target_state(Edge *);
char get_input_symbol(Edge *);
void print_edge(Edge *);
void destroy_edge(Edge *);

#endif
