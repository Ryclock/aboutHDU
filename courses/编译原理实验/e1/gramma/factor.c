#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "factor.h"

int left_factor_max_length(struct Rule_symbol *select)
{
    if (!select)
    {
        return 0;
    }

    int max_cnt = 0;
    struct Rule_symbol *cur_select = select->next_select;
    while (cur_select)
    {
        int cnt = 0;
        while (1)
        {
            struct Rule_symbol *cur_symbol = cur_select, *target_symbol = select;
            for (int i = 0; i < cnt; i++)
            {
                if (!cur_symbol || !target_symbol)
                {
                    break;
                }
                cur_symbol = cur_symbol->next_symbol;
                target_symbol = target_symbol->next_symbol;
            }
            if (!cur_symbol || !target_symbol || cur_symbol->name != target_symbol->name)
            {
                break;
            }
            cnt++;
        }
        max_cnt = max_cnt > cnt ? max_cnt : cnt;
        cur_select = cur_select->next_select;
    }

    return max_cnt;
}

int need_pickup(struct Rule_symbol *picked_select, int cnt, struct Rule_symbol *select)
{
    struct Rule_symbol *picked_symbol = picked_select, *cur_symbol = select;
    for (int i = 0; i < cnt; i++)
    {
        if (!picked_symbol || picked_symbol->name != cur_symbol->name)
        {
            return 0;
        }
        picked_symbol = picked_symbol->next_symbol;
        cur_symbol = cur_symbol->next_symbol;
    }
    return 1;
}

void extract_left_factor(struct Rule *gramma)
{
    int is_change = 1;
    while (is_change)
    {
        is_change = 0;
        struct Rule *cur_rule = gramma, *next_rule;
        while (cur_rule)
        {
            next_rule = cur_rule->next_rule;
            int cnt = 0;
            struct Rule_symbol *cur_select = cur_rule->first_symbol;
            while (cur_select)
            {
                if ((cnt = left_factor_max_length(cur_select)) > 0)
                {
                    break;
                }
                cur_select = cur_select->next_select;
            }
            if (0 == cnt)
            {
                cur_rule = next_rule;
                continue;
            }
            int num_prime = cur_rule->num_prime;
            struct Rule *tmp_rul = gramma;
            while (tmp_rul)
            {
                if (tmp_rul->left_hand == cur_rule->left_hand)
                {
                    num_prime = num_prime > tmp_rul->num_prime ? num_prime : tmp_rul->num_prime;
                }
                tmp_rul = tmp_rul->next_rule;
            }
            struct Rule *new_rule = init_rule(cur_rule->left_hand);
            new_rule->num_prime = num_prime + 1;
            struct Rule_symbol *new_symbol = init_symbol(cur_rule->left_hand, 0);
            new_symbol->p_rule = new_rule;
            is_change = 1;
            struct Rule_symbol *last_symbol = cur_select;
            for (int i = 0; i < cnt - 1; i++)
            {
                last_symbol = last_symbol->next_symbol;
            }
            if (!(last_symbol->next_symbol))
            {
                last_symbol->next_symbol = init_symbol(EPSILON, 1);
            }
            struct Rule_symbol *added_select = last_symbol->next_symbol;
            add_select(&(new_rule->first_symbol), added_select);
            last_symbol->next_symbol = new_symbol;
            struct Rule_symbol *later_select = cur_select->next_select, *next_select;
            while (later_select)
            {
                next_select = later_select->next_select;
                if (need_pickup(later_select, cnt, cur_select))
                {
                    struct Rule_symbol *last_symbol = later_select;
                    for (int i = 0; i < cnt - 1; i++)
                    {
                        last_symbol = last_symbol->next_symbol;
                    }
                    if (!(last_symbol->next_symbol))
                    {
                        last_symbol->next_symbol = init_symbol(EPSILON, 1);
                    }
                    struct Rule_symbol *added_select = last_symbol->next_symbol;
                    add_select(&(new_rule->first_symbol), added_select);
                    last_symbol->next_symbol = NULL;
                    delete_select(cur_rule, later_select);
                }
                later_select = next_select;
            }
            new_rule->next_rule = cur_rule->next_rule;
            cur_rule->next_rule = new_rule;
            cur_rule = next_rule;
        }
    }
}