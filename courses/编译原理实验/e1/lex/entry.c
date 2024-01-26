#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "re2NFA.h"
#include "NFA2DFA.h"

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
        printf("  --regex <regex> [--dfa] [--print | --graphviz]\n");
        printf("  --help\n");
        return 0;
    }

    if (argc >= 3 && 0 == strcmp(argv[1], "--regex"))
    {
        NFA nfa = construct_NFA_from_regex(argv[2]);

        if (argc >= 4 && 0 == strcmp(argv[3], "--dfa"))
        {
            DFA dfa = convert_NFA_to_DFA(&nfa);
            if (4 == argc || 0 == strcmp(argv[4], "--print"))
            {
                printDFA(&dfa);
                destroyDFA(&dfa);
                return 0;
            }

            if (0 == strcmp(argv[4], "--graphviz"))
            {
                char *filename = (argc >= 6) ? argv[5] : "output.dot";
                saveNFA2graphviz(&dfa, filename, "DFA");
                destroyNFA(&dfa);
                return 0;
            }
        }
        else
        {
            if (3 == argc || 0 == strcmp(argv[3], "--print"))
            {
                printNFA(&nfa, 1);
                destroyNFA(&nfa);
                return 0;
            }

            if (0 == strcmp(argv[3], "--graphviz"))
            {
                char *filename = (argc >= 5) ? argv[4] : "output.dot";
                saveNFA2graphviz(&nfa, filename, "NFA");
                destroyNFA(&nfa);
                return 0;
            }
        }
    }

    printf("Invalid parameter. Please use --help for assistance.\n");
    return 1;
}
