/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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


#line 201 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EQ = 258,                      /* EQ  */
    NE = 259,                      /* NE  */
    LE = 260,                      /* LE  */
    GE = 261,                      /* GE  */
    AND = 262,                     /* AND  */
    OR = 263,                      /* OR  */
    INT = 264,                     /* INT  */
    FLOAT = 265,                   /* FLOAT  */
    VOID = 266,                    /* VOID  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    RETURN = 270,                  /* RETURN  */
    BREAK = 271,                   /* BREAK  */
    CONTINUE = 272,                /* CONTINUE  */
    FOR = 273,                     /* FOR  */
    CONST = 274,                   /* CONST  */
    IDENTIFIER = 275,              /* IDENTIFIER  */
    FLOATVAL = 276,                /* FLOATVAL  */
    INTVAL = 277                   /* INTVAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define EQ 258
#define NE 259
#define LE 260
#define GE 261
#define AND 262
#define OR 263
#define INT 264
#define FLOAT 265
#define VOID 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define RETURN 270
#define BREAK 271
#define CONTINUE 272
#define FOR 273
#define CONST 274
#define IDENTIFIER 275
#define FLOATVAL 276
#define INTVAL 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 136 "parser.y"

    char *str;
    double dval;
    int ival;
    struct node *node;

#line 305 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_EQ = 3,                         /* EQ  */
  YYSYMBOL_NE = 4,                         /* NE  */
  YYSYMBOL_LE = 5,                         /* LE  */
  YYSYMBOL_GE = 6,                         /* GE  */
  YYSYMBOL_AND = 7,                        /* AND  */
  YYSYMBOL_OR = 8,                         /* OR  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_VOID = 11,                      /* VOID  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_BREAK = 16,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 17,                  /* CONTINUE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_CONST = 19,                     /* CONST  */
  YYSYMBOL_IDENTIFIER = 20,                /* IDENTIFIER  */
  YYSYMBOL_FLOATVAL = 21,                  /* FLOATVAL  */
  YYSYMBOL_INTVAL = 22,                    /* INTVAL  */
  YYSYMBOL_23_ = 23,                       /* ';'  */
  YYSYMBOL_24_ = 24,                       /* '+'  */
  YYSYMBOL_25_ = 25,                       /* '-'  */
  YYSYMBOL_26_ = 26,                       /* '*'  */
  YYSYMBOL_27_ = 27,                       /* '/'  */
  YYSYMBOL_28_ = 28,                       /* '%'  */
  YYSYMBOL_29_ = 29,                       /* '!'  */
  YYSYMBOL_30_ = 30,                       /* '('  */
  YYSYMBOL_31_ = 31,                       /* ')'  */
  YYSYMBOL_32_ = 32,                       /* '{'  */
  YYSYMBOL_33_ = 33,                       /* '}'  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* ']'  */
  YYSYMBOL_36_ = 36,                       /* ','  */
  YYSYMBOL_37_ = 37,                       /* '<'  */
  YYSYMBOL_38_ = 38,                       /* '>'  */
  YYSYMBOL_39_ = 39,                       /* '='  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_CompUnit = 41,                  /* CompUnit  */
  YYSYMBOL_Decl = 42,                      /* Decl  */
  YYSYMBOL_ConstDecl = 43,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 44,              /* ConstDefList  */
  YYSYMBOL_BType = 45,                     /* BType  */
  YYSYMBOL_ConstDef = 46,                  /* ConstDef  */
  YYSYMBOL_ConstArrayDef = 47,             /* ConstArrayDef  */
  YYSYMBOL_ConstInitVal = 48,              /* ConstInitVal  */
  YYSYMBOL_ConstInitValList = 49,          /* ConstInitValList  */
  YYSYMBOL_VarDecl = 50,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 51,                /* VarDefList  */
  YYSYMBOL_VarDef = 52,                    /* VarDef  */
  YYSYMBOL_ArrayDef = 53,                  /* ArrayDef  */
  YYSYMBOL_InitVal = 54,                   /* InitVal  */
  YYSYMBOL_InitValList = 55,               /* InitValList  */
  YYSYMBOL_FuncDef = 56,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 57,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 58,                /* FuncFParam  */
  YYSYMBOL_Block = 59,                     /* Block  */
  YYSYMBOL_BlockItemList = 60,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 61,                 /* BlockItem  */
  YYSYMBOL_Stmt = 62,                      /* Stmt  */
  YYSYMBOL_Exp = 63,                       /* Exp  */
  YYSYMBOL_Cond = 64,                      /* Cond  */
  YYSYMBOL_LVal = 65,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 66,                /* PrimaryExp  */
  YYSYMBOL_Number = 67,                    /* Number  */
  YYSYMBOL_UnaryExp = 68,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 69,                   /* UnaryOp  */
  YYSYMBOL_FuncRParams = 70,               /* FuncRParams  */
  YYSYMBOL_MulExp = 71,                    /* MulExp  */
  YYSYMBOL_AddExp = 72,                    /* AddExp  */
  YYSYMBOL_RelExp = 73,                    /* RelExp  */
  YYSYMBOL_EqExp = 74,                     /* EqExp  */
  YYSYMBOL_LAndExp = 75,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 76,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 77,                  /* ConstExp  */
  YYSYMBOL_INT_WRAP = 78,                  /* INT_WRAP  */
  YYSYMBOL_FLOAT_WRAP = 79,                /* FLOAT_WRAP  */
  YYSYMBOL_VOID_WRAP = 80,                 /* VOID_WRAP  */
  YYSYMBOL_IDENTIFIER_WRAP = 81,           /* IDENTIFIER_WRAP  */
  YYSYMBOL_CONST_WRAP = 82,                /* CONST_WRAP  */
  YYSYMBOL_EQ_WRAP = 83,                   /* EQ_WRAP  */
  YYSYMBOL_NE_WRAP = 84,                   /* NE_WRAP  */
  YYSYMBOL_LE_WRAP = 85,                   /* LE_WRAP  */
  YYSYMBOL_GE_WRAP = 86,                   /* GE_WRAP  */
  YYSYMBOL_AND_WRAP = 87,                  /* AND_WRAP  */
  YYSYMBOL_OR_WRAP = 88,                   /* OR_WRAP  */
  YYSYMBOL_IF_WRAP = 89,                   /* IF_WRAP  */
  YYSYMBOL_ELSE_WRAP = 90,                 /* ELSE_WRAP  */
  YYSYMBOL_WHILE_WRAP = 91,                /* WHILE_WRAP  */
  YYSYMBOL_RETURN_WRAP = 92,               /* RETURN_WRAP  */
  YYSYMBOL_BREAK_WRAP = 93,                /* BREAK_WRAP  */
  YYSYMBOL_CONTINUE_WRAP = 94,             /* CONTINUE_WRAP  */
  YYSYMBOL_INTVAL_WRAP = 95,               /* INTVAL_WRAP  */
  YYSYMBOL_FLOATVAL_WRAP = 96,             /* FLOATVAL_WRAP  */
  YYSYMBOL_plus_WRAP = 97,                 /* plus_WRAP  */
  YYSYMBOL_minus_WRAP = 98,                /* minus_WRAP  */
  YYSYMBOL_mul_WRAP = 99,                  /* mul_WRAP  */
  YYSYMBOL_div_WRAP = 100,                 /* div_WRAP  */
  YYSYMBOL_mod_WRAP = 101,                 /* mod_WRAP  */
  YYSYMBOL_not_WRAP = 102,                 /* not_WRAP  */
  YYSYMBOL_left_paren_WRAP = 103,          /* left_paren_WRAP  */
  YYSYMBOL_right_paren_WRAP = 104,         /* right_paren_WRAP  */
  YYSYMBOL_left_brace_WRAP = 105,          /* left_brace_WRAP  */
  YYSYMBOL_right_brace_WRAP = 106,         /* right_brace_WRAP  */
  YYSYMBOL_left_bracket_WRAP = 107,        /* left_bracket_WRAP  */
  YYSYMBOL_right_bracket_WRAP = 108,       /* right_bracket_WRAP  */
  YYSYMBOL_comma_WRAP = 109,               /* comma_WRAP  */
  YYSYMBOL_less_WRAP = 110,                /* less_WRAP  */
  YYSYMBOL_greater_WRAP = 111,             /* greater_WRAP  */
  YYSYMBOL_assign_WRAP = 112               /* assign_WRAP  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  231

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,    28,     2,     2,
      30,    31,    26,    24,    36,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
      37,    39,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   152,   152,   156,   160,   163,   166,   172,   176,   182,
     193,   205,   209,   215,   219,   223,   229,   237,   246,   252,
     261,   268,   280,   284,   289,   297,   302,   312,   316,   323,
     333,   343,   347,   353,   358,   365,   370,   380,   386,   395,
     402,   414,   418,   423,   431,   437,   448,   452,   458,   469,
     483,   487,   493,   498,   507,   512,   520,   524,   528,   532,
     538,   544,   553,   557,   564,   568,   576,   586,   594,   598,
     605,   609,   616,   620,   627,   632,   643,   649,   654,   670,
     677,   689,   695,   699,   705,   709,   715,   719,   737,   756,
     763,   767,   771,   777,   781,   788,   792,   798,   804,   812,
     816,   822,   830,   834,   840,   846,   852,   860,   864,   870,
     878,   882,   890,   894,   902,   909,   915,   921,   927,   935,
     941,   947,   953,   959,   965,   971,   977,   983,   988,   994,
    1000,  1006,  1012,  1020,  1028,  1034,  1040,  1046,  1052,  1058,
    1064,  1070,  1076,  1083,  1092,  1098,  1104,  1110,  1116,  1122
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "EQ", "NE", "LE", "GE",
  "AND", "OR", "INT", "FLOAT", "VOID", "IF", "ELSE", "WHILE", "RETURN",
  "BREAK", "CONTINUE", "FOR", "CONST", "IDENTIFIER", "FLOATVAL", "INTVAL",
  "';'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'('", "')'", "'{'",
  "'}'", "'['", "']'", "','", "'<'", "'>'", "'='", "$accept", "CompUnit",
  "Decl", "ConstDecl", "ConstDefList", "BType", "ConstDef",
  "ConstArrayDef", "ConstInitVal", "ConstInitValList", "VarDecl",
  "VarDefList", "VarDef", "ArrayDef", "InitVal", "InitValList", "FuncDef",
  "FuncFParams", "FuncFParam", "Block", "BlockItemList", "BlockItem",
  "Stmt", "Exp", "Cond", "LVal", "PrimaryExp", "Number", "UnaryExp",
  "UnaryOp", "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp",
  "LAndExp", "LOrExp", "ConstExp", "INT_WRAP", "FLOAT_WRAP", "VOID_WRAP",
  "IDENTIFIER_WRAP", "CONST_WRAP", "EQ_WRAP", "NE_WRAP", "LE_WRAP",
  "GE_WRAP", "AND_WRAP", "OR_WRAP", "IF_WRAP", "ELSE_WRAP", "WHILE_WRAP",
  "RETURN_WRAP", "BREAK_WRAP", "CONTINUE_WRAP", "INTVAL_WRAP",
  "FLOATVAL_WRAP", "plus_WRAP", "minus_WRAP", "mul_WRAP", "div_WRAP",
  "mod_WRAP", "not_WRAP", "left_paren_WRAP", "right_paren_WRAP",
  "left_brace_WRAP", "right_brace_WRAP", "left_bracket_WRAP",
  "right_bracket_WRAP", "comma_WRAP", "less_WRAP", "greater_WRAP",
  "assign_WRAP", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-147)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     273,  -147,  -147,  -147,  -147,  -147,   269,  -147,  -147,    11,
    -147,  -147,  -147,  -147,  -147,   200,  -147,  -147,  -147,  -147,
      26,  -147,    -2,    11,  -147,  -147,  -147,    11,  -147,  -147,
    -147,   -14,   127,   290,   265,    58,  -147,   -14,  -147,   -14,
     290,   265,  -147,    11,   152,  -147,     2,  -147,  -147,  -147,
    -147,  -147,    35,  -147,  -147,  -147,   290,   295,   125,    17,
      30,  -147,  -147,  -147,  -147,  -147,   290,  -147,  -147,  -147,
     125,   169,  -147,  -147,    11,   -14,   265,    38,  -147,    35,
       2,   200,  -147,   221,   290,  -147,  -147,  -147,  -147,   290,
     290,   290,   290,   290,    50,  -147,  -147,   278,    65,  -147,
    -147,  -147,    70,  -147,  -147,   265,  -147,  -147,   183,    50,
    -147,    35,   290,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,    11,  -147,   221,  -147,  -147,    21,   -14,    30,    30,
     199,    88,   156,  -147,    89,  -147,  -147,  -147,   295,   295,
    -147,  -147,   152,  -147,  -147,  -147,  -147,   265,  -147,  -147,
    -147,    86,  -147,  -147,   290,    90,  -147,  -147,  -147,  -147,
     290,   290,   290,  -147,  -147,   158,  -147,  -147,  -147,  -147,
      50,  -147,  -147,   290,  -147,  -147,  -147,   265,    96,    50,
    -147,   174,    65,   125,   149,   192,   105,   106,    65,  -147,
    -147,  -147,  -147,  -147,    50,  -147,  -147,  -147,  -147,   243,
    -147,  -147,  -147,  -147,   290,   290,   290,   290,  -147,  -147,
     290,   290,  -147,   290,  -147,   290,   243,  -147,   126,   125,
     125,   125,   125,   149,   149,   192,   105,  -147,  -147,   243,
    -147
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,   115,   116,   117,   119,     0,     3,     7,     0,
       8,     2,    13,    14,    15,     0,     1,     4,     5,   118,
       0,    31,    33,     0,    30,    29,   146,     0,   140,   144,
     149,    35,     0,     0,     0,     0,    11,     0,    32,    33,
       0,     0,   141,     0,     0,    50,     0,   133,   132,   134,
     135,   139,    82,    86,    83,    95,     0,    99,   114,     0,
      78,    84,    85,    90,    91,    92,     0,   142,    34,    41,
      76,     0,    10,     9,     0,     0,     0,     0,    36,    52,
       0,     0,    48,     0,     0,    89,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   145,    18,     0,     0,    43,
     143,    46,     0,    42,    12,     0,    17,    22,     0,     0,
      20,    53,     0,    49,    51,   126,   128,   129,   130,   131,
      58,     0,    64,     0,    56,    59,     0,    82,     0,     0,
       0,     0,     0,    54,     0,    96,    97,    98,   100,   101,
      19,    93,     0,    87,    81,    45,    44,     0,    16,    24,
      27,     0,    23,    21,     0,     0,    57,    55,    63,    62,
       0,     0,     0,    73,    72,     0,    69,    68,    71,    70,
       0,    79,    88,     0,    47,    26,    25,     0,     0,     0,
      37,     0,     0,   102,   107,   110,   112,    77,     0,    75,
      74,    80,    94,    28,     0,    39,    38,    61,    60,     0,
     122,   123,   147,   148,     0,     0,     0,     0,   120,   121,
       0,     0,   124,     0,   125,     0,     0,    40,    65,   105,
     106,   103,   104,   108,   109,   111,   113,    67,   127,     0,
      66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,    24,  -147,  -147,    -3,    69,   109,   -89,  -147,
    -147,  -147,   129,  -147,   -30,  -147,   154,  -147,    95,    52,
    -147,    83,  -146,   -20,    23,   -81,  -147,  -147,   -23,  -147,
    -147,   133,   -33,     7,   -21,    -1,  -147,    62,  -147,  -147,
    -147,    31,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,   -57,   -53,  -147,
    -147,  -147,  -147,   -13,   -41,   -26,   -47,    34,   -71,    -9,
    -147,  -147,   -27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,   120,     8,    35,     9,    36,    31,   106,   151,
      10,    20,    21,   111,    68,   102,    11,    44,    45,   122,
     123,   124,   125,   126,   182,    52,    53,    54,    55,    56,
     142,    57,    70,   184,   185,   186,   187,   107,    12,    13,
      14,    60,    15,   210,   211,   204,   205,   213,   215,   128,
     229,   129,   130,   131,   132,    61,    62,    63,    64,    89,
      90,    91,    65,    66,    46,    83,   103,    33,    96,    27,
     206,   207,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    92,   127,    80,    41,    93,   110,    58,    71,    32,
      76,    78,    23,    92,    69,    71,   148,    93,    94,   150,
      29,    69,   158,   140,     7,    30,    74,    24,    28,    43,
      17,    19,    29,    85,    67,    81,   133,    30,   153,   109,
      22,   101,   127,    58,   159,    71,    98,    97,   105,    25,
     108,    69,    95,   218,    37,   146,   143,   144,    39,    72,
      28,   152,    26,   171,   134,    40,   135,   136,   137,    29,
     227,   145,    58,    95,    79,    58,   157,   141,    43,   108,
     121,    73,   108,   230,   180,    95,    84,   175,   193,   166,
     170,   179,   155,   147,    26,    59,    42,   194,    82,   191,
     160,   172,    77,   100,   176,    37,    26,   195,   196,    40,
     165,   167,   212,   112,   214,   161,   162,   174,   127,   100,
     121,    71,    26,   217,    95,    95,    92,    69,   183,   183,
      93,    95,   113,   173,   178,   127,     2,     3,     4,   228,
     181,   199,   177,   104,    58,   154,    75,   216,   127,    49,
      50,   108,    39,   192,   200,   201,    38,   168,    42,   189,
      18,    84,    92,    92,    92,    92,    93,    93,    93,    93,
      99,   219,   220,   221,   222,   197,   114,   183,   183,   169,
     183,   190,   183,    42,   149,   188,   202,   203,    26,    19,
      47,    48,   225,    49,    50,   208,   209,   198,    51,    28,
     163,    67,   100,    19,    47,    48,   156,    49,    50,     2,
       3,     4,    51,    28,   226,    67,   100,   223,   224,    19,
      47,    48,   164,    49,    50,   138,   139,     0,    51,    28,
       2,     3,     4,   115,     0,   116,   117,   118,   119,     0,
       5,    19,    47,    48,     0,    49,    50,     0,     0,     0,
      51,    28,     0,    67,   100,   115,     0,   116,   117,   118,
     119,     0,     0,    19,    47,    48,     0,    49,    50,    16,
       0,     0,    51,    28,     1,    67,     0,     0,     2,     3,
       4,     0,     2,     3,     4,    19,    47,    48,     5,    49,
      50,     0,     5,     0,    51,    28,     0,    67,    19,    47,
      48,     0,    49,    50,     0,     0,     0,    51,    28,    42,
      19,    47,    48,     0,    49,    50,     0,     0,     0,    51,
      28,    86,    87,    88
};

static const yytype_int16 yycheck[] =
{
      33,    58,    83,    44,    31,    58,    77,    40,    34,    22,
      37,    41,    15,    70,    34,    41,   105,    70,     1,   108,
      34,    41,     1,    94,     0,    39,    35,     1,    30,    32,
       6,    20,    34,    56,    32,    44,    83,    39,   109,     1,
       9,    71,   123,    76,    23,    71,    66,    60,    75,    23,
      76,    71,    35,   199,    23,   102,    97,    98,    27,     1,
      30,   108,    36,   134,    84,    31,    89,    90,    91,    34,
     216,     1,   105,    35,    43,   108,   123,    97,    81,   105,
      83,    23,   108,   229,   155,    35,    52,     1,   177,     1,
       1,     1,   112,   102,    36,    33,    31,     1,    46,   170,
     127,   142,    40,    33,   151,    74,    36,   178,   179,    75,
     130,    23,     7,    79,     8,   128,   129,   147,   199,    33,
     123,   147,    36,   194,    35,    35,   183,   147,   161,   162,
     183,    35,    80,   142,   154,   216,     9,    10,    11,    13,
     160,   182,   151,    74,   177,   111,    37,   188,   229,    24,
      25,   177,   121,   173,     5,     6,    27,     1,    31,     1,
       6,   127,   219,   220,   221,   222,   219,   220,   221,   222,
       1,   204,   205,   206,   207,     1,    81,   210,   211,    23,
     213,    23,   215,    31,     1,   162,    37,    38,    36,    20,
      21,    22,   213,    24,    25,     3,     4,    23,    29,    30,
       1,    32,    33,    20,    21,    22,   123,    24,    25,     9,
      10,    11,    29,    30,   215,    32,    33,   210,   211,    20,
      21,    22,    23,    24,    25,    92,    93,    -1,    29,    30,
       9,    10,    11,    12,    -1,    14,    15,    16,    17,    -1,
      19,    20,    21,    22,    -1,    24,    25,    -1,    -1,    -1,
      29,    30,    -1,    32,    33,    12,    -1,    14,    15,    16,
      17,    -1,    -1,    20,    21,    22,    -1,    24,    25,     0,
      -1,    -1,    29,    30,     1,    32,    -1,    -1,     9,    10,
      11,    -1,     9,    10,    11,    20,    21,    22,    19,    24,
      25,    -1,    19,    -1,    29,    30,    -1,    32,    20,    21,
      22,    -1,    24,    25,    -1,    -1,    -1,    29,    30,    31,
      20,    21,    22,    -1,    24,    25,    -1,    -1,    -1,    29,
      30,    26,    27,    28
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     9,    10,    11,    19,    41,    42,    43,    45,
      50,    56,    78,    79,    80,    82,     0,    42,    56,    20,
      51,    52,    81,    45,     1,    23,    36,   109,    30,    34,
      39,    47,   103,   107,   112,    44,    46,    81,    52,    81,
     107,   112,    31,    45,    57,    58,   104,    21,    22,    24,
      25,    29,    65,    66,    67,    68,    69,    71,    72,    77,
      81,    95,    96,    97,    98,   102,   103,    32,    54,    63,
      72,   105,     1,    23,   109,    47,   112,    77,    54,    81,
     104,   109,    59,   105,   107,    68,    26,    27,    28,    99,
     100,   101,    97,    98,     1,    35,   108,   103,    63,     1,
      33,    54,    55,   106,    46,   112,    48,    77,   105,     1,
     108,    53,   107,    59,    58,    12,    14,    15,    16,    17,
      42,    45,    59,    60,    61,    62,    63,    65,    89,    91,
      92,    93,    94,   106,    63,    68,    68,    68,    71,    71,
     108,    63,    70,   104,   104,     1,   106,   109,    48,     1,
      48,    49,   106,   108,   107,    63,    61,   106,     1,    23,
     112,   103,   103,     1,    23,    63,     1,    23,     1,    23,
       1,   108,   104,   109,    54,     1,   106,   109,    63,     1,
     108,    63,    64,    72,    73,    74,    75,    76,    64,     1,
      23,   108,    63,    48,     1,   108,   108,     1,    23,   104,
       5,     6,    37,    38,    85,    86,   110,   111,     3,     4,
      83,    84,     7,    87,     8,    88,   104,   108,    62,    72,
      72,    72,    72,    73,    73,    74,    75,    62,    13,    90,
      62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    41,    41,    41,    41,    42,    42,    43,
      43,    44,    44,    45,    45,    45,    46,    46,    47,    47,
      47,    47,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    53,    53,    53,
      53,    54,    54,    54,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    64,    65,    65,
      65,    66,    66,    66,    67,    67,    68,    68,    68,    68,
      69,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    72,    73,    73,    73,    73,    73,    74,    74,    74,
      75,    75,    76,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     1,     4,
       4,     1,     3,     1,     1,     1,     4,     3,     3,     4,
       4,     5,     1,     2,     2,     3,     3,     1,     3,     3,
       3,     1,     3,     1,     3,     2,     4,     3,     4,     4,
       5,     1,     2,     2,     3,     3,     1,     3,     5,     6,
       1,     3,     2,     3,     2,     3,     1,     2,     1,     1,
       4,     4,     2,     2,     1,     5,     7,     5,     2,     2,
       2,     2,     2,     2,     3,     3,     1,     1,     1,     4,
       5,     3,     1,     1,     1,     1,     1,     3,     4,     2,
       1,     1,     1,     1,     3,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* CompUnit: FuncDef  */
