%{
#include "y.tab.h"
extern int error_flag;
%}

%option yylineno

HEX_PREFIX      0(x|X)[0-9a-zA-Z]+
OCT_PREFIX      0[0-9]+

%%
"/*" {
    char pre='\0';
    char cur=input();
    while (pre != '*' || cur != '/') {
        pre=cur; cur=input();
    }
}

"//" {
    char c = input();
    while (c != '\n') {
        c = input();
    }
}
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
"%"     { return '%'; }
"="     { return '='; }

"<"     { return '<'; }
">"     { return '>'; }
"<="    { return LEQ; }
">="    { return GEQ; }
"=="    { return EQ; }
"!="    { return NEQ; }

"&&"    { return AND; }
"||"    { return OR; }

"!"     { return '!'; }

"{"     { return '{'; }
"}"     { return '}'; }
"("     { return '('; }
")"     { return ')'; }
"["     { return '['; }
"]"     { return ']'; }
";"     { return ';'; }
","     { return ','; }

[0-9]*"."[0-9]+|[0-9]+"."[0-9]* { yylval.float_val = atof(yytext); return FLOAT_CONST; }

{HEX_PREFIX} {
    char* endptr;
    yylval.int_val = strtol(yytext, &endptr, 16);
    if ('\0' != *endptr || yylval.int_val <= INT_MIN || yylval.int_val >= INT_MAX) {
        error_flag = 1;
        fprintf(stderr, "Error type A at line %d: Illegal hexadecimal number \"%s\"\n", yylineno, yytext);
    }
    char int_str[20];
    sprintf(int_str, "%d", yylval.int_val);
    return INT_CONST;
}

{OCT_PREFIX} {
    char* endptr;
    yylval.int_val = strtol(yytext, &endptr, 8);
    if ('\0' != *endptr || yylval.int_val <= INT_MIN || yylval.int_val >= INT_MAX) {
        error_flag = 1;
        fprintf(stderr, "Error type A at line %d: Illegal octal number \"%s\"\n", yylineno, yytext);
    }
    char int_str[20];
    sprintf(int_str, "%d", yylval.int_val);
    return INT_CONST;
}

[0-9]+          { yylval.int_val = atoi(yytext); return INT_CONST; }

"const"     { return KW_CONST; }
"int"       { return KW_INT; }
"float"     { return KW_FLOAT; }
"void"      { return KW_VOID; }
"if"        { return KW_IF; }
"else"      { return KW_ELSE; }
"while"     { return KW_WHILE; }
"break"     { return KW_BREAK; }
"continue"  { return KW_CONTINUE; }
"return"    { return KW_RETURN; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str_val = strdup(yytext);
    return IDENTIFIER;
}

[ \t\n]  ; // Skip whitespaces

.       {error_flag = 1; fprintf(stderr, "Error type A at line %d: Invalid characters \"%s\"\n", yylineno, yytext);}

%%

int yywrap() {
    return 1;
}
