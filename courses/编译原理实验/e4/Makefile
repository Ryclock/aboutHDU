LEX = flex
YACC = bison
CC = gcc
CFLAGS = -Wall -Wextra

all: sysy_parser

sysy_parser: lex.yy.c y.tab.c
	$(CC) $(CFLAGS) -o $@ lex.yy.c y.tab.c

lex.yy.c: sysy_lexer.l
	$(LEX) $^

y.tab.c y.tab.h: sysy_parser.y
	$(YACC) -vdty $^

clean:
	rm -f sysy_parser lex.yy.c y.tab.c y.tab.h y.output
