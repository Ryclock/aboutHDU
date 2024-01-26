%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 256

extern int yylineno;

int yylex(void);

int error_flag=0;

int yyerror(const char* msg) {
    error_flag = 1;
    fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
    return 0;
}

struct TreeNode {
    char* nodeType;
    char* attribute;
    int lineno;
    struct TreeNode* child;
    struct TreeNode* sibling;
};

struct TreeNode* createNode(const char* nodeType, const char* attribute, int lineno) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    node->nodeType = strdup(nodeType);
    if (node->nodeType == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->attribute = attribute? strdup(attribute):NULL;
    node->lineno = lineno;
    node->child = NULL;
    node->sibling = NULL;

    return node;
}

void printTree(struct TreeNode* root,int indent) {
    if (root == NULL) {
        return;
    }

    if (strcmp(root->nodeType, "empty") == 0){
        printTree(root->sibling, indent);
        return;
    }

    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    if (root->attribute) {
        printf("%s: %s\n",root->nodeType, root->attribute);
    }else if (strncmp(root->nodeType, "KW_", 3) == 0){
        printf("%s\n", root->nodeType);
    }else{
        printf("%s (%d)\n", root->nodeType, root->lineno);
    }

    printTree(root->child, indent + 1);
    printTree(root->sibling, indent);
}

%}

%locations
%define parse.error verbose

%union {
    int int_val;
    float float_val;
    char* str_val;
    struct TreeNode* treeNode;
}

%token <int_val> INT_CONST
%token <float_val> FLOAT_CONST
%token <str_val> IDENTIFIER

%token KW_CONST KW_INT KW_FLOAT KW_VOID KW_IF KW_ELSE KW_WHILE KW_BREAK KW_CONTINUE KW_RETURN

%left '+' '-'
%left '*' '/' '%'
%left '<' '>' LEQ GEQ
%left EQ NEQ
%left AND
%left OR
%right '!' '='

%type <treeNode> Start CompUnitList CompUnit Decl ConstDecl BType ConstDefList ConstDef ConstExpList ConstInitVal ConstInitValList VarDecl VarDefList VarDef InitVal InitValList FuncDef FuncFParams FuncFParam ExpList Block BlockItemList BlockItem StmtOther StmtMustELSE Stmt Exp Cond LVal PrimaryExp UnaryExp UnaryOp FuncRParams MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp
%type <treeNode> Node_const Node_if Node_else Node_while Node_jumpout Node_return
%type <treeNode> Node_ID Node_open_brace Node_close_brace Node_open_bracket Node_close_bracket Node_open_paren Node_close_paren Node_semicolon Node_comma
%type <treeNode> Node_mul_div_mod Node_lgeq Node_eqn Node_and Node_or Node_assign


%%

Start: CompUnitList { $$=$1; if(!error_flag){ printTree($$, 0); } }

Node_const: KW_CONST {
        $$ = createNode("KW_CONST", NULL, yylineno);}
    ;

Node_if: KW_IF {
        $$ = createNode("KW_IF", NULL, yylineno);}
    ;

Node_else: KW_ELSE {
        $$ = createNode("KW_ELSE", NULL, yylineno);}
    ;

Node_while: KW_WHILE {
        $$ = createNode("KW_WHILE", NULL, yylineno);}
    ;

Node_jumpout: KW_BREAK {
        $$ = createNode("KW_BREAK", NULL, yylineno);}
    | KW_CONTINUE {
        $$ = createNode("KW_CONTINUE", NULL, yylineno);}
    ;

Node_return: KW_RETURN {
        $$ = createNode("KW_RETURN", NULL, yylineno);}
    ;

Node_ID: IDENTIFIER {
        $$ = createNode("Ident", $1, yylineno);}
    ;

Node_open_brace: '{' {
        $$ = createNode("Seperator", "{", yylineno);}
    ;

Node_close_brace: '}' {
        $$ = createNode("Seperator", "}", yylineno);}
    ;

Node_open_bracket: '[' {
        $$ = createNode("Seperator", "[", yylineno);}
    ;

Node_close_bracket: ']' {
        $$ = createNode("Seperator", "]", yylineno);}
    ;

