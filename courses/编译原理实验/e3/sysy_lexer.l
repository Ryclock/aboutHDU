%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define LEQ  260
#define GEQ  261
#define EQ   262
#define NEQ  263
#define AND  264
#define OR   265

#define KW_CONST      266
#define KW_INT        267
#define KW_FLOAT      268
#define KW_VOID       269
#define KW_IF         270
#define KW_ELSE       271
#define KW_WHILE      272
#define KW_BREAK      273
#define KW_CONTINUE   274
#define KW_RETURN     275

#define IDENTIFIER    276
#define INT_CONST     277
#define FLOAT_CONST   278

#define MAX_TOKENS 1000

struct Token {
    char type[20];
    char value[100];
};

struct Token token_list[MAX_TOKENS];
int token_count = 0;
int error_flag = 0;

int add_token(const char* type, const char* value) {
    if (token_count >= MAX_TOKENS) {
        error_flag=1;
        fprintf(stderr, "Error: Too many tokens\n");
        return 1;
    }
    strcpy(token_list[token_count].type, type);
    strcpy(token_list[token_count].value, value);
    token_count++;
    return 0;
}
%}

%option yylineno

%{
struct {
    int int_val;
    float float_val;
    char* str_val;
} yylval;
%}

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

"+"     { add_token("OPERATOR", "+"); return '+'; }
"-"     { add_token("OPERATOR", "-"); return '-'; }
"*"     { add_token("OPERATOR", "*"); return '*'; }
"/"     { add_token("OPERATOR", "/"); return '/'; }
"%"     { add_token("OPERATOR", "%"); return '%'; }
"="     { add_token("OPERATOR", "="); return '='; }

"<"     { add_token("OPERATOR", "<"); return '<'; }
">"     { add_token("OPERATOR", ">"); return '>'; }
"<="    { add_token("OPERATOR", "<="); return LEQ; }
">="    { add_token("OPERATOR", ">="); return GEQ; }
"=="    { add_token("OPERATOR", "=="); return EQ; }
"!="    { add_token("OPERATOR", "!="); return NEQ; }

"&&"    { add_token("OPERATOR", "&&"); return AND; }
"||"    { add_token("OPERATOR", "||"); return OR; }

"!"     { add_token("OPERATOR", "!"); return '!'; }

"{"     { add_token("DELIMITER", "{"); return '{'; }
"}"     { add_token("DELIMITER", "}"); return '}'; }
"("     { add_token("DELIMITER", "("); return '('; }
")"     { add_token("DELIMITER", ")"); return ')'; }
"["     { add_token("DELIMITER", "["); return '['; }
"]"     { add_token("DELIMITER", "]"); return ']'; }
";"     { add_token("DELIMITER", ";"); return ';'; }
","     { add_token("DELIMITER", ","); return ','; }

[0-9]*"."[0-9]+|[0-9]+"."[0-9]* { yylval.float_val = atof(yytext); add_token("FLOAT_CONST", yytext); return FLOAT_CONST; }

{HEX_PREFIX} {
    char* endptr;
    yylval.int_val = strtol(yytext, &endptr, 16);
    if ('\0' != *endptr || yylval.int_val <= INT_MIN || yylval.int_val >= INT_MAX) {
        error_flag=1;
        fprintf(stderr, "Error type A at line %d: Illegal hexadecimal number \"%s\"\n", yylineno, yytext);
        return 1;
    }
    char int_str[20];
    sprintf(int_str, "%d", yylval.int_val);
    add_token("INT_CONST", int_str);
    return INT_CONST;
}

{OCT_PREFIX} {
    char* endptr;
    yylval.int_val = strtol(yytext, &endptr, 8);
    if ('\0' != *endptr || yylval.int_val <= INT_MIN || yylval.int_val >= INT_MAX) {
        error_flag=1;
        fprintf(stderr, "Error type A at line %d: Illegal octal number \"%s\"\n", yylineno, yytext);
        return 1;
    }
    char int_str[20];
    sprintf(int_str, "%d", yylval.int_val);
    add_token("INT_CONST", int_str);
    return INT_CONST;
}

[0-9]+          { yylval.int_val = atoi(yytext); add_token("INT_CONST", yytext); return INT_CONST; }

"const"     { add_token("KEYWORD_CONST", "const"); return KW_CONST; }
"int"       { add_token("KEYWORD_INT", "int"); return KW_INT; }
"float"     { add_token("KEYWORD_FLOAT", "float"); return KW_FLOAT; }
"void"      { add_token("KEYWORD_VOID", "void"); return KW_VOID; }
"if"        { add_token("KEYWORD_IF", "if"); return KW_IF; }
"else"      { add_token("KEYWORD_ELSE", "else"); return KW_ELSE; }
"while"     { add_token("KEYWORD_WHILE", "while"); return KW_WHILE; }
"break"     { add_token("KEYWORD_BREAK", "break"); return KW_BREAK; }
"continue"  { add_token("KEYWORD_CONTINUE", "continue"); return KW_CONTINUE; }
"return"    { add_token("KEYWORD_RETURN", "return"); return KW_RETURN; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str_val = strdup(yytext);
    add_token("IDENTIFIER", yytext);
    return IDENTIFIER;
}

[ \t\n]  ; // Skip whitespaces

.       {error_flag=1; fprintf(stderr, "Error type A at line %d: Invalid characters \"%s\"\n", yylineno, yytext); return 1; }

%%

int yywrap() {
    return 1;
}

int main(int argc, char** argv) {
    if(argc <2){
        yylex();
        return 0;
    }
    for(int i=1;i<argc;i++){
        FILE*fp=fopen(argv[i],"r");
        if(!fp){
            perror(argv[i]);
            return 1;
        }
        printf("---START %s---\n",argv[i]);
        YY_BUFFER_STATE buf=yy_create_buffer(fp,YY_BUF_SIZE);
        yy_switch_to_buffer(buf);
        yyrestart(fp);
        yylineno=1;
        yy_flush_buffer(buf);
        error_flag = 0;
        token_count = 0;
        while(0!=yylex());
        yy_delete_buffer(buf);
        fclose(fp);
        if (0!=error_flag) {
            printf("---END %s---\n",argv[i]);
            continue;
        }
        printf("token_count: %d\n",token_count);
        for (int j = 0; j < token_count; j++) {
            printf("<%s, %s>\n", token_list[j].type, token_list[j].value);
        }
        printf("---END %s---\n",argv[i]);
    }
    return 0;
}
