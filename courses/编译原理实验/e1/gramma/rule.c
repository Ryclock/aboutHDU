#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rule.h"

struct Rule_symbol *init_symbol(char name, int is_token)
{
    struct Rule_symbol *new_symbol = (struct Rule_symbol *)malloc(sizeof(struct Rule_symbol));
    if (new_symbol == NULL)
    {
        printf("Memory allocation failed for Rule_symbol.\n");
        exit(1);
    }
    new_symbol->name = name;
    new_symbol->is_token = is_token;
    new_symbol->next_symbol = NULL;
    new_symbol->next_select = NULL;
    new_symbol->p_rule = NULL;
    return new_symbol;
}

struct Rule *init_rule(char left_hand)
{
    struct Rule *new_rule = (struct Rule *)malloc(sizeof(struct Rule));
    if (new_rule == NULL)
    {
        printf("Memory allocation failed for Rule.\n");
        exit(1);
    }

    new_rule->left_hand = left_hand;
    new_rule->first_symbol = NULL;
    new_rule->next_rule = NULL;
    new_rule->num_prime = 0;
    return new_rule;
}

void free_symbol(struct Rule_symbol *symbol)
{
    if (symbol == NULL)
    {
        return;
    }
    if (symbol->next_symbol)
    {
        printf("Error free symbol: next symbol is not NULL\n");
        exit(1);
    }

    symbol->p_rule = NULL;
    free(symbol);
}

void free_select(struct Rule_symbol *select)
{
    if (select == NULL)
    {
        return;
    }
    if (select->next_select)
    {
        printf("Error free select: next select is not NULL\n");
        exit(1);
    }

    struct Rule_symbol *cur = select, *next = NULL;
    while (cur)
    {
        next = cur->next_symbol;
        cur->next_symbol = NULL;
        free_symbol(cur);
        cur = next;
    }
    // free(select);
}

void free_rule(struct Rule *rule)
{
    if (rule == NULL)
    {
        return;
    }
    if (rule->next_rule)
    {
        printf("Error free rule: next rule is not NULL\n");
        exit(1);
    }

    struct Rule_symbol *cur = rule->first_symbol, *next = NULL;
    while (cur)
    {
        next = cur->next_select;
        cur->next_select = NULL;
        free_select(cur);
        cur = next;
    }
    rule->first_symbol = NULL;
    free(rule);
}

void free_gramma(struct Rule *gramma)
{
    if (gramma == NULL)
    {
        return;
    }

    struct Rule *cur = gramma, *next = NULL;
    while (cur)
    {
        next = cur->next_rule;
        cur->next_rule = NULL;
        free_rule(cur);
        cur = next;
    }
    // free(gramma);
}

void add_symbol(struct Rule_symbol **cur_p, struct Rule_symbol *symbol)
{
    if (!*cur_p)
    {
        *cur_p = symbol;
        return;
    }
    struct Rule_symbol *cur = *cur_p;
    while (cur->next_symbol)
    {
        cur = cur->next_symbol;
    }
    cur->next_symbol = symbol;
}

void add_select(struct Rule_symbol **cur_p, struct Rule_symbol *select)
{
    if (!*cur_p)
    {
        *cur_p = select;
        return;
    }
    struct Rule_symbol *cur = *cur_p;
    while (cur->next_select)
    {
        cur = cur->next_select;
    }
    cur->next_select = select;
}

void add_rule(struct Rule **cur_p, struct Rule *rule)
{
    if (!*cur_p)
    {
        *cur_p = rule;
        return;
    }
    struct Rule *cur = *cur_p;
    while (cur->next_rule)
    {
        cur = cur->next_rule;
    }
    cur->next_rule = rule;
}

struct Rule_symbol *copy_symbol(struct Rule_symbol *symbol)
{
    struct Rule_symbol *new_symbol = init_symbol(symbol->name, symbol->is_token);
    new_symbol->p_rule = symbol->p_rule;
    return new_symbol;
}

struct Rule_symbol *copy_select(struct Rule_symbol *select)
{
    struct Rule_symbol *new_select = NULL;
    struct Rule_symbol *cur_symbol = select, *new_symbol = NULL;
    while (cur_symbol)
    {
        new_symbol = copy_symbol(cur_symbol);
        add_symbol(&new_select, new_symbol);
        cur_symbol = cur_symbol->next_symbol;
    }
    return new_select;
}

void delete_select(struct Rule *rule, struct Rule_symbol *select)
{
    if (NULL == rule)
    {
        printf("delete owner: rule is null.\n");
        return;
    }
    if (NULL == select)
    {
        printf("delete target: select is null.\n");
        return;
    }

    struct Rule_symbol *cur_select = rule->first_symbol, *pre_select = NULL;
    while (cur_select && cur_select != select)
    {
        pre_select = cur_select;
        cur_select = cur_select->next_select;
    }

    if (NULL == cur_select)
    {
        printf("delete target: select not found.\n");
        return;
    }

    if (NULL == pre_select)
    {
        rule->first_symbol = cur_select->next_select;
    }
    else
    {
        pre_select->next_select = cur_select->next_select;
    }
    cur_select->next_select = NULL;
    free_select(select);
}

