#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int unique_id()
{
    return global_id_counter++;
}

void reset_id()
{
    global_id_counter = 0;
}