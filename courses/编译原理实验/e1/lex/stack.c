#include <stdlib.h>
#include "stack.h"

void init_stack(Stack *stack)
{
    stack->top = -1;
}

int is_stack_empty(Stack *stack)
{
    return -1 == stack->top;
}

void push_stack(Stack *stack, char operator)
{
    stack->array[++stack->top] = operator;
}

char pop_stack(Stack *stack)
{
    if (!is_stack_empty(stack))
    {
        return stack->array[stack->top--];
    }
    return '\0';
}

char top_stack(Stack *stack)
{
    if (!is_stack_empty(stack))
    {
        return stack->array[stack->top];
    }
    return '\0';
}