#line 152 "parser.y"
            {
        root = new_node("CompUnit", (yyvsp[0].node)->lineno);
        add_child(root, (yyvsp[0].node));
    }
#line 1864 "y.tab.c"
    break;

  case 3: /* CompUnit: Decl  */
#line 156 "parser.y"
         {
        root = new_node("CompUnit", (yyvsp[0].node)->lineno);
        add_child(root, (yyvsp[0].node));
    }
#line 1873 "y.tab.c"
    break;

  case 4: /* CompUnit: CompUnit Decl  */
#line 160 "parser.y"
                  {
        add_child(root, (yyvsp[0].node));
    }
#line 1881 "y.tab.c"
    break;

  case 5: /* CompUnit: CompUnit FuncDef  */
#line 163 "parser.y"
                     {
        add_child(root, (yyvsp[0].node));
    }
#line 1889 "y.tab.c"
    break;

  case 6: /* CompUnit: error  */
#line 166 "parser.y"
          {
        root = new_node("ERROR", -1);
    }
#line 1897 "y.tab.c"
    break;

  case 7: /* Decl: ConstDecl  */
#line 172 "parser.y"
             {
        (yyval.node) = new_node("Decl", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1906 "y.tab.c"
    break;

  case 8: /* Decl: VarDecl  */
#line 176 "parser.y"
             {
        (yyval.node) = new_node("Decl", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1915 "y.tab.c"
    break;

  case 9: /* ConstDecl: CONST_WRAP BType ConstDefList ';'  */
#line 182 "parser.y"
                                     {
        (yyval.node) = new_node("ConstDecl", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        int btype=0;
        unsigned int offset=0;
        if (strcmp((yyvsp[-2].node)->childs[0]->name,"int")==0){btype=TYPE_INT;offset=4;}
        if (strcmp((yyvsp[-2].node)->childs[0]->name,"float")==0){btype=TYPE_FLOAT;offset=8;}
        traverse_and_add_ident((yyvsp[-1].node),btype,offset);
    }
#line 1931 "y.tab.c"
    break;

  case 10: /* ConstDecl: CONST_WRAP BType ConstDefList error  */
#line 193 "parser.y"
                                        {
        (yyval.node) = new_node("ConstDecl", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";", $3->lineno);
        yyerrok;
        yyclearin;
    }
#line 1945 "y.tab.c"
    break;

  case 11: /* ConstDefList: ConstDef  */
#line 205 "parser.y"
            {
        (yyval.node) = new_node("ConstDefList", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1954 "y.tab.c"
    break;

  case 12: /* ConstDefList: ConstDefList comma_WRAP ConstDef  */
#line 209 "parser.y"
                                     {
        add_child((yyvsp[-2].node), (yyvsp[-1].node));
        add_child((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1963 "y.tab.c"
    break;

  case 13: /* BType: INT_WRAP  */
#line 215 "parser.y"
            {
        (yyval.node) = new_node("BType", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1972 "y.tab.c"
    break;

  case 14: /* BType: FLOAT_WRAP  */
#line 219 "parser.y"
               {
        (yyval.node) = new_node("BType", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1981 "y.tab.c"
    break;

  case 15: /* BType: VOID_WRAP  */
#line 223 "parser.y"
              {
        (yyval.node) = new_node("BType", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1990 "y.tab.c"
    break;

  case 16: /* ConstDef: IDENTIFIER_WRAP ConstArrayDef assign_WRAP ConstInitVal  */
#line 229 "parser.y"
                                                          {
        (yyval.node) = new_node("ConstDef", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        check_not_duplicate((yyvsp[-3].node)->val.data.sval, TOP_TABLE,(yyvsp[-3].node)->lineno);
    }
#line 2003 "y.tab.c"
    break;

  case 17: /* ConstDef: IDENTIFIER_WRAP assign_WRAP ConstInitVal  */
#line 237 "parser.y"
                                              {
        (yyval.node) = new_node("ConstDef", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        check_not_duplicate((yyvsp[-2].node)->val.data.sval, TOP_TABLE,(yyvsp[-2].node)->lineno);
    }
#line 2015 "y.tab.c"
    break;

  case 18: /* ConstArrayDef: left_bracket_WRAP ConstExp right_bracket_WRAP  */
#line 246 "parser.y"
                                                 {
        (yyval.node) = new_node("ConstArrayDef", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2026 "y.tab.c"
    break;

  case 19: /* ConstArrayDef: left_bracket_WRAP ConstExp error right_bracket_WRAP  */
#line 252 "parser.y"
                                                        {
        (yyval.node) = new_node("ConstArrayDef", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        //missing_symbol("]", $2->lineno);
        yyerrok;
        struct node* n=new_node("]", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2040 "y.tab.c"
    break;

  case 20: /* ConstArrayDef: ConstArrayDef left_bracket_WRAP ConstExp right_bracket_WRAP  */
#line 261 "parser.y"
                                                                {
        (yyval.node) = new_node("ConstArrayDef", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2052 "y.tab.c"
    break;

  case 21: /* ConstArrayDef: ConstArrayDef left_bracket_WRAP ConstExp error right_bracket_WRAP  */
#line 268 "parser.y"
                                                                      {
        (yyval.node) = new_node("ConstArrayDef", (yyvsp[-4].node)->lineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        //missing_symbol("]", $3->lineno);
        yyerrok;
        struct node* n=new_node("]", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2067 "y.tab.c"
    break;

  case 22: /* ConstInitVal: ConstExp  */
#line 280 "parser.y"
            {
        (yyval.node) = new_node("ConstInitVal", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2076 "y.tab.c"
    break;

  case 23: /* ConstInitVal: left_brace_WRAP right_brace_WRAP  */
#line 284 "parser.y"
                                     {
        (yyval.node) = new_node("ConstInitVal", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2086 "y.tab.c"
    break;

  case 24: /* ConstInitVal: left_brace_WRAP error  */
#line 289 "parser.y"
                          {
        (yyval.node) = new_node("ConstInitVal", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol("}", $1->lineno);
        yyerrok;
        struct node* n=new_node("}", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2099 "y.tab.c"
    break;

  case 25: /* ConstInitVal: left_brace_WRAP ConstInitValList right_brace_WRAP  */
#line 297 "parser.y"
                                                       {
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2109 "y.tab.c"
    break;

  case 26: /* ConstInitVal: left_brace_WRAP ConstInitValList error  */
#line 302 "parser.y"
                                           {
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol("}", $2->lineno);
        yyerrok;
        struct node* n=new_node("}", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2122 "y.tab.c"
    break;

  case 27: /* ConstInitValList: ConstInitVal  */
#line 312 "parser.y"
                {
        (yyval.node) = new_node("ConstInitValList", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2131 "y.tab.c"
    break;

  case 28: /* ConstInitValList: ConstInitValList comma_WRAP ConstInitVal  */
#line 316 "parser.y"
                                             {
        add_child((yyvsp[-2].node), (yyvsp[-1].node));
        add_child((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2140 "y.tab.c"
    break;

  case 29: /* VarDecl: BType VarDefList ';'  */
#line 323 "parser.y"
                        {
        (yyval.node) = new_node("VarDecl", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        int btype=0;
        unsigned int offset=0;
        if (strcmp((yyvsp[-2].node)->childs[0]->name,"int")==0){btype=TYPE_INT;offset=4;}
        if (strcmp((yyvsp[-2].node)->childs[0]->name,"float")==0){btype=TYPE_FLOAT;offset=8;}
        traverse_and_add_ident((yyvsp[-1].node),btype,offset);
    }
#line 2155 "y.tab.c"
    break;

  case 30: /* VarDecl: BType VarDefList error  */
#line 333 "parser.y"
                           {
        (yyval.node) = new_node("VarDecl", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";", $2->lineno);
        yyerrok;
        yyclearin;
    }
#line 2168 "y.tab.c"
    break;

  case 31: /* VarDefList: VarDef  */
#line 343 "parser.y"
          {
        (yyval.node) = new_node("VarDefList", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2177 "y.tab.c"
    break;

  case 32: /* VarDefList: VarDefList comma_WRAP VarDef  */
#line 347 "parser.y"
                                 {
        add_child((yyvsp[-2].node), (yyvsp[-1].node));
        add_child((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2186 "y.tab.c"
    break;

  case 33: /* VarDef: IDENTIFIER_WRAP  */
#line 353 "parser.y"
                   {
        (yyval.node) = new_node("VarDef", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
        check_not_duplicate((yyvsp[0].node)->val.data.sval, TOP_TABLE,(yyvsp[0].node)->lineno);
    }
#line 2196 "y.tab.c"
    break;

  case 34: /* VarDef: IDENTIFIER_WRAP assign_WRAP InitVal  */
#line 358 "parser.y"
                                        {
        (yyval.node) = new_node("VarDef", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        check_not_duplicate((yyvsp[-2].node)->val.data.sval, TOP_TABLE,(yyvsp[-2].node)->lineno);
    }
#line 2208 "y.tab.c"
    break;

  case 35: /* VarDef: IDENTIFIER_WRAP ConstArrayDef  */
#line 365 "parser.y"
                                  {
        (yyval.node) = new_node("VarDef", (yyvsp[-1].node)->lineno);
        add_child((yyval.node),(yyvsp[-1].node));
        check_not_duplicate((yyvsp[-1].node)->val.data.sval, TOP_TABLE,(yyvsp[-1].node)->lineno);
    }
#line 2218 "y.tab.c"
    break;

  case 36: /* VarDef: IDENTIFIER_WRAP ConstArrayDef assign_WRAP InitVal  */
#line 370 "parser.y"
                                                      {
        (yyval.node) = new_node("VarDef", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        check_not_duplicate((yyvsp[-3].node)->val.data.sval, TOP_TABLE,(yyvsp[-3].node)->lineno);
    }
#line 2231 "y.tab.c"
    break;

  case 37: /* ArrayDef: left_bracket_WRAP Exp right_bracket_WRAP  */
#line 380 "parser.y"
                                            {
        (yyval.node) = new_node("ArrayDef", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2242 "y.tab.c"
    break;

  case 38: /* ArrayDef: left_bracket_WRAP Exp error right_bracket_WRAP  */
#line 386 "parser.y"
                                                   {
        (yyval.node) = new_node("ArrayDef", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        //missing_symbol("]", $2->lineno);
        yyerrok;
        struct node* n=new_node("]", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2256 "y.tab.c"
    break;

  case 39: /* ArrayDef: ArrayDef left_bracket_WRAP Exp right_bracket_WRAP  */
#line 395 "parser.y"
                                                      {
        (yyval.node) = new_node("ArrayDef", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2268 "y.tab.c"
    break;

  case 40: /* ArrayDef: ArrayDef left_bracket_WRAP Exp error right_bracket_WRAP  */
#line 402 "parser.y"
                                                            {
        (yyval.node) = new_node("ArrayDef", (yyvsp[-4].node)->lineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        //missing_symbol("]", $3->lineno);
        yyerrok;
        struct node* n=new_node("]", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2283 "y.tab.c"
    break;

  case 41: /* InitVal: Exp  */
#line 414 "parser.y"
       {
        (yyval.node) = new_node("InitVal", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2292 "y.tab.c"
    break;

  case 42: /* InitVal: left_brace_WRAP right_brace_WRAP  */
#line 418 "parser.y"
                                     {
        (yyval.node) = new_node("InitVal", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2302 "y.tab.c"
    break;

  case 43: /* InitVal: left_brace_WRAP error  */
#line 423 "parser.y"
                          {
        (yyval.node) = new_node("InitVal", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol("}", $1->lineno);
        yyerrok;
        struct node* n=new_node("}", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2315 "y.tab.c"
    break;

  case 44: /* InitVal: left_brace_WRAP InitValList right_brace_WRAP  */
#line 431 "parser.y"
                                                  {
        (yyval.node) = new_node("InitVal", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2326 "y.tab.c"
    break;

  case 45: /* InitVal: left_brace_WRAP InitValList error  */
#line 437 "parser.y"
                                       {
        (yyval.node) = new_node("InitVal", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol("}",$2->lineno);
        yyerrok;
        struct node* n=new_node("}", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2340 "y.tab.c"
    break;

  case 46: /* InitValList: InitVal  */
#line 448 "parser.y"
           {
        (yyval.node) = new_node("InitValList", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2349 "y.tab.c"
    break;

  case 47: /* InitValList: InitValList comma_WRAP InitVal  */
#line 452 "parser.y"
                                   {
        add_child((yyvsp[-2].node), (yyvsp[-1].node));
        add_child((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2358 "y.tab.c"
    break;

  case 48: /* FuncDef: BType IDENTIFIER_WRAP left_paren_WRAP right_paren_WRAP Block  */
#line 458 "parser.y"
                                                                {
        (yyval.node) = new_node("FuncDef", (yyvsp[-4].node)->lineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        if(0==check_not_duplicate((yyvsp[-3].node)->val.data.sval, TOP_TABLE,(yyvsp[-3].node)->lineno)){
            strcpy(TOP_TABLE->elem[TOP_TABLE->total_elems-1].name, (yyvsp[-3].node)->val.data.sval);
        }
    }
#line 2374 "y.tab.c"
    break;

  case 49: /* FuncDef: BType IDENTIFIER_WRAP left_paren_WRAP FuncFParams right_paren_WRAP Block  */
#line 469 "parser.y"
                                                                             {
        (yyval.node) = new_node("FuncDef", (yyvsp[-5].node)->lineno);
        add_child((yyval.node), (yyvsp[-5].node));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        if(0==check_not_duplicate((yyvsp[-4].node)->val.data.sval, TOP_TABLE, (yyvsp[-4].node)->lineno)){
            strcpy(TOP_TABLE->elem[TOP_TABLE->total_elems-1].name, (yyvsp[-4].node)->val.data.sval);
        }
    }
#line 2391 "y.tab.c"
    break;

  case 50: /* FuncFParams: FuncFParam  */
#line 483 "parser.y"
              {
        (yyval.node) = new_node("FuncFParams", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2400 "y.tab.c"
    break;

  case 51: /* FuncFParams: FuncFParams comma_WRAP FuncFParam  */
#line 487 "parser.y"
                                      {
        add_child((yyvsp[-2].node), (yyvsp[-1].node));
        add_child((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2409 "y.tab.c"
    break;

  case 52: /* FuncFParam: BType IDENTIFIER_WRAP  */
#line 493 "parser.y"
                         {
        (yyval.node) = new_node("FuncFParam", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2419 "y.tab.c"
    break;

  case 53: /* FuncFParam: BType IDENTIFIER_WRAP ArrayDef  */
#line 498 "parser.y"
                                   {
        (yyval.node) = new_node("FuncFParam", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2430 "y.tab.c"
    break;

  case 54: /* Block: left_brace_WRAP right_brace_WRAP  */
#line 507 "parser.y"
                                     {
        (yyval.node) = new_node("Block", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2440 "y.tab.c"
    break;

  case 55: /* Block: left_brace_WRAP BlockItemList right_brace_WRAP  */
#line 512 "parser.y"
                                                    {
        (yyval.node) = new_node("Block", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2451 "y.tab.c"
    break;

  case 56: /* BlockItemList: BlockItem  */
#line 520 "parser.y"
             {
        (yyval.node) = new_node("BlockItemList", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2460 "y.tab.c"
    break;

  case 57: /* BlockItemList: BlockItemList BlockItem  */
#line 524 "parser.y"
                            {
        add_child((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 2468 "y.tab.c"
    break;

  case 58: /* BlockItem: Decl  */
#line 528 "parser.y"
        {
        (yyval.node) = new_node("BlockItem", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2477 "y.tab.c"
    break;

  case 59: /* BlockItem: Stmt  */
#line 532 "parser.y"
         {
        (yyval.node) = new_node("BlockItem", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2486 "y.tab.c"
    break;

  case 60: /* Stmt: LVal assign_WRAP Exp ';'  */
#line 538 "parser.y"
                            {
        (yyval.node) = new_node("Stmt", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2497 "y.tab.c"
    break;

  case 61: /* Stmt: LVal assign_WRAP Exp error  */
#line 544 "parser.y"
                               {
        (yyval.node) = new_node("Stmt", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";",$3->lineno);
        yyerrok;
        yyclearin;
    }
#line 2511 "y.tab.c"
    break;

  case 62: /* Stmt: Exp ';'  */
#line 553 "parser.y"
            {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2520 "y.tab.c"
    break;

  case 63: /* Stmt: Exp error  */
#line 557 "parser.y"
              {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";", $1->lineno);
        yyerrok;
        yyclearin;
    }
#line 2532 "y.tab.c"
    break;

  case 64: /* Stmt: Block  */
#line 564 "parser.y"
          {
        (yyval.node) = new_node("Stmt", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2541 "y.tab.c"
    break;

  case 65: /* Stmt: IF_WRAP left_paren_WRAP Cond right_paren_WRAP Stmt  */
#line 568 "parser.y"
                                                       {
        (yyval.node) = new_node("Stmt", (yyvsp[-4].node)->lineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2554 "y.tab.c"
    break;

  case 66: /* Stmt: IF_WRAP left_paren_WRAP Cond right_paren_WRAP Stmt ELSE_WRAP Stmt  */
#line 576 "parser.y"
                                                                      {
        (yyval.node) = new_node("Stmt", (yyvsp[-6].node)->lineno);
        add_child((yyval.node), (yyvsp[-6].node));
        add_child((yyval.node), (yyvsp[-5].node));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2569 "y.tab.c"
    break;

  case 67: /* Stmt: WHILE_WRAP left_paren_WRAP Cond right_paren_WRAP Stmt  */
#line 586 "parser.y"
                                                          {
        (yyval.node) = new_node("Stmt", (yyvsp[-4].node)->lineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2582 "y.tab.c"
    break;

  case 68: /* Stmt: BREAK_WRAP ';'  */
#line 594 "parser.y"
                   {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2591 "y.tab.c"
    break;

  case 69: /* Stmt: BREAK_WRAP error  */
#line 598 "parser.y"
                     {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";",$1->lineno);
        yyerrok;
        yyclearin;
    }
#line 2603 "y.tab.c"
    break;

  case 70: /* Stmt: CONTINUE_WRAP ';'  */
#line 605 "parser.y"
                      {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2612 "y.tab.c"
    break;

  case 71: /* Stmt: CONTINUE_WRAP error  */
#line 609 "parser.y"
                        {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";", $1->lineno);
        yyerrok;
        yyclearin;
    }
#line 2624 "y.tab.c"
    break;

  case 72: /* Stmt: RETURN_WRAP ';'  */
#line 616 "parser.y"
                    {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2633 "y.tab.c"
    break;

  case 73: /* Stmt: RETURN_WRAP error  */
#line 620 "parser.y"
                      {
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";", $1->lineno);
        yyerrok;
        yyclearin;
    }
#line 2645 "y.tab.c"
    break;

  case 74: /* Stmt: RETURN_WRAP Exp ';'  */
#line 627 "parser.y"
                        {
        (yyval.node) = new_node("Stmt", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2655 "y.tab.c"
    break;

  case 75: /* Stmt: RETURN_WRAP Exp error  */
#line 632 "parser.y"
                          {
        (yyval.node) = new_node("Stmt", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        //missing_symbol(";", $2->lineno);
        yyerrok;
        yyclearin;
    }
#line 2668 "y.tab.c"
    break;

  case 76: /* Exp: AddExp  */
#line 643 "parser.y"
          {
        (yyval.node) = new_node("Exp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2677 "y.tab.c"
    break;

  case 77: /* Cond: LOrExp  */
#line 649 "parser.y"
          {
        (yyval.node) = new_node("Cond", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2686 "y.tab.c"
    break;

  case 78: /* LVal: IDENTIFIER_WRAP  */
#line 654 "parser.y"
                   {
        (yyval.node) = new_node("LVal", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
        struct sym_elem *e=sym_lookup(TOP_TABLE,(yyvsp[0].node)->val.data.sval);
        memset(msg_buf,0,sizeof(msg_buf));
        if(!e){
            error_flag=1;
            sprintf(msg_buf,"undefined variable \"%s\"",(yyvsp[0].node)->val.data.sval);
            printf(LOGGING_FORMAT, "1", msg_buf, (yyvsp[0].node)->lineno);
        }
        else if(e->ptr){
            error_flag=1;
            sprintf(msg_buf,"Improper reference to function name \"%s\"",(yyvsp[0].node)->val.data.sval);
            printf(LOGGING_FORMAT, "6", msg_buf, (yyvsp[0].node)->lineno);
        }
    }
#line 2707 "y.tab.c"
    break;

  case 79: /* LVal: LVal left_bracket_WRAP Exp right_bracket_WRAP  */
#line 670 "parser.y"
                                                  {
        (yyval.node) = new_node("LVal", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2719 "y.tab.c"
    break;

  case 80: /* LVal: LVal left_bracket_WRAP Exp error right_bracket_WRAP  */
#line 677 "parser.y"
                                                        {
        (yyval.node) = new_node("LVal", (yyvsp[-4].node)->lineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        //missing_symbol("]",$3->lineno);
        yyerrok;
        struct node* n=new_node("]", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), n);
    }
#line 2734 "y.tab.c"
    break;

  case 81: /* PrimaryExp: left_paren_WRAP Exp right_paren_WRAP  */
#line 689 "parser.y"
                                        {
        (yyval.node) = new_node("PrimaryExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2745 "y.tab.c"
    break;

  case 82: /* PrimaryExp: LVal  */
#line 695 "parser.y"
         {
        (yyval.node) = new_node("PrimaryExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2754 "y.tab.c"
    break;

  case 83: /* PrimaryExp: Number  */
#line 699 "parser.y"
           {
        (yyval.node) = new_node("PrimaryExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2763 "y.tab.c"
    break;

  case 84: /* Number: INTVAL_WRAP  */
#line 705 "parser.y"
               {
        (yyval.node) = new_node("Number", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2772 "y.tab.c"
    break;

  case 85: /* Number: FLOATVAL_WRAP  */
#line 709 "parser.y"
                  {
        (yyval.node) = new_node("Number", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2781 "y.tab.c"
    break;

  case 86: /* UnaryExp: PrimaryExp  */
#line 715 "parser.y"
              {
        (yyval.node) = new_node("UnaryExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2790 "y.tab.c"
    break;

  case 87: /* UnaryExp: IDENTIFIER_WRAP left_paren_WRAP right_paren_WRAP  */
#line 719 "parser.y"
                                                      {
        (yyval.node) = new_node("UnaryExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        struct sym_elem *e=sym_lookup(TOP_TABLE,(yyvsp[-2].node)->val.data.sval);
        memset(msg_buf,0,sizeof(msg_buf));
        if(!e){
            error_flag=1;
            sprintf(msg_buf,"undefined function \"%s\"",(yyvsp[-2].node)->val.data.sval);
            printf(LOGGING_FORMAT, "3", msg_buf, (yyvsp[-2].node)->lineno);
        }
        else if(0!=e->type){
            error_flag=1;
            sprintf(msg_buf,"Improper reference to variable name \"%s\"",(yyvsp[-2].node)->val.data.sval);
            printf(LOGGING_FORMAT, "5", msg_buf, (yyvsp[-2].node)->lineno);
        }
    }
#line 2813 "y.tab.c"
    break;

  case 88: /* UnaryExp: IDENTIFIER_WRAP left_paren_WRAP FuncRParams right_paren_WRAP  */
#line 737 "parser.y"
                                                                  {
        (yyval.node) = new_node("UnaryExp", (yyvsp[-3].node)->lineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
        struct sym_elem *e=sym_lookup(TOP_TABLE,(yyvsp[-3].node)->val.data.sval);
        memset(msg_buf,0,sizeof(msg_buf));
        if(!e){
            error_flag=1;
            sprintf(msg_buf,"undefined function \"%s\"",(yyvsp[-3].node)->val.data.sval);
            printf(LOGGING_FORMAT, "3", msg_buf, (yyvsp[-3].node)->lineno);
        }
        else if(0!=e->type){
            error_flag=1;
            sprintf(msg_buf,"Improper reference to variable name \"%s\"",(yyvsp[-3].node)->val.data.sval);
            printf(LOGGING_FORMAT, "5", msg_buf, (yyvsp[-3].node)->lineno);
        }
    }
#line 2837 "y.tab.c"
    break;

  case 89: /* UnaryExp: UnaryOp UnaryExp  */
#line 756 "parser.y"
                      {
        (yyval.node) = new_node("UnaryExp", (yyvsp[-1].node)->lineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2847 "y.tab.c"
    break;

  case 90: /* UnaryOp: plus_WRAP  */
#line 763 "parser.y"
             {
        (yyval.node) = new_node("UnaryOp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2856 "y.tab.c"
    break;

  case 91: /* UnaryOp: minus_WRAP  */
#line 767 "parser.y"
               {
        (yyval.node) = new_node("UnaryOp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2865 "y.tab.c"
    break;

  case 92: /* UnaryOp: not_WRAP  */
#line 771 "parser.y"
             {
        (yyval.node) = new_node("UnaryOp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2874 "y.tab.c"
    break;

  case 93: /* FuncRParams: Exp  */
#line 777 "parser.y"
       {
        (yyval.node) = new_node("FuncRParams", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2883 "y.tab.c"
    break;

  case 94: /* FuncRParams: FuncRParams comma_WRAP Exp  */
#line 781 "parser.y"
                               {
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2893 "y.tab.c"
    break;

  case 95: /* MulExp: UnaryExp  */
#line 788 "parser.y"
            {
        (yyval.node) = new_node("MulExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2902 "y.tab.c"
    break;

  case 96: /* MulExp: MulExp mul_WRAP UnaryExp  */
#line 792 "parser.y"
                             {
        (yyval.node) = new_node("MulExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2913 "y.tab.c"
    break;

  case 97: /* MulExp: MulExp div_WRAP UnaryExp  */
#line 798 "parser.y"
                             {
        (yyval.node) = new_node("MulExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2924 "y.tab.c"
    break;

  case 98: /* MulExp: MulExp mod_WRAP UnaryExp  */
#line 804 "parser.y"
                             {
        (yyval.node) = new_node("MulExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2935 "y.tab.c"
    break;

  case 99: /* AddExp: MulExp  */
#line 812 "parser.y"
          {
        (yyval.node) = new_node("AddExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2944 "y.tab.c"
    break;

  case 100: /* AddExp: AddExp plus_WRAP MulExp  */
#line 816 "parser.y"
                            {
        (yyval.node) = new_node("AddExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2955 "y.tab.c"
    break;

  case 101: /* AddExp: AddExp minus_WRAP MulExp  */
#line 822 "parser.y"
                             {
        (yyval.node) = new_node("AddExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2966 "y.tab.c"
    break;

  case 102: /* RelExp: AddExp  */
#line 830 "parser.y"
          {
        (yyval.node) = new_node("RelExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2975 "y.tab.c"
    break;

  case 103: /* RelExp: RelExp less_WRAP AddExp  */
#line 834 "parser.y"
                            {
        (yyval.node) = new_node("RelExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2986 "y.tab.c"
    break;

  case 104: /* RelExp: RelExp greater_WRAP AddExp  */
#line 840 "parser.y"
                               {
        (yyval.node) = new_node("RelExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2997 "y.tab.c"
    break;

  case 105: /* RelExp: RelExp LE_WRAP AddExp  */
#line 846 "parser.y"
                          {
        (yyval.node) = new_node("RelExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3008 "y.tab.c"
    break;

  case 106: /* RelExp: RelExp GE_WRAP AddExp  */
#line 852 "parser.y"
                          {
        (yyval.node) = new_node("RelExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3019 "y.tab.c"
    break;

  case 107: /* EqExp: RelExp  */
#line 860 "parser.y"
          {
        (yyval.node) = new_node("EqExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3028 "y.tab.c"
    break;

  case 108: /* EqExp: EqExp EQ_WRAP RelExp  */
#line 864 "parser.y"
                         {
        (yyval.node) = new_node("EqExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3039 "y.tab.c"
    break;

  case 109: /* EqExp: EqExp NE_WRAP RelExp  */
#line 870 "parser.y"
                         {
        (yyval.node) = new_node("EqExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3050 "y.tab.c"
    break;

  case 110: /* LAndExp: EqExp  */
#line 878 "parser.y"
         {
        (yyval.node) = new_node("LAndExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3059 "y.tab.c"
    break;

  case 111: /* LAndExp: LAndExp AND_WRAP EqExp  */
#line 882 "parser.y"
                           {
        (yyval.node) = new_node("LAndExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3070 "y.tab.c"
    break;

  case 112: /* LOrExp: LAndExp  */
#line 890 "parser.y"
           {
        (yyval.node) = new_node("LOrExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3079 "y.tab.c"
    break;

  case 113: /* LOrExp: LOrExp OR_WRAP LAndExp  */
#line 894 "parser.y"
                           {
        (yyval.node) = new_node("LOrExp", (yyvsp[-2].node)->lineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3090 "y.tab.c"
    break;

  case 114: /* ConstExp: AddExp  */
#line 902 "parser.y"
          {
        (yyval.node) = new_node("ConstExp", (yyvsp[0].node)->lineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 3099 "y.tab.c"
    break;

  case 115: /* INT_WRAP: INT  */
#line 909 "parser.y"
       {
        (yyval.node) = new_node("int", yylineno);
    }
#line 3107 "y.tab.c"
    break;

  case 116: /* FLOAT_WRAP: FLOAT  */
#line 915 "parser.y"
         {
        (yyval.node) = new_node("float", yylineno);
    }
#line 3115 "y.tab.c"
    break;

  case 117: /* VOID_WRAP: VOID  */
#line 921 "parser.y"
        {
        (yyval.node) = new_node("void", yylineno);
    }
#line 3123 "y.tab.c"
    break;

  case 118: /* IDENTIFIER_WRAP: IDENTIFIER  */
#line 927 "parser.y"
              {
        (yyval.node) = new_node("id", yylineno);
        (yyval.node)->val.type = TYPE_STRING;
        (yyval.node)->val.data.sval = (yyvsp[0].str);
    }
#line 3133 "y.tab.c"
    break;

  case 119: /* CONST_WRAP: CONST  */
#line 935 "parser.y"
         {
        (yyval.node) = new_node("const", yylineno);
    }
#line 3141 "y.tab.c"
    break;

  case 120: /* EQ_WRAP: EQ  */
#line 941 "parser.y"
      {
        (yyval.node) = new_node("==", yylineno);
    }
#line 3149 "y.tab.c"
    break;

  case 121: /* NE_WRAP: NE  */
#line 947 "parser.y"
      {
        (yyval.node) = new_node("!=", yylineno);
    }
#line 3157 "y.tab.c"
    break;

  case 122: /* LE_WRAP: LE  */
#line 953 "parser.y"
      {
        (yyval.node) = new_node("<=", yylineno);
    }
#line 3165 "y.tab.c"
    break;

  case 123: /* GE_WRAP: GE  */
#line 959 "parser.y"
      {
        (yyval.node) = new_node(">=", yylineno);
    }
#line 3173 "y.tab.c"
    break;

  case 124: /* AND_WRAP: AND  */
#line 965 "parser.y"
       {
        (yyval.node) = new_node("&&", yylineno);
    }
#line 3181 "y.tab.c"
    break;

  case 125: /* OR_WRAP: OR  */
#line 971 "parser.y"
      {
        (yyval.node) = new_node("||", yylineno);
    }
#line 3189 "y.tab.c"
    break;

  case 126: /* IF_WRAP: IF  */
#line 977 "parser.y"
      {
        (yyval.node) = new_node("if", yylineno);
    }
#line 3197 "y.tab.c"
    break;

  case 127: /* ELSE_WRAP: ELSE  */
#line 983 "parser.y"
        {
        (yyval.node) = new_node("else", yylineno);
    }
#line 3205 "y.tab.c"
    break;

  case 128: /* WHILE_WRAP: WHILE  */
#line 988 "parser.y"
         {
        (yyval.node) = new_node("while", yylineno);
    }
#line 3213 "y.tab.c"
    break;

  case 129: /* RETURN_WRAP: RETURN  */
#line 994 "parser.y"
          {
        (yyval.node) = new_node("return", yylineno);
    }
#line 3221 "y.tab.c"
    break;

  case 130: /* BREAK_WRAP: BREAK  */
#line 1000 "parser.y"
         {
        (yyval.node) = new_node("break", yylineno);
    }
#line 3229 "y.tab.c"
    break;

  case 131: /* CONTINUE_WRAP: CONTINUE  */
#line 1006 "parser.y"
            {
        (yyval.node) = new_node("continue", yylineno);
    }
#line 3237 "y.tab.c"
    break;

  case 132: /* INTVAL_WRAP: INTVAL  */
#line 1012 "parser.y"
          {
        (yyval.node) = new_node("int", yylineno);
        (yyval.node)->val.type = TYPE_INT;
        (yyval.node)->val.data.ival = (yyvsp[0].ival);
    }
#line 3247 "y.tab.c"
    break;

  case 133: /* FLOATVAL_WRAP: FLOATVAL  */
#line 1020 "parser.y"
            {
        (yyval.node) = new_node("float", yylineno);
        (yyval.node)->val.type = TYPE_FLOAT;
        (yyval.node)->val.data.fval = (yyvsp[0].dval);
    }
#line 3257 "y.tab.c"
    break;

  case 134: /* plus_WRAP: '+'  */
#line 1028 "parser.y"
       {
        (yyval.node) = new_node("+", yylineno);
    }
#line 3265 "y.tab.c"
    break;

  case 135: /* minus_WRAP: '-'  */
#line 1034 "parser.y"
       {
        (yyval.node) = new_node("-", yylineno);
    }
#line 3273 "y.tab.c"
    break;

  case 136: /* mul_WRAP: '*'  */
#line 1040 "parser.y"
       {
        (yyval.node) = new_node("*", yylineno);
    }
#line 3281 "y.tab.c"
    break;

  case 137: /* div_WRAP: '/'  */
#line 1046 "parser.y"
       {
        (yyval.node) = new_node("/", yylineno);
    }
#line 3289 "y.tab.c"
    break;

  case 138: /* mod_WRAP: '%'  */
#line 1052 "parser.y"
       {
        (yyval.node) = new_node("%", yylineno);
    }
#line 3297 "y.tab.c"
    break;

  case 139: /* not_WRAP: '!'  */
#line 1058 "parser.y"
       {
        (yyval.node) = new_node("!", yylineno);
    }
#line 3305 "y.tab.c"
    break;

  case 140: /* left_paren_WRAP: '('  */
#line 1064 "parser.y"
       {
        (yyval.node) = new_node("(", yylineno);
    }
#line 3313 "y.tab.c"
    break;

  case 141: /* right_paren_WRAP: ')'  */
#line 1070 "parser.y"
       {
        (yyval.node) = new_node(")", yylineno);
    }
#line 3321 "y.tab.c"
    break;

  case 142: /* left_brace_WRAP: '{'  */
#line 1076 "parser.y"
       {
        (yyval.node) = new_node("{", yylineno);
        global_table[total_tables++] = sym_mktable(TOP_TABLE);
    }
#line 3330 "y.tab.c"
    break;

  case 143: /* right_brace_WRAP: '}'  */
#line 1083 "parser.y"
       {
        (yyval.node) = new_node("}", yylineno);
        sprintf(name_buf,"%u",unque_name++);
        sym_enter_proc(PARENT_TABLE,name_buf,TOP_TABLE);
        total_tables--;
    }
#line 3341 "y.tab.c"
    break;

  case 144: /* left_bracket_WRAP: '['  */
#line 1092 "parser.y"
       {
        (yyval.node) = new_node("[", yylineno);
    }
#line 3349 "y.tab.c"
    break;

  case 145: /* right_bracket_WRAP: ']'  */
#line 1098 "parser.y"
       {
        (yyval.node) = new_node("]", yylineno);
    }
#line 3357 "y.tab.c"
    break;

  case 146: /* comma_WRAP: ','  */
#line 1104 "parser.y"
       {
        (yyval.node) = new_node(",", yylineno);
    }
#line 3365 "y.tab.c"
    break;

  case 147: /* less_WRAP: '<'  */
#line 1110 "parser.y"
       {
        (yyval.node) = new_node("<", yylineno);
    }
#line 3373 "y.tab.c"
    break;

  case 148: /* greater_WRAP: '>'  */
#line 1116 "parser.y"
       {
        (yyval.node) = new_node(">", yylineno);
    }
#line 3381 "y.tab.c"
    break;

  case 149: /* assign_WRAP: '='  */
#line 1122 "parser.y"
       {
        (yyval.node) = new_node("=", yylineno);
    }
#line 3389 "y.tab.c"
    break;


#line 3393 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1129 "parser.y"


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
