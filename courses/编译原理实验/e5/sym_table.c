#include "sym_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

struct sym_table *sym_mktable(struct sym_table *prev)
{
    struct sym_table *new_table = malloc(sizeof(struct sym_table));
    new_table->parent = prev;
    new_table->total_elems = 0;
    new_table->width = 0;
    return new_table;
}
void sym_enter(struct sym_table *table, char *name, int type, unsigned int offset)
{
    int ptr = table->total_elems;
    strcpy(table->elem[ptr].name, name);
    table->elem[ptr].type = type;
    table->elem[ptr].offset = offset;
    table->elem[ptr].ptr = NULL;
    table->width += offset;
    table->total_elems++;
}
void sym_enter_proc(struct sym_table *table, char *name, struct sym_table *new_table)
{
    int ptr = table->total_elems;
    strcpy(table->elem[ptr].name, name);
    table->elem[ptr].ptr = new_table;
    table->width += new_table->width;
    table->total_elems++;
}
void sym_free_table(struct sym_table *cur)
{
    for (int i = 0; i < cur->total_elems; i++)
    {
        if (NULL == cur->elem[i].ptr)
        {
            continue;
        }
        sym_free_table(cur->elem[i].ptr);
    }
    cur->parent = NULL;
    free(cur);
}
struct sym_elem *sym_lookup(struct sym_table *table, char *name)
{
    for (int i = 0; i < table->total_elems; i++)
    {
        if (strcmp(table->elem[i].name, name) == 0)
        {
            return &(table->elem[i]);
        }
    }
    if(table->parent){
        return sym_lookup(table->parent,name);
    }
    return NULL;
}
void sym_print_table(struct sym_table *table, int depth)
{
    for (int j = 0; j < depth; j++)
    {
        printf("\t");
    }
    printf("Total Width: %d\n", table->width);
    for (int i = 0; i < table->total_elems; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            printf("\t");
        }
        printf("%s %d %d\n", table->elem[i].name, table->elem[i].type, table->elem[i].offset);
        if (NULL != table->elem[i].ptr)
        {
            sym_print_table(table->elem[i].ptr, depth + 1);
        }
    }
}