void print_symbol(struct Rule_symbol *symbol)
{
    if (symbol == NULL)
    {
        return;
    }
    printf("%c", symbol->name);
    if (symbol->p_rule)
    {
        for (int i = 0; i < symbol->p_rule->num_prime; i++)
        {
            printf("'");
        }
    }
}

void print_select(struct Rule_symbol *select)
{
    if (select == NULL)
    {
        return;
    }

    struct Rule_symbol *cur = select;
    while (cur)
    {
        print_symbol(cur);
        cur = cur->next_symbol;
    }
}

void print_rule(struct Rule *rule)
{
    if (rule == NULL)
    {
        return;
    }
    printf("%c", rule->left_hand);
    for (int i = 0; i < rule->num_prime; i++)
    {
        printf("'");
    }
    printf("->");

    struct Rule_symbol *cur = rule->first_symbol;
    while (cur->next_select)
    {
        print_select(cur);
        printf("|");
        cur = cur->next_select;
    }
    print_select(cur);
}

void print_gramma(struct Rule *gramma)
{
    if (gramma == NULL)
    {
        return;
    }

    struct Rule *cur = gramma;
    while (cur)
    {
        print_rule(cur);
        printf("\n");
        cur = cur->next_rule;
    }
}

int check_duplicate_select(struct Rule *rule, struct Rule_symbol *select)
{
    if (!rule || !(rule->first_symbol) || !select)
    {
        return 1;
    }
    int flag = 0;
    struct Rule_symbol *cur_select = rule->first_symbol;
    struct Rule_symbol *cur_symbol = NULL, *target_symbol = NULL;
    while (cur_select)
    {
        if (cur_select == select)
        {
            cur_select = cur_select->next_select;
            continue;
        }

        flag = 1;
        cur_symbol = cur_select;
        target_symbol = select;
        while (cur_symbol && target_symbol)
        {
            if (cur_symbol->name != target_symbol->name)
            {
                flag = 0;
                break;
            }
            cur_symbol = cur_symbol->next_symbol;
            target_symbol = target_symbol->next_symbol;
        }
        if (cur_symbol || target_symbol)
        {
            flag = 0;
        }
        if (flag)
        {
            break;
        }
        cur_select = cur_select->next_select;
    }
    return flag;
}

void sync_rule_pointer(struct Rule *gramma)
{
    struct Rule *cur_rule = gramma;
    while (cur_rule)
    {
        struct Rule_symbol *cur_select = cur_rule->first_symbol;
        while (cur_select)
        {
            struct Rule_symbol *cur_symbol = cur_select;
            while (cur_symbol)
            {
                if (1 == cur_symbol->is_token)
                {
                    cur_symbol = cur_symbol->next_symbol;
                    continue;
                }
                int flag = 0;
                struct Rule *cur_rule_to_search = gramma;
                while (cur_rule_to_search)
                {
                    if (cur_rule_to_search->left_hand == cur_symbol->name)
                    {
                        cur_symbol->p_rule = cur_rule_to_search;
                        flag = 1;
                    }
                    cur_rule_to_search = cur_rule_to_search->next_rule;
                }
                if (0 == flag)
                {
                    printf("non-terminator %c mismatch.\n", cur_symbol->name);
                    exit(1);
                }
                cur_symbol = cur_symbol->next_symbol;
            }
            cur_select = cur_select->next_select;
        }
        cur_rule = cur_rule->next_rule;
    }
}

int read_rule_from_file(const char *filename, struct Rule **gramma_p)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening the file");
        return 1;
    }

    int line = 0;
    char input[1024];
    while (fgets(input, sizeof(input), file))
    {
        line++;
        char *left_hand = strtok(input, "-\n");
        if (!left_hand)
        {
            printf("Line %d: invalid gramma rule of left part \"%s\"\n", line, left_hand);
            continue;
        }
        int i = 0;
        while (' ' == left_hand[i])
        {
            i++;
        }
        if ('\0' == left_hand[i])
        {
            printf("Line %d: invalid gramma rule of left part \"%s\"\n", line, left_hand);
            continue;
        }
        struct Rule *rule = init_rule(left_hand[i]);

        char *right_hand = strtok(NULL, ">\n");
        if (!right_hand)
        {
            printf("Line %d: invalid gramma rule of right part \"%s\"\n", line, right_hand);
            continue;
        }

        struct Rule_symbol *first_select = NULL;
        struct Rule_symbol *first_symbol = NULL;

        char *token = strtok(right_hand, "|\n");
        while (token != NULL)
        {
            for (int i = 0; token[i] != '\0'; i++)
            {
                struct Rule_symbol *symbol;

                if (' ' == token[i])
                {
                    continue;
                }

                if ('\'' == token[i] && '\0' != token[i + 1] && '\'' == token[i + 2])
                {
                    symbol = init_symbol(token[i + 1], 1);
                    i = i + 2;
                }

                if ('A' <= token[i] && 'Z' >= token[i])
                {
                    symbol = init_symbol(token[i], 0);
                }
                else
                {
                    symbol = init_symbol(token[i], 1);
                }
                add_symbol(&first_symbol, symbol);
            }
            add_select(&first_select, first_symbol);
            token = strtok(NULL, "|\n");
            first_symbol = NULL;
        }

        rule->first_symbol = first_select;
        add_rule(gramma_p, rule);
        first_select = NULL;
    }

    fclose(file);
    return 0;
}
