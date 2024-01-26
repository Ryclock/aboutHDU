%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logging.h"
#include "sym_table.h"

#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_STRING 3

// int yydebug=1;
void yyerror(const char*);
extern int yylineno;
int error_flag=0;

unsigned int unque_name=0;
char name_buf[MAX_SYMBOL_TABLE];
char msg_buf[512];

struct sym_table* global_table[20];
int total_tables = 0;
#define TOP_TABLE (global_table[total_tables-1])
#define PARENT_TABLE (global_table[total_tables-2])

int check_not_duplicate(char *name,struct sym_table* table, int lineno){
    memset(msg_buf,0,sizeof(msg_buf));
    for(int i=0;i<table->total_elems;i++){
        if(0!=strcmp(table->elem[i].name,name)){
            continue;
        }
        error_flag=1;
        if(0!=table->elem[i].type){
            sprintf(msg_buf,"redefined ident \"%s\", first is variable, duplicate one",name);
            printf(LOGGING_FORMAT, "2", msg_buf, lineno);
            return 1;
        }
        if(table->elem[i].ptr){
            sprintf(msg_buf,"redefined ident \"%s\", first is function, duplicate one",name);
            printf(LOGGING_FORMAT, "4", msg_buf, lineno);
            return 1;
        }
        printf(LOGGING_FORMAT, "unknown", "others", lineno);
        return 1;
    }
    if(!table->parent){
        return 0;
    }
    return check_not_duplicate(name,table->parent,lineno);
}


struct value {
    int type; // 0 for none, 1 for int, 2 for float, 3 for string
    union {
        int ival;
        float fval;
        char *sval;
    } data;
};

struct node {
    char name[32];
    int lineno;
    struct value val;
    int nchild;
    struct node *childs[32];
} *root;


struct node* new_node(const char* name, int lineno) {
    struct node* n = malloc(sizeof(struct node));
    strcpy(n->name, name);
    n->val.type = 0; // no value
    n->nchild = 0;
    n->lineno = lineno;
    return n;
}

void set_node_value(struct node* n, struct value val) {
    n->val = val;
}

void add_child(struct node* parent, struct node* child) {
    if (parent->nchild < 10) {
        parent->childs[parent->nchild++] = child;
    } else {
        printf("Too many children\n");
        exit(1);
    }
}

void print_tree(struct node* root, int level) {
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s (%d)", root->name, root->lineno);
    if (root->val.type != 0) {
        printf(": ");
        switch (root->val.type) {
            case TYPE_INT:
                printf("%d", root->val.data.ival);
                break;
            case TYPE_FLOAT:
                printf("%f", root->val.data.fval);
                break;
            case TYPE_STRING:
                printf("%s", root->val.data.sval);
                break;
        }
    }
    printf("\n");
    for (int i = 0; i < root->nchild; i++) {
        if (root->childs[i] != NULL)
            print_tree(root->childs[i], level + 1);
    }
}

void traverse_and_add_ident(struct node* root, int type, unsigned int offset){
    if (strcmp(root->name,"id")==0){
        sym_enter(TOP_TABLE, root->val.data.sval, type, offset);
        return;
    }
    // printf("\n");
    for (int i = 0; i < root->nchild; i++) {
        if (root->childs[i] != NULL)
            traverse_and_add_ident(root->childs[i], type, offset);
    }
}

%}

%define parse.error verbose

