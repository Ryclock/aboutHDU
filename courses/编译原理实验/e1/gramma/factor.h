#ifndef _FACTOR_H
#define _FACTOR_H

#include "rule.h"

int left_factor_max_length(struct Rule_symbol *);
int need_pickup(struct Rule_symbol *picked_select, int, struct Rule_symbol *select);
void extract_left_factor(struct Rule *);

#endif