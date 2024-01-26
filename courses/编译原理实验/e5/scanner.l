%{
#include "y.tab.h"
#include "config.h"
int cur_line = 1;
void yyerror(const char *msg);
extern int error_flag;
void unrecognized_char(char*comment, char *str);
%}

identifier {identifier-nondigit}({identifier-nondigit}|{identifier-digit})*
identifier-digit [0-9]
identifier-nondigit [_a-zA-Z]
br [ \t]+
hex_number      0(x|X)[0-9a-zA-Z]+
oct_number      0[0-9]+

%%
{br} { ; }
"/\*" {
    char curr, prev;
    prev = '\0';
    curr = input();
    while(prev != '*' || curr != '/') {
        prev = curr;
        curr = input();
        if (curr == '\n') ++yylineno;
    }
}
"//" {
    char curr;
    curr = input();
    while(curr != '\n') curr = input();
}

"int" { return INT; }
"float" { return FLOAT; }
"void" { return VOID; }

"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"break"  { return BREAK; }
"return" { return RETURN; }
"continue" { return CONTINUE; }

"const" { return CONST; }

"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"%" { return '%'; }

"!" { return '!'; }

"," { return ','; }
"=" { return '='; }
";" { return ';'; }

">=" { return GE; }
"<=" { return LE; }
"==" { return EQ; }
"!=" { return NE; }
">" { return '>'; }
"<" { return '<'; }

"||" { return OR; }
"&&" { return AND; }

"(" { return '('; }
")" { return ')'; }
"[" { return '['; }
"]" { return ']'; }
"{" { return '{'; }
"}" { return '}'; }

{hex_number} {
    char* endptr;
    yylval.ival = strtol(yytext, &endptr, 16);
    if ('\0' != *endptr) {
        unrecognized_char("Illegal hexadecimal number",yytext);
    }
    return INTVAL;
}

{oct_number} {
    char* endptr;
    yylval.ival = strtol(yytext, &endptr, 8);
    if ('\0' != *endptr) {
        unrecognized_char("Illegal octal number",yytext);
    }
    return INTVAL;
}

{identifier} {yylval.str = strdup(yytext);return IDENTIFIER;}
[0-9]+ {yylval.ival=atoi(yytext); return INTVAL;}
[0-9]+\.[0-9]+ {yylval.dval=atof(yytext); return FLOATVAL;}
[0-9]+\. {yylval.dval=atof(yytext); return FLOATVAL;}
\n { ++yylineno; }

. { unrecognized_char("Unrecognized character", yytext); }

%%

int yywrap() {
    return 1;
}
void unrecognized_char(char*comment, char *str) {
    char buf[125];
    error_flag=1;
    sprintf(buf, "%s %s", comment,str);
    printf(LOGGING_FORMAT, "A", buf, yylineno);
}