%type <node> CompUnit Decl ConstDecl ConstDefList BType ConstDef ConstArrayDef ConstInitVal ConstInitValList VarDecl VarDefList VarDef ArrayDef InitVal InitValList FuncDef FuncFParams FuncFParam Block BlockItem Stmt Exp Cond LVal PrimaryExp Number UnaryExp UnaryOp FuncRParams MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp BlockItemList INT_WRAP FLOAT_WRAP VOID_WRAP IDENTIFIER_WRAP CONST_WRAP EQ_WRAP NE_WRAP LE_WRAP GE_WRAP AND_WRAP OR_WRAP IF_WRAP ELSE_WRAP WHILE_WRAP RETURN_WRAP BREAK_WRAP CONTINUE_WRAP INTVAL_WRAP FLOATVAL_WRAP plus_WRAP minus_WRAP mul_WRAP div_WRAP mod_WRAP not_WRAP left_paren_WRAP right_paren_WRAP left_brace_WRAP right_brace_WRAP left_bracket_WRAP right_bracket_WRAP comma_WRAP less_WRAP greater_WRAP assign_WRAP

%token EQ NE LE GE AND OR INT FLOAT VOID IF ELSE WHILE RETURN BREAK CONTINUE FOR CONST
%union{
    char *str;
    double dval;
    int ival;
    struct node *node;
}


%token <str> IDENTIFIER
%token <dval> FLOATVAL
%token <ival> INTVAL


%%

CompUnit :
    FuncDef {
        root = new_node("CompUnit", $1->lineno);
        add_child(root, $1);
    }
    |Decl{
        root = new_node("CompUnit", $1->lineno);
        add_child(root, $1);
    }
    |CompUnit Decl{
        add_child(root, $2);
    }
    |CompUnit FuncDef{
        add_child(root, $2);
    }
    |error{
        root = new_node("ERROR", -1);
    }
    ;

Decl :
    ConstDecl{
        $$ = new_node("Decl", $1->lineno);
        add_child($$, $1);
    }
    |VarDecl {
        $$ = new_node("Decl", $1->lineno);
        add_child($$, $1);
    }
    ;
