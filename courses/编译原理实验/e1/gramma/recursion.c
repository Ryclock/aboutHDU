#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "recursion.h"

void merge_same_left_hand(struct Rule *gramma)
{
    struct Rule *merger = gramma;
    while (merger)
    {
        char left_hand_to_merge = merger->left_hand;
        struct Rule *cur = merger->next_rule;
        struct Rule *pre = merger;
        while (cur)
        {
            if (cur->left_hand != left_hand_to_merge)
            {
                pre = cur;
                cur = cur->next_rule;
                continue;
            }
            struct Rule_symbol *cur_select = cur->first_symbol, *next_select = NULL;
            while (cur_select)
            {
                next_select = cur_select->next_select;
                cur_select->next_select = NULL;
                if (0 == check_duplicate_select(merger, cur_select))
                {
                    add_select(&(merger->first_symbol), cur_select);
                }
                cur_select = next_select;
            }
            struct Rule *next = cur->next_rule;
            cur->first_symbol = NULL;
            cur->next_rule = NULL;
            free_rule(cur);
            pre->next_rule = next;
            cur = next;
        }
        merger = merger->next_rule;
    }
}

void produce_non_terminator_table(struct Rule *gramma)
{
    table_size = 0;
    table = NULL;
    if (gramma == NULL)
    {
        printf("gramma is null, stop produce non-terminal table.\n");
        return;
    }
    struct Rule *cur = gramma;
    while (cur)
    {
        table_size++;
        cur = cur->next_rule;
    }
    table = (char *)malloc(table_size * sizeof(char));
    int i = 0;
    cur = gramma;
    while (cur)
    {
        table[i++] = cur->left_hand;
        cur = cur->next_rule;
    }
}

int get_table_idx(char non_terminator)
{
    if (table == NULL)
    {
        printf("table is null, stop get idx.\n");
        return -1;
    }
    for (int i = 0; i < table_size; i++)
    {
        if (table[i] == non_terminator)
        {
            return i;
        }
    }
    return -1;
}

int convert_general_recursion(struct Rule_symbol *cur_select, char left_hand)
{
    if (cur_select == NULL)
    {
        printf("cur_select is null, stop convert general recursion.\n");
        return 1;
    }

    struct Replace **replace = (struct Replace **)malloc(sizeof(struct Replace *));
    int size = 0;
    struct Rule_symbol *cur_symbol = cur_select;
    int id = 0;
    int new_cnt = 1;
    while (cur_symbol)
    {
        if (NULL == cur_symbol->p_rule)
        {
            id++;
            cur_symbol = cur_symbol->next_symbol;
            continue;
        }
        int table_idx = get_table_idx(cur_symbol->name);
        if (table_idx == -1)
        {
            printf("table not found non_terminator: %c\n", cur_symbol->name);
            free(replace);
            return 1;
        }
        if (table_idx >= get_table_idx(left_hand))
        {
            id++;
            cur_symbol = cur_symbol->next_symbol;
            continue;
        }

        replace[size++] = (struct Replace *)malloc(sizeof(struct Replace));
        replace[size - 1]->id = id;
        replace[size - 1]->cnt = 0;
        replace[size - 1]->select = (struct Rule_symbol **)malloc(sizeof(struct Rule_symbol *));
        struct Rule_symbol *target_select = cur_symbol->p_rule->first_symbol;
        while (target_select)
        {
            replace[size - 1]->select[(replace[size - 1]->cnt)++] = target_select;
            target_select = target_select->next_select;
        }
        if (0 == replace[size - 1]->cnt)
        {
            replace[size - 1]->select = NULL;
            free(replace[size - 1]);
            size--;
            id++;
            cur_symbol = cur_symbol->next_symbol;
            continue;
        }
        new_cnt *= replace[size - 1]->cnt;
        id++;
        cur_symbol = cur_symbol->next_symbol;
    }

    if (0 == size)
    {
        free(replace);
        return 1;
    }

    struct Rule_symbol *new_select_list[new_cnt];
    for (int i = 0; i < new_cnt; i++)
    {
        new_select_list[i] = NULL;
    }

    int size_i = 0;
    cur_symbol = cur_select;
    id = 0;
    while (cur_symbol)
    {
        if (size_i < size && id == replace[size_i]->id)
        {
            for (int i = 0; i < new_cnt; i++)
            {
                struct Rule_symbol *new_select = copy_select(replace[size_i]->select[i % (replace[size_i]->cnt)]);
                if (NULL == new_select)
                {
                    printf("copy symbol or select error\n");
                    exit(1);
                }
                add_symbol(&(new_select_list[i]), new_select);
            }
            size_i++;
        }
        else
        {
            for (int i = 0; i < new_cnt; i++)
            {
                struct Rule_symbol *new_symbol = copy_symbol(cur_symbol);
                if (NULL == new_symbol)
                {
                    printf("copy symbol error\n");
                    exit(1);
                }
                add_symbol(&(new_select_list[i]), new_symbol);
            }
        }
        id++;
        cur_symbol = cur_symbol->next_symbol;
    }

    for (int i = 0; i < size; i++)
    {
        replace[i]->select = NULL;
        free(replace[i]);
        replace[i] = NULL;
    }
    free(replace);
    replace = NULL;

    for (int i = 0; i < new_cnt; i++)
    {
        new_select_list[i]->next_select = cur_select->next_select;
        cur_select->next_select = new_select_list[i];
    }
    return 0;
}

