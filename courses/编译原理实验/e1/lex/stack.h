#ifndef _MY_STACK_H
#define _MY_STACK_H

typedef struct Stack
{
    char array[256];
    int top;
} Stack;

void init_stack(Stack *);
int is_stack_empty(Stack *);
void push_stack(Stack *, char);
char pop_stack(Stack *);
char top_stack(Stack *);

#endif
