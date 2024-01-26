#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rule.h"
#include "recursion.h"
#include "factor.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Insufficient arguments. Please use --help for assistance.\n");
        return 1;
    }

    if (0 == strcmp(argv[1], "--help"))
    {
        printf("Usage:\n");
        printf("  --simplify <file>\n");
        printf("  --help\n");
        return 0;
    }

    if (argc >= 3)
    {
        if (0 == strcmp(argv[1], "--simplify"))
        {
            char *filename = argv[2];
            struct Rule *gramma = NULL;
            if (1 == read_rule_from_file(filename, &gramma))
            {
                return 1;
            }
            merge_same_left_hand(gramma);
            produce_non_terminator_table(gramma);

            eliminate_left_recursion(gramma);
            printf("---After Eliminate Left Recursion---\n");
            print_gramma(gramma);

            extract_left_factor(gramma);
            printf("---After Extract Left Factor---\n");
            print_gramma(gramma);

            free_gramma(gramma);
            return 0;
        }
    }

    printf("Invalid parameter. Please use --help for assistance.\n");
    return 1;
}