void eliminate_left_recursion(struct Rule *gramma)
{
    sync_rule_pointer(gramma);
    struct Rule *cur_rule = gramma, *next_rule;
    while (cur_rule)
    {
        next_rule = cur_rule->next_rule;
        if (cur_rule != gramma)
        {
            struct Rule_symbol *cur_select = cur_rule->first_symbol, *next_select;
            while (cur_select)
            {
                next_select = cur_select->next_select;
                if (0 == convert_general_recursion(cur_select, cur_rule->left_hand))
                {
                    struct Rule_symbol *tmp_select = cur_select->next_select, *tmp_next_select;
                    delete_select(cur_rule, cur_select);
                    while (tmp_select)
                    {
                        tmp_next_select = tmp_select->next_select;
                        if (1 == check_duplicate_select(cur_rule, tmp_select))
                        {
                            delete_select(cur_rule, tmp_select);
                        }
                        tmp_select = tmp_next_select;
                    }
                }
                cur_select = next_select;
            }
        }
        struct Rule_symbol **alpha = (struct Rule_symbol **)malloc(sizeof(struct Rule_symbol *));
        int size_alpha = 0;
        struct Rule_symbol *cur_select = cur_rule->first_symbol, *next_select;
        while (cur_select)
        {
            next_select = cur_select->next_select;
            struct Rule_symbol *first_symbol = cur_select;
            if (first_symbol->name == cur_rule->left_hand)
            {
                alpha[size_alpha++] = copy_select(first_symbol->next_symbol);
                delete_select(cur_rule, cur_select);
            }
            cur_select = next_select;
        }

        if (size_alpha > 0)
        {
            struct Rule *new_rule = init_rule(cur_rule->left_hand);
            (new_rule->num_prime)++;
            struct Rule_symbol *new_symbol = init_symbol(cur_rule->left_hand, 0);
            new_symbol->p_rule = new_rule;
            struct Rule_symbol *cur_select = cur_rule->first_symbol;
            while (cur_select)
            {
                add_symbol(&(cur_select), copy_symbol(new_symbol));
                cur_select = cur_select->next_select;
            }
            for (int i = 0; i < size_alpha; i++)
            {
                add_symbol(&(alpha[i]), copy_symbol(new_symbol));
                add_select(&(new_rule->first_symbol), alpha[i]);
            }
            new_symbol->p_rule = NULL;
            new_symbol->is_token = 1;
            new_symbol->name = EPSILON;
            struct Rule_symbol *new_select = NULL;
            add_symbol(&new_select, new_symbol);
            add_select(&(new_rule->first_symbol), new_select);
            new_rule->next_rule = cur_rule->next_rule;
            cur_rule->next_rule = new_rule;
        }
        cur_rule = next_rule;
    }
}