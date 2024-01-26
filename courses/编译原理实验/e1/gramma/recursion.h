#ifndef _RECURSION_H
#define _RECURSION_H

#include "rule.h"

struct Replace
{
    int id;
    int cnt;
    struct Rule_symbol **select;
};

char *table;
int table_size;

void merge_same_left_hand(struct Rule *);
void produce_non_terminator_table(struct Rule *);
int get_table_idx(char);
int convert_general_recursion(struct Rule_symbol *, char);
void eliminate_left_recursion(struct Rule *);

#endif