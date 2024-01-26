#ifndef __RE_TO_NFA_H
#define __RE_TO_NFA_H
#define MAX_BUF 255
#include "NFA.h"

void infix2post(char *infix, char *postfix);
NFA construct_NFA_from_regex(char *);

#endif