Node_open_paren: '(' {
        $$ = createNode("Seperator", "(", yylineno);}
    ;

Node_close_paren: ')' {
        $$ = createNode("Seperator", ")", yylineno);}
    ;

Node_semicolon: ';' {
        $$ = createNode("Seperator", ";", yylineno);}
    ;

Node_comma: ',' {
        $$ = createNode("Seperator", ",", yylineno);}
    ;

Node_mul_div_mod: '*' {
        $$ = createNode("Operator", "*", yylineno);}
    | '/' {
        $$ = createNode("Operator", "/", yylineno);}
    | '%' {
        $$ = createNode("Operator", "%", yylineno);}
    ;

Node_lgeq: '<' {
        $$ = createNode("Operator", "<", yylineno);}
    | '>' {
        $$ = createNode("Operator", ">", yylineno);}
    | LEQ {
        $$ = createNode("Operator", "<=", yylineno);}
    | GEQ {
        $$ = createNode("Operator", ">=", yylineno);}
    ;

Node_eqn: EQ {
        $$ = createNode("Operator", "==", yylineno);}
    | NEQ {
        $$ = createNode("Operator", "!=", yylineno);}
    ;

Node_and: AND {
        $$ = createNode("Operator", "&&", yylineno);}
    ;

Node_or: OR {
        $$ = createNode("Operator", "||", yylineno);}
    ;

Node_assign: '=' {
        $$ = createNode("Operator", "=", yylineno);}
    ;

BType: KW_VOID {
        $$ = createNode("BType", NULL, yylineno);
        $$->child = createNode("Type", "void", yylineno);}
    |KW_INT {
        $$ = createNode("BType", NULL, yylineno);
        $$->child = createNode("Type", "int", yylineno);}
    | KW_FLOAT {
        $$ = createNode("BType", NULL, yylineno);
        $$->child = createNode("Type", "float", yylineno);}
    ;

UnaryOp: '+' {
        $$ = createNode("UnaryOp", NULL, yylineno);
        $$->child = createNode("Operator", "+", yylineno);}
    | '-' {
        $$ = createNode("UnaryOp", NULL, yylineno);
        $$->child = createNode("Operator", "-", yylineno);}
    | '!' {
        $$ = createNode("UnaryOp", NULL, yylineno);
        $$->child = createNode("Operator", "!", yylineno);}
    ;

CompUnitList: CompUnitList CompUnit {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->child = $$->sibling->child->sibling = $2;
        $$->sibling->child = NULL;}
    | CompUnit {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->child = $$->sibling = $1;}
    ;

CompUnit: Decl {
        $$ = createNode("CompUnit", NULL, $1->lineno);
        $$->child = $1; }
    | FuncDef {
        $$ = createNode("CompUnit", NULL, $1->lineno);
        $$->child = $1; }
    ;

Decl: ConstDecl {
        $$ = createNode("Decl", NULL, $1->lineno);
        $$->child = $1; }
    | VarDecl {
        $$ = createNode("Decl", NULL, $1->lineno);
        $$->child = $1; }
    ;

