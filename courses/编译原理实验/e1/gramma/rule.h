#ifndef _RULE_H
#define _RULE_H

struct Rule
{
    char left_hand;
    struct Rule_symbol *first_symbol;
    struct Rule *next_rule;
    int num_prime;
};

struct Rule_symbol
{
    struct Rule_symbol *next_symbol;
    struct Rule_symbol *next_select;
    int is_token;
    char name;
    struct Rule *p_rule;
};

/* INIT */
struct Rule_symbol *init_symbol(char, int);
struct Rule *init_rule(char);

/* FREE */
void free_symbol(struct Rule_symbol *);
void free_select(struct Rule_symbol *);
void free_rule(struct Rule *);
void free_gramma(struct Rule *);

/* ADD */
void add_symbol(struct Rule_symbol **, struct Rule_symbol *);
void add_select(struct Rule_symbol **, struct Rule_symbol *);
void add_rule(struct Rule **, struct Rule *);

/* COPY */
struct Rule_symbol *copy_symbol(struct Rule_symbol *);
struct Rule_symbol *copy_select(struct Rule_symbol *);

/* DELETE */
void delete_select(struct Rule *, struct Rule_symbol *);

/* PRINT */
void print_symbol(struct Rule_symbol *);
void print_select(struct Rule_symbol *);
void print_rule(struct Rule *);
void print_gramma(struct Rule *);

/* OTHERS */
int check_duplicate_select(struct Rule *, struct Rule_symbol *);
void sync_rule_pointer(struct Rule *);
int read_rule_from_file(const char *, struct Rule **);

#endif