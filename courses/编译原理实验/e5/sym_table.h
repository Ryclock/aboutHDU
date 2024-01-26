#ifndef SYM_TABLE_H
#define SYM_TABLE_H
#include "config.h"

struct sym_elem
{
    char name[MAX_SYMBOL_LENGTH];
    struct sym_table *ptr;
    int type;
    unsigned int offset;
};
struct sym_table
{
    struct sym_table *parent;
    int total_elems;
    unsigned int width;
    struct sym_elem elem[MAX_SYMBOL_TABLE];
};

struct sym_table *sym_mktable(struct sym_table *prev);
void sym_enter(struct sym_table *table, char *name, int type, unsigned int offset);
void sym_enter_proc(struct sym_table *table, char *name, struct sym_table *new_table);
void sym_free_table(struct sym_table *cur);
struct sym_elem *sym_lookup(struct sym_table *table, char *name);
void sym_print_table(struct sym_table *table, int depth);

#endif