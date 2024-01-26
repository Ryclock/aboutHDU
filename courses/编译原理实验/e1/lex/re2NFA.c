#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "re2NFA.h"

int get_priority(char operator)
{
    if ('*' == operator|| '+' == operator)
    {
        return 3;
    }

    if ('&' == operator)
    {
        return 2;
    }

    if ('|' == operator)
    {
        return 1;
    }
    return 0;
}

int is_operand(char a)
{
    if (a >= '0' && a <= '9')
    {
        return 1;
    }
    if (a >= 'a' && a <= 'z')
    {
        return 1;
    }
    if (a >= 'A' && a <= 'Z')
    {
        return 1;
    }
    return 0;
}

void infix2post(char *infix, char *postfix)
{
    Stack stack;
    init_stack(&stack);

    int j = 0;

    for (int i = 0; '\0' != infix[i]; i++)
    {
        char c = infix[i];

        if ('(' == c)
        {
            push_stack(&stack, c);
            continue;
        }
        else if (')' == c)
        {
            while (!is_stack_empty(&stack) && top_stack(&stack) != '(')
            {
                postfix[j++] = pop_stack(&stack);
            }
            pop_stack(&stack);
        }
        else if ('|' == c || '&' == c)
        {
            while (!is_stack_empty(&stack) && get_priority(top_stack(&stack)) >= get_priority(c))
            {
                postfix[j++] = pop_stack(&stack);
            }
            push_stack(&stack, c);
            continue;
        }
        else
        {
            postfix[j++] = c;
        }

        if ('\0' == infix[i + 1])
        {
            break;
        }

        if ((is_operand(infix[i]) && infix[i + 1] == '(') ||
            (is_operand(infix[i]) && is_operand(infix[i + 1])) ||
            (infix[i] == '*' && is_operand(infix[i + 1])) ||
            (infix[i] == '*' && infix[i + 1] == '(') ||
            (infix[i] == ')' && infix[i + 1] == '('))
        {
            if (is_stack_empty(&stack))
            {
                push_stack(&stack, '&');
                continue;
            }

            char a = top_stack(&stack);
            if (get_priority(a) < get_priority('&'))
            {

                push_stack(&stack, '&');
                continue;
            }

            while (get_priority(a) >= get_priority('&'))
            {
                if ('(' != a)
                {
                    postfix[j++] = a;
                }
                pop_stack(&stack);

                if (is_stack_empty(&stack))
                {
                    break;
                }
                a = top_stack(&stack);
            }
            push_stack(&stack, '&');
        }
    }

    while (!is_stack_empty(&stack))
    {
        postfix[j++] = pop_stack(&stack);
    }

    postfix[j] = '\0';
}

NFA construct_NFA_from_regex(char *regex)
{
    int regex_len = strlen(regex);
    if (regex_len <= 0)
    {
        printf("Invalid regex!\n");
        exit(1);
    }

    char postfix[MAX_BUF + 1];
    infix2post(regex, postfix);

    int postfix_len = strlen(postfix);
    int state = 0;
    NFA stack[MAX_BUF];
    int stack_top = -1;

    for (int i = 0; i < postfix_len; i++)
    {
        char c = postfix[i];

        if (is_operand(c))
        {
            NFA nfa = createNFA_single_char(c);
            stack[++stack_top] = nfa;
            continue;
        }

        if ('|' == c)
        {
            NFA nfa2 = stack[stack_top--];
            NFA nfa1 = stack[stack_top--];
            NFA nfa = createNFA_union(&nfa1, &nfa2);
            stack[++stack_top] = nfa;
            continue;
        }

        if ('&' == c)
        {
            NFA nfa2 = stack[stack_top--];
            NFA nfa1 = stack[stack_top--];
            NFA nfa = createNFA_concat(&nfa1, &nfa2);
            stack[++stack_top] = nfa;
            continue;
        }

        if ('*' == c)
        {
            NFA nfa1 = stack[stack_top--];
            NFA nfa = createNFA_Kleene_star(&nfa1);
            stack[++stack_top] = nfa;
            continue;
        }
    }

    return stack[stack_top];
}