ConstDecl:
    CONST_WRAP BType ConstDefList ';'{
        $$ = new_node("ConstDecl", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        int btype=0;
        unsigned int offset=0;
        if (strcmp($2->childs[0]->name,"int")==0){btype=TYPE_INT;offset=4;}
        if (strcmp($2->childs[0]->name,"float")==0){btype=TYPE_FLOAT;offset=8;}
        traverse_and_add_ident($3,btype,offset);
    }
    |CONST_WRAP BType ConstDefList error{
        $$ = new_node("ConstDecl", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        //missing_symbol(";", $3->lineno);
        yyerrok;
        yyclearin;
    }
    ;

ConstDefList:
    ConstDef{
        $$ = new_node("ConstDefList", $1->lineno);
        add_child($$, $1);
    }
    |ConstDefList comma_WRAP ConstDef{
        add_child($1, $2);
        add_child($1, $3);
    }
    ;
BType:
    INT_WRAP{
        $$ = new_node("BType", $1->lineno);
        add_child($$, $1);
    }
    |FLOAT_WRAP{
        $$ = new_node("BType", $1->lineno);
        add_child($$, $1);
    }
    |VOID_WRAP{
        $$ = new_node("BType", $1->lineno);
        add_child($$, $1);
    }
    ;
ConstDef:
    IDENTIFIER_WRAP ConstArrayDef assign_WRAP ConstInitVal{
        $$ = new_node("ConstDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        check_not_duplicate($1->val.data.sval, TOP_TABLE,$1->lineno);
    }
    |IDENTIFIER_WRAP assign_WRAP ConstInitVal {
        $$ = new_node("ConstDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        check_not_duplicate($1->val.data.sval, TOP_TABLE,$1->lineno);
    }
    ;
ConstArrayDef:
    left_bracket_WRAP ConstExp right_bracket_WRAP{
        $$ = new_node("ConstArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |left_bracket_WRAP ConstExp error right_bracket_WRAP{
        $$ = new_node("ConstArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        //missing_symbol("]", $2->lineno);
        yyerrok;
        struct node* n=new_node("]", $2->lineno);
        add_child($$, n);
    }
    |ConstArrayDef left_bracket_WRAP ConstExp right_bracket_WRAP{
        $$ = new_node("ConstArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
    }
    |ConstArrayDef left_bracket_WRAP ConstExp error right_bracket_WRAP{
        $$ = new_node("ConstArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        //missing_symbol("]", $3->lineno);
        yyerrok;
        struct node* n=new_node("]", $3->lineno);
        add_child($$, n);
    }
    ;
ConstInitVal:
    ConstExp{
        $$ = new_node("ConstInitVal", $1->lineno);
        add_child($$, $1);
    }
    |left_brace_WRAP right_brace_WRAP{
        $$ = new_node("ConstInitVal", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    |left_brace_WRAP error{
        $$ = new_node("ConstInitVal", $1->lineno);
        add_child($$, $1);
        //missing_symbol("}", $1->lineno);
        yyerrok;
        struct node* n=new_node("}", $1->lineno);
        add_child($$, n);
    }
    |left_brace_WRAP ConstInitValList  right_brace_WRAP{
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |left_brace_WRAP ConstInitValList error{
        add_child($$, $1);
        add_child($$, $2);
        //missing_symbol("}", $2->lineno);
        yyerrok;
        struct node* n=new_node("}", $2->lineno);
        add_child($$, n);
    }
    ;
ConstInitValList:
    ConstInitVal{
        $$ = new_node("ConstInitValList", $1->lineno);
        add_child($$, $1);
    }
    |ConstInitValList comma_WRAP ConstInitVal{
        add_child($1, $2);
        add_child($1, $3);
    }
    ;

VarDecl:
    BType VarDefList ';'{
        $$ = new_node("VarDecl", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        int btype=0;
        unsigned int offset=0;
        if (strcmp($1->childs[0]->name,"int")==0){btype=TYPE_INT;offset=4;}
        if (strcmp($1->childs[0]->name,"float")==0){btype=TYPE_FLOAT;offset=8;}
        traverse_and_add_ident($2,btype,offset);
    }
    |BType VarDefList error{
        $$ = new_node("VarDecl", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        //missing_symbol(";", $2->lineno);
        yyerrok;
        yyclearin;
    }
    ;
VarDefList:
    VarDef{
        $$ = new_node("VarDefList", $1->lineno);
        add_child($$, $1);
    }
    |VarDefList comma_WRAP VarDef{
        add_child($1, $2);
        add_child($1, $3);
    }
    ;
VarDef:
    IDENTIFIER_WRAP{
        $$ = new_node("VarDef", $1->lineno);
        add_child($$, $1);
        check_not_duplicate($1->val.data.sval, TOP_TABLE,$1->lineno);
    }
    |IDENTIFIER_WRAP assign_WRAP InitVal{
        $$ = new_node("VarDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        check_not_duplicate($1->val.data.sval, TOP_TABLE,$1->lineno);
    }
    |IDENTIFIER_WRAP ConstArrayDef{
        $$ = new_node("VarDef", $1->lineno);
        add_child($$,$1);
        check_not_duplicate($1->val.data.sval, TOP_TABLE,$1->lineno);
    }
    |IDENTIFIER_WRAP ConstArrayDef assign_WRAP InitVal{
        $$ = new_node("VarDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        check_not_duplicate($1->val.data.sval, TOP_TABLE,$1->lineno);
    }
    ;
ArrayDef:
    left_bracket_WRAP Exp right_bracket_WRAP{
        $$ = new_node("ArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |left_bracket_WRAP Exp error right_bracket_WRAP{
        $$ = new_node("ArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        //missing_symbol("]", $2->lineno);
        yyerrok;
        struct node* n=new_node("]", $2->lineno);
        add_child($$, n);
    }
    |ArrayDef left_bracket_WRAP Exp right_bracket_WRAP{
        $$ = new_node("ArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
    }
    |ArrayDef left_bracket_WRAP Exp error right_bracket_WRAP{
        $$ = new_node("ArrayDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        //missing_symbol("]", $3->lineno);
        yyerrok;
        struct node* n=new_node("]", $3->lineno);
        add_child($$, n);
    }
    ;
InitVal:
    Exp{
        $$ = new_node("InitVal", $1->lineno);
        add_child($$, $1);
    }
    |left_brace_WRAP right_brace_WRAP{
        $$ = new_node("InitVal", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    |left_brace_WRAP error{
        $$ = new_node("InitVal", $1->lineno);
        add_child($$, $1);
        //missing_symbol("}", $1->lineno);
        yyerrok;
        struct node* n=new_node("}", $1->lineno);
        add_child($$, n);
    }
    |left_brace_WRAP InitValList  right_brace_WRAP{
        $$ = new_node("InitVal", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |left_brace_WRAP InitValList  error{
        $$ = new_node("InitVal", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        //missing_symbol("}",$2->lineno);
        yyerrok;
        struct node* n=new_node("}", $2->lineno);
        add_child($$, n);
    }
    ;
InitValList:
    InitVal{
        $$ = new_node("InitValList", $1->lineno);
        add_child($$, $1);
    }
    |InitValList comma_WRAP InitVal{
        add_child($1, $2);
        add_child($1, $3);
    }
    ;
FuncDef:
    BType IDENTIFIER_WRAP left_paren_WRAP right_paren_WRAP Block{
        $$ = new_node("FuncDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        add_child($$, $5);
        if(0==check_not_duplicate($2->val.data.sval, TOP_TABLE,$2->lineno)){
            strcpy(TOP_TABLE->elem[TOP_TABLE->total_elems-1].name, $2->val.data.sval);
        }
    }
    |BType IDENTIFIER_WRAP left_paren_WRAP FuncFParams right_paren_WRAP Block{
        $$ = new_node("FuncDef", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        add_child($$, $5);
        add_child($$, $6);
        if(0==check_not_duplicate($2->val.data.sval, TOP_TABLE, $2->lineno)){
            strcpy(TOP_TABLE->elem[TOP_TABLE->total_elems-1].name, $2->val.data.sval);
        }
    }
    ;
FuncFParams:
    FuncFParam{
        $$ = new_node("FuncFParams", $1->lineno);
        add_child($$, $1);
    }
    |FuncFParams comma_WRAP FuncFParam{
        add_child($1, $2);
        add_child($1, $3);
    }
    ;
FuncFParam:
    BType IDENTIFIER_WRAP{
        $$ = new_node("FuncFParam", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    |BType IDENTIFIER_WRAP ArrayDef{
        $$ = new_node("FuncFParam", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;

Block:
    left_brace_WRAP  right_brace_WRAP{
        $$ = new_node("Block", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    |left_brace_WRAP BlockItemList  right_brace_WRAP{
        $$ = new_node("Block", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
BlockItemList:
    BlockItem{
        $$ = new_node("BlockItemList", $1->lineno);
        add_child($$, $1);
    }
    |BlockItemList BlockItem{
        add_child($1, $2);
    }
BlockItem:
    Decl{
        $$ = new_node("BlockItem", $1->lineno);
        add_child($$, $1);
    }
    |Stmt{
        $$ = new_node("BlockItem", $1->lineno);
        add_child($$, $1);
    }
    ;
Stmt:
    LVal assign_WRAP Exp ';'{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |LVal assign_WRAP Exp error{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        //missing_symbol(";",$3->lineno);
        yyerrok;
        yyclearin;
    }
    |Exp ';'{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
    }
    |Exp error{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        //missing_symbol(";", $1->lineno);
        yyerrok;
        yyclearin;
    }
    |Block{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
    }
    |IF_WRAP left_paren_WRAP Cond right_paren_WRAP Stmt{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        add_child($$, $5);
    }
    |IF_WRAP left_paren_WRAP Cond right_paren_WRAP Stmt ELSE_WRAP Stmt{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        add_child($$, $5);
        add_child($$, $6);
        add_child($$, $7);
    }
    |WHILE_WRAP left_paren_WRAP Cond right_paren_WRAP Stmt{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        add_child($$, $5);
    }
    |BREAK_WRAP ';'{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
    }
    |BREAK_WRAP error{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        //missing_symbol(";",$1->lineno);
        yyerrok;
        yyclearin;
    }
    |CONTINUE_WRAP ';'{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
    }
    |CONTINUE_WRAP error{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        //missing_symbol(";", $1->lineno);
        yyerrok;
        yyclearin;
    }
    |RETURN_WRAP ';'{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
    }
    |RETURN_WRAP error{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        //missing_symbol(";", $1->lineno);
        yyerrok;
        yyclearin;
    }
    |RETURN_WRAP Exp ';'{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    |RETURN_WRAP Exp error{
        $$ = new_node("Stmt", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        //missing_symbol(";", $2->lineno);
        yyerrok;
        yyclearin;
    }
    ;

Exp:
    AddExp{
        $$ = new_node("Exp", $1->lineno);
        add_child($$, $1);
    }
    ;
Cond:
    LOrExp{
        $$ = new_node("Cond", $1->lineno);
        add_child($$, $1);
    }
LVal:
    IDENTIFIER_WRAP{
        $$ = new_node("LVal", $1->lineno);
        add_child($$, $1);
        struct sym_elem *e=sym_lookup(TOP_TABLE,$1->val.data.sval);
        memset(msg_buf,0,sizeof(msg_buf));
        if(!e){
            error_flag=1;
            sprintf(msg_buf,"undefined variable \"%s\"",$1->val.data.sval);
            printf(LOGGING_FORMAT, "1", msg_buf, $1->lineno);
        }
        else if(e->ptr){
            error_flag=1;
            sprintf(msg_buf,"Improper reference to function name \"%s\"",$1->val.data.sval);
            printf(LOGGING_FORMAT, "6", msg_buf, $1->lineno);
        }
    }
    |LVal left_bracket_WRAP Exp right_bracket_WRAP{
        $$ = new_node("LVal", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
    }
    |LVal left_bracket_WRAP Exp error right_bracket_WRAP{
        $$ = new_node("LVal", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        //missing_symbol("]",$3->lineno);
        yyerrok;
        struct node* n=new_node("]", $3->lineno);
        add_child($$, n);
    }
    ;
PrimaryExp:
    left_paren_WRAP Exp right_paren_WRAP{
        $$ = new_node("PrimaryExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |LVal{
        $$ = new_node("PrimaryExp", $1->lineno);
        add_child($$, $1);
    }
    |Number{
        $$ = new_node("PrimaryExp", $1->lineno);
        add_child($$, $1);
    }
    ;
Number:
    INTVAL_WRAP{
        $$ = new_node("Number", $1->lineno);
        add_child($$, $1);
    }
    |FLOATVAL_WRAP{
        $$ = new_node("Number", $1->lineno);
        add_child($$, $1);
    }
    ;
UnaryExp:
    PrimaryExp{
        $$ = new_node("UnaryExp", $1->lineno);
        add_child($$, $1);
    }
    | IDENTIFIER_WRAP left_paren_WRAP right_paren_WRAP{
        $$ = new_node("UnaryExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        struct sym_elem *e=sym_lookup(TOP_TABLE,$1->val.data.sval);
        memset(msg_buf,0,sizeof(msg_buf));
        if(!e){
            error_flag=1;
            sprintf(msg_buf,"undefined function \"%s\"",$1->val.data.sval);
            printf(LOGGING_FORMAT, "3", msg_buf, $1->lineno);
        }
        else if(0!=e->type){
            error_flag=1;
            sprintf(msg_buf,"Improper reference to variable name \"%s\"",$1->val.data.sval);
            printf(LOGGING_FORMAT, "5", msg_buf, $1->lineno);
        }
    }
    | IDENTIFIER_WRAP left_paren_WRAP FuncRParams right_paren_WRAP{
        $$ = new_node("UnaryExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, $4);
        struct sym_elem *e=sym_lookup(TOP_TABLE,$1->val.data.sval);
        memset(msg_buf,0,sizeof(msg_buf));
        if(!e){
            error_flag=1;
            sprintf(msg_buf,"undefined function \"%s\"",$1->val.data.sval);
            printf(LOGGING_FORMAT, "3", msg_buf, $1->lineno);
        }
        else if(0!=e->type){
            error_flag=1;
            sprintf(msg_buf,"Improper reference to variable name \"%s\"",$1->val.data.sval);
            printf(LOGGING_FORMAT, "5", msg_buf, $1->lineno);
        }
    }
    | UnaryOp UnaryExp{
        $$ = new_node("UnaryExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    ;
UnaryOp:
    plus_WRAP{
        $$ = new_node("UnaryOp", $1->lineno);
        add_child($$, $1);
    }
    |minus_WRAP{
        $$ = new_node("UnaryOp", $1->lineno);
        add_child($$, $1);
    }
    |not_WRAP{
        $$ = new_node("UnaryOp", $1->lineno);
        add_child($$, $1);
    }
    ;
FuncRParams:
    Exp{
        $$ = new_node("FuncRParams", $1->lineno);
        add_child($$, $1);
    }
    |FuncRParams comma_WRAP Exp{
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
MulExp:
    UnaryExp{
        $$ = new_node("MulExp", $1->lineno);
        add_child($$, $1);
    }
    |MulExp mul_WRAP UnaryExp{
        $$ = new_node("MulExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |MulExp div_WRAP UnaryExp{
        $$ = new_node("MulExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |MulExp mod_WRAP UnaryExp{
        $$ = new_node("MulExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
AddExp:
    MulExp{
        $$ = new_node("AddExp", $1->lineno);
        add_child($$, $1);
    }
    |AddExp plus_WRAP MulExp{
        $$ = new_node("AddExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |AddExp minus_WRAP MulExp{
        $$ = new_node("AddExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
RelExp:
    AddExp{
        $$ = new_node("RelExp", $1->lineno);
        add_child($$, $1);
    }
    |RelExp less_WRAP AddExp{
        $$ = new_node("RelExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |RelExp greater_WRAP AddExp{
        $$ = new_node("RelExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |RelExp LE_WRAP AddExp{
        $$ = new_node("RelExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |RelExp GE_WRAP AddExp{
        $$ = new_node("RelExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
EqExp:
    RelExp{
        $$ = new_node("EqExp", $1->lineno);
        add_child($$, $1);
    }
    |EqExp EQ_WRAP RelExp{
        $$ = new_node("EqExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    |EqExp NE_WRAP RelExp{
        $$ = new_node("EqExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
LAndExp:
    EqExp{
        $$ = new_node("LAndExp", $1->lineno);
        add_child($$, $1);
    }
    |LAndExp AND_WRAP EqExp{
        $$ = new_node("LAndExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
LOrExp:
    LAndExp{
        $$ = new_node("LOrExp", $1->lineno);
        add_child($$, $1);
    }
    |LOrExp OR_WRAP LAndExp{
        $$ = new_node("LOrExp", $1->lineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, $3);
    }
    ;
ConstExp:
    AddExp{
        $$ = new_node("ConstExp", $1->lineno);
        add_child($$, $1);
    }
    ;

INT_WRAP:
    INT{
        $$ = new_node("int", yylineno);
    }
    ;

FLOAT_WRAP:
    FLOAT{
        $$ = new_node("float", yylineno);
    }
    ;

VOID_WRAP:
    VOID{
        $$ = new_node("void", yylineno);
    }
    ;

IDENTIFIER_WRAP:
    IDENTIFIER{
        $$ = new_node("id", yylineno);
        $$->val.type = TYPE_STRING;
        $$->val.data.sval = $1;
    }
    ;

CONST_WRAP:
    CONST{
        $$ = new_node("const", yylineno);
    }
    ;

EQ_WRAP:
    EQ{
        $$ = new_node("==", yylineno);
    }
    ;

NE_WRAP:
    NE{
        $$ = new_node("!=", yylineno);
    }
    ;

LE_WRAP:
    LE{
        $$ = new_node("<=", yylineno);
    }
    ;

GE_WRAP:
    GE{
        $$ = new_node(">=", yylineno);
    }
    ;

AND_WRAP:
    AND{
        $$ = new_node("&&", yylineno);
    }
    ;

OR_WRAP:
    OR{
        $$ = new_node("||", yylineno);
    }
    ;

IF_WRAP:
    IF{
        $$ = new_node("if", yylineno);
    }
    ;

ELSE_WRAP:
    ELSE{
        $$ = new_node("else", yylineno);
    }

WHILE_WRAP:
    WHILE{
        $$ = new_node("while", yylineno);
    }
    ;

RETURN_WRAP:
    RETURN{
        $$ = new_node("return", yylineno);
    }
    ;

BREAK_WRAP:
    BREAK{
        $$ = new_node("break", yylineno);
    }
    ;

CONTINUE_WRAP:
    CONTINUE{
        $$ = new_node("continue", yylineno);
    }
    ;

INTVAL_WRAP:
    INTVAL{
        $$ = new_node("int", yylineno);
        $$->val.type = TYPE_INT;
        $$->val.data.ival = $1;
    }
    ;

FLOATVAL_WRAP:
    FLOATVAL{
        $$ = new_node("float", yylineno);
        $$->val.type = TYPE_FLOAT;
        $$->val.data.fval = $1;
    }
    ;

plus_WRAP:
    '+'{
        $$ = new_node("+", yylineno);
    }
    ;

minus_WRAP:
    '-'{
        $$ = new_node("-", yylineno);
    }
    ;

mul_WRAP:
    '*'{
        $$ = new_node("*", yylineno);
    }
    ;

div_WRAP:
    '/'{
        $$ = new_node("/", yylineno);
    }
    ;

mod_WRAP:
    '%'{
        $$ = new_node("%", yylineno);
    }
    ;

not_WRAP:
    '!'{
        $$ = new_node("!", yylineno);
    }
    ;

left_paren_WRAP:
    '('{
        $$ = new_node("(", yylineno);
    }
    ;

right_paren_WRAP:
    ')'{
        $$ = new_node(")", yylineno);
    }
    ;

left_brace_WRAP:
    '{'{
        $$ = new_node("{", yylineno);
        global_table[total_tables++] = sym_mktable(TOP_TABLE);
    }
    ;

right_brace_WRAP:
    '}'{
        $$ = new_node("}", yylineno);
        sprintf(name_buf,"%u",unque_name++);
        sym_enter_proc(PARENT_TABLE,name_buf,TOP_TABLE);
        total_tables--;
    }
    ;

left_bracket_WRAP:
    '['{
        $$ = new_node("[", yylineno);
    }
    ;

right_bracket_WRAP:
    ']'{
        $$ = new_node("]", yylineno);
    }
    ;

comma_WRAP:
    ','{
        $$ = new_node(",", yylineno);
    }
    ;

less_WRAP:
    '<'{
        $$ = new_node("<", yylineno);
    }
    ;

greater_WRAP:
    '>'{
        $$ = new_node(">", yylineno);
    }
    ;

assign_WRAP:
    '='{
        $$ = new_node("=", yylineno);
    }
    ;



%%

void yyerror(const char *msg) {
    error_flag=1;
    printf(LOGGING_FORMAT, "B", msg, yylineno);
}


int main(){
    global_table[total_tables++] = sym_mktable(NULL);
    yyparse();
    if(!error_flag){
        /* print_tree(root, 0); */
        sym_print_table(global_table[0],0);
    }
}