ConstDecl: Node_const BType ConstDefList Node_semicolon {
        $$ = createNode("ConstDecl", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->child->sibling = $4;
        $$->child->sibling->sibling->child = NULL;
        if(strcmp($2->child->nodeType, "Type")==0&&strcmp($2->child->attribute, "void")==0){
            yyerror("Incomplete types are not allowed");
        }}
    | Node_const BType ConstDefList error Node_semicolon{
        $$ = createNode("ConstDecl", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->child->sibling = createNode("Seperator", ";", yylineno);
        $$->child->sibling->sibling->child = NULL;
        yyerrok;
        yyclearin;}
    ;

ConstDefList: ConstDefList Node_comma ConstDef {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->child->sibling = $2;
        $$->child = $$->sibling->child->sibling->sibling = $3;
        $$->sibling->child = NULL;}
    | ConstDef {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->child = $$->sibling = $1;}
    ;

ConstDef: Node_ID ConstExpList Node_assign ConstInitVal {
        $$ = createNode("ConstDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = $3;
        $$->child->sibling->child->sibling->sibling = $4;
        $$->child->sibling->child = NULL;}
    | Node_ID Node_assign ConstInitVal {
        $$ = createNode("ConstDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    ;

ConstExpList: ConstExpList Node_open_bracket ConstExp Node_close_bracket {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->child->sibling =  $2;
        $$->sibling->child->sibling->sibling = $3;
        $$->child = $$->sibling->child->sibling->sibling->sibling = $4;
        $$->sibling->child = NULL;}
    | Node_open_bracket ConstExp Node_close_bracket {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->sibling = $2;
        $$->child = $$->sibling->sibling->sibling = $3;}
    /* | ConstExpList Node_open_bracket ConstExp error Node_close_bracket {
        yyerrok;
        yyclearin;}
    | Node_open_bracket ConstExp error Node_close_bracket {
        yyerrok;
        yyclearin;} */
    ;

ConstInitVal: ConstExp {
        $$ = createNode("ConstInitVal", NULL, $1->lineno);
        $$->child = $1;}
    | Node_open_brace ConstInitValList Node_close_brace {
        $$ = createNode("ConstInitVal", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = $3;
        $$->child->sibling->child = NULL;}
    | Node_open_brace Node_close_brace {
        $$ = createNode("ConstInitVal", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    /* | Node_open_brace ConstInitValList error Node_close_brace{
        yyerrok;
        yyclearin;}
    | Node_open_brace error Node_close_brace{
        yyerrok;
        yyclearin;} */
    ;

ConstInitValList: ConstInitValList Node_comma ConstInitVal{
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->child->sibling = $2;
        $$->child = $$->sibling->child->sibling->sibling = $3;
        $$->sibling->child = NULL;}
    | ConstInitVal {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->child = $$->sibling = $1;}
    ;

VarDecl: BType VarDefList Node_semicolon {
        $$ = createNode("VarDecl", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = $3;
        $$->child->sibling->child=NULL;
        if(strcmp($1->child->nodeType, "Type")==0&&strcmp($1->child->attribute, "void")==0){
            yyerror("Incomplete types are not allowed");
        }}
    | BType VarDefList error Node_semicolon{
        $$ = createNode("VarDecl", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = createNode("Seperator", ";", yylineno);
        $$->child->sibling->child=NULL;
        yyerrok;
        yyclearin;}
    ;

VarDefList: VarDefList Node_comma VarDef {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->child->sibling = $2;
        $$->child = $$->sibling->child->sibling->sibling = $3;
        $$->sibling->child=NULL;}
    | VarDef {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->child = $$->sibling = $1;}
    ;

VarDef: Node_ID ConstExpList Node_assign InitVal {
        $$ = createNode("VarDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = $3;
        $$->child->sibling->child->sibling->sibling = $4;
        $$->child->sibling->child = NULL;}
   | Node_ID Node_assign InitVal {
        $$ = createNode("VarDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    | Node_ID ConstExpList {
        $$ = createNode("VarDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    | Node_ID {
        $$ = createNode("VarDef", NULL, $1->lineno);
        $$->child = $1;}
   ;

InitVal: Exp {
        $$ = createNode("InitVal", NULL, $1->lineno);
        $$->child = $1;}
    | Node_open_brace InitValList Node_close_brace {
        $$ = createNode("InitVal", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = $3;
        $$->child->sibling->child=NULL; }
    | Node_open_brace Node_close_brace {
        $$ = createNode("InitVal", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    /* | Node_open_brace InitValList error Node_close_brace{
        yyerrok;
        yyclearin;}
    | Node_open_brace error Node_close_brace{
        yyerrok;
        yyclearin;} */
    ;

InitValList: InitValList Node_comma InitVal {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->child->sibling = $2;
        $$->child = $$->sibling->child->sibling->sibling = $3;
        $$->sibling->child=NULL;}
    | InitVal {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->child = $$->sibling = $1;}
    ;

FuncDef: BType Node_ID Node_open_paren FuncFParams Node_close_paren Block {
        $$ = createNode("FuncDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->nodeType = "FuncType";
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5;
        $$->child->sibling->sibling->sibling->sibling->sibling = $6;}
    | BType Node_ID Node_open_paren Node_close_paren Block {
        $$ = createNode("FuncDef", NULL, $1->lineno);
        $$->child = $1;
        $$->child->nodeType = "FuncType";
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5; }
    ;

FuncFParams: FuncFParam Node_comma FuncFParams {
        $$ = createNode("FuncFParams", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    | FuncFParam {
        $$ = createNode("FuncFParams", NULL, $1->lineno);
        $$->child = $1;}
    ;

FuncFParam: BType Node_ID Node_open_bracket Node_close_bracket ExpList {
        $$ = createNode("FuncFParam", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5;
        if(strcmp($1->child->nodeType, "Type")==0&&strcmp($1->child->attribute, "void")==0){
            yyerror("The parameter cannot be of the type void");
        }}
    |  BType Node_ID Node_open_bracket Node_close_bracket  {
        $$ = createNode("FuncFParam", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        if(strcmp($1->child->nodeType, "Type")==0&&strcmp($1->child->attribute, "void")==0){
            yyerror("The parameter cannot be of the type void");
        }}
    /* |  BType Node_ID Node_open_bracket error Node_close_bracket{
        yyerrok;
        yyclearin;} */
    | BType Node_ID {
        $$ = createNode("FuncFParam", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    ;

ExpList: ExpList Node_open_bracket Exp Node_close_bracket {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->child->sibling = $2;
        $$->sibling->child->sibling->sibling = $3;
        $$->child = $$->sibling->child->sibling->sibling->sibling = $4;
        $$->sibling->child = NULL;}
    | Node_open_bracket Exp Node_close_bracket {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->sibling->sibling = $2;
        $$->child = $$->sibling->sibling->sibling = $3;}
    | ExpList Node_open_bracket Exp error Node_close_bracket{
        yyerrok;
        yyclearin;}
    | Node_open_bracket Exp error Node_close_bracket{
        yyerrok;
        yyclearin;}
    ;

Block: Node_open_brace BlockItemList Node_close_brace {
        $$ = createNode("Block", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->child->sibling = $3;
        $$->child->sibling->child=NULL;}
    | Node_open_brace Node_close_brace {
        $$ = createNode("Block", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    /* | Node_open_brace BlockItemList error Node_close_brace{
        yyerrok;
        yyclearin;}
    | Node_open_brace error Node_close_brace{
        yyerrok;
        yyclearin;} */
    ;

BlockItemList: BlockItemList BlockItem {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->sibling = $1;
        $$->child = $$->sibling->child->sibling = $2;
        $$->sibling->child = NULL;}
    | BlockItem {
        $$ = createNode("empty", NULL, $1->lineno);
        $$->child = $$->sibling = $1;}
    ;

BlockItem: Decl {
        $$ = createNode("BlockItem", NULL, $1->lineno);
        $$->child = $1;}
    | Stmt {
        $$ = createNode("BlockItem", NULL, $1->lineno);
        $$->child = $1;}
    ;

StmtOther: LVal Node_assign Exp Node_semicolon {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;}
    | LVal Node_assign Exp error Node_semicolon{
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
    | Node_semicolon {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child=$1;}
    | Exp Node_semicolon {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    | Exp error Node_semicolon{
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
    | Block {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1; }
    | Node_while Node_open_paren Cond Node_close_paren Stmt {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5;}
    | Node_jumpout Node_semicolon {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    | Node_return Exp Node_semicolon {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    | Node_return Node_semicolon {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;}
    | Node_jumpout error Node_semicolon{
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
    | Node_return Exp error Node_semicolon{
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
    | Node_return error Node_semicolon{
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = createNode("Seperator", ";", yylineno);
        yyerrok;
        yyclearin;}
    ;

StmtMustELSE: StmtOther {
        $$ = $1;}
    | Node_if Node_open_paren Cond Node_close_paren StmtMustELSE Node_else StmtMustELSE {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5;
        $$->child->sibling->sibling->sibling->sibling->sibling = $6;
        $$->child->sibling->sibling->sibling->sibling->sibling->sibling = $7; }
    ;

Stmt: StmtOther {
        $$ = $1;}
    | Node_if Node_open_paren Cond Node_close_paren StmtMustELSE Node_else Stmt {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5;
        $$->child->sibling->sibling->sibling->sibling->sibling = $6;
        $$->child->sibling->sibling->sibling->sibling->sibling->sibling = $7; }
    | Node_if Node_open_paren Cond Node_close_paren Stmt {
        $$ = createNode("Stmt", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;
        $$->child->sibling->sibling->sibling->sibling = $5;}
    ;

Exp: AddExp {
        $$ = createNode("Exp", NULL, $1->lineno);
        $$->child = $1;}
    ;

Cond: LOrExp {
        $$ = createNode("Cond", NULL, $1->lineno);
        $$->child = $1;}
     ;

LVal: Node_ID ExpList {
        $$ = createNode("LVal", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2; }
    | Node_ID {
        $$ = createNode("LVal", NULL, $1->lineno);
        $$->child = $1;}
    ;

PrimaryExp: Node_open_paren Cond Node_close_paren {
        $$ = createNode("PrimaryExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    | LVal {
        $$ = createNode("PrimaryExp", NULL, $1->lineno);
        $$->child = $1;}
    | INT_CONST {
        $$ = createNode("PrimaryExp", NULL, yylineno);
        char* strValue = (char*)malloc(MAX_STRING_LENGTH);
        if (strValue == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        snprintf(strValue, MAX_STRING_LENGTH, "%d", yylval.int_val);
        $$->child = createNode("Int_const", strValue, yylineno);}
    | FLOAT_CONST {
        $$ = createNode("PrimaryExp", NULL, yylineno);
        char* strValue = (char*)malloc(MAX_STRING_LENGTH);
        if (strValue == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        snprintf(strValue, MAX_STRING_LENGTH, "%f", yylval.float_val);
        $$->child = createNode("Float_const", strValue, yylineno);}
    ;

UnaryExp: PrimaryExp {
        $$ = createNode("UnaryExp", NULL, $1->lineno);
        $$->child = $1;}
    | Node_ID Node_open_paren FuncRParams Node_close_paren {
        $$ = createNode("UnaryExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        $$->child->sibling->sibling->sibling = $4;}
    | Node_ID Node_open_paren Node_close_paren {
        $$ = createNode("UnaryExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    | UnaryOp UnaryExp {
        $$ = createNode("UnaryExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2; }
    ;

FuncRParams: Exp Node_comma FuncRParams {
        $$ = createNode("FuncRParams", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    | Exp {
        $$ = createNode("FuncRParams", NULL, $1->lineno);
        $$->child = $1;}
    ;

MulExp: UnaryExp {
        $$ = createNode("MulExp", NULL, $1->lineno);
        $$->child = $1;}
    | MulExp Node_mul_div_mod UnaryExp {
        $$ = createNode("MulExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;}
    ;

AddExp: MulExp {
        $$ = createNode("AddExp", NULL, $1->lineno);
        $$->child = $1;}
    | AddExp UnaryOp MulExp {
        $$ = createNode("AddExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3;
        if(strcmp($2->child->attribute, "!")==0){
            yyerror("Unusable operator '!'");
        }}
    ;

RelExp: AddExp {
        $$ = createNode("RelExp", NULL, $1->lineno);
        $$->child = $1;}
    | RelExp Node_lgeq AddExp {
        $$ = createNode("RelExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3; }
    ;

EqExp: RelExp {
        $$ = createNode("EqExp", NULL, $1->lineno);
        $$->child = $1;}
    | EqExp Node_eqn RelExp {
        $$ = createNode("EqExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3; }
    ;

LAndExp: EqExp {
        $$ = createNode("LAndExp", NULL, $1->lineno);
        $$->child = $1;}
    | LAndExp Node_and EqExp {
        $$ = createNode("LAndExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3; }
    ;

LOrExp: LAndExp {
        $$ = createNode("LOrExp", NULL, $1->lineno);
        $$->child = $1;}
    | LOrExp Node_or LAndExp {
        $$ = createNode("LOrExp", NULL, $1->lineno);
        $$->child = $1;
        $$->child->sibling = $2;
        $$->child->sibling->sibling = $3; }
   ;

ConstExp: AddExp {
        $$ = createNode("ConstExp", NULL, $1->lineno);
        $$->child = $1;}
    ;

%%

int main() {
#ifdef YYDEBUG
  yydebug = 0;
#endif
    yyparse();
    return 0;